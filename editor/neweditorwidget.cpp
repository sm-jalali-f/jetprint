#include "neweditorwidget.h"

NewEditorWidget::NewEditorWidget(QWidget *parent):QWidget(parent)
{
    qDebug()<<"NewEditorWidget: start constructor";

    this->setWindowState(Qt::WindowFullScreen);
    QBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *menuWidget = new QWidget;
    QHBoxLayout *menuLaout = new QHBoxLayout(menuWidget);
    settingBtn = new QPushButton();
    saveBtn = new QPushButton();
    newProjectBtn = new QPushButton();
    openProjectBtn = new QPushButton();
    undoBtn = new QPushButton();
    redoBtn = new QPushButton();
//    qDebug()<<"NewEditorWidget: NewEditorWidget: middle -1";
    QPixmap pixmapSetting(":/res/icons/ic_setting");
    QPixmap pixmapSave(":/res/icons/ic_save");
    QPixmap pixmapNewProject(":/res/icons/ic_new_project");
    QPixmap pixmapOpenProject(":/res/icons/ic_open");
    QPixmap pixmapUndo(":/res/icons/ic_undo");
    QPixmap pixmaRedo(":/res/icons/ic_redo");

    QIcon settingIcon(pixmapSetting);
    QIcon saveIcon(pixmapSave);
    QIcon newProjectIcon(pixmapNewProject);
    QIcon openProjectIcon(pixmapOpenProject);
    QIcon undoIcon(pixmapUndo);
    QIcon redoIcon(pixmaRedo);

    settingBtn->setIcon(settingIcon);
    saveBtn->setIcon(saveIcon);
    newProjectBtn->setIcon(newProjectIcon);
    openProjectBtn->setIcon(openProjectIcon);
    undoBtn->setIcon(undoIcon);
    redoBtn->setIcon(redoIcon);

    settingBtn->setIconSize(pixmapSetting.rect().size()/8);
    saveBtn->setIconSize(pixmapSave.rect().size()/8);
    newProjectBtn->setIconSize(pixmapNewProject.rect().size()/8);
    openProjectBtn->setIconSize(pixmapOpenProject.rect().size()/8);
    undoBtn->setIconSize(pixmapUndo.rect().size()/2);
    redoBtn->setIconSize(pixmaRedo.rect().size()/2);

    settingBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);
    saveBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);
    newProjectBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);
    openProjectBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);
    undoBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);
    redoBtn->setFixedSize(pixmapSetting.rect().size().height()/8,pixmapSetting.rect().size().height()/8);

    qDebug()<<"NewEditorWidget: created buttons";

    menuLaout->addWidget(saveBtn);
    menuLaout->addWidget(settingBtn);
    menuLaout->addStretch(1);
    menuLaout->addWidget(newProjectBtn);
    menuLaout->addWidget(openProjectBtn);

    menuLaout->addStretch(1);
    menuLaout->addWidget(undoBtn);
    menuLaout->addWidget(redoBtn);
    menuLaout->addStretch(40);
    mainLayout->addWidget(menuWidget);
    qDebug()<<"NewEditorWidget: added buttons";

    tabWidget = new QTabWidget;
    mShapeTabWidget = new ShapeTabWidget;
    mInsertTabWidget = new InsertTabWidget;
    mBarcodeTabWidget = new BarcodeTabWidget;
    mFormatTabWidget = new FormatTabWidget;
    tabWidget->addTab(mShapeTabWidget, tr("   Shape   "));
    tabWidget->addTab(mInsertTabWidget,tr("  Insert  "));
    tabWidget->addTab(mBarcodeTabWidget, tr(" Barcode "));
    tabWidget->addTab(mFormatTabWidget, tr("   Format   "));
    qDebug()<<"NewEditorWidget: add tab";
    mainLayout->addWidget(tabWidget);
    mPaintframe = new PaintFrame();
    mainLayout->addWidget(mPaintframe);

    QWidget *bottomWidget = new QWidget;
    QWidget *bottomLeftWidget = new QWidget;
    QWidget *bottomRightWidget = new QWidget;
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    QVBoxLayout *bottomLeftLayout = new QVBoxLayout(bottomLeftWidget);
    QVBoxLayout *bottomRightLayout = new QVBoxLayout(bottomRightWidget);
//    bottomLeftWidget->setStyleSheet(".QWidget{border-style:solid;border-width:5px;border-color:black;}");
    bottomRightWidget->setStyleSheet(".QWidget{border-style:solid;border-width:5px;border-color:black;background-color:#d3d3d3;}");
    QWidget *printWidget = new QWidget();
    QVBoxLayout *printVLayout = new QVBoxLayout(printWidget);


    printBtn= new QPushButton();
    QPixmap pixmapPrint(":/res/icons/ic_print");
    QIcon printIcon(pixmapPrint);
    printBtn->setIcon(printIcon);
    printBtn->setIconSize(pixmapPrint.rect().size()/1);
    printBtn->setFixedSize(pixmapPrint.rect().size()*1.3);
    printVLayout->addStretch();
    printVLayout->addWidget(printBtn);
    printVLayout->setAlignment(Qt::AlignCenter);
    printVLayout->addStretch();
    bottomLeftLayout->addWidget(printWidget);

    qDebug()<<"NewEditorWidget: print detail";

    QWidget *companyWidget = new QWidget();
    QVBoxLayout *companyVLayout = new QVBoxLayout(companyWidget);
    logoLabel = new QLabel();
    QPixmap pixmapLogo(":/res/icons/ic_app");
    pixmapLogo = pixmapLogo.scaled(pixmapLogo.width()/2,pixmapLogo.height()/2);
//    QIcon logoIcon(pixmapLogo);
    logoLabel->setPixmap(pixmapLogo);
    companyVLayout->addStretch(1);
    companyVLayout->addWidget(logoLabel);
    companyVLayout->setAlignment(Qt::AlignCenter);
    websiteInfo = new QLabel("Best Online JetPrinter \nhttp://www.doti.black");
    websiteInfo->setStyleSheet("QLabel {color : blue; }");
    websiteInfo->setFont(QFont("Arial",18));
    companyWidget->setStyleSheet(".QWidget{border-style:solid;border-width:5px;border-color:black;background-color:#d3d3d3;}");
    companyVLayout->addWidget(websiteInfo);
    companyVLayout->addStretch();
    bottomLeftLayout->addWidget(companyWidget);
    printWidthLabel = new QLabel("عرض چاپ:  ");
    printHeightLabel = new QLabel("ارتفاع چاپ:  ۱۸ میلی متر");
    QLabel *infoLabel =new QLabel("گزارش های آنلاین شما:\nهزینه هر چاپ\nتعداد چاب در هر کارتریج\nتعداد پیکسل های چاپ\nطول و عرض چاپ\nتعداد چاپ های های اخیر از این پروژه\n");
    printWidthLabel->setFont(QFont("Arial",18 ));
    printHeightLabel->setFont(QFont("Arial",18 ));
    infoLabel->setFont(QFont("Arial",18 ));
    bottomRightLayout->addStretch();
    bottomRightLayout->setAlignment(Qt::AlignCenter);
    bottomRightLayout->addWidget(printWidthLabel);
    bottomRightLayout->addWidget(printHeightLabel);
    bottomRightLayout->addWidget(infoLabel);
    bottomRightLayout->addStretch();

    bottomLayout->addWidget(bottomLeftWidget,1);
    bottomLayout->addWidget(bottomRightWidget,4);

    mainLayout->addWidget(bottomWidget);
    tabWidget->setFixedHeight(TAB_HEIGHT);
    setLayout(mainLayout);
    printBtn->setStyleSheet("border-style:None;");
    qDebug()<<"NewEditorWidget: before connect object";
    connect(printBtn,SIGNAL(clicked(bool)),this,SLOT(printClicked()));
    printWidget->setStyleSheet("border-style:None;");
    QObject::connect(mShapeTabWidget, SIGNAL(circleBtnClicked()),
                         this, SLOT(addCircle()));
    QObject::connect(mShapeTabWidget, SIGNAL(rectangleBtnClicked()),
                         this, SLOT(addRectangle()));
    QObject::connect(mShapeTabWidget, SIGNAL(squareBtnClicked()),
                         this, SLOT(addSquare()));
    QObject::connect(mShapeTabWidget, SIGNAL(lineBtnClicked()),
                         this, SLOT(addLine()));
    QObject::connect(mShapeTabWidget, SIGNAL(triangleBtnClicked()),
                         this, SLOT(addTriangle()));
    QObject::connect(mShapeTabWidget, SIGNAL(ovalBtnClicked()),
                         this, SLOT(addOval()));
    QObject::connect(mShapeTabWidget, SIGNAL(diamondBtnClicked()),
                         this, SLOT(addDiamond()));
    QObject::connect(mShapeTabWidget, SIGNAL(parallelogramBtnClicked()),
                     this, SLOT(addParallelogoram()));

    QObject::connect(mBarcodeTabWidget, SIGNAL(qrClicked()),
                     this, SLOT(addQrBarcode()));

    QObject::connect(mBarcodeTabWidget, SIGNAL(ean13Clicked()),
                     this, SLOT(addEan13Barcode()));

    QObject::connect(mBarcodeTabWidget, SIGNAL(code128Clicked()),
                     this, SLOT(addCode128Barcode()));

    QObject::connect(mFormatTabWidget, SIGNAL(onFontSizeChanged(int)),
                     this, SLOT(fontSizeChanged(int)));

    QObject::connect(mInsertTabWidget, SIGNAL(onTextBtnClicked()),this, SLOT(addText()));
    QObject::connect(mInsertTabWidget, SIGNAL(onImageBtnClicked()),this, SLOT(addImage()));
    QObject::connect(mInsertTabWidget, SIGNAL(onCounterBtnClicked()),this, SLOT(addCounter()));
    QObject::connect(mInsertTabWidget, SIGNAL(onDateBtnClicked()),this, SLOT(addDate()));
    QObject::connect(mInsertTabWidget, SIGNAL(onTimeBtnClicked()),this, SLOT(addTime()));
    connect(settingBtn,SIGNAL(clicked(bool)),this,SLOT(settingClicked()));
    connect(saveBtn,SIGNAL(clicked(bool)),this,SLOT(saveClicked()));
    connect(openProjectBtn,SIGNAL(clicked(bool)),this,SLOT(openProjectClicked()));
    connect(newProjectBtn,SIGNAL(clicked(bool)),this,SLOT(newProjectClicked()));
    connect(undoBtn,SIGNAL(clicked(bool)),this,SLOT(undoClicked()));
    connect(redoBtn,SIGNAL(clicked(bool)),this,SLOT(redoClicked()));
    connect(mPaintframe, SIGNAL(paintFrameChanged(double,double)),
                         this, SLOT(paintFrameChanged(double,double)));

    qDebug()<<"NewEditorWidget: end constructor";
}

void NewEditorWidget::addCircle()
{
    mPaintframe->addCircle(QPointF(20,50),90);
}

void NewEditorWidget::addRectangle()
{
    mPaintframe->addRectangle(QPointF(50,50),240,80);
}

void NewEditorWidget::addSquare()
{
    mPaintframe->addSquare(QPointF(75,50),80);
}

void NewEditorWidget::addLine()
{
    mPaintframe->addLine(QPointF(10,10),QPointF(40,40));
}

void NewEditorWidget::addTriangle()
{
    mPaintframe->addTriangle(QPointF(50,10),QPointF(20,50),QPointF(80,50));
}

void NewEditorWidget::addOval()
{
    mPaintframe->addOval(QPointF(64,64),60,20);
}

void NewEditorWidget::addDiamond()
{
    mPaintframe->addDiamond(QPointF(50,10),50,20);
}

void NewEditorWidget::addParallelogoram()
{
    mPaintframe->addParallelogram(QPointF(50,10),90,30,75);
}

void NewEditorWidget::addText()
{
    mPaintframe->addTextItem(QPoint(20,20));
}

void NewEditorWidget::addImage()
{
    qDebug()<<"NewEditorWidget: addImage 1";
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "C:/",
                                                    tr("Images (*.png *.jpg)"));
    mPaintframe->addImage(QPointF(30,30),fileName);
}

void NewEditorWidget::addCounter()
{
    mPaintframe->addCounterItem(QPoint(20,20));

}

void NewEditorWidget::addDate()
{
     mPaintframe->addDate(QPointF(0,0),440,120);

}

void NewEditorWidget::addTime()
{
    mPaintframe->addTime(QPointF(0,0),320,120);
}

void NewEditorWidget::addQrBarcode()
{
    qDebug()<<"NewEditorWidget:addQrBarcode: ";

    unsigned char c[] ={0x61,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62};
    mPaintframe->addBarcode(QPointF(30,30),60,30,c,13,BARCODE_QRCODE);
}

void NewEditorWidget::addEan13Barcode()
{
    qDebug()<<"NewEditorWidget:addEan13Barcode: start";
    unsigned char c[] ={0x61,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62};
    mPaintframe->addBarcode(QPointF(30,30),60,30,c,13,BARCODE_EAN14);

}

void NewEditorWidget::addCode128Barcode()
{

    qDebug()<<"NewEditorWidget:addCode128Barcode: start";
    unsigned char c[] ={0x61,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62};
    mPaintframe->addBarcode(QPointF(30,30),60,30,c,13,BARCODE_CODE128);

}

void NewEditorWidget::printClicked()
{
//    JetPrintWindow *printWin = new JetPrintWindow(this->mPaintframe->getPrintPixmap(),this->mPaintframe);
//    printWin->show();
//    this->close();
    mPaintframe->unSelectAllItem();

    NewPrintWindow *printWindow = new NewPrintWindow(this->mPaintframe);// = new NewPrintWindow();
    printWindow->show();
}

void NewEditorWidget::settingClicked()
{
    SettingDialog *dialog = new SettingDialog;
    dialog->setAcceptDrops(false);
    dialog->exec();
}

void NewEditorWidget::saveClicked()
{

}

void NewEditorWidget::openProjectClicked()
{

}

void NewEditorWidget::newProjectClicked()
{

}

void NewEditorWidget::undoClicked()
{

}

void NewEditorWidget::redoClicked()
{

}

void NewEditorWidget::paintFrameChanged(double width, double height)
{
    qDebug()<<"signaaaaaaaaaaaaaaaaaaaaaaaal width change";
    QString widthStr = "عرض چاپ:   ";
    widthStr.append(QString::number(width));
    widthStr.append("میلی متر");
    printWidthLabel->setText(widthStr);
    QString heightStr = "ارتفاع چاپ:   ";
    heightStr.append(QString::number(height));
    heightStr.append("میلی متر");
    printHeightLabel->setText(heightStr);
}

void NewEditorWidget::fontSizeChanged(int fontSize)
{
    mPaintframe->fontSizeChanged(fontSize);
}

