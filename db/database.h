#ifndef DATABASE_H
#define DATABASE_H

#include "training.h"

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME "NameDataBase"
#define DATABASE_NAME "/Trainings.db"

#define TABLE "TrainingTable" // Название таблицы

#define TYPE "Type"
#define DATE "Date"
#define TIME_WITH_STIMULATION "TimeWithStimulation"
#define TIME_WITHOUT_STIMULATION "TimeWithoutStimulation"
#define TIME_STIMULATION "TimeStimulation"
#define TIME_REST "TimeRest"
#define AVG_STIMULATION_AMPLITUDE "AvgStimulationAmplitude"
#define AVG_STEP_LENGTH "AvgStepLength"
#define AVG_STEP_FREQUENCY "AvgStepFrequency"
#define AVG_SPEED_WITHOUT_STIMULATION "AvgSpeedWithoutStimulation"
#define AVG_SPEED_WITH_STIMULATION "AvgSpeedWithStimulation"
#define TOTAL_DISTANCE "TotalDistance"
#define TOTAL_STIMULATION_DISTANCE "TotalStimulationDistance"

// Первая колонка содержит Autoincrement ID

class DataBase : public QObject {
    Q_OBJECT
public:
    explicit DataBase(QObject* parent = nullptr);
    ~DataBase();
    // Методы для непосредственной работы с классом
    // Подключение к базе данных и вставка записей в таблицу
    void connectToDataBase();

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase db;

private:
    // Внутренние методы для работы с базой данных
    bool openDataBase(); // Открытие базы данных
    bool restoreDataBase(); // Восстановление базы данных
    void closeDataBase(); // Закрытие базы данных
    bool createTable(); // Создание базы таблицы в базе данных

public slots:
    //    bool inserIntoTable(const QVariantList& data); // Добавление записей в таблицу
    //    bool inserIntoTable(const Training& t);
    bool inserIntoTable(Training* t);
    bool removeRecord(const int id); // Удаление записи из таблицы по её id
};

#endif // DATABASE_H
