#include "feedbackclient.h"

FeedbackClient* FeedbackClient::m_self = nullptr;

FeedbackClient::FeedbackClient(QObject* parent)
    : QObject(parent)
    , m_soundPlay(":/sound/tap.wav")
{
    m_self = this;
}

FeedbackClient::~FeedbackClient()
{
    m_self = nullptr;
}

FeedbackClient* FeedbackClient::self()
{
    return m_self;
}

void FeedbackClient::on(long duration)
{
    if (m_vibration) {
#if defined(Q_OS_IOS)
        Q_UNUSED(duration)
        //AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
#elif defined(Q_OS_ANDROID)
        jlong jl = duration;
        QAndroidJniObject::callStaticMethod<void>("ru/roc/dems/DemsActivity", "vibro", "(J)V", jl);
#endif
    }
    if (m_sound) {
        m_soundPlay.play();
    }
}

bool FeedbackClient::getSound() const
{
    return m_sound;
}

void FeedbackClient::setSound(bool value)
{
    if (m_sound != value) {
        m_sound = value;
        soundChanged();
    }
}

bool FeedbackClient::getVibration() const
{
    return m_vibration;
}

void FeedbackClient::setVibration(bool value)
{
    if (m_vibration != value) {
        m_vibration = value;
        vibrationChanged();
    }
}
