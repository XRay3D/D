#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include "training.h"

class ListModel : public QSqlQueryModel {
    Q_OBJECT
public:
    // Перечисляем все роли, которые будут использоваться в TableView
    // Как видите, они должны лежать в памяти выше параметра Qt::UserRole
    // Связано с тем, что информация ниже этого адреса не для кастомизаций
    enum TrainingRoles {
        idRole = Qt::UserRole, // id
        typeRole,
        dateRole,
        timeWithStimulationRole,
        timeWithoutStimulationRole,
        timeStimulationRole,
        timeRestRole,
        avgStimulationAmplitudeRole,
        avgStepLengthRole,
        avgStepFrequencyRole,
        avgSpeedWithoutStimulationRole,
        avgSpeedWithStimulationRole,
        totalDistanceRole,
        totalStimulationDistanceRole,
    };

    // объявляем конструктор класса
    explicit ListModel(QObject* parent = 0);

    // Переопределяем метод, который будет возвращать данные
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    inline QVariant data2(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    // хешированная таблица ролей для колонок.
    // Метод используется в дебрях базового класса QAbstractItemModel,
    // от которого наследован класс QSqlQueryModel
    // Метод для получения имен ролей через хешированную таблицу.
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    int count();
    int getId(int row);
    void updateModel();

    int getType(int row);
    QString getDate(int row);
    QString getTrainingTime(int row);
    QString getTimeWithStimulation(int row);
    QString getTimeWithoutStimulation(int row);
    QString getTimeStimulation(int row);
    QString getTimeRest(int row);
    QString getAvgStimulationAmplitude(int row);
    QString getAvgStepLength(int row);
    QString getAvgStepFrequency(int row);
    QString getAvgSpeedWithoutStimulation(int row);
    QString getAvgSpeedWithStimulation(int row);
    QString getTotalDistance(int row);
    QString getTotalStimulationDistance(int row);
};

#endif // LISTMODEL_H
