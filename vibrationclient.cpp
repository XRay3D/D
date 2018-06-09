#include "vibrationclient.h"

VibrationClient* VibrationClient::m_self = nullptr;

VibrationClient::VibrationClient(QObject* parent)
    : QObject(parent)
{
    m_self = this;
}

VibrationClient::~VibrationClient()
{
    m_self = nullptr;
}

VibrationClient* VibrationClient::self()
{
    return m_self;
}

void VibrationClient::on(long duration)
{
    if (!m_enabled)
        return;
#if defined(Q_OS_IOS)
    Q_UNUSED(duration)
    //AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
#elif defined(Q_OS_ANDROID)
    jlong jl = duration;
    QAndroidJniObject::callStaticMethod<void>("ru/roc/dems/DemsActivity", "vibro", "(J)V", jl);
#endif
}

bool VibrationClient::enabled() const
{
    return m_enabled;
}

void VibrationClient::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        enabledChanged();
    }
}
