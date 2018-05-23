#ifndef TRAINING_H
#define TRAINING_H

#include <QDateTime>
#include <QGeoPositionInfoSource>
#include <QLocation>
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
    float m_avgStepFrequency = 3;
    float m_avgStepLength = 2;
    int m_avgStimulationAmplitude = 1;
    int m_totalDistance = 6;
    int m_totalStimulationDistance = 7;
    int m_type = 0;

    QString totalTime() const;
    void setTotalTime(const QString& totalTime);

    int type() const;
    void setType(int type);

    QString state() const;

public slots:
    void start();
    void pause();
    void resume();
    void stop();

signals:
    void typeChanged();
    void stateChanged();
    void totalTimeChanged();
    void addToDataBase(Training*);
    void showTraining();

private:
    DeviceHandler* m_deviceHandler;

    QString m_state;
    QString m_totalTime;

    QTime m_trainingTimer;
    QTime m_pausedTimer;

    int m_timerId = 0;

    typedef enum {
        Stopped,
        Running,
        Paused
    } State;

    inline void reset();

    void positionUpdated(const QGeoPositionInfo& info);
    QGeoPositionInfoSource* m_geoSource;
    QGeoCoordinate m_lastPoint;
    double m_distanceWithStimulation = 0;
    double m_distanceWithoutStimulation = 0;
    int m_speedWithStimulation = 0;
    int m_speedWithoutStimulation = 0;

    State m_eState;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent* event) override;
};

#endif // TRAINING_H
