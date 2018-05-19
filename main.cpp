#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include <QQuickStyle>
#include <QThread>
#include <bt/devicefinder.h>
#include <bt/devicehandler.h>
#include <db/database.h>
#include <db/listmodel.h>
#include <QtPlugin>
#include "guiapplication.h"

int main(int argc, char* argv[])
{
    //Q_IMPORT_PLUGIN(qsqlite);
    GuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Bold.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Heavy.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Light.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Medium.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Roman.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Thin.ttf");

    DeviceHandler deviceHandler;
    DeviceFinder deviceFinder(&deviceHandler);
    Training training(&deviceHandler);

    //qmlRegisterUncreatableType<DeviceHandler>("Shared", 1, 0, "AddressType", "Enum is not a type");

    QFont fon("HelveticaNeueCyr");
    app.setFont(fon);

    DataBase database; // Подключаемся к базе данных (в конструкторе)
    ListModel model; // Объявляем и инициализируем модель данных

    app.connect(&training, &Training::addToDataBase, &database, &DataBase::inserIntoTable, Qt::DirectConnection);
    app.connect(&training, &Training::addToDataBase, &model, &ListModel::updateModel);

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("GUI", &app);
    // Обеспечиваем доступ к модели и классу для работы с базой данных из QML
    rootContext->setContextProperty("myModel", &model);
    rootContext->setContextProperty("database", &database);
    // bt
    //rootContext->setContextProperty("connectionHandler", &connectionHandler);
    rootContext->setContextProperty("deviceFinder", &deviceFinder);
    rootContext->setContextProperty("deviceHandler", &deviceHandler);
    rootContext->setContextProperty("training", &training);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // Connect QML signal to C++ slot
    //app.connect(qmlObj, SIGNAL(qmlSignal(QString)), cppObj, SLOT(cppSlot(QString)));
    // Connect C++ signal to QML slot
    //app.connect(deviceHandler, SIGNAL(aliveChanged(QVariant)), rootContext, SLOT(setAlive(QVariant)));

    return app.exec();
}
