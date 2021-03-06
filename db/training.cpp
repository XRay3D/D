#include "training.h"

#include <QDebug>
#include <QTimerEvent>

Training::Training(DeviceHandler* handler, QObject* parent)
    : QObject(parent)
    , m_date(QDateTime::currentDateTime())
    , m_deviceHandler(handler)
    , m_state(QStringLiteral("Stopped"))
    , m_eState(State::Stopped)
{
    m_geoSource = QGeoPositionInfoSource::createDefaultSource(this /*nullptr*/);
    if (m_geoSource) {
        connect(m_geoSource, &QGeoPositionInfoSource::positionUpdated, this, &Training::positionUpdated);
        m_geoSource->setUpdateInterval(1000);
        //m_geoSource->startUpdates();
    } else {
        m_deviceHandler->setError("QGeoPositionInfoSource!");
    }
}

void Training::start()
{
    if (m_eState != State::Prepare && m_eState != State::Stopped)
        return;
    setState(State::Running);
    reset();
    m_trainingTimer.start();

    if (m_timerId)
        killTimer(m_timerId);
    m_timerId = startTimer(100);
    m_geoSource->startUpdates();
}

void Training::prepare()
{
    if (m_eState != State::Stopped)
        return;
    setState(State::Prepare);
    m_deviceHandler->selectTrainingType(m_type);
    m_deviceHandler->resetStatistics();
    m_deviceHandler->enableTraining(true);
}

void Training::pause()
{
    if (m_eState != State::Running)
        return;
    setState(State::Paused);
    m_pausedTimer.start();
    m_deviceHandler->enableTraining(false);
}

void Training::resume()
{
    if (m_eState != State::Paused)
        return;
    setState(State::Running);
    m_timeWithoutStimulation += m_pausedTimer.elapsed();
    m_deviceHandler->enableTraining(true);
}

void Training::stop()
{
    if (m_eState == State::Stopped)
        return;
    if (m_eState == State::Paused)
        m_timeWithoutStimulation += m_pausedTimer.elapsed();
    setState(State::Stopped);

    m_geoSource->stopUpdates();

    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }

    m_timeWithStimulation = m_trainingTimer.elapsed() - m_timeWithoutStimulation;

    Ski::Statistics_t st;
    Ski::Statistics_t sp;

    m_deviceHandler->getPauseStatistics(sp);
    m_deviceHandler->getTrainingStatistics(st);
    m_deviceHandler->enableTraining(false);

    if ((st.steps + sp.steps) > 0) {
        m_avgStepFrequency = (st.steps + sp.steps) / ((m_timeWithoutStimulation + m_timeWithStimulation) / 1000.f);
        m_avgStepLength = m_totalDistance;
        m_avgStepLength /= (st.steps + sp.steps);
    } else {
        m_avgStepFrequency = 0;
        m_avgStepLength = 0;
    }

    m_avgStimulationAmplitude = st.averageAmplitude;

    if (m_timeWithoutStimulation > 0)
        m_avgSpeedWithoutStimulation = m_distanceWithoutStimulation / (m_timeWithoutStimulation / 1000.);
    else
        m_avgSpeedWithoutStimulation = 0;

    if (m_timeWithStimulation > 0)
        m_avgSpeedWithStimulation = m_distanceWithStimulation / (m_timeWithStimulation / 1000.);
    else
        m_avgSpeedWithStimulation = 0;

    m_totalDistance = m_distanceWithoutStimulation + m_distanceWithStimulation;
    m_totalStimulationDistance = m_distanceWithStimulation;

    addToDataBase(this);
    showTraining();
}

void Training::setState(Training::State state)
{
    m_eState = state;
    switch (state) {
    case State::Stopped:
        m_state = QStringLiteral("Stopped");
        break;
    case State::Prepare:
        m_state = QStringLiteral("Prepare");
        m_totalTime = "Настройка";
        emit totalTimeChanged();
        break;
    case State::Running:
        m_state = QStringLiteral("Running");
        break;
    case State::Paused:
        m_state = QStringLiteral("Paused");
        break;
    }
    stateChanged();
}

int Training::type() const
{
    return m_type;
}

void Training::setType(int type)
{
    m_type = type;
    typeChanged();
}

QString Training::state() const
{
    return m_state;
}

void Training::reset()
{
    m_date = QDateTime::currentDateTime();
    m_timeWithStimulation = 0;
    m_timeWithoutStimulation = 0;
    m_timeStimulation = 0;
    m_timeRest = 0;
    m_avgSpeedWithStimulation = 5;
    m_avgSpeedWithoutStimulation = 4;
    m_avgStepFrequency = 3;
    m_avgStepLength = 2;
    m_avgStimulationAmplitude = 1;
    m_totalDistance = 6;
    m_totalStimulationDistance = 7;

    m_distanceWithStimulation = 0.0;
    m_distanceWithoutStimulation = 0.0;
    m_speedWithStimulation = 0.0;
    m_speedWithoutStimulation = 0.0;

    setTotalTime(QStringLiteral("00:00:00"));
}

void Training::positionUpdated(const QGeoPositionInfo& info)
{
    switch (m_eState) {
    case State::Running:
        if (m_lastPoint.isValid())
            m_distanceWithStimulation = m_distanceWithStimulation + info.coordinate().distanceTo(m_lastPoint);
        break;
    case State::Paused:
        if (m_lastPoint.isValid())
            m_distanceWithoutStimulation = m_distanceWithoutStimulation + info.coordinate().distanceTo(m_lastPoint);
        break;
    default:
        break;
    }
    m_lastPoint = info.coordinate();
    m_deviceHandler->setInfo(info.coordinate().toString());
    qDebug() << info << info.coordinate().distanceTo(m_lastPoint);
}

QString Training::totalTime() const
{
    return m_totalTime;
}

void Training::setTotalTime(const QString& totalTime)
{
    m_totalTime = totalTime;
    emit totalTimeChanged();
}

void Training::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerId) {
        setTotalTime(QTime::fromMSecsSinceStartOfDay(m_trainingTimer.elapsed()).toString("hh:mm:ss"));
        event->accept();
    }
}
