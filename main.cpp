#include <QApplication>
#include <QDebug>

#include "clipboard.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try{
        qDebug() << *Clipboard::content();
    } catch (...) {
        qDebug() << "Что-то пошло не так";
    }

    return app.exec();
}
