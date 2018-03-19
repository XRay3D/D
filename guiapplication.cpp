#include "guiapplication.h"
#include <QDebug>

#define Q_OS_ANDROID

GuiApplication::GuiApplication(int& argc, char** argv, int)
    : QGuiApplication(argc, argv)
{
}

bool GuiApplication::notify(QObject* receiver, QEvent* event)
{
// to intercept android's back button
#ifdef Q_OS_ANDROID
    if (event->type() == QEvent::Close) {
        emit back();
        return false;
    }
    else {
        return QGuiApplication::notify(receiver, event);
    }
#else
    return QGuiApplication::notify(receiver, event);
#endif
}
