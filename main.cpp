#include "main.h"

#include <QApplication>

#include "clipboard.h"


Main::Main()
    : window(),
      trShell(),
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
        this->translateClipboard();
    });

    // Other options ...

    QObject::connect(&window, &Window::needTranslateSourceText, this, &Main::translate);
    QObject::connect(&window, &Window::needTranslateClipboard, this, &Main::translateClipboard);

    // .................


    window.show();
    translateClipboard();
}

void Main::translateClipboard() {
    auto text_ptr = Clipboard::content();
    if(!text_ptr->isEmpty()) {
        window.updateSourceText(*text_ptr);
        text_ptr = trShell.translate(std::move(text_ptr));
        window.updateTranslatedText(*text_ptr);
    }
}

void Main::translate(QString source) {
    if(!source.isEmpty()) {

        // Выдержка из cppreference
        // ...................
        // The function is equivalent to:
        // unique_ptr<T>(new T(std::forward<Args>(args)...))
        // ...................
        // На сколько я понял тип ссылки rvalue(lvalue) определяется типом параметра

        auto text_ptr = trShell.translate(std::make_unique<QString>(std::move(source)));
        window.updateTranslatedText(*text_ptr);
    }
}



int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Main main{};
    main.run();

    return app.exec();
}
