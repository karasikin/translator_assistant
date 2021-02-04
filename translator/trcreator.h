#ifndef TRCREATOR_H
#define TRCREATOR_H

#include "translatortrshell.h"

class TrCreator {
public:
    static std::unique_ptr<ITranslator> create() {
        return std::make_unique<TranslatorTrShell>();
    }
};

#endif // TRCREATOR_H
