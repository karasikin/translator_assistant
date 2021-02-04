#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPlainTextEdit;
class QComboBox;
class QPushButton;
class ITranslator;

class Window : public QWidget {
    Q_OBJECT

public:
    explicit Window(const ITranslator &translator, QWidget *parent = nullptr);

    const QString &getCurrentSrcLang() const;
    const QString &getCurrentDstLang() const;

public slots:
    void updateText(const QString &sourceText, const QString &translatedText);
    void updateSourceText(const QString &sourceText);
    void updateTranslatedText(const QString &translatedText);

signals:
    void needTranslateClipboard(const QString &srcLang, const QString &dstLang);
    void needTranslateSourceText(QString text, const QString &srcLang, const QString &destLang);

private:
    void createLayout();
    void customizingWidgets();

private slots:
    void onTranslateBtnClicked();
    void onExchangeLanguageBtnClicked();
    void onSourceEditChanged();

    void onSrcLangChanged(const QString &text);
    void onDstLangChanged(const QString &text);

private:
    bool isSourceEditChanged;

    QString currentSrcLang;
    QString currentDstLang;

    QPlainTextEdit *sourceTextEdit;
    QPlainTextEdit *translatedTextEdit;

    QComboBox *srcLanguageComboBox;
    QComboBox *destLanguageComboBox;

    QPushButton *translatePushButton;
    QPushButton *exchangeLanguageButton;

};

#endif // WINDOW_H
