#include "translatortrshell.h"

#include <QProcess>
#include <QDebug>


TranslatorTrShell::TranslatorTrShell()
    : PROGRAM("/usr/bin/trans"),
      TIMEOUT_MS(5000),
      defaultSrcLang("Englesh"),
      defaultDstLang("Russian")
{

    // Заприосить список языков и поместить в supportedLanguages!!!

    supportedLanguages = {
        {defaultSrcLang, "en"},
        {defaultDstLang, "ru"}
    };
}

string_ptr TranslatorTrShell::translate(string_ptr src, const QString &srcLang, const QString &dstLang) {
    QProcess trShell;
    QString response;
    QStringList args;

    args << "-no-ansi";

    if(src->contains(' ')) {
        args << "-brief";
    }

    // Надо проверять !!!
    args << (supportedLanguages.contains(srcLang) ? supportedLanguages[srcLang] : supportedLanguages[defaultSrcLang])
                + QString(":")
                + (supportedLanguages.contains(dstLang) ? supportedLanguages[dstLang] : supportedLanguages[defaultDstLang]);
    args << *src;

    trShell.setReadChannel(QProcess::ProcessChannel::StandardOutput);
    trShell.start(PROGRAM, args, QIODevice::ReadOnly);

    if(trShell.waitForReadyRead(TIMEOUT_MS)) {
        response = QString(trShell.readAllStandardOutput());
    }

    trShell.close();

    return std::make_unique<QString>(std::move(response));
}

QStringList TranslatorTrShell::getSupportedLanguages() const{
    return supportedLanguages.keys();
}

const QString &TranslatorTrShell::getDefaultSourceLanguage() const {
    return defaultSrcLang;
}

const QString &TranslatorTrShell::getDefaultDestinationLanguage() const {
    return defaultDstLang;
}
