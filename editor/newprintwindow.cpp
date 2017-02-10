#include "newprintwindow.h"

NewPrintWindow::NewPrintWindow(PaintFrame *frame,QWidget *parent ):
    QWidget(parent)
{
    mPrintHandler =new PrintHandler();
    this->mPaintFrame = frame;
    QPixmap previewPixmap = mPaintFrame->getPrintPixmap();

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

    printCounterLabel = new QLabel("1957");

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
}

void NewPrintWindow::startStopClicked()
{
    if(isPrinting){
        isPrinting = false;
        startStopBtn->setText("  Start  ");
    }else{
        isPrinting =true;
        startStopBtn->setText("  Stop  ");
//        mPrintHandler->setData(byteArray);
//        mPrintHandler->setPrintInterval(printCommandIntervalEt->text().toLong());
//        mPrintHandler->setSectorInterval(sectorIntervalEt->text().toLong());
//        if(resultFrame->isDynamic()){
//            mPrintHandler->setPrintMode(DYNAMIC);
//            mPrintHandler->setPaintFrame(resultFrame,WIDTH_SCALED,HEIGHT_SCALED);
//        }else{
//            mPrintHandler->setPrintMode(STATIC);
//        }
//        mPrintHandler->run();
    }
}

void NewPrintWindow::settingClicked()
{
    PrintSettingDialog *dialog =new PrintSettingDialog();
    dialog->exec();
}

void NewPrintWindow::backToEditorClicked()
{
    this->close();
}



