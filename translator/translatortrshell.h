#ifndef TRANSLATORTRSHELL_H
#define TRANSLATORTRSHELL_H

#include <QStringList>

#include "i_translator.h"

class TranslatorTrShell : public ITranslator {
public:
    const QString PROGRAM;
    const int TIMEOUT_MS;

public:
    TranslatorTrShell();

    string_ptr translate(string_ptr src) override;


};

#endif // TRANSLATORTRSHELL_H
