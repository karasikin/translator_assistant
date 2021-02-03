#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPlainTextEdit;
class QComboBox;
class QPushButton;

class Window : public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

public slots:
    void updateText(const QString &sourceText, const QString &translatedText);
    void updateSourceText(const QString &sourceText);
    void updateTranslatedText(const QString &translatedText);

signals:
    void needTranslateClipboard();
    void needTranslateSourceText(QString);

private:
    void createLayout();
    void customizingWidgets();

private slots:
    void onTranslateBtnClicked();
    void onSourceEditChanged();

private:
    bool isSourceEditChanged;

    QPlainTextEdit *sourceTextEdit;
    QPlainTextEdit *translatedTextEdit;

    QComboBox *srcLanguageComboBox;
    QComboBox *destLanguageComboBox;

    QPushButton *translatePushButton;

};

#endif // WINDOW_H
