//#include <QGuiApplication>
//#include <QKeyEvent>
//#include <QQmlApplicationEngine>
#include <QQuickStyle>

//int main(int argc, char* argv[])
//{
// QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

// QGuiApplication app(argc, argv);

// QQuickStyle::setStyle("Material");

// QQmlApplicationEngine engine;
// engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
// if (engine.rootObjects().isEmpty())
// return -1;

// return app.exec();
//}
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "guiapplication.h"
#include "trainings.h"
int main(int argc, char* argv[])
{
    // QGuiApplication app(argc, argv);
    GuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Bold.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Heavy.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Light.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Medium.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Roman.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Thin.ttf");

    TrainingModel model;
    QFont fon("HelveticaNeueCyr");
    app.setFont(fon);

//    QQuickStyle::setStyle("Material");
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("GUI", &app);
    rootContext->setContextProperty("trainingModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
