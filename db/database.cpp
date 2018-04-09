#include "database.h"

DataBase::DataBase(QObject* parent)
    : QObject(parent)
{
}

DataBase::~DataBase()
{
}

// Методы для подключения к базе данных

void DataBase::connectToDataBase()
{
    // Перед подключением к базе данных производим проверку на её существование.
    // В зависимости от результата производим открытие базы данных или её восстановление

    if (!QFile(DATABASE_NAME).exists()) {
        if (this->restoreDataBase()) {
            for (int i = 0; i < 10; ++i) { //////////////////////////////
                inserIntoTable(Training()); ////////////////
            } ////////////////////////
        }
    }
    else {
        this->openDataBase();
    }
}

// Методы восстановления базы данных

bool DataBase::restoreDataBase()
{
    // Если база данных открылась ...
    if (this->openDataBase()) {
        // Производим восстановление базы данных
        return (this->createTable()) ? true : false;
    }
    else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

// Метод для открытия базы данных

bool DataBase::openDataBase()
{
    // База данных открывается по заданному пути
    // и имени базы данных, если она существует

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if (db.open()) {
        return true;
    }
    else {
        return false;
    }
}

// Методы закрытия базы данных

void DataBase::closeDataBase()
{
    db.close();
}

// Метод для создания таблицы в базе данных

bool DataBase::createTable()
{
    // В данном случае используется формирование сырого SQL-запроса
    // с последующим его выполнением.

    QSqlQuery query;
    if (!query.exec("CREATE TABLE " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, " TYPE " INT NOT NULL," DATE " DATETIME NOT NULL," TIME_WITH_STIMULATION
                    " TIME NOT NULL," TIME_WITHOUT_STIMULATION " TIME NOT NULL," TIME_PAUSE " TIME NOT NULL," AVG_STIMULATION_AMPLITUDE " INT NOT NULL," AVG_STEP_LENGTH " INT NOT NULL," AVG_STEP_FREQUENCY " INT NOT NULL," AVG_SPEED_WITHOUT_STIMULATION " INT NOT NULL," AVG_SPEED_WITH_STIMULATION " INT NOT NULL," TOTAL_DISTANCE " INT NOT NULL," TOTAL_STIMULATION_DISTANCE " INT NOT NULL"
                    " )")) {
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}

// Метод для вставки записи в базу данных
bool DataBase::inserIntoTable(const QVariantList& data)
{
    // Запрос SQL формируется из QVariantList,
    // в который передаются данные для вставки в таблицу.
    QSqlQuery query;
    // В начале SQL запрос формируется с ключами,
    // которые потом связываются методом bindValue
    // для подстановки данных из QVariantList
    query.prepare("INSERT INTO " TABLE " ( " TYPE ", " DATE ", " TIME_WITH_STIMULATION ", " TIME_WITHOUT_STIMULATION ", " TIME_PAUSE ", " AVG_STIMULATION_AMPLITUDE ", " AVG_STEP_LENGTH ", " AVG_STEP_FREQUENCY ", " AVG_SPEED_WITHOUT_STIMULATION ", " AVG_SPEED_WITH_STIMULATION ", " TOTAL_DISTANCE ", " TOTAL_STIMULATION_DISTANCE
                  " ) VALUES (:Val1, :Val2, :Val3, :Val4, :Val5, :Val6, :Val7, :Val8, :Val9, :Val10, :Val11, :Val12)");
    query.bindValue(":Val1", data[0].toInt());
    query.bindValue(":Val2", data[1].toDateTime());
    query.bindValue(":Val3", data[2].toTime());
    query.bindValue(":Val4", data[3].toTime());
    query.bindValue(":Val5", data[4].toTime());
    query.bindValue(":Val6", data[5].toInt());
    query.bindValue(":Val7", data[6].toInt());
    query.bindValue(":Val8", data[7].toInt());
    query.bindValue(":Val9", data[8].toInt());
    query.bindValue(":Val10", data[9].toInt());
    query.bindValue(":Val11", data[10].toInt());
    query.bindValue(":Val12", data[11].toInt());

    // После чего выполняется запросом методом exec()
    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}

// Второй метод для вставки записи в базу данных
bool DataBase::inserIntoTable(const Training& t)
{
    // Запрос SQL формируется из QVariantList,
    // в который передаются данные для вставки в таблицу.
    QSqlQuery query;
    // В начале SQL запрос формируется с ключами,
    // которые потом связываются методом bindValue
    // для подстановки данных из QVariantList
    query.prepare("INSERT INTO " TABLE " ( " TYPE ", " DATE ", " TIME_WITH_STIMULATION ", " TIME_WITHOUT_STIMULATION ", " TIME_PAUSE ", " AVG_STIMULATION_AMPLITUDE ", " AVG_STEP_LENGTH ", " AVG_STEP_FREQUENCY ", " AVG_SPEED_WITHOUT_STIMULATION ", " AVG_SPEED_WITH_STIMULATION ", " TOTAL_DISTANCE ", " TOTAL_STIMULATION_DISTANCE
                  " ) VALUES (:Val1, :Val2, :Val3, :Val4, :Val5, :Val6, :Val7, :Val8, :Val9, :Val10, :Val11, :Val12)");
    query.bindValue(":Val1", t.type);
    query.bindValue(":Val2", t.date);
    query.bindValue(":Val3", t.timeWithStimulation);
    query.bindValue(":Val4", t.timeWithoutStimulation);
    query.bindValue(":Val5", t.timePause);
    query.bindValue(":Val6", t.avgStimulationAmplitude);
    query.bindValue(":Val7", t.avgStepLength);
    query.bindValue(":Val8", t.avgStepFrequency);
    query.bindValue(":Val9", t.avgSpeedWithoutStimulation);
    query.bindValue(":Val10", t.avgSpeedWithStimulation);
    query.bindValue(":Val11", t.totalDistance);
    query.bindValue(":Val12", t.totalStimulationDistance);

    // После чего выполняется запросом методом exec()
    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;

    //    QVariantList data;
    //    data.append(t.type);
    //    data.append(t.date);
    //    data.append(t.timeWithStimulation);
    //    data.append(t.timeWithoutStimulation);
    //    data.append(t.timePause);
    //    data.append(t.avgStimulationAmplitude);
    //    data.append(t.avgStepLength);
    //    data.append(t.avgStepFrequency);
    //    data.append(t.avgSpeedWithoutStimulation);
    //    data.append(t.avgSpeedWithStimulation);
    //    data.append(t.totalDistance);
    //    data.append(t.totalStimulationDistance);
    //    if (inserIntoTable(data)) {
    //        return true;
    //    }
    //    else {
    //        return false;
    //    }
}

bool DataBase::inserIntoTable()
{
    // Запрос SQL формируется из QVariantList,
    // в который передаются данные для вставки в таблицу.
    QSqlQuery query;
    // В начале SQL запрос формируется с ключами,
    // которые потом связываются методом bindValue
    // для подстановки данных из QVariantList
    query.prepare("INSERT INTO " TABLE " ( " TYPE ", " DATE ", " TIME_WITH_STIMULATION ", " TIME_WITHOUT_STIMULATION ", " TIME_PAUSE ", " AVG_STIMULATION_AMPLITUDE ", " AVG_STEP_LENGTH ", " AVG_STEP_FREQUENCY ", " AVG_SPEED_WITHOUT_STIMULATION ", " AVG_SPEED_WITH_STIMULATION ", " TOTAL_DISTANCE ", " TOTAL_STIMULATION_DISTANCE
                  " ) VALUES (:Val1, :Val2, :Val3, :Val4, :Val5, :Val6, :Val7, :Val8, :Val9, :Val10, :Val11, :Val12)");
    Training t;
    query.bindValue(":Val1", t.type);
    query.bindValue(":Val2", t.date);
    query.bindValue(":Val3", t.timeWithStimulation);
    query.bindValue(":Val4", t.timeWithoutStimulation);
    query.bindValue(":Val5", t.timePause);
    query.bindValue(":Val6", t.avgStimulationAmplitude);
    query.bindValue(":Val7", t.avgStepLength);
    query.bindValue(":Val8", t.avgStepFrequency);
    query.bindValue(":Val9", t.avgSpeedWithoutStimulation);
    query.bindValue(":Val10", t.avgSpeedWithStimulation);
    query.bindValue(":Val11", t.totalDistance);
    query.bindValue(":Val12", t.totalStimulationDistance);

    // После чего выполняется запросом методом exec()
    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
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
    if (!query.exec()) {
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else {
        return true;
    }
    return false;
}
