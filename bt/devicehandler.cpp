#include "devicehandler.h"
#include "deviceinfo.h"
#include <QElapsedTimer>
#include <QtEndian>
#include <notificationclient.h>

int id101 = qRegisterMetaType<QLowEnergyDescriptor>("QLowEnergyDescriptor");
int id102 = qRegisterMetaType<QLowEnergyCharacteristic>("QLowEnergyCharacteristic");

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
        m_control = new QLowEnergyController(m_currentDevice->getDevice() /*, this*/);
        m_control->setRemoteAddressType(QLowEnergyController::PublicAddress);
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
    if (!checkService())
        return false;
    m_stimSettings.voltage = static_cast<quint8>(voltage);
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings)))
        return success();
    return m_success;
}

bool DeviceHandler::setDuration(int duration)
{
    if (!checkService())
        return false;
    m_stimSettings.duration = static_cast<quint16>(duration);
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings)))
        return success();
    return m_success;
}

bool DeviceHandler::setDelay(int delay)
{
    if (!checkService())
        return false;
    m_stimSettings.delay = static_cast<quint16>(delay);
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STIMULATION_SETTINGS, m_stimSettings)))
        return success();
    return m_success;
}

bool DeviceHandler::resetStatistics()
{
    if (!checkService())
        return false;
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::RESET))))
        return success();
    return m_success;
}

bool DeviceHandler::getTrainingStatistics(Ski::Statistics_t& s)
{
    if (!checkService())
        return false;
    m_statisticsType = Ski::GET_TRAINING;
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::GET_TRAINING))))
        if (success())
            s = m_st;
    return m_success;
}

bool DeviceHandler::getPauseStatistics(Ski::Statistics_t& s)
{
    if (!checkService())
        return false;
    m_statisticsType = Ski::GET_PAUSE;
    if (writeToSki(parcel(Ski::Cmmand::SET_GET_STATISTICS, uint8_t(Ski::GET_PAUSE))))
        if (success())
            s = m_sp;
    return m_success;
}

bool DeviceHandler::getBatteryCharge()
{
    if (!checkService())
        return false;
    if (writeToSki(parcel(Ski::Cmmand::GET_BATTERY)))
        return success();
    return m_success;
}

bool DeviceHandler::impulse()
{
    if (!checkService())
        return false;
    qDebug() << "22222222222222222222222";
    if (writeToSki(parcel(Ski::Cmmand::IMPULSE)))
        return success();
    qDebug() << "33333333333333333333333";
    return m_success;
}

bool DeviceHandler::enableTraining(bool enabled)
{
    if (!checkService())
        return false;
    if (writeToSki(parcel(Ski::Cmmand::ON_OFF, uint8_t(enabled))))
        return success();
    return m_success;
}

bool DeviceHandler::selectTrainingType(int type)
{
    if (!checkService())
        return false;
    if (writeToSki(parcel(Ski::Cmmand::TRAINING_TYPE, uint8_t(type))))
        return success();
    return m_success;
}

bool DeviceHandler::checkService()
{
    if (m_service == nullptr)
        return false;
    m_semaphore.acquire(m_semaphore.available());
    return true;
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
        m_service = m_control->createServiceObject(QBluetoothUuid(m_service_uuid) /*, this*/);
    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &DeviceHandler::serviceStateChanged);
        qDebug() << connect(m_service, &QLowEnergyService::characteristicChanged, this, &DeviceHandler::updateValue, Qt::DirectConnection);
        //        connect(m_service, &QLowEnergyService::characteristicChanged, [this](const QLowEnergyCharacteristic& info, const QByteArray& value) // this, &DeviceHandler::updateValue);
        //            {
        //                qDebug() << info.uuid() << value.toHex().toUpper();
        //                m_semaphore.release();
        //            });
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
        m_semaphore.release();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////m_semaphore.release();
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
    if (m_battery.right < 20 || m_battery.left < 20)
        NotificationClient::self()->setNotification("Критический заряд батареи!\n" + QString::number(m_battery.right).append("% ") + QString::number(m_battery.left).append('%'));

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

    //m_success = m_semaphore.tryAcquire(1, 1000);
    if (m_success)
        setInfo("Ok!");
    else
        setError("Timeout!");

    qDebug() << "++++++++++++++++++++++" << timer.elapsed();

    return m_success;
}

bool DeviceHandler::writeToSki(const QByteArray& data)
{
    const auto characteristic = m_service->characteristic(QBluetoothUuid(m_characteristic_uuid));
    if (characteristic.isValid()) {
#if defined(Q_OS_IOS)
        m_service->writeCharacteristic(characteristic, data, QLowEnergyService::WriteWithoutResponse);
#else
        m_service->writeCharacteristic(characteristic, data);
#endif
        return true;
    }
    return false;
}

void DeviceHandler::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_batTimerId) {
        getBatteryCharge();
        event->accept();
    }
}
