#include "listmodel.h"
#include "database.h"

ListModel::ListModel(QObject* parent)
    : QSqlQueryModel(parent)
{
    this->updateModel();
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
    //qDebug() << columnId << tmp << QDateTime::fromString(tmp.toString(), Qt::ISODate);
    switch (role) {
    case idRole:
    case typeRole:
        return tmp.toInt();
    case dateRole:
        return QVariant(QDateTime::fromString(tmp.toString(), Qt::ISODate));
    case timeWithStimulationRole:
    case timeWithoutStimulationRole:
    case timePauseRole:
        return QVariant(QTime::fromString(tmp.toString(), Qt::ISODate));
    case avgStimulationAmplitudeRole:
    case avgStepLengthRole:
    case avgStepFrequencyRole:
    case avgSpeedWithoutStimulationRole:
    case avgSpeedWithStimulationRole:
    case totalDistanceRole:
    case totalStimulationDistanceRole:
        return tmp.toInt();
    default:
        return QVariant();
        break;
    }
}

QVariant ListModel::getData(int row, const QString& role)
{
    return data(index(row, 0), roleNames().key(role.toLocal8Bit()));
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

int ListModel::count()
{
    return rowCount();
}

// Получение id из строки в модели представления данных
int ListModel::getId(int row)
{
    return this->data(this->index(row, 0), idRole).toInt();
}

// Метод обновления таблицы в модели представления данных
void ListModel::updateModel()
{
    // Обновление производится SQL-запросом к базе данных
    this->setQuery("SELECT id, " TYPE ", " DATE ", " TIME_WITH_STIMULATION ", " TIME_WITHOUT_STIMULATION ", " TIME_PAUSE ", " AVG_STIMULATION_AMPLITUDE ", " AVG_STEP_LENGTH ", " AVG_STEP_FREQUENCY ", " AVG_SPEED_WITHOUT_STIMULATION ", " AVG_SPEED_WITH_STIMULATION ", " TOTAL_DISTANCE ", " TOTAL_STIMULATION_DISTANCE " FROM " TABLE);
}

//Training ListModel::getTraining(int row)
//{
//    return Training();
//}
