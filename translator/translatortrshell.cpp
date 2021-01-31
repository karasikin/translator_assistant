#include "translatortrshell.h"

#include <QProcess>

TranslatorTrShell::TranslatorTrShell() {}

string_ptr TranslatorTrShell::translate(string_ptr src) {
    QProcess trShell;

    trShell.setReadChannel(QProcess::ProcessChannel::StandardOutput);

    trShell.start(PROGRAM, QStringList() << *src, QIODevice::ReadOnly);

    if(trShell.waitForReadyRead(TIMEOUT_MS)) {
        return std::make_unique<QString>(QString(trShell.readAllStandardOutput()));
    } else {
        return std::make_unique<QString>();
    }
}
