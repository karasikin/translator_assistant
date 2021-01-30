#include "clipboard.h"

#include <QApplication>
#include <QClipboard>

Clipboard::Clipboard() {}

std::unique_ptr<QString> Clipboard::content() {
    auto clipboard = QApplication::clipboard();

    auto mode = clipboard->supportsSelection() ? QClipboard::Mode::Selection : QClipboard::Mode::Clipboard;

    auto text = clipboard->text(mode);

    if(mode == QClipboard::Mode::Selection && text.isEmpty()) {
        text = clipboard->text(QClipboard::Mode::Clipboard);
    }

    return std::make_unique<QString>(std::move(text));
}
