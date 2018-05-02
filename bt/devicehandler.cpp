#include "devicehandler.h"
#include "deviceinfo.h"
#include <QElapsedTimer>
#include <QtEndian>

DeviceHandler::DeviceHandler(QObject* parent)
    : BluetoothBaseClass(parent)
    , m_control(nullptr)
    , m_service(nullptr)
    , m_currentDevice(nullptr)
    , m_foundService(false)
    , m_training(false)
    , m_characteristic_uuid(
          "{0000FFE1-0000-1000-8000-00805F9B34FB}")
    , m_service_uuid(
          "{0000FFE0-0000-1000-8000-00805F9B34FB}")
{
}

void DeviceHandler::setAddressType(AddressType type)
{
    switch (type) {
    case DeviceHandler::AddressType::PublicAddress:
        m_addressType = QLowEnergyController::PublicAddress;
        break;
    case DeviceHandler::AddressType::RandomAddress:
        m_addressType = QLowEnergyController::RandomAddress;
        break;
    }
}

DeviceHandler::AddressType DeviceHandler::addressType() const
{
    if (m_addressType == QLowEnergyController::RandomAddress)
        return DeviceHandler::AddressType::RandomAddress;
    return DeviceHandler::AddressType::PublicAddress;
}

void DeviceHandler::setDevice(DeviceInfo* device)
{
    clearMessages();
    m_currentDevice = device;
    // Отключить и удалить старое соединение
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }
    // Создайте новый контроллер и подключение его, если доступно устройство.
    if (m_currentDevice) {

        // Выполнение соединения
        m_control = new QLowEnergyController(m_currentDevice->getDevice(), this);
        m_control->setRemoteAddressType(m_addressType);
        connect(m_control, &QLowEnergyController::serviceDiscovered, this, &DeviceHandler::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished, this, &DeviceHandler::serviceScanDone);

        connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, [this](QLowEnergyController::Error error) {
                Q_UNUSED(error);
                setError("Не удается подключиться к удаленному устройству.");
            });
        connect(m_control, &QLowEnergyController::connected, this, [this]() {
            setInfo("Контроллер подключен. Поиск услуг...");
            m_control->discoverServices();
        });
        connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
            setError("Контроллер BLE отключен");
        });

        // Соединиться
        m_control->connectToDevice();
    }
}

void DeviceHandler::startTraining()
{
    if (alive()) {
        m_start = QDateTime::currentDateTime();
        m_training = true;
        m_measurements.clear();
        emit trainingChanged();
    }
}

void DeviceHandler::stopTraining()
{
    m_training = false;
    emit trainingChanged();
}

void DeviceHandler::serviceDiscovered(const QBluetoothUuid& gatt)
{
    if (gatt == m_service_uuid) {
        setInfo("Обнаружена служба. Ожидание завершения сканирования служб...");
        m_foundService = true;
    }
}

void DeviceHandler::serviceScanDone()
{
    setInfo("Выполнение сканирования служб.");

    // Удаление старого сервиса, если он доступен
    if (m_service) {
        delete m_service;
        m_service = nullptr;
    }

    // Если обнаружено свойство Ski, создать новый сервис
    if (m_foundService)
        m_service = m_control->createServiceObject(QBluetoothUuid(m_service_uuid), this);
    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &DeviceHandler::serviceStateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &DeviceHandler::updateValue);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &DeviceHandler::confirmedDescriptorWrite);
        m_service->discoverDetails();
    }
    else {
        setError("Служба не найдена.");
    }
}

void DeviceHandler::serviceStateChanged(QLowEnergyService::ServiceState state)
{
    switch (state) {
    case QLowEnergyService::DiscoveringServices:
        setInfo(tr("Обнаружение служб..."));
        break;
    case QLowEnergyService::ServiceDiscovered: {
        setInfo(tr("Обнаружена служба."));

        const QLowEnergyCharacteristic characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
        if (!characteristic.isValid()) {
            setError("Ski не найден.");
            break;
        }

        m_notificationDesc = characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if (m_notificationDesc.isValid())
            m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));

        m_service->writeCharacteristic(characteristic, parcel(Ski::SET_GET_DATE_TIME));

        break;
    }
    default:
        break;
    }
    qDebug() << state;
    emit aliveChanged();
}

void DeviceHandler::updateValue(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    // игнорировать любые другие изменения характеристик.
    // на самом деле не должно произойти.
    if (characteristic.uuid() != m_characteristic_uuid)
        return;

    static QElapsedTimer t;

    const Ski::DateTime_t date = value<Ski::DateTime_t>(data);
    QString str(QTime(date.hour, date.minute, date.second).toString("hh:mm:ss") + QString::number(t.elapsed()));
    setInfo(str);
    if (checkParcel(data))
        qDebug() << data.toHex().toUpper();
    t.start();
    m_service->writeCharacteristic(characteristic, parcel(Ski::SET_GET_DATE_TIME));
}

void DeviceHandler::confirmedDescriptorWrite(const QLowEnergyDescriptor& d, const QByteArray& value)
{
    if (d.isValid() && d == m_notificationDesc && value == QByteArray::fromHex("0000")) {
        // отключенные уведомления -> предполагать отключение
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = nullptr;
    }
}

void DeviceHandler::disconnectService()
{
    m_foundService = false;
    //disable notifications
    if (m_notificationDesc.isValid() && m_service && m_notificationDesc.value() == QByteArray::fromHex("0100")) {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    }
    else {
        if (m_control)
            m_control->disconnectFromDevice();
        delete m_service;
        m_service = nullptr;
    }
}

bool DeviceHandler::training() const
{
    return m_training;
}

bool DeviceHandler::alive() const
{
    if (m_service)
        return m_service->state() == QLowEnergyService::ServiceDiscovered;
    return false;
}

int DeviceHandler::time() const
{
    return m_start.secsTo(m_stop);
}
