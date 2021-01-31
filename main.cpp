#include <iostream>

#include <QApplication>
#include <QDebug>

#include "clipboard.h"
#include "translatortrshell.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try{
        auto clipboard_content = Clipboard::content();
        TranslatorTrShell trShell;
        auto translated_content = trShell.translate(std::move(clipboard_content));
        std::cout << translated_content->toStdString();
    } catch (...) {
        qDebug() << "Что-то пошло не так";
    }

    return app.exec();
}
