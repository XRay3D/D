#include "devicehandler.h"
#include "deviceinfo.h"
#include <QElapsedTimer>
#include <QtEndian>

DeviceHandler::DeviceHandler(QObject* parent)
    : BluetoothBaseClass(parent)
    , m_func(QVector<DeviceHandler::func>(0x100, &DeviceHandler::cbWrongCommand))
    , m_control(nullptr)
    , m_service(nullptr)
    , m_currentDevice(nullptr)
    , m_foundService(false)
    , m_characteristic_uuid("{0000FFE1-0000-1000-8000-00805F9B34FB}")
    , m_service_uuid("{0000FFE0-0000-1000-8000-00805F9B34FB}")
{
    m_func[static_cast<int>(Ski::Cmmand::PING)] = &DeviceHandler::cbPing;
    m_func[static_cast<int>(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS)] = &DeviceHandler::cbSetGetStimulationSettings;
    m_func[static_cast<int>(Ski::Cmmand::SET_GET_STATISTICS)] = &DeviceHandler::cbSetGetStatistics;
    m_func[static_cast<int>(Ski::Cmmand::GET_BATTERY)] = &DeviceHandler::cbGetBattery;
    m_func[static_cast<int>(Ski::Cmmand::IMPULSE)] = &DeviceHandler::cbImpulse;
    m_func[static_cast<int>(Ski::Cmmand::ON_OFF)] = &DeviceHandler::cbOnOff;
    m_func[static_cast<int>(Ski::Cmmand::BUFFER_OVERFLOW)] = &DeviceHandler::cbBufferOverflow;
    m_func[static_cast<int>(Ski::Cmmand::WRONG_COMMAND)] = &DeviceHandler::cbWrongCommand;
    m_func[static_cast<int>(Ski::Cmmand::TEXTUAL_PARCEL)] = &DeviceHandler::cbTextualParcel;
    m_func[static_cast<int>(Ski::Cmmand::CRC_ERROR)] = &DeviceHandler::cbCrcError;
}

void DeviceHandler::setDevice(DeviceInfo* device)
{
    clearMessages();
    m_currentDevice = device;
    if (m_batTimerId) {
        killTimer(m_batTimerId);
        m_batTimerId = 0;
    }
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

        using pError = void (QLowEnergyController::*)(QLowEnergyController::Error);
        connect(m_control, static_cast<pError>(&QLowEnergyController::error),
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

int DeviceHandler::batteryLeft()
{
    return m_battery.left;
}

int DeviceHandler::batteryRight()
{
    return m_battery.right;
}

void DeviceHandler::disconnectService()
{
    m_foundService = false;
    //disable notifications
    if (m_notificationDesc.isValid() && m_service && m_notificationDesc.value() == QByteArray::fromHex("0100")) {
        m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0000"));
    } else {
        if (m_control)
            m_control->disconnectFromDevice();
        delete m_service;
        m_service = nullptr;
    }
}

bool DeviceHandler::setVoltage(int voltage)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    m_stimSettings.voltage = static_cast<quint8>(voltage);
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings));
    else
        return m_success;
    return success();
}

bool DeviceHandler::setDuration(int duration)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    m_stimSettings.duration = static_cast<quint16>(duration);
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings));
    else
        return m_success;
    return success();
}

bool DeviceHandler::setDelay(int delay)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    m_stimSettings.delay = static_cast<quint16>(delay);
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings));
    else
        return m_success;
    return success();
}

bool DeviceHandler::resetStatistics()
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::RESET)));
    else
        return m_success;
    return success();
}

bool DeviceHandler::getTrainingStatistics(Ski::Statistics_t& s)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    m_statisticsType = Ski::GET_TRAINING;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::GET_TRAINING)));
    else
        return m_success;
    if (success())
        s = m_st;
    return m_success;
}

bool DeviceHandler::getPauseStatistics(Ski::Statistics_t& s)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    m_statisticsType = Ski::GET_PAUSE;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::GET_PAUSE)));
    else
        return m_success;
    if (success())
        s = m_sp;
    return m_success;
}

bool DeviceHandler::getBatteryCharge()
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::GET_BATTERY));
    else
        return m_success;
    return success();
}

bool DeviceHandler::impulse()
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::IMPULSE));
    else
        return m_success;
    return success();
}

bool DeviceHandler::enableTraining(bool enabled)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::ON_OFF, uint8_t(enabled)));
    else
        return m_success;
    return success();
}

bool DeviceHandler::selectTrainingType(int type)
{
    if (m_service == nullptr)
        return m_success;
    m_success = false;
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid())
        m_service->writeCharacteristic(characteristic, parcel(Ski::Cmmand::TRAINING_TYPE, uint8_t(type)));
    else
        return m_success;
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
    } else {
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
        else
            qErrnoWarning("m_notificationDesc.isValid()");

        //m_service->writeCharacteristic(characteristic, parcel(Ski::PING));
        if (getBatteryCharge())
            m_batTimerId = startTimer(10000); //10 cek
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

    m_retData.append(data);
    if (checkParcel(data)) {
        (this->*m_func[data[3]])(data);
        m_retData.clear();
    }
    //    else
    //        cbCrcError(data); /////////////?????????????????????
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
    //m_batTimerId = startTimer(100000); //10 cek
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

        switch (m_statisticsType) {
        case Ski::GET_TRAINING:
            m_st = value<Ski::Statistics_t>(data);
            break;
        case Ski::GET_PAUSE:
            m_sp = value<Ski::Statistics_t>(data);
            break;
        default:
            break;
        }
    }
    qDebug("cbSetGetStatistics");
    m_success = true;
}

void DeviceHandler::cbGetBattery(const QByteArray& data)
{
    m_battery = value<Ski::Battery_t>(data);
    batteryChanged();
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

void DeviceHandler::cbTrType(const QByteArray& data)
{
    const Ski::Parcel_t* parcel = reinterpret_cast<const Ski::Parcel_t*>(data.constData());
    if (parcel->len != Ski::MIN_LEN) {
    }
    qDebug("cbTrType");
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

bool DeviceHandler::success()
{
    QTime timer;
    timer.start();

    while (!m_success && timer.elapsed() < 1000)
        qApp->processEvents();

    if (m_success)
        setInfo("Ok!");
    else
        setError("Timeout!");

    return m_success;
}

void DeviceHandler::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_batTimerId) {
        getBatteryCharge();
        event->accept();
    }
}
