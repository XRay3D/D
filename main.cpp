#include <QQuickStyle>
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "guiapplication.h"
#include "trainings.h"
int main(int argc, char* argv[])
{
    GuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //#if ios
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Bold.ttf");
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Heavy.ttf");
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Light.ttf");
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Medium.ttf");
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Roman.ttf");
    //    QFontDatabase::addApplicationFont("HelveticaNeueCyr-Thin.ttf");
    //#else
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Bold.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Heavy.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Light.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Medium.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Roman.ttf");
    QFontDatabase::addApplicationFont("qrc:/fonts/HelveticaNeueCyr-Thin.ttf");
    //#endif

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
