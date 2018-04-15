#include "training.h"

Training::Training(QObject* parent)
    : QObject(parent)
    , m_date(QDateTime::currentDateTime())
    , m_timeWithStimulation(QTime::currentTime())
    , m_timeWithoutStimulation(QTime::currentTime())
    , m_timePause(QTime::currentTime())
{
    m_type = qrand() > RAND_MAX / 2;
}

//QDateTime Training::date() const { return m_date; }
//QTime Training::timePause() const { return m_timePause; }
//QTime Training::timeWithStimulation() const { return m_timeWithStimulation; }
//QTime Training::timeWithoutStimulation() const { return m_timeWithoutStimulation; }
//int Training::avgSpeedWithStimulation() const { return m_avgSpeedWithStimulation; }
//int Training::avgSpeedWithoutStimulation() const { return m_avgSpeedWithoutStimulation; }
//int Training::avgStepFrequency() const { return m_avgStepFrequency; }
//int Training::avgStepLength() const { return m_avgStepLength; }
//int Training::avgStimulationAmplitude() const { return m_avgStimulationAmplitude; }
//int Training::totalDistance() const { return m_totalDistance; }
//int Training::totalStimulationDistance() const { return m_totalStimulationDistance; }
//int Training::type() const { return m_type; }

//void Training::setAvgSpeedWithStimulation(int avgSpeedWithStimulation) { m_avgSpeedWithStimulation = avgSpeedWithStimulation; }
//void Training::setAvgSpeedWithoutStimulation(int avgSpeedWithoutStimulation) { m_avgSpeedWithoutStimulation = avgSpeedWithoutStimulation; }
//void Training::setAvgStepFrequency(int avgStepFrequency) { m_avgStepFrequency = avgStepFrequency; }
//void Training::setAvgStepLength(int avgStepLength) { m_avgStepLength = avgStepLength; }
//void Training::setAvgStimulationAmplitude(int avgStimulationAmplitude) { m_avgStimulationAmplitude = avgStimulationAmplitude; }
//void Training::setDate(const QDateTime& date) { m_date = date; }
//void Training::setTimePause(const QTime& timePause) { m_timePause = timePause; }
//void Training::setTimeWithStimulation(const QTime& timeWithStimulation) { m_timeWithStimulation = timeWithStimulation; }
//void Training::setTimeWithoutStimulation(const QTime& timeWithoutStimulation) { m_timeWithoutStimulation = timeWithoutStimulation; }
//void Training::setTotalDistance(int totalDistance) { m_totalDistance = totalDistance; }
//void Training::setTotalStimulationDistance(int totalStimulationDistance) { m_totalStimulationDistance = totalStimulationDistance; }
//void Training::setType(int type) { m_type = type; }
