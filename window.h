#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPlainTextEdit;

class Window : public QWidget {
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

public slots:
    void updateText(const QString &sourceText, const QString &translatedText);
    void updateSourceText(const QString &sourceText);
    void updateTranslatedText(const QString &translatedText);

private:
    void createLayout();
    void customizingWidgets();

private:
    QPlainTextEdit *sourceTextEdit;
    QPlainTextEdit *translatedTextEdit;

};

#endif // WINDOW_H
