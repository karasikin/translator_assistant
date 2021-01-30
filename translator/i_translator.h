#ifndef I_TRANSLATOR_H
#define I_TRANSLATOR_H

#include <memory>
#include <QString>

using string_ptr = std::unique_ptr<QString>;

class ITranslator {
public:
    virtual string_ptr translate(string_ptr src) = 0;  // Подумать над интерфейсом функции!!!
    virtual ~ITranslator() {}
};

#endif // I_TRANSLATOR_H
