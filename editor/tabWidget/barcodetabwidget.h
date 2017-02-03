#ifndef BARCODETABWIDGET_H
#define BARCODETABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class BarcodeTabWidget :public QWidget
{
    Q_OBJECT
public:
    BarcodeTabWidget(QWidget *parent=0);
    QPushButton *addQrBtn,*addEan13Btn,*addCode128Btn;

};

#endif // BARCODETABWIDGET_H
