#ifndef INSERTTABWIDGET_H
#define INSERTTABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

class InsertTabWidget:public QWidget
{
    Q_OBJECT
public:
    InsertTabWidget(QWidget *parent=0);
    QPushButton *addTextBtn,*addImageBtn,*addCounterBtn,*addDateBtn,*addTimeBtn;
public slots:
    void TextBtnClicked();
    void ImageBtnClicked();
    void CounterBtnClicked();
    void DateBtnClicked();
    void TimeBtnClicked();

signals:
    void onTextBtnClicked();
    void onImageBtnClicked();
    void onCounterBtnClicked();
    void onDateBtnClicked();
    void onTimeBtnClicked();
};

#endif // INSERTTABWIDGET_H
