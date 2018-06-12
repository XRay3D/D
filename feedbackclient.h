#ifndef VIBRATIONCLIENT_H
#define VIBRATIONCLIENT_H

#include <QObject>
#if defined(Q_OS_IOS)
#include <AudioToolbox/AudioServices.h>
#elif defined(Q_OS_ANDROID)
#include <QtAndroidExtras/QAndroidJniObject>
#endif
#include <QSound>

class FeedbackClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool sound READ getSound WRITE setSound NOTIFY soundChanged)
    Q_PROPERTY(bool vibration READ getVibration WRITE setVibration NOTIFY vibrationChanged)

public:
    explicit FeedbackClient(QObject* parent = nullptr);
    ~FeedbackClient();

    static FeedbackClient* self();

    bool getSound() const;
    void setSound(bool value);

    bool getVibration() const;
    void setVibration(bool value);

signals:
    void soundChanged() const;
    void vibrationChanged() const;

public slots:
    void on(long duration);

private:
    static FeedbackClient* m_self;
    bool m_sound = false;
    bool m_vibration = false;
    QSound m_soundPlay;
};

#endif // VIBRATIONCLIENT_H
