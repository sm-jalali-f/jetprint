#include "barcodetabwidget.h"

BarcodeTabWidget::BarcodeTabWidget(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("background-color:#E8E8E8");
    QHBoxLayout *mainLayout = new QHBoxLayout;

    addQrBtn = new QPushButton("    QR    ");
    addEan13Btn = new QPushButton("   EAN13   ");
    addCode128Btn = new QPushButton("   code128   ");

    addQrBtn->setFixedSize(128*1.3,128*1.3);
    addEan13Btn->setFixedSize(128*1.3,128*1.3);
    addCode128Btn->setFixedSize(128*1.3,128*1.3);
//    QPixmap qrPixmap(":/res/icons/ic_circle");
//    QPixmap ean13Pixmap(":/res/icons/ic_circle");
//    QPixmap code128Pixmap(":/res/icons/ic_circle");

//    QIcon qrIcon(qrPixmap);
//    QIcon ean13Icon(ean13Pixmap);
//    QIcon code128Icon(code128Pixmap);

//    addQrBtn->setIcon(circleIcon);
//    addEan13Btn->setIcon(circleIcon);
//    addCode128Btn->setIcon(circleIcon);

//    addQrBtn->setIconSize(pixmapCircle.rect().size()/2);
//    addEan13Btn->setIconSize(pixmapCircle.rect().size()/2);
//    addCode128Btn->setIconSize(pixmapCircle.rect().size()/2);

//    addQrBtn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);
//    addEan13Btn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);
//    addCode128Btn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);

//    addQrBtn->setStyleSheet("margin-left: 3px;margin-right:30px");
//    addEan13Btn->setStyleSheet("margin-left: 3px;margin-right:30px");
//    addCode128Btn->setStyleSheet("margin-left: 3px;margin-right:30px");

    mainLayout->addWidget(addQrBtn);
    mainLayout->addWidget(addEan13Btn);
    mainLayout->addWidget(addCode128Btn);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

