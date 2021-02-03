#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <QString>
#include <QObject>

#include "window.h"
#include "translatortrshell.h"
#include "blocker.h"

class Window;

using string_ptr = std::unique_ptr<QString>;

class Main : public QObject {

Q_OBJECT

public:
    Main();

    void run();

private slots:
    void translate();

signals:
    void needQuit();

private:
    Window window;
    TranslatorTrShell trSell;
    Blocker blocker;

};

#endif // MAIN_H
