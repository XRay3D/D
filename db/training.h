#ifndef TRAINING_H
#define TRAINING_H

#include <QDateTime>
#include <QObject>

class Training : public QObject {
    Q_OBJECT
public:
    explicit Training(QObject* parent = nullptr);

//    QDateTime date() const;
//    QTime timePause() const;
//    QTime timeWithStimulation() const;
//    QTime timeWithoutStimulation() const;
//    int avgSpeedWithStimulation() const;
//    int avgSpeedWithoutStimulation() const;
//    int avgStepFrequency() const;
//    int avgStepLength() const;
//    int avgStimulationAmplitude() const;
//    int totalDistance() const;
//    int totalStimulationDistance() const;
//    int type() const;

//    void setAvgSpeedWithStimulation(int avgSpeedWithStimulation);
//    void setAvgSpeedWithoutStimulation(int avgSpeedWithoutStimulation);
//    void setAvgStepFrequency(int avgStepFrequency);
//    void setAvgStepLength(int avgStepLength);
//    void setAvgStimulationAmplitude(int avgStimulationAmplitude);
//    void setDate(const QDateTime& date);
//    void setTimePause(const QTime& timePause);
//    void setTimeWithStimulation(const QTime& timeWithStimulation);
//    void setTimeWithoutStimulation(const QTime& timeWithoutStimulation);
//    void setTotalDistance(int totalDistance);
//    void setTotalStimulationDistance(int totalStimulationDistance);
//    void setType(int type);

//private:
    QDateTime m_date;
    QTime m_timePause;
    QTime m_timeWithStimulation;
    QTime m_timeWithoutStimulation;
    int m_avgSpeedWithStimulation = 5;
    int m_avgSpeedWithoutStimulation = 4;
    int m_avgStepFrequency = 3;
    int m_avgStepLength = 2;
    int m_avgStimulationAmplitude = 1;
    int m_totalDistance = 6;
    int m_totalStimulationDistance = 7;
    int m_type = 0;
};

#endif // TRAINING_H
