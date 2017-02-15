#include "newprintwindow.h"
#include "types/printtype.h"
NewPrintWindow::NewPrintWindow(PaintFrame *frame,QWidget *parent ):
    QWidget(parent)
{
    qDebug()<<"saaaadflwegrwgjrkgmrklmgreklngrklngrelkngreklngreklgn";
    mPrintHandler =new PrintHandler();
    this->mPaintFrame = frame;
    QPixmap previewPixmap = mPaintFrame->getPrintPixmap();

    int scaledWidth,scaledheight;
    scaledheight = 128;
    double factor = previewPixmap.height()/128;
    scaledWidth = previewPixmap.width()/factor;
    previewPixmap = previewPixmap.scaled(scaledWidth,scaledheight);

    this->setWindowState(Qt::WindowFullScreen);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    printPreviewLabel = new QLabel();
    printPreviewLabel->setAlignment(Qt::AlignCenter);
    printPreviewLabel->setPixmap(previewPixmap);

    mainLayout->addWidget(printPreviewLabel,1);

    QWidget *bottomWidget = new QWidget;
    QHBoxLayout *hLay = new QHBoxLayout(bottomWidget);

    QWidget *leftWidget= new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setAlignment(Qt::AlignCenter);

    printCounterLabel = new QLabel("0000");

    QFont f( "Arial", 100, QFont::Bold);
    printCounterLabel->setFont( f);
    leftLayout->addWidget(printCounterLabel);
    hLay->addWidget(leftWidget,4);

    QWidget *rightWidget = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    startStopBtn = new QPushButton("  Start  ");
    printSettingBtn = new QPushButton("  Setting  ");
    backToEditorBtn= new QPushButton("  back to Editor  ");

    startStopBtn->setFixedHeight(300);
    printSettingBtn->setFixedHeight(300);
    backToEditorBtn->setFixedHeight(300);

    QFont btnFont( "Arial", 25, QFont::Bold);
    startStopBtn->setFont(btnFont);
    printSettingBtn->setFont(btnFont);
    backToEditorBtn->setFont(btnFont);
//    startStopBtn->setStyleSheet("padding-top:10px;padding-bottom:10px");
    rightLayout->addWidget(startStopBtn,1);
    rightLayout->addWidget(printSettingBtn,1);
    rightLayout->addWidget(backToEditorBtn,1);

    hLay->addWidget(rightWidget,1);

    mainLayout->addWidget(bottomWidget,1);

    connect(backToEditorBtn,SIGNAL(clicked(bool)),this,SLOT(backToEditorClicked()));
    connect(startStopBtn,SIGNAL(clicked(bool)),this,SLOT(startStopClicked()));
    connect(printSettingBtn,SIGNAL(clicked(bool)),this,SLOT(settingClicked()));

    setLayout(mainLayout);
    mPrintSetting =new QSettings(COMPANY_NAME, APPLICATION_NAME);
    settingDialog =new PrintSettingDialog();
    connect(settingDialog,SIGNAL(finished(int)),this,SLOT(settingDialogClosed()));
    QObject::connect(mPrintHandler, SIGNAL(valueChanged(int)),
                         this, SLOT(printCountChanged(int)));

}

void NewPrintWindow::loadSetting()
{
    autoSpeed = mPrintSetting->value(SPEED_TYPE_AUTO_KEY,true).toBool();
    speedValue = mPrintSetting->value(SPEED_VALUE_KEY,DEFAULT_SPEED_VALUE).toInt();
    autoInterval = mPrintSetting->value(INTERVAL_TYPE_AUTO_KEY,false).toBool();
    intervalValue = mPrintSetting->value(INTERVAL_TIME_KEY,DEFAULT_INTERVAL_VALUE).toInt();
}

void NewPrintWindow::startStopClicked()
{
    if(isPrinting){
        mPrintHandler->pausePrint();
        isPrinting = false;
        startStopBtn->setText("  Start  ");
    }else{
        isPrinting =true;
        startStopBtn->setText("  Stop  ");
        mPrintHandler->setPaintFrame(mPaintFrame);
        mPrintHandler->setPrintInterval(intervalValue);
        mPrintHandler->setSectorInterval(speedValue);
        if(mPaintFrame->isDynamic()){
            mPrintHandler->setPrintMode(DYNAMIC);
        }else{
            mPrintHandler->setPrintMode(STATIC);
        }
        mPrintHandler->run();
    }
}

void NewPrintWindow::settingClicked()
{

    settingDialog->exec();
}

void NewPrintWindow::backToEditorClicked()
{
    this->close();
}

void NewPrintWindow::settingDialogClosed()
{
    qDebug()<<"NewPrintWindow :settingDialogClosed();";
    loadSetting();
}

void NewPrintWindow::printCountChanged(int count)
{
    printCounterLabel->setText(QString::number(count));
}



