#include "main.h"

#include <QApplication>

#include "clipboard.h"


Main::Main()
    : window(),
      trSell(),
      blocker("unique_name_my_www")
{
    QObject::connect(this, &Main::needQuit, qApp, &QApplication::quit, Qt::QueuedConnection);
}

void Main::run() {
    if(!blocker.isThisProcessFirst()) {
        emit needQuit();
        return;
    }

    blocker.setCollback([this]() {
        this->translate();
    });

    //* Other options ...


    //************


    window.show();
    translate();
}

void Main::translate() {
    auto text_ptr = Clipboard::content();
    if(!text_ptr->isEmpty()) {
        window.updateSourceText(*text_ptr);
        text_ptr = trSell.translate(std::move(text_ptr));
        window.updateTranslatedText(*text_ptr);
    }
}



int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Main main{};
    main.run();

    return app.exec();
}
