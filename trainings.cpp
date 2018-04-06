#include "trainings.h"

TrainingModel::TrainingModel(QObject* parent)
    : QAbstractListModel(parent)
{
    for (int i = 0; i < 100; ++i) {
        m_data.append(Training());
    }
}

void TrainingModel::addTraining(const Training& /*training*/)
{
}

int TrainingModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}

QVariant TrainingModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case typeRole:
        return m_data.at(index.row()).type;
    case dateRole:
        return m_data.at(index.row()).date;
    case timeWithStimulationRole:
        return m_data.at(index.row()).timeWithStimulation;
    case timeWithoutStimulationRole:
        return m_data.at(index.row()).timeWithoutStimulation;
    case timePauseRole:
        return m_data.at(index.row()).timePause;
    case avgStimulationAmplitudeRole:
        return m_data.at(index.row()).avgStimulationAmplitude;
    case avgStepLengthRole:
        return m_data.at(index.row()).avgStepLength;
    case avgStepFrequencyRole:
        return m_data.at(index.row()).avgStepFrequency;
    case avgSpeedWithoutStimulationRole:
        return m_data.at(index.row()).avgSpeedWithoutStimulation;
    case avgSpeedWithStimulationRole:
        return m_data.at(index.row()).avgSpeedWithStimulation;
    case totalDistanceRole:
        return m_data.at(index.row()).totalDistance;
    case totalStimulationDistanceRole:
        return m_data.at(index.row()).totalStimulationDistance;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TrainingModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[typeRole] = "type";
    roles[dateRole] = "date";
    roles[timeWithStimulationRole] = "timeWithStimulation";
    roles[timeWithoutStimulationRole] = "timeWithoutStimulation";
    roles[timePauseRole] = "timePause";
    roles[avgStimulationAmplitudeRole] = "avgStimulationAmplitude";
    roles[avgStepLengthRole] = "avgStepLength";
    roles[avgStepFrequencyRole] = "avgStepFrequency";
    roles[avgSpeedWithoutStimulationRole] = "avgSpeedWithoutStimulation";
    roles[avgSpeedWithStimulationRole] = "avgSpeedWithStimulation";
    roles[totalDistanceRole] = "totalDistance";
    roles[totalStimulationDistanceRole] = "totalStimulationDistance";
    return roles;
}

void TrainingModel::add()
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(Training());
    endInsertRows();

    //m_data[0] = QString("Size: %1").arg(m_data.size());
    QModelIndex index = createIndex(0, 0, static_cast<void*>(0));
    emit dataChanged(index, index);
}

bool TrainingModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    switch (role) {
    case typeRole:
        m_data[index.row()].type = value.toInt();
        break;
    case dateRole:
        m_data[index.row()].date = value.toDateTime();
        break;
    case timeWithStimulationRole:
        m_data[index.row()].timeWithStimulation = value.toTime();
        break;
    case timeWithoutStimulationRole:
        m_data[index.row()].timeWithoutStimulation = value.toTime();
        break;
    case timePauseRole:
        m_data[index.row()].timePause = value.toTime();
        break;
    case avgStimulationAmplitudeRole:
        m_data[index.row()].avgStimulationAmplitude = value.toInt();
        break;
    case avgStepLengthRole:
        m_data[index.row()].avgStepLength = value.toInt();
        break;
    case avgStepFrequencyRole:
        m_data[index.row()].avgStepFrequency = value.toInt();
        break;
    case avgSpeedWithoutStimulationRole:
        m_data[index.row()].avgSpeedWithoutStimulation = value.toInt();
        break;
    case avgSpeedWithStimulationRole:
        m_data[index.row()].avgSpeedWithStimulation = value.toInt();
        break;
    case totalDistanceRole:
        m_data[index.row()].totalDistance = value.toInt();
        break;
    case totalStimulationDistanceRole:
        m_data[index.row()].totalStimulationDistance = value.toInt();
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

Qt::ItemFlags TrainingModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
