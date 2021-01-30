#include "clipboard.h"

#include <QApplication>
#include <QClipboard>

Clipboard::Clipboard() {

}

std::unique_ptr<QString> Clipboard::content() {
    auto clipboard = QApplication::clipboard();

    return std::make_unique<QString>(clipboard->text());
}
