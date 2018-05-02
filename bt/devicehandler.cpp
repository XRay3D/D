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
    , m_characteristic_uuid(
          "{0000FFE1-0000-1000-8000-00805F9B34FB}")
    , m_service_uuid(
          "{0000FFE0-0000-1000-8000-00805F9B34FB}")
    , m_func(QVector<DeviceHandler::func>(0x100, &DeviceHandler::cbWrongCommand))
{
    m_func[Ski::PING] = &DeviceHandler::cbPing;
    //    m_func[Ski::SET_GET_RF_SETTINGS] = &DeviceHandler::cbSetGetRfSettings;
    m_func[Ski::SET_GET_STIMULATION_SETTINGS] = &DeviceHandler::cbSetGetStimulationSettings;
    m_func[Ski::SET_GET_STATISTICS] = &DeviceHandler::cbSetGetStatistics;
    //    m_func[Ski::SET_GET_DATE_TIME] = &DeviceHandler::cbSetGetDateTime;
    m_func[Ski::GET_BATTERY] = &DeviceHandler::cbGetBattery;
    //    m_func[Ski::GET_ACC_GYR] = &DeviceHandler::cbGetAccGyr;
    //    m_func[Ski::GET_STATUS] = &DeviceHandler::cbGetStatus;
    m_func[Ski::IMPULSE] = &DeviceHandler::cbImpulse;
    m_func[Ski::ON_OFF] = &DeviceHandler::cbOnOff;
    m_func[Ski::BUFFER_OVERFLOW] = &DeviceHandler::cbBufferOverflow;
    m_func[Ski::WRONG_COMMAND] = &DeviceHandler::cbWrongCommand;
    m_func[Ski::TEXTUAL_PARCEL] = &DeviceHandler::cbTextualParcel;
    m_func[Ski::CRC_ERROR] = &DeviceHandler::cbCrcError;
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

void DeviceHandler::setAddressType(DeviceHandler::AddressType type)
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

bool DeviceHandler::alive() const
{
    if (m_service)
        return m_service->state() == QLowEnergyService::ServiceDiscovered;
    return false;
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

bool DeviceHandler::setVoltage(int voltage)
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    m_stimulationSettings.voltage = voltage;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STIMULATION_SETTINGS, m_stimulationSettings));
    }
    return success();
}

bool DeviceHandler::setDuration(int duration)
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    m_stimulationSettings.duration = duration;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STIMULATION_SETTINGS, m_stimulationSettings));
    }
    return success();
}

bool DeviceHandler::setDelay(int delay)
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    m_stimulationSettings.voltage = delay;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STIMULATION_SETTINGS, m_stimulationSettings));
    }
    return success();
}

bool DeviceHandler::resetStatistics()
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STATISTICS, uint8_t(Ski::RESET)));
    }

    return success();
}

bool DeviceHandler::getTrainingStatistics()
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    m_statisticsType = Ski::GET_TRAINING;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STATISTICS, uint8_t(Ski::GET_TRAINING)));
    }
    return success();
}

bool DeviceHandler::getPauseStatistics()
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    m_statisticsType = Ski::GET_PAUSE;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::SET_GET_STATISTICS, uint8_t(Ski::GET_PAUSE)));
    }
    return success();
}

bool DeviceHandler::getBatteryCharge()
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::GET_BATTERY, uint8_t(Ski::GET_BATTERY)));
    }
    return success();
}

bool DeviceHandler::impulse()
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::IMPULSE));
    }
    return success();
}

bool DeviceHandler::enableTraining(bool enabled)
{
    m_success = false;
    if (m_service == nullptr)
        return m_success;
    const QLowEnergyCharacteristic characteristic
        = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
        m_service->writeCharacteristic(characteristic,
            parcel(Ski::ON_OFF, uint8_t(enabled)));
    }
    return success();
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

        //m_service->writeCharacteristic(characteristic, parcel(Ski::SET_GET_DATE_TIME));
        break;
    }
    default:
        break;
    }
    qDebug() << state;
    emit aliveChanged(alive());
}

void DeviceHandler::updateValue(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    // игнорировать любые другие изменения характеристик.
    // на самом деле не должно произойти.
    if (characteristic.uuid() != m_characteristic_uuid)
        return;
    if (!checkParcel(data)) {
        cbCrcError(data);
        return;
    }
    else {
        (this->*m_func[data[3]])(data);
    }

    qDebug() << data.toHex().toUpper();

    //    static QElapsedTimer t;
    //    const Ski::DateTime_t date = value<Ski::DateTime_t>(data);
    //    QString str(QTime(date.hour, date.minute, date.second).toString("hh:mm:ss") + QString::number(t.elapsed()));
    //    setInfo(str);
    //    if (checkParcel(data))
    //        qDebug() << data.toHex().toUpper();
    //    t.start();
    //    m_service->writeCharacteristic(characteristic, parcel(Ski::SET_GET_DATE_TIME));
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

//Ski callbacks
void DeviceHandler::cbPing(const QByteArray& data)
{
    qDebug() << "cbPing" << static_cast<quint16>(data[4]); //fw version
    m_success = true;
}

void DeviceHandler::cbSetGetStimulationSettings(const QByteArray& data)
{
    const Ski::Parcel_t* parcel = reinterpret_cast<const Ski::Parcel_t*>(data.constData());
    if (parcel->len != Ski::MIN_LEN) {
        value<Ski::StimulationSettings_t>(data);
    }
    qDebug("cbSetGetStimulationSettings");
    m_success = true;
}

void DeviceHandler::cbSetGetStatistics(const QByteArray& data)
{
    const Ski::Parcel_t* parcel = reinterpret_cast<const Ski::Parcel_t*>(data.constData());
    if (parcel->len != Ski::MIN_LEN) {
        value<Ski::Statistics_t>(data);
        switch (m_statisticsType) {
        case Ski::GET_TRAINING:
            // signal GET_TRAINING
            break;
        case Ski::GET_PAUSE:
            // signal GET_PAUSE
            break;
        }
    }
    qDebug("cbSetGetStatistics");
    m_success = true;
}

void DeviceHandler::cbGetBattery(const QByteArray& data)
{
    value<Ski::Battery_t>(data);
    qDebug("cbGetBattery");
    m_success = true;
}

void DeviceHandler::cbImpulse(const QByteArray&)
{
    qDebug("cbImpulse");
    m_success = true;
}

void DeviceHandler::cbOnOff(const QByteArray& data)
{
    const Ski::Parcel_t* parcel = reinterpret_cast<const Ski::Parcel_t*>(data.constData());
    if (parcel->len != Ski::MIN_LEN) {
    }
    qDebug("cbOnOff");
    m_success = true;
}

void DeviceHandler::cbBufferOverflow(const QByteArray&)
{
    qDebug("cbBufferOverflow");
    m_success = true;
}

void DeviceHandler::cbWrongCommand(const QByteArray&)
{
    qDebug("cbWrongCommand");
    m_success = true;
}

void DeviceHandler::cbTextualParcel(const QByteArray& data)
{
    qDebug() << "cbTextualParcel" << QString(data);
    m_success = true;
}

void DeviceHandler::cbCrcError(const QByteArray&)
{
    qDebug("cbCrcError");
    m_success = true;
}
