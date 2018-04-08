#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSqlQueryModel>

class ListModel : public QSqlQueryModel {
    Q_OBJECT
public:
    // Перечисляем все роли, которые будут использоваться в TableView
    // Как видите, они должны лежать в памяти выше параметра Qt::UserRole
    // Связано с тем, что информация ниже этого адреса не для кастомизаций
    enum TrainingRoles {
        idRole = Qt::UserRole , // id
        typeRole,
        dateRole,
        timeWithStimulationRole,
        timeWithoutStimulationRole,
        timePauseRole,
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

protected:
    // хешированная таблица ролей для колонок.
    // Метод используется в дебрях базового класса QAbstractItemModel,
    // от которого наследован класс QSqlQueryModel
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void updateModel();
    int getId(int row);
};

#endif // LISTMODEL_H