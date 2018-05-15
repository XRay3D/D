#include "devicefinder.h"
#include "devicehandler.h"
#include "deviceinfo.h"

DeviceFinder::DeviceFinder(DeviceHandler* handler, QObject* parent)
    : BluetoothBaseClass(parent)
    , m_deviceHandler(handler)
{
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(1000);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &DeviceFinder::addDevice);
    typedef void (QBluetoothDeviceDiscoveryAgent::*pError)(QBluetoothDeviceDiscoveryAgent::Error);
    connect(m_deviceDiscoveryAgent, static_cast<pError>(&QBluetoothDeviceDiscoveryAgent::error), this, &DeviceFinder::scanError);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &DeviceFinder::scanFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this, &DeviceFinder::scanFinished);
}

DeviceFinder::~DeviceFinder()
{
    qDeleteAll(m_devices);
    m_devices.clear();
}

void DeviceFinder::startSearch()
{
    clearMessages();
    m_deviceHandler->setDevice(nullptr);
    qDeleteAll(m_devices);
    m_devices.clear();

    emit devicesChanged();

    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    emit scanningChanged();
    setInfo(tr("Сканирование устройств..."));
}

void DeviceFinder::addDevice(const QBluetoothDeviceInfo& device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        if (device.name().startsWith("Ski"))
            m_devices.append(new DeviceInfo(device));
        setInfo(tr("Обнаружено устройство LowEnergy. Сканирование больше..."));
        emit devicesChanged();
    }
}

void DeviceFinder::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        setError(tr("Адаптер Bluetooth выключен."));
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
        setError(tr("Запись или чтение с устройства привели к ошибке."));
    else
        setError(tr("Произошла неизвестная ошибка."));
}

void DeviceFinder::scanFinished()
{

    if (m_devices.size() == 0)
        setError(tr("Не обнаружено устройств LowEnergy."));
    else
        setInfo(tr("Сканирование завершено."));

    emit scanningChanged();
    emit devicesChanged();
}

void DeviceFinder::connectToService(const QString& address)
{
    m_deviceDiscoveryAgent->stop();

    DeviceInfo* currentDevice = nullptr;
    for (int i = 0; i < m_devices.size(); i++) {
        if (reinterpret_cast<DeviceInfo*>(m_devices.at(i))->getAddress() == address) {
            currentDevice = reinterpret_cast<DeviceInfo*>(m_devices.at(i));
            break;
        }
    }

    if (currentDevice)
        m_deviceHandler->setDevice(currentDevice);

    clearMessages();
}

bool DeviceFinder::scanning() const
{
    return m_deviceDiscoveryAgent->isActive();
}

QVariant DeviceFinder::devices()
{
    return QVariant::fromValue(m_devices);
}
