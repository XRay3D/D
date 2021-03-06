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

    switch (role) {
    case idRole:
    case typeRole:
        return QVariant(tmp.toInt());
    case dateRole:
        return QVariant(QDateTime::fromString(tmp.toString(), Qt::ISODate));
    case timeWithStimulationRole:
    case timeWithoutStimulationRole:
    case timeStimulationRole:
    case timeRestRole:
        return QVariant(QTime::fromMSecsSinceStartOfDay(tmp.toInt()));
    case avgStimulationAmplitudeRole:
    case avgStepLengthRole:
    case avgStepFrequencyRole:
    case avgSpeedWithoutStimulationRole:
    case avgSpeedWithStimulationRole:
    case totalDistanceRole:
    case totalStimulationDistanceRole:
        return QVariant(tmp.toInt());
    default:
        break;
    }
    return tmp;
}

// Метод для получения данных из модели
QVariant ListModel::data2(int row, int role) const
{
    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole;
    // Создаём индекс с помощью новоиспечённого ID колонки
    QModelIndex modelIndex = this->index(row, columnId);
    // И с помощью уже метода data() базового класса вытаскиваем данные для таблицы из модели
    return QVariant(QSqlQueryModel::data(modelIndex, Qt::DisplayRole));
}

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
    return data(index(row, 0), idRole).toInt();
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

int ListModel::getType(int row)
{
    return data2(row, typeRole).toInt();
}

QString ListModel::getDate(int row)
{
    return QDateTime::fromString(data2(row, dateRole).toString(), Qt::ISODate).toString("dd.MM.yyyy — hh:mm");
}

QString ListModel::getTrainingTime(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data2(row, timeWithStimulationRole).toInt() + data2(row, timeWithoutStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeWithStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data2(row, timeWithStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeWithoutStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data2(row, timeWithoutStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeStimulation(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data2(row, timeStimulationRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getTimeRest(int row)
{
    return QTime::fromMSecsSinceStartOfDay(data2(row, timeRestRole).toInt()).toString("hh:mm:ss");
}

QString ListModel::getAvgStimulationAmplitude(int row)
{
    return data2(row, avgStimulationAmplitudeRole).toString();
}

QString ListModel::getAvgStepLength(int row)
{
    return QString::number( data2(row, avgStepLengthRole).toFloat());
}

QString ListModel::getAvgStepFrequency(int row)
{
    return QString::number(data2(row, avgStepFrequencyRole).toFloat());
}

QString ListModel::getAvgSpeedWithoutStimulation(int row)
{
    return data2(row, avgSpeedWithoutStimulationRole).toString();
}

QString ListModel::getAvgSpeedWithStimulation(int row)
{
    return data2(row, avgSpeedWithStimulationRole).toString();
}

QString ListModel::getTotalDistance(int row)
{
    return data2(row, totalDistanceRole).toString();
}

QString ListModel::getTotalStimulationDistance(int row)
{
    return data2(row, totalStimulationDistanceRole).toString();
}
