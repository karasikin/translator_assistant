#include "window.h"

#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

#include <QDebug>

Window::Window(QWidget *parent)
    : QWidget(parent),
      isSourceEditChanged(false),
      sourceTextEdit(new QPlainTextEdit),
      translatedTextEdit(new QPlainTextEdit),
      srcLanguageComboBox(new QComboBox),
      destLanguageComboBox(new QComboBox),
      translatePushButton(new QPushButton{"Translate"})
{
    customizingWidgets();
    createLayout();

    QObject::connect(translatePushButton, &QPushButton::clicked, this, &Window::onTranslateBtnClicked);
    QObject::connect(sourceTextEdit, &QPlainTextEdit::textChanged, this, &Window::onSourceEditChanged);
}

void Window::updateText(const QString &sourceText, const QString &translatedText) {
    updateSourceText(sourceText);
    updateTranslatedText(translatedText);
}

void Window::updateSourceText(const QString &sourceText) {
    sourceTextEdit->setPlainText(sourceText);
}

void Window::updateTranslatedText(const QString &translatedText) {
    translatedTextEdit->setPlainText(translatedText);

    // Я считаю, что если перевод произошел, то будет вызван updateTranslatedText,
    // и в этот момент необходимо делать откат isSourceEditChanged
    isSourceEditChanged = false;
}

void Window::customizingWidgets() {
    translatedTextEdit->setMinimumWidth(150);
    translatedTextEdit->setMinimumHeight(200);

    translatedTextEdit->setReadOnly(true);

    sourceTextEdit->setMinimumWidth(150);
    sourceTextEdit->setMinimumHeight(200);
}

void Window::createLayout() {
    auto layout = new QGridLayout;

    layout->addWidget(srcLanguageComboBox, 0, 0);
    layout->addWidget(destLanguageComboBox, 0, 10);
    layout->addWidget(sourceTextEdit, 1, 0, 10, 10);
    layout->addWidget(translatedTextEdit, 1, 10, 10, 10);
    layout->addWidget(translatePushButton, 11, 0);

    setLayout(layout);
}

void Window::onTranslateBtnClicked() {
    if(!isSourceEditChanged) {
        emit needTranslateClipboard();
        return;
    }

    emit needTranslateSourceText(sourceTextEdit->toPlainText());
}

void Window::onSourceEditChanged() {
    isSourceEditChanged = true;
}
