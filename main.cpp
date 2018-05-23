#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <bt/devicefinder.h>
#include <bt/devicehandler.h>
#include <db/database.h>
#include <db/listmodel.h>

#include "guiapplication.h"

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

    DeviceHandler deviceHandler; // = new DeviceHandler();

    //    QThread thread;
    //    deviceHandler->moveToThread(&thread);
    //    thread.connect(&thread, &QThread::finished, deviceHandler, &QObject::deleteLater);
    //    app.connect(&engine, &QQmlApplicationEngine::quit, &thread, &QThread::quit);
    //    app.connect(&engine, &QQmlApplicationEngine::quit, &thread, &QThread::quit);
    //    thread.start();

    DeviceFinder deviceFinder(&deviceHandler);
    Training training(&deviceHandler);

    //qmlRegisterUncreatableType<DeviceHandler>("Shared", 1, 0, "AddressType", "Enum is not a type");

    QFont fon("HelveticaNeueCyr");
    app.setFont(fon);

    DataBase database; // Подключаемся к базе данных (в конструкторе)
    ListModel model; // Объявляем и инициализируем модель данных

    app.connect(&training, &Training::addToDataBase, &database, &DataBase::inserIntoTable, Qt::DirectConnection);
    app.connect(&training, &Training::addToDataBase, [&]() { model.updateModel(); });

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("GUI", &app);
    // Обеспечиваем доступ к модели и классу для работы с базой данных из QML
    rootContext->setContextProperty("myModel", &model);
    rootContext->setContextProperty("database", &database);
    // bt
    rootContext->setContextProperty("deviceFinder", &deviceFinder);
    rootContext->setContextProperty("deviceHandler", &deviceHandler);
    rootContext->setContextProperty("training", &training);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [&deviceHandler](QObject* object, const QUrl& url) {
        qDebug() << object, url;
        if (object->objectName() == "window") {
            qDebug() << QObject::connect(object, SIGNAL(powerChanged(int)), &deviceHandler, SLOT(setVoltage(int)), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(durationChanged(int)), &deviceHandler, SLOT(setDuration(int)), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(impulse()), &deviceHandler, SLOT(impulse()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(delayChanged(int)), &deviceHandler, SLOT(setDelay(int)), Qt::QueuedConnection);
        }
    });

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
