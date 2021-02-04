#ifndef TRANSLATORTRSHELL_H
#define TRANSLATORTRSHELL_H

#include <QStringList>
#include <QMap>

#include "i_translator.h"

class TranslatorTrShell : public ITranslator {
public:
    const QString PROGRAM;
    const int TIMEOUT_MS;

public:
    TranslatorTrShell();

    string_ptr translate(string_ptr src) override;
    QStringList getSupportedLanguages() override;

private:
    QMap<QString, QString> supportedLanguages;

};

#endif // TRANSLATORTRSHELL_H
