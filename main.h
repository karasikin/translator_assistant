#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <QString>
#include <QObject>

#include "window.h"
#include "blocker.h"
#include "i_translator.h"

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
    Blocker blocker;

    std::unique_ptr<ITranslator> translator;

    QStringList supportedLanguages;
};

#endif // MAIN_H
