#include <iostream>

#include <QApplication>
#include <QDebug>

#include "clipboard.h"
#include "translatortrshell.h"
#include "window.h"
#include "blocker.h"

int main(int argc, char *argv[]) {
    Blocker blocker{"trAssistant"};
    if(!blocker.isThisProcessFirst()) {
        return 0;
    }

    QApplication app{argc, argv};

    Window window{};
    TranslatorTrShell trShell{};

    auto clipboard_content = Clipboard::content();
    window.updateSourceText(*clipboard_content);

    auto translated_content = trShell.translate(std::move(clipboard_content));
    window.updateTranslatedText(*translated_content);

    qDebug() << *translated_content;

    window.show();

    return app.exec();
}
