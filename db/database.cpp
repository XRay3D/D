#include "database.h"
#include <QStandardPaths>
DataBase::DataBase(QObject* parent)
    : QObject(parent)
{
    connectToDataBase();
}

DataBase::~DataBase()
{
}

// Методы для подключения к базе данных
void DataBase::connectToDataBase()
{
    // Перед подключением к базе данных производим проверку на её существование.
    // В зависимости от результата производим открытие базы данных или её восстановление

#if defined(Q_OS_IOS)
    QStringList paths(QStandardPaths::standardLocations(QStandardPaths::DataLocation));
    QString dbFile(paths.first().append("/") + DATABASE_NAME);
    qDebug() << paths;
#elif defined(Q_OS_ANDROID)
    QString dbFile(DATABASE_NAME);
#endif

    if (QFile(dbFile /*DATABASE_NAME*/).exists())
        openDataBase();
    else
        restoreDataBase();
}

// Методы восстановления базы данных
bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if (openDataBase())
        // Производим восстановление базы данных
        return (createTable()) ? true : false;

    qDebug() << "Не удалось восстановить базу данных";
    return false;
}

// Метод для открытия базы данных
bool DataBase::openDataBase()
{
    // База данных открывается по заданному пути
    // и имени базы данных, если она существует
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
#if defined(Q_OS_IOS)
    QStringList paths(QStandardPaths::standardLocations(QStandardPaths::DataLocation));
    QString dbFile(paths.first().append("/") + DATABASE_NAME);
    db.setDatabaseName(dbFile);
    qDebug() << db;
#elif defined(Q_OS_ANDROID)
    db.setDatabaseName(DATABASE_NAME);
#endif

    if (db.open())
        return true;
    return false;
}

// Методы закрытия базы данных
void DataBase::closeDataBase()
{
    db.close();
}

// Метод для создания таблицы в базе данных
bool DataBase::createTable()
{
    // В данном случае используется формирование сырого SQL-запроса с последующим его выполнением.
    QSqlQuery query;
    if (query.exec("CREATE TABLE " TABLE " ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "" TYPE " INT NOT NULL,"
                   "" DATE " DATETIME NOT NULL,"
                   "" TIME_WITH_STIMULATION " INT NOT NULL,"
                   "" TIME_WITHOUT_STIMULATION " INT NOT NULL,"
                   "" TIME_STIMULATION " INT NOT NULL,"
                   "" TIME_REST " INT NOT NULL,"
                   "" AVG_STIMULATION_AMPLITUDE " INT NOT NULL,"
                   "" AVG_STEP_LENGTH " INT NOT NULL,"
                   "" AVG_STEP_FREQUENCY " INT NOT NULL,"
                   "" AVG_SPEED_WITHOUT_STIMULATION " INT NOT NULL,"
                   "" AVG_SPEED_WITH_STIMULATION " INT NOT NULL,"
                   "" TOTAL_DISTANCE " INT NOT NULL,"
                   "" TOTAL_STIMULATION_DISTANCE " INT NOT NULL"
                   " )"))
        return true;
    qDebug() << "DataBase: error of create " << TABLE;
    qDebug() << query.lastError().text();
    return false;
}

// Mетод для вставки записи в базу данных
bool DataBase::inserIntoTable(Training* t)
{
    // Запрос SQL формируется из QVariantList,
    // в который передаются данные для вставки в таблицу.
    QSqlQuery query;
    // В начале SQL запрос формируется с ключами,
    // которые потом связываются методом bindValue
    // для подстановки данных из QVariantList
    query.prepare("INSERT INTO " TABLE " ("
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
                  "" TOTAL_STIMULATION_DISTANCE
                  ") VALUES (:Val1, :Val2, :Val3, :Val4, :Val5, :Val6, :Val7, :Val8, :Val9, :Val10, :Val11, :Val12, :Val13)");
    query.bindValue(":Val1", t->m_type);
    query.bindValue(":Val2", t->m_date);
    query.bindValue(":Val3", t->m_timeWithStimulation);
    query.bindValue(":Val4", t->m_timeWithoutStimulation);
    query.bindValue(":Val5", t->m_timeStimulation);
    query.bindValue(":Val6", t->m_timeRest);
    query.bindValue(":Val7", t->m_avgStimulationAmplitude);
    query.bindValue(":Val8", t->m_avgStepLength);
    query.bindValue(":Val9", t->m_avgStepFrequency);
    query.bindValue(":Val10", t->m_avgSpeedWithoutStimulation);
    query.bindValue(":Val11", t->m_avgSpeedWithStimulation);
    query.bindValue(":Val12", t->m_totalDistance);
    query.bindValue(":Val13", t->m_totalStimulationDistance);

    // После чего выполняется запросом методом exec()
    if (query.exec())
        return true;

    qDebug() << "error insert into " << TABLE;
    qDebug() << query.lastError().text();
    return false;
}

// Метод для удаления записи из таблицы
bool DataBase::removeRecord(const int id)
{
    // Удаление строки из базы данных будет производитсья с помощью SQL-запроса
    QSqlQuery query;

    // Удаление производим по id записи, который передается в качестве аргумента функции
    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    // Выполняем удаление
    if (query.exec())
        return true;

    qDebug() << "error delete row " << TABLE;
    qDebug() << query.lastError().text();
    return false;
}
