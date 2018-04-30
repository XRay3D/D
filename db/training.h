#ifndef TRAINING_H
#define TRAINING_H

#include <QDateTime>
#include <QObject>

#include <bt/devicehandler.h>

class Training : public QObject {
    Q_OBJECT
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString totalTime READ totalTime NOTIFY totalTimeChanged)

public:
    explicit Training(DeviceHandler* handler, QObject* parent = nullptr);

    //private:
    QDateTime m_date; //дата и время начала тренировки
    int m_timeWithStimulation = 0; //с стимулированием
    int m_timeWithoutStimulation = 0; //без стимулирования
    int m_timeStimulation = 0; //время стимулирования, суммарно длительность импульсов.
    int m_timeRest = 0; //отдых - без движа
    int m_avgSpeedWithStimulation = 5;
    int m_avgSpeedWithoutStimulation = 4;
    int m_avgStepFrequency = 3;
    int m_avgStepLength = 2;
    int m_avgStimulationAmplitude = 1;
    int m_totalDistance = 6;
    int m_totalStimulationDistance = 7;
    int m_type = 0;

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void stop();

    QString totalTime() const;
    void setTotalTime(const QString& totalTime);

    int type() const;
    void setType(int type);

    QString state() const;

signals:
    void typeChanged();
    void stateChanged();
    void totalTimeChanged();
    void addToDataBase(Training*);

private:
    DeviceHandler* m_deviceHandler;

    QString m_state;
    QString m_totalTime;

    //int m_trainingTimeMs; //time in msecs
    //int m_pausedTimeMs; //time in msecs

    QTime m_trainingTimer;
    QTime m_pausedTimer;

    int m_timerId = 0;

    typedef enum {
        Stopped,
        Running,
        Paused
    } State;

    inline void reset();

    State m_eState;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent* event) override;
};

#endif // TRAINING_H
