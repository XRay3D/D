#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include <QGuiApplication>

class GuiApplication : public QGuiApplication {
    Q_OBJECT
public:
#ifdef Q_QDOC
    explicit GuiApplication(int& argc, char** argv);
#else
    explicit GuiApplication(int& argc, char** argv, int = ApplicationFlags);
#endif

    bool notify(QObject* receiver, QEvent* event);
signals:
    void back();
};

#endif // GUIAPPLICATION_H
