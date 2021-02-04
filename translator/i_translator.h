#ifndef I_TRANSLATOR_H
#define I_TRANSLATOR_H

#include <memory>
#include <QString>

using string_ptr = std::unique_ptr<QString>;

class ITranslator {
public:
    virtual string_ptr translate(string_ptr src, const QString &srcLang, const QString &dstLang) = 0;  // Подумать над интерфейсом функции!!!
    virtual QStringList getSupportedLanguages() const = 0;
    virtual const QString &getDefaultSourceLanguage() const = 0;
    virtual const QString &getDefaultDestinationLanguage() const = 0;
    virtual ~ITranslator() {}
};

#endif // I_TRANSLATOR_H
