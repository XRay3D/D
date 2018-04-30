#include "listmodel.h"
#include "database.h"

ListModel::ListModel(QObject* parent)
    : QSqlQueryModel(parent)
{
    updateModel();
}

// Метод для получения данных из модели
QVariant ListModel::data(const QModelIndex& index, int role) const
{
    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole;
    // Создаём индекс с помощью новоиспечённого ID колонки
    QModelIndex modelIndex = this->index(index.row(), columnId);
    // И с помощью уже метода data() базового класса вытаскиваем данные для таблицы из модели
    QVariant tmp(QSqlQueryModel::data(modelIndex, Qt::DisplayRole));
    return tmp;
    //    switch (role) {
    //    case idRole:
    //    case typeRole:
    //        return tmp.toInt();
    //    case dateRole:
    //        return QVariant(QDateTime::fromString(tmp.toString(), Qt::ISODate));
    //    case timeWithStimulationRole:
    //    case timeWithoutStimulationRole:
    //    case timeStimulationRole:
    //    case timeRestRole:
    //    case avgStimulationAmplitudeRole:
    //    case avgStepLengthRole:
    //    case avgStepFrequencyRole:
    //    case avgSpeedWithoutStimulationRole:
    //    case avgSpeedWithStimulationRole:
    //    case totalDistanceRole:
    //    case totalStimulationDistanceRole:
    //        return tmp.toInt();
    //    default:
    //        return QVariant();
    //        break;
    //    }
}

QString ListModel::getType(int row)
{
    return data(index(row, 0), typeRole).toInt();
}

QString ListModel::getDate(int row)
{
    return QDateTime::fromString(data(index(row, 0), dateRole).toString(), Qt::ISODate).toString("dd.MM.yyyy — hh:mm");
}

QString ListModel::getTrainingTime(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data(index(row, 0), timeWithStimulationRole).toInt() + data(index(row, 0), timeWithoutStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeWithStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data(index(row, 0), timeWithStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeWithoutStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data(index(row, 0), timeWithoutStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data(index(row, 0), timeStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeRest(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data(index(row, 0), timeRestRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getAvgStimulationAmplitude(int row)
{
    return data(index(row, 0), avgStimulationAmplitudeRole).toString();
}

QString ListModel::getAvgStepLength(int row)
{
    return data(index(row, 0), avgStepLengthRole).toString();
}

QString ListModel::getAvgStepFrequency(int row)
{
    return data(index(row, 0), avgStepFrequencyRole).toString();
}

QString ListModel::getAvgSpeedWithoutStimulation(int row)
{
    return data(index(row, 0), avgSpeedWithoutStimulationRole).toString();
}

QString ListModel::getAvgSpeedWithStimulation(int row)
{
    return data(index(row, 0), avgSpeedWithStimulationRole).toString();
}

QString ListModel::getTotalDistance(int row)
{
    return data(index(row, 0), totalDistanceRole).toString();
}

QString ListModel::getTotalStimulationDistance(int row)
{
    return data(index(row, 0), totalStimulationDistanceRole).toString();
}

// Метод для получения имен ролей через хешированную таблицу.
QHash<int, QByteArray> ListModel::roleNames() const
{
    // То есть сохраняем в хеш-таблицу названия ролей по их номеру
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[typeRole] = "type";
    roles[dateRole] = "date";
    roles[timeWithStimulationRole] = "timeWithStimulation";
    roles[timeWithoutStimulationRole] = "timeWithoutStimulation";
    roles[timeStimulationRole] = "timeStimulation";
    roles[timeRestRole] = "timeRest";
    roles[avgStimulationAmplitudeRole] = "avgStimulationAmplitude";
    roles[avgStepLengthRole] = "avgStepLength";
    roles[avgStepFrequencyRole] = "avgStepFrequency";
    roles[avgSpeedWithoutStimulationRole] = "avgSpeedWithoutStimulation";
    roles[avgSpeedWithStimulationRole] = "avgSpeedWithStimulation";
    roles[totalDistanceRole] = "totalDistance";
    roles[totalStimulationDistanceRole] = "totalStimulationDistance";
    return roles;
}

int ListModel::count()
{
    return rowCount();
}

// Получение id из строки в модели представления данных
int ListModel::getId(int row)
{
    return data(this->index(row, 0), idRole).toInt();
}

// Метод обновления таблицы в модели представления данных
void ListModel::updateModel()
{
    // Обновление производится SQL-запросом к базе данных
    setQuery("SELECT id, "
             "" TYPE ", "
             "" DATE ", "
             "" TIME_WITH_STIMULATION ", "
             "" TIME_WITHOUT_STIMULATION ", "
             "" TIME_STIMULATION ", "
             "" TIME_REST ", "
             "" AVG_STIMULATION_AMPLITUDE ", "
             "" AVG_STEP_LENGTH ", "
             "" AVG_STEP_FREQUENCY ", "
             "" AVG_SPEED_WITHOUT_STIMULATION ", "
             "" AVG_SPEED_WITH_STIMULATION ", "
             "" TOTAL_DISTANCE ", "
             "" TOTAL_STIMULATION_DISTANCE ""
             " FROM " TABLE);
}

//Training ListModel::getTraining(int row)
//{
//    return Training();
//}
