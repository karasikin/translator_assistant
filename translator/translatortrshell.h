#ifndef TRANSLATORTRSHELL_H
#define TRANSLATORTRSHELL_H

#include "i_translator.h"

class TranslatorTrShell : public ITranslator {
public:
    const QString PROGRAM = "/usr/bin/trans";
    const int TIMEOUT_MS = 5000;

public:
    TranslatorTrShell();

    string_ptr translate(string_ptr src) override;
};

#endif // TRANSLATORTRSHELL_H
