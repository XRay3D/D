#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include "bluetoothbaseclass.h"
#include "skiprotokol.h"

#include <QDateTime>
#include <QVector>
#include <QTimer>
#include <QLowEnergyController>
#include <QLowEnergyService>

class DeviceInfo;

class DeviceHandler : public BluetoothBaseClass, private Ski::Protokol {
    Q_OBJECT

    Q_PROPERTY(int training READ training NOTIFY trainingChanged)
    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)
    Q_PROPERTY(int time READ time NOTIFY statsChanged)
    Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:
    enum class AddressType {
        PublicAddress,
        RandomAddress
    };
    Q_ENUM(AddressType)




    DeviceHandler(QObject* parent = 0);

    void setDevice(DeviceInfo* device);
    void setAddressType(AddressType type);
    AddressType addressType() const;

    bool training() const;
    bool alive() const;

    // Statistics
    int time() const;

signals:
    void trainingChanged();
    void aliveChanged();
    void statsChanged();

public slots:
    void startTraining();
    void stopTraining();
    void disconnectService();

private:
    //  QLowEnergyController
    void serviceDiscovered(const QBluetoothUuid&);
    void serviceScanDone();

    // QLowEnergyService
    void serviceStateChanged(QLowEnergyService::ServiceState state);
    void updateValue(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor& d, const QByteArray& value);

private:
    QLowEnergyController* m_control;
    QLowEnergyService* m_service;
    QLowEnergyDescriptor m_notificationDesc;
    DeviceInfo* m_currentDevice;

    bool m_foundService;
    bool m_training;

    // Statistics
    QDateTime m_start;
    QDateTime m_stop;

    QVector<int> m_measurements;
    QLowEnergyController::RemoteAddressType m_addressType = QLowEnergyController::PublicAddress;

    const QUuid m_characteristic_uuid;
    const QUuid m_service_uuid;
};

#endif // DEVICEHANDLER_H
