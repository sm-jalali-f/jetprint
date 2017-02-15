#include "printwindow.h"
#include "types/printtype.h"
JetPrintWindow::JetPrintWindow(QPixmap pixmap,PaintFrame *resultFrame,QWidget *parent ):
    QWidget(parent)
{

//    widget->setAttribute( Qt::WA_DeleteOnClose );
//    connect( widget, SIGNAL(destroyed(QObject*)), this, SLOT(widgetDestroyed(this) );
    mPrintHandler = new PrintHandler();
    QObject::connect(mPrintHandler, SIGNAL(valueChanged(int)),
                         this, SLOT(printCountChanged(int)));
    mainLayout = new QVBoxLayout(this);

//    this->resultFrame = resultFrame;
    this->setFixedWidth(800);
    this->setFixedHeight(600);

    speedLabel = new QLabel("Print Speed");
    speedLabel->setAlignment(Qt::AlignHCenter);
    sectorIntervalEt = new QLineEdit();
    sectorIntervalEt->setAlignment(Qt::AlignCenter);
    sectorIntervalEt->setStyleSheet("padding: 10px;background-color: #e3e3e3");


    QWidget *topWidget = new QWidget();
    topWidget->setStyleSheet("background-color: red");
    QWidget *startBtnWidget = new QWidget();
    startBtnWidget->setStyleSheet("background-color: #efefef");
    QVBoxLayout *startBtnLayout = new QVBoxLayout();
    startPauseBtn = new QPushButton("Start");
    startPauseBtn->setStyleSheet("padding: 15px;");
    startBtnLayout->setAlignment(Qt::AlignCenter);
    startBtnLayout->addWidget(startPauseBtn);
    startBtnWidget->setLayout(startBtnLayout);



    QWidget *previewWidget = new QWidget();
    previewWidget->setStyleSheet("background-color: white");
    QVBoxLayout *previewLayout  = new QVBoxLayout();
    previewWidget->setLayout(previewLayout);
    PreviewPaintFrame= new PaintFrame();
    PreviewPaintFrame->scene->addPixmap(pixmap);

    previewLayout->addWidget(PreviewPaintFrame);



    QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
    topLayout->addWidget(startBtnWidget,1);
    topLayout->addWidget(previewWidget,2);
    topWidget->setLayout(topLayout);

    QWidget *bottomWidget = new QWidget();
    bottomWidget->setStyleSheet("background-color: blue");

    QWidget *printSpeedWidget = new QWidget();
    printSpeedWidget->setStyleSheet("background-color: white");
    QVBoxLayout *printSpeedLayout = new QVBoxLayout();
    printSpeedLayout->addWidget(speedLabel);
    printSpeedLayout->addWidget(sectorIntervalEt);
    printSpeedLayout->setAlignment(Qt::AlignHCenter);
    printSpeedWidget->setLayout(printSpeedLayout);

    QWidget *printIntervalWidget= new QWidget();
    printIntervalWidget->setStyleSheet("background-color: white");
    QVBoxLayout *intervalLayout = new QVBoxLayout();
    printTypeGroupBox = new QGroupBox(tr("Print Type:"));

    sensorRadioBtn = new QRadioButton(tr("Print by sensor"));
    autoRadioBtn = new QRadioButton(tr("auto print"));
    autoRadioBtn->setChecked(true);
    printCommandIntervalEt = new QLineEdit();
    printCommandIntervalEt ->setStyleSheet("padding: 10px;background-color: #e3e3e3");
    printCommandIntervalEt->setAlignment(Qt::AlignCenter);

    intervalLayout->addWidget(sensorRadioBtn);
    intervalLayout->addWidget(autoRadioBtn);
    intervalLayout->addWidget(printCommandIntervalEt);
    printIntervalWidget->setLayout(intervalLayout);

    QWidget *counterWidget= new QWidget();
    counterWidget->setStyleSheet("background-color: orange");
    QVBoxLayout *counterLayout = new QVBoxLayout();
    counterLabel = new QLabel("Count :");
    counterLayout->addWidget(counterLabel);
    counterWidget->setLayout(counterLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomLayout->addWidget(printSpeedWidget,1);
    bottomLayout->addWidget(printIntervalWidget,1);
    bottomLayout->addWidget(counterWidget,1);
    bottomWidget->setLayout(bottomLayout);

    mainLayout->addWidget(topWidget,4);
    mainLayout->addWidget(bottomWidget,2);
    setLayout(mainLayout);
    connect(startPauseBtn,SIGNAL(clicked(bool)),this,SLOT(startPauseClicked()));
}

void JetPrintWindow::startPauseClicked(){
    qDebug()<<"PrintWindow: startPauseClicked ";
    if(isPrint){
        qDebug()<<"PrintWindow: startPauseClicked: isprint =false";
        mPrintHandler->pausePrint();
        startPauseBtn->setText("Start");
        isPrint =false;

    }else{
        startPauseBtn->setText("Pause");
        isPrint =true;
        QPixmap pixmap = PreviewPaintFrame->toPixmap();
        QByteArray byteArray = generateByteData(pixmap);
//        qDebug()<<"PrintWindow: startPauseClicked.length="<<byteArray.size();
//         this is for test:
//        QByteArray byteArray;
//        pixmap = pixmap.scaled(128,128);
//        QImage img = pixmap.toImage();
//        qDebug()<<"PrintWindow :startPauseClicked(); imgsize="<<img.size().width()<<","<<img.size().height();
//        for(int i=0;i<img.size().height();i++){
//            for(int j =0;j<img.size().width();j++){
//                QRgb rgb= img.pixel(QPoint(j,i));
//                if(QColor(rgb).name()=="#ffffff"){
//                    byteArray.append(32);
//                }else{
//                    byteArray.append(254);
//                }
//            }
//            byteArray.append(0x0A);
//            byteArray.append(0x0D);
//        }
        qDebug()<<"PrintWindow :startPauseClicked(); length="<<byteArray.length();
        mPrintHandler->setData(byteArray);
        mPrintHandler->setPrintInterval(printCommandIntervalEt->text().toLong());
        mPrintHandler->setSectorInterval(sectorIntervalEt->text().toLong());
        if(resultFrame->isDynamic()){
            mPrintHandler->setPrintMode(DYNAMIC);
//            mPrintHandler->setPaintFrame(resultFrame,WIDTH_SCALED,HEIGHT_SCALED);
        }else{
            mPrintHandler->setPrintMode(STATIC);
        }
        mPrintHandler->run();
    }
}

void JetPrintWindow::widgetDestroyed()
{
    qDebug()<< " print window qwidget closed";
}

void JetPrintWindow::printCountChanged(int count)
{
    counterLabel->setText(QString::number(count));
}
QByteArray JetPrintWindow::generateByteData(QPixmap pixmap){
    qDebug()<<"PrintWindow: generateByteData call";


    pixmap = pixmap.scaled(WIDTH_SCALED,HEIGHT_SCALED);
    QImage img = pixmap.toImage();
    QByteArray byteArray ;

    QString temp;
    int x =0;
    for(int i=0;i<img.size().width();i++){
        for(int j =img.size().height()-1;j>=0;j--){
            x+=1;
            QRgb rgb= img.pixel(QPoint(i,j));
            if(QColor(rgb).name()=="#ffffff"){
//                byteArray.append(32);
                temp.append("0");
            }else{
//                byteArray.append(256);
                temp.append("1");
            }
            if(temp.length()==8){
//                qDebug()<<temp;
                byteArray.append(QStringToByte(temp));
                temp.clear();
            }
        }
//        byteArray.append("\n");
    }
    return byteArray;
}
char JetPrintWindow:: QStringToByte(QString s)    //s is 8 bits
{
  bool ok;
  return (char)(s.left( 8 ).toInt( &ok, 2 ));
}
