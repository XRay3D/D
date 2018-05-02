#include "training.h"

#include <QTimerEvent>
#include <QDebug>

Training::Training(DeviceHandler* handler, QObject* parent)
    : QObject(parent)
    , m_date(QDateTime::currentDateTime())
    , m_deviceHandler(handler)
    , m_state(QStringLiteral("Stopped"))
    , m_eState(Stopped)
{
}

void Training::start()
{
    reset();
    m_trainingTimer.start();

    if (m_timerId)
        killTimer(m_timerId);
    m_timerId = startTimer(100);

    m_state = QStringLiteral("Running");
    m_eState = Running;
    stateChanged();
}

void Training::pause()
{
    m_pausedTimer.start();
    m_state = QStringLiteral("Paused");
    m_eState = Paused;
    stateChanged();
}

void Training::resume()
{
    m_timeWithoutStimulation += m_pausedTimer.elapsed();
    m_state = QStringLiteral("Running");
    m_eState = Running;
    stateChanged();
}

void Training::stop()
{
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }

    m_timeWithoutStimulation += m_pausedTimer.elapsed();
    m_timeWithStimulation = m_trainingTimer.elapsed() - m_timeWithoutStimulation;

    m_state = QStringLiteral("Stopped");
    m_eState = Stopped;
    addToDataBase(this);
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

    setTotalTime(QStringLiteral("00:00:00"));
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
