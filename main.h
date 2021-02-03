#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <QString>
#include <QObject>

#include "window.h"
#include "translatortrshell.h"
#include "blocker.h"

using string_ptr = std::unique_ptr<QString>;

class Main : public QObject {

Q_OBJECT

public:
    Main();

    void run();

private slots:
    void translateClipboard();
    void translate(QString source);

signals:
    void needQuit();

private:
    Window window;
    TranslatorTrShell trShell;
    Blocker blocker;

};

#endif // MAIN_H
