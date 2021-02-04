#ifndef TRANSLATORTRSHELL_H
#define TRANSLATORTRSHELL_H

#include <QStringList>
#include <QMap>

#include "i_translator.h"

class TranslatorTrShell : public ITranslator {
public:
    const QString PROGRAM;
    const int TIMEOUT_MS;
    const QString defaultSrcLang;
    const QString defaultDstLang;

public:
    TranslatorTrShell();

    string_ptr translate(string_ptr src, const QString &srcLang, const QString &dstLang) override;
    QStringList getSupportedLanguages() const override;
    const QString &getDefaultSourceLanguage() const override;
    const QString &getDefaultDestinationLanguage() const override;

private:
    QMap<QString, QString> supportedLanguages;

};

#endif // TRANSLATORTRSHELL_H
