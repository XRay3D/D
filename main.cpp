#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <bt/connectionhandler.h>
#include <bt/devicefinder.h>
#include <bt/devicehandler.h>
#include <db/database.h>
#include <db/listmodel.h>

#include "guiapplication.h"
#include "trainings.h"

int main(int argc, char* argv[])
{
    GuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Bold.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Heavy.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Light.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Medium.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Roman.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Thin.ttf");

    ConnectionHandler connectionHandler;
    DeviceHandler deviceHandler;
    DeviceFinder deviceFinder(&deviceHandler);
    qmlRegisterUncreatableType<DeviceHandler>("Shared", 1, 0, "AddressType", "Enum is not a type");

    //    TrainingModel model;
    QFont fon("HelveticaNeueCyr");
    app.setFont(fon);

    // Подключаемся к базе данных
    DataBase database;
    database.connectToDataBase();
    // Объявляем и инициализируем модель данных
    ListModel* model = new ListModel();

    //    QQuickStyle::setStyle("Material");
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("GUI", &app);
    // rootContext->setContextProperty("trainingModel", &model);
    // Обеспечиваем доступ к модели и классу для работы с базой данных из QML
    rootContext->setContextProperty("myModel", model);
    rootContext->setContextProperty("database", &database);
    // bt
    rootContext->setContextProperty("connectionHandler", &connectionHandler);
    rootContext->setContextProperty("deviceFinder", &deviceFinder);
    rootContext->setContextProperty("deviceHandler", &deviceHandler);



    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
