#include "neweditorwidget.h"

NewEditorWidget::NewEditorWidget(QWidget *parent):QWidget(parent)
{
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

//    this->setStyleSheet("background-color:#e0e0d1");
    tabWidget = new QTabWidget;
//    tabWidget->tabBar()->setStyleSheet("color:red;background-color:#e0e0eb");
//    tabWidget->tabBar()->setStyleSheet("background-color:#E8E8E8;QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #E8E8E8, stop: 1.0 #E8E8E8);}QTabBar::tab:selected {border-color: #9B9B9B;border-bottom-color: black; }QTabBar::tab:!selected {margin-top: 2px;}");
    mShapeTabWidget = new ShapeTabWidget;
    mInsertTabWidget = new InsertTabWidget;
    mBarcodeTabWidget = new BarcodeTabWidget;
    mFormatTabWidget = new FormatTabWidget;
    tabWidget->addTab(mShapeTabWidget, tr("   Shape   "));
    tabWidget->addTab(mInsertTabWidget,tr("  Insert  "));
    tabWidget->addTab(mBarcodeTabWidget, tr(" Barcode "));
    tabWidget->addTab(mFormatTabWidget, tr("   Format   "));

    mainLayout->addWidget(tabWidget);
    mPaintframe = new PaintFrame;
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

    QLabel *infoLabel =new QLabel("گزارش های آنلاین شما:\nهزینه هر چاپ\nتعداد چاب در هر کارتریج\nتعداد پیکسل های چاپ\nطول و عرض چاپ\nتعداد چاپ های های اخیر از این پروژه\n");
    infoLabel->setFont(QFont("Arial",18 ));
    bottomRightLayout->addStretch();
    bottomRightLayout->setAlignment(Qt::AlignCenter);
    bottomRightLayout->addWidget(infoLabel);
    bottomRightLayout->addStretch();

    bottomLayout->addWidget(bottomLeftWidget,1);
    bottomLayout->addWidget(bottomRightWidget,4);

    mainLayout->addWidget(bottomWidget);
//    mainLayout->addStretch();
    tabWidget->setFixedHeight(TAB_HEIGHT);
    setLayout(mainLayout);
    printBtn->setStyleSheet("border-style:None;");
    connect(printBtn,SIGNAL(clicked(bool)),this,SLOT(printClicked()));
    printWidget->setStyleSheet("border-style:None;");
//    tabWidget->setCurrentIndex(3);
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

    connect(settingBtn,SIGNAL(clicked(bool)),this,SLOT(settingClicked()));
    connect(saveBtn,SIGNAL(clicked(bool)),this,SLOT(saveClicked()));
    connect(openProjectBtn,SIGNAL(clicked(bool)),this,SLOT(openProjectClicked()));
    connect(newProjectBtn,SIGNAL(clicked(bool)),this,SLOT(newProjectClicked()));
    connect(undoBtn,SIGNAL(clicked(bool)),this,SLOT(undoClicked()));
    connect(redoBtn,SIGNAL(clicked(bool)),this,SLOT(redoClicked()));
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

void NewEditorWidget::printClicked()
{
//    JetPrintWindow *printWin = new JetPrintWindow(this->mPaintframe->getPrintPixmap(),this->mPaintframe);
//    printWin->show();
//    this->close();

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

