#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <memory>
#include <QString>

class Clipboard {

public:

    Clipboard();

    static std::unique_ptr<QString> content();
};

#endif // CLIPBOARD_H
