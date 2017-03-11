#ifndef BARCODETABWIDGET_H
#define BARCODETABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <paintItems/barcodeitem.h>
class BarcodeTabWidget :public QWidget
{
    Q_OBJECT
public:
    BarcodeTabWidget(QWidget *parent=0);
    QPushButton *addQrBtn,*addEan13Btn,*addCode128Btn;
signals:
    void qrClicked();
    void ean13Clicked();
    void code128Clicked();
public slots:
    void qrBtnClicked();
    void ean13BtnClicked();
    void code128BtnClicked();
};

#endif // BARCODETABWIDGET_H
