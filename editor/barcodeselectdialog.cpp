#include "barcodeselectdialog.h"
#include <QDebug>
BarcodeSelectDialog::BarcodeSelectDialog(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("select your barcode");

    imageScene = new QGraphicsScene();
//    imageScene->setSceneRect(0,0,1000,400);
    imageView = new QGraphicsView(imageScene);
    imageView->setFixedHeight(400);
    imageView->setFixedWidth(1000);
    imageView->setStyleSheet("margin-left:100;margin-right:100;");
//    imageView->fitInView(0, 0, 1000, 400, Qt::KeepAspectRatio);


    this->setFixedWidth(1200);
    this->setFixedHeight(900);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(imageView);
    this->barcodeTypeCombo = new QComboBox;
    this->barcodeTypeCombo->addItem("QRCODE");
    this->barcodeTypeCombo->addItem("EAN13");
    this->barcodeTypeCombo->addItem("CODE128");

    mainLayout->addWidget(barcodeTypeCombo);
    QHBoxLayout *sizeLayout = new QHBoxLayout;
    barcodeWidthEt = new QLineEdit();
    barcodeHeightEt = new QLineEdit;
    barcodeHeightEt->setValidator( new QIntValidator(50, 300, this));
    barcodeWidthEt->setValidator( new QIntValidator(50, 800, this));
    barcodeWidthEt->setText("100");
    barcodeHeightEt->setText("100");
    QLabel *widthLabel = new QLabel("Width: ");
    QLabel *heightLabel = new QLabel("Height: ");
    sizeLayout->addWidget(widthLabel);
    sizeLayout->addWidget(barcodeWidthEt);
    sizeLayout->addWidget(heightLabel);
    sizeLayout->addWidget(barcodeHeightEt);
    mainLayout->addLayout(sizeLayout);
    QLabel *label = new QLabel("Data to Encode:");
    mainLayout->addWidget(label);
    QHBoxLayout *hbox = new QHBoxLayout;
    encodeDataEt = new QLineEdit;
    this->generateBtn = new QPushButton("Generate");
    hbox->addWidget(encodeDataEt);
    hbox->addWidget(generateBtn);
    mainLayout->addLayout(hbox);
    QWidget *widget = new QWidget();
    mainLayout->addWidget(widget);
    imageView->setAlignment(Qt::AlignHCenter);
    setLayout(mainLayout);

    qDebug()<<"created BarcodeSelectDialog";
    this->show();
    connect(barcodeWidthEt, SIGNAL(textChanged(const QString &)), this, SLOT(barcodeTypeChanged()));
    connect(barcodeHeightEt, SIGNAL(textChanged(const QString &)), this, SLOT(barcodeTypeChanged()));
    connect(encodeDataEt, SIGNAL(textChanged(const QString &)), this, SLOT(barcodeTypeChanged()));
    connect(barcodeTypeCombo, SIGNAL(currentIndexChanged(int)), SLOT(barcodeTypeChanged()));
}
void BarcodeSelectDialog::setupBarcode(int type,int width,int height,unsigned char *c){
    my_symbol = ZBarcode_Create();
    my_symbol->input_mode = UNICODE_MODE;
    my_symbol->symbology = type ;
    my_symbol->bitmap_height=height;
    my_symbol->bitmap_width =width;
    my_symbol->width=width;
    my_symbol->height=height;
    my_symbol->scale =5;
    ZBarcode_Encode(my_symbol, c,encodeDataEt->text().length());
    ZBarcode_Encode_File(my_symbol, "pic.png");
    ZBarcode_Print(my_symbol, 0);
    ZBarcode_Encode_and_Print(my_symbol, c,encodeDataEt->text().length(),0);
    ZBarcode_Encode_File_and_Print(my_symbol, "pic.png",0);

    qDebug()<<my_symbol->width;
    qDebug()<<my_symbol->height;
    ZBarcode_Delete(my_symbol);
}

void BarcodeSelectDialog::barcodeTypeChanged()
{
    unsigned char *c = new unsigned char[encodeDataEt->text().length()];
    c = (unsigned char*) encodeDataEt->text().data();
    int width = barcodeWidthEt->text().toInt();
    int height = barcodeHeightEt->text().toInt();
    if(barcodeTypeCombo->currentIndex() ==0){
       setupBarcode(BARCODE_QRCODE,width,height,c);

    }else if(barcodeTypeCombo->currentIndex() ==1){
       setupBarcode(BARCODE_EAN14,width,height,c);

    }else if(barcodeTypeCombo->currentIndex() ==2){
       setupBarcode(BARCODE_CODE128,width,height,c);
    }
    imageScene->clear();
    imageItem = new QGraphicsPixmapItem();
    QPixmap png("out.png");
    qDebug()<<"png width "<<png.width();
    imageItem->setPixmap(png);
    imageScene->addItem(imageItem);
    imageScene->update();
}

