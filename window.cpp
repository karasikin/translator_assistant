#include "window.h"

#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

#include "i_translator.h"

#include <QDebug>

Window::Window(const ITranslator &translator, QWidget *parent)
  : QWidget(parent),
    isSourceEditChanged(false),
    sourceTextEdit(new QPlainTextEdit),
    translatedTextEdit(new QPlainTextEdit),
    srcLanguageComboBox(new QComboBox),
    destLanguageComboBox(new QComboBox),
    translatePushButton(new QPushButton{"&Translate"}),
    exchangeLanguageButton(new QPushButton)
{
    auto supportedLanguages = translator.getSupportedLanguages();
    srcLanguageComboBox->addItems(supportedLanguages);
    destLanguageComboBox->addItems(supportedLanguages);
    srcLanguageComboBox->setCurrentText(translator.getDefaultSourceLanguage());
    destLanguageComboBox->setCurrentText(translator.getDefaultDestinationLanguage());

    currentSrcLang = srcLanguageComboBox->currentText();
    currentDstLang = destLanguageComboBox->currentText();

    customizingWidgets();
    createLayout();

    QObject::connect(translatePushButton, &QPushButton::clicked, this, &Window::onTranslateBtnClicked);
    QObject::connect(exchangeLanguageButton, &QPushButton::clicked, this, &Window::onExchangeLanguageBtnClicked);
    QObject::connect(sourceTextEdit, &QPlainTextEdit::textChanged, this, &Window::onSourceEditChanged);
    QObject::connect(srcLanguageComboBox, &QComboBox::currentTextChanged, this, &Window::onSrcLangChanged);
    QObject::connect(destLanguageComboBox, &QComboBox::currentTextChanged, this, &Window::onDstLangChanged);

}

const QString &Window::getCurrentSrcLang() const {
    return currentSrcLang;
}

const QString &Window::getCurrentDstLang() const {
    return currentDstLang;
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

    layout->addWidget(srcLanguageComboBox, 0, 0, Qt::AlignLeft);
    layout->addWidget(destLanguageComboBox, 0, 20, Qt::AlignRight);
    layout->addWidget(exchangeLanguageButton, 0, 9, 1, 3);
    layout->addWidget(sourceTextEdit, 1, 0, 10, 10);
    layout->addWidget(translatedTextEdit, 1, 11, 10, 10);
    layout->addWidget(translatePushButton, 11, 0);

    setLayout(layout);
}

void Window::onTranslateBtnClicked() {
    if(!isSourceEditChanged) {
        emit needTranslateClipboard(currentSrcLang, currentDstLang);
        return;
    }

    emit needTranslateSourceText(sourceTextEdit->toPlainText(), currentSrcLang, currentDstLang);
}

void Window::onExchangeLanguageBtnClicked() {
    QString tmp = std::move(currentDstLang);
    currentDstLang = std::move(currentSrcLang);
    currentSrcLang = std::move(tmp);

    srcLanguageComboBox->setCurrentText(currentSrcLang);
    destLanguageComboBox->setCurrentText(currentDstLang);

    tmp = translatedTextEdit->toPlainText();
    translatedTextEdit->setPlainText(sourceTextEdit->toPlainText());
    sourceTextEdit->setPlainText(tmp);

    emit needTranslateSourceText(tmp, currentSrcLang, currentDstLang);
}

void Window::onSourceEditChanged() {
    isSourceEditChanged = true;
}

void Window::onSrcLangChanged(const QString &text) {
    currentSrcLang = text;
    isSourceEditChanged = true;
}

void Window::onDstLangChanged(const QString &text) {
    currentDstLang = text;
    isSourceEditChanged = true;
}
