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
};

#endif // INSERTTABWIDGET_H
