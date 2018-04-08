//#ifndef TRAININGS_H
//#define TRAININGS_H

//#include <QAbstractListModel>
//#include <QHash>
//#include <QDate>



//class TrainingModel : public QAbstractListModel {
//    Q_OBJECT
//public:
//    enum TrainingRoles {
//        typeRole = Qt::UserRole + 1,
//        dateRole,
//        timeWithStimulationRole,
//        timeWithoutStimulationRole,
//        timePauseRole,
//        avgStimulationAmplitudeRole,
//        avgStepLengthRole,
//        avgStepFrequencyRole,
//        avgSpeedWithoutStimulationRole,
//        avgSpeedWithStimulationRole,
//        totalDistanceRole,
//        totalStimulationDistanceRole,
//    };
//    TrainingModel(QObject* parent = 0);
//    void addTraining(const Training& training);
//    virtual int rowCount(const QModelIndex& parent) const;
//    virtual QVariant data(const QModelIndex& index, int role) const;
//    virtual QHash<int, QByteArray> roleNames() const;
//    virtual bool setData(const QModelIndex& index, const QVariant& value, int role);
//    virtual Qt::ItemFlags flags(const QModelIndex& index) const;
//    Q_INVOKABLE void add();

//private:
//    QList<Training> m_data;
//};

//#endif // TRAININGS_H
