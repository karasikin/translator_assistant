#include "window.h"

#include <QPlainTextEdit>
#include <QLabel>
#include <QGridLayout>


Window::Window(QWidget *parent)
    : QWidget(parent),
      sourceTextEdit(new QPlainTextEdit{}),
      translatedTextEdit(new QPlainTextEdit{})
{
    customizingWidgets();
    createLayout();
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
}

void Window::customizingWidgets() {
    translatedTextEdit->setMinimumWidth(150);
    translatedTextEdit->setMinimumHeight(200);

    translatedTextEdit->setReadOnly(true);

    sourceTextEdit->setMinimumWidth(150);
    sourceTextEdit->setMinimumHeight(200);
}

void Window::createLayout() {
    auto layout = new QGridLayout{};

    layout->addWidget(sourceTextEdit, 0, 0, 10, 10);
    layout->addWidget(translatedTextEdit, 0, 11, 10, 10);

    setLayout(layout);
}
