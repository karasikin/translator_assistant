#include "translatortrshell.h"

#include <QProcess>

TranslatorTrShell::TranslatorTrShell() {}

string_ptr TranslatorTrShell::translate(string_ptr src) {
    QProcess trShell;
    QString response{};
    QStringList args{};

    args << "-no-ansi" << *src;
    if(src->contains(' ')) {
        args << "-brief";
    }

    trShell.setReadChannel(QProcess::ProcessChannel::StandardOutput);
    trShell.start(PROGRAM, args, QIODevice::ReadOnly);

    if(trShell.waitForReadyRead(TIMEOUT_MS)) {
        response = QString(trShell.readAllStandardOutput());
    }

    trShell.close();

    return std::make_unique<QString>(std::move(response));
}
