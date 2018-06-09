#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <bt/devicefinder.h>
#include <bt/devicehandler.h>
#include <db/database.h>
#include <db/listmodel.h>

#include "guiapplication.h"
#include "networkcontroller.h"
#include "notificationclient.h"
#include "shareutils/applicationui.h"
#include "vibrationclient.h"

#if defined(Q_OS_IOS)
#include "ios/QtAppDelegate-C-Interface.h"
#include <qtquick2applicationviewer.h>
#endif

int main(int argc, char* argv[])
{
    //QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    GuiApplication app(argc, argv);
#if defined(Q_OS_IOS)
    //QtAppDelegateInitialize();
    //QtQuick2ApplicationViewer engine;
#else
#endif
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
    NetworkController networkController;

    //    NotificationClient notificationClient;

    NotificationClient* notificationClient = new NotificationClient(&engine);
    Q_UNUSED(notificationClient)
    VibrationClient* vibrationClient = new VibrationClient(&engine);

    QObject::connect(&training, &Training::addToDataBase, &database, &DataBase::inserIntoTable, Qt::DirectConnection);
    QObject::connect(&training, &Training::addToDataBase, [&]() { model.updateModel(); });

    ApplicationUI appui;

    // from QML we have access to ApplicationUI as myApp

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("GUI", &app);
    rootContext->setContextProperty("myApp", &appui);
    appui.addContextProperty(rootContext);

    rootContext->setContextProperty("vibration", vibrationClient);
    // Обеспечиваем доступ к модели и классу для работы с базой данных из QML
    rootContext->setContextProperty("myModel", &model);
    rootContext->setContextProperty("database", &database);
    // bt
    rootContext->setContextProperty("deviceFinder", &deviceFinder);
    rootContext->setContextProperty("deviceHandler", &deviceHandler);
    rootContext->setContextProperty("training", &training);
    rootContext->setContextProperty("networkController", &networkController);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [&deviceHandler, &training](QObject* object, const QUrl& url) {
        qDebug() << object << url;
        if (object->objectName() == "window") {
            qDebug() << QObject::connect(object, SIGNAL(powerChanged(int)), &deviceHandler, SLOT(setVoltage(int)), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(durationChanged(int)), &deviceHandler, SLOT(setDuration(int)), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(impulse()), &deviceHandler, SLOT(impulse()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(delayChanged(int)), &deviceHandler, SLOT(setDelay(int)), Qt::QueuedConnection);

            qDebug() << QObject::connect(object, SIGNAL(pause()), &training, SLOT(pause()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(prepare()), &training, SLOT(prepare()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(resume()), &training, SLOT(resume()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(start()), &training, SLOT(start()), Qt::QueuedConnection);
            qDebug() << QObject::connect(object, SIGNAL(stop()), &training, SLOT(stop()), Qt::DirectConnection);
        }
    });
#if defined(Q_OS_ANDROID)
    QObject::connect(&app, SIGNAL(applicationStateChanged(Qt::ApplicationState)), &appui, SLOT(onApplicationStateChanged(Qt::ApplicationState)));
#endif
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    //QTimer::singleShot(100,[&engine](){engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));});
    return app.exec();
}
