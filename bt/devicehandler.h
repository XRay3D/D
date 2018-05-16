#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include "bluetoothbaseclass.h"
#include "skiprotokol.h"

#include <QDateTime>
#include <QGuiApplication>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QTimer>
#include <QVector>

class DeviceInfo;

class DeviceHandler : public BluetoothBaseClass, private Ski::Protokol {
    Q_OBJECT

    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)
    Q_PROPERTY(int batteryLeft READ batteryLeft NOTIFY batteryChanged)
    Q_PROPERTY(int batteryRight READ batteryRight NOTIFY batteryChanged)
    Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:
    enum class AddressType {
        PublicAddress,
        RandomAddress
    };
    Q_ENUM(AddressType)

    DeviceHandler(QObject* parent = nullptr);

    void setDevice(DeviceInfo* device);
    void setAddressType(AddressType type);
    AddressType addressType() const;

    bool alive() const;
    int batteryLeft();
    int batteryRight();

signals:
    void aliveChanged(const QVariant&);
    void batteryChanged();

public slots:
    void disconnectService();

    bool setVoltage(int voltage);
    bool setDuration(int duration);
    bool setDelay(int delay);
    bool resetStatistics();
    bool getTrainingStatistics(Ski::Statistics_t& s);
    bool getPauseStatistics(Ski::Statistics_t& s);
    bool getBatteryCharge();
    bool impulse();
    bool enableTraining(bool enabled);
    bool selectTrainingType(int enabled);

private:
    Ski::Statistics_t m_st;
    Ski::Statistics_t m_sp;
    Ski::Battery_t m_battery;

    //  QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid& gatt);
    void serviceScanDone();

    // QLowEnergyService
    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void updateValue(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor& d, const QByteArray& value);

    using func = void (DeviceHandler::*)(const QByteArray&);
    QVector<func> m_func;

    //Ski callbacks
    void cbPing(const QByteArray& data);
    //User functions
    void cbSetGetStimulationSettings(const QByteArray& data);
    void cbSetGetStatistics(const QByteArray& data);
    void cbGetBattery(const QByteArray& data);
    void cbImpulse(const QByteArray& data);
    void cbOnOff(const QByteArray& data);
    void cbTrType(const QByteArray& data);
    //Service functions
    void cbBufferOverflow(const QByteArray& data);
    void cbWrongCommand(const QByteArray& data);
    void cbTextualParcel(const QByteArray& data);
    void cbCrcError(const QByteArray& data);

    Ski::StimulationSettings_t m_stimSettings;

    QLowEnergyController* m_control;
    QLowEnergyService* m_service;
    QLowEnergyDescriptor m_notificationDesc;
    DeviceInfo* m_currentDevice;
    bool m_foundService;
    bool m_success;
    bool success();

    QByteArray m_retData;
    Ski::Statistics m_statisticsType;

    QVector<int> m_measurements;
    QLowEnergyController::RemoteAddressType m_addressType = QLowEnergyController::PublicAddress;

    const QUuid m_characteristic_uuid;
    const QUuid m_service_uuid;

    int m_batTimerId = 0;

    // QObject interface
protected:
    void timerEvent(QTimerEvent* event) override;
};



#endif // DEVICEHANDLER_H
