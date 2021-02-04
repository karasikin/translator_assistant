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
    void translateClipboard(const QString &srcLang, const QString &dstLang);
    void translate(QString source, const QString &srdLang, const QString &dstLang);

signals:
    void needQuit();

private:
    Blocker blocker;

    std::unique_ptr<Window> window;
    std::unique_ptr<ITranslator> translator;
};

#endif // MAIN_H
