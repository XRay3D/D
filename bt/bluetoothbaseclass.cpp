#include "bluetoothbaseclass.h"
#include <QTimer>
BluetoothBaseClass::BluetoothBaseClass(QObject* parent)
    : QObject(parent)
{
}

QString BluetoothBaseClass::error() const
{
    return m_error;
}

QString BluetoothBaseClass::info() const
{
    return m_info;
}

void BluetoothBaseClass::setError(const QString& error)
{
    if (m_error != error) {
        m_error = error;
        emit errorChanged();
        //QTimer::singleShot(1000, Qt::CoarseTimer, [this]() { m_error.clear(); emit errorChanged(); });
    }
}

void BluetoothBaseClass::setInfo(const QString& info)
{
    if (m_info != info) {
        m_info = info;
        emit infoChanged();
        //QTimer::singleShot(1000, Qt::CoarseTimer, [this]() { m_info.clear(); emit infoChanged(); });
    }
}

void BluetoothBaseClass::clearMessages()
{
    setInfo("");
    setError("");
}
