#ifndef TEXTFORMATTAB_H
#define TEXTFORMATTAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class TextFormatTab : public QWidget
{
    Q_OBJECT
public:
    explicit TextFormatTab(QWidget *parent = 0);
signals:

    void onFontSizeChanged(int size);
public slots:

    void fontSizeChanged(QString text);

public slots:
};

#endif // TEXTFORMATTAB_H
