#ifndef FORMATTABWIDGET_H
#define FORMATTABWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QValidator>

class FormatTabWidget:public QWidget
{
    Q_OBJECT
public:
    FormatTabWidget(QWidget *parent=0);
signals:

    void onFontSizeChanged(int size);
public slots:

    void fontSizeChanged(QString text);



};

#endif // FORMATTABWIDGET_H
