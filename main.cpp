#include "main.h"

#include <QApplication>
#include <QDebug>

#include "clipboard.h"
#include "trcreator.h"


Main::Main()
    : blocker("unique_name_my_www"),
      window(nullptr),
      translator(nullptr)
{
    QObject::connect(this, &Main::needQuit, qApp, &QApplication::quit, Qt::QueuedConnection);
}

void Main::run() {
    if(!blocker.isThisProcessFirst()) {
        emit needQuit();
        return;
    }


    // Options ...

    translator = TrCreator::create();
    window = std::make_unique<Window>(*translator);

    blocker.setCollback([this]() {
        this->translateClipboard(this->window->getCurrentSrcLang(), this->window->getCurrentDstLang());
    });

    QObject::connect(window.get(), &Window::needTranslateSourceText, this, &Main::translate);
    QObject::connect(window.get(), &Window::needTranslateClipboard, this, &Main::translateClipboard);

    // .................


    window->show();
    translateClipboard(window->getCurrentSrcLang(), window->getCurrentDstLang());
}

void Main::translateClipboard(const QString &srcLang, const QString &dstLang) {
    auto text_ptr = Clipboard::content();
    if(!text_ptr->isEmpty()) {
        window->updateSourceText(*text_ptr);
        text_ptr = translator->translate(std::move(text_ptr), srcLang, dstLang);
        window->updateTranslatedText(*text_ptr);
    }
}

void Main::translate(QString source, const QString &srcLang, const QString &dstLang) {
    if(!source.isEmpty()) {

        // Выдержка из cppreference
        // ...................
        // The function is equivalent to:
        // unique_ptr<T>(new T(std::forward<Args>(args)...))
        // ...................
        // На сколько я понял тип ссылки rvalue(lvalue) определяется типом параметра

        auto text_ptr = translator->translate(std::make_unique<QString>(std::move(source)), srcLang, dstLang);

        window->updateTranslatedText(*text_ptr);
    }
}



int main(int argc, char **argv) {

    QApplication app(argc, argv);

    Main main{};
    main.run();

    return app.exec();
}
