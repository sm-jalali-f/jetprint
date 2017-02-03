#include "neweditorwidget.h"

NewEditorWidget::NewEditorWidget(QWidget *parent):QWidget(parent)
{
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
    QBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(new PaintFrame);

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
    printWidget->setStyleSheet("border-style:None;");
//    tabWidget->setCurrentIndex(3);
}

