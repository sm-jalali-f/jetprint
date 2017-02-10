#include "printhandler.h"

PrintHandler::PrintHandler()
{
    serialPort = new QSerialPort();
    scanSerialPort();
    qint32 myBaudrate = 921600;
    setupSerialPort("ttyUSB0",myBaudrate,"Data8","NoFlowControl","NoParity","OneStop",QSerialPort::ReadWrite);

//    readTimer = new QTimer();
//    connect(readTimer, SIGNAL(timeout()),this, SLOT(readFromPort()));
//    readTimer->start(1);

    writePermission = true;
    writeTimer = new QTimer();
    writeTimer->setSingleShot(true);
    connect(writeTimer, SIGNAL(timeout()),this, SLOT(writeTimerTimeout()));

    intervalTimer = new QTimer();
    intervalTimer->setSingleShot(true);
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(intervalPrintTimeout()));

}
void PrintHandler::run(){
    qDebug()<<"PrintHandler: run call";
    this->printCount = 0;
    switch (printMode) {
    case STATIC:
        qDebug()<<"PrintHandler: run 2 selected";
        printPeriodicManualStaticData(printInterval,sectorInterval,data);
        break;
    case DYNAMIC:
        printPeriodicManualDynamicData(printInterval,sectorInterval,data);
        break;
    default:
        break;
    }
}

void PrintHandler::printPeriodicManualStaticData(long miliSecondInterval
                                                 , long sectorMicroSecondInterval,QByteArray data){
    qDebug()<<"PrintHandler: printPeriodicManualStaticData";
    this->data  = data;
    this->sectorInterval = sectorInterval;
    this->printInterval = miliSecondInterval;
    resetPointersCommand();
    setSectorIntervalCommand(sectorMicroSecondInterval);
    QByteArray tempData;
    tempData.append("0123456789123456");
    tempData.append("0123456789123456");
    tempData.append("0123456789123456");
    tempData.append("0123456789123456");
    tempData.append("0123456789123456");
    writeDataCommand(tempData);
    normalPrintCommand();
    isPrint =true;
    qDebug()<<"PrintHandler: printPeriodicManualStaticData finish";

}

void PrintHandler::printPeriodicManualDynamicData(long miliSecondInterval, long sectorMicroSecondInterval, QByteArray data)
{
    this->data  = data;
    this->sectorInterval = sectorInterval;
    this->printInterval = miliSecondInterval;
    resetPointersCommand();
    setSectorIntervalCommand(sectorMicroSecondInterval);
    writeDataCommand(data);
    normalPrintCommand();
    isPrint =true;
    qDebug()<<"PrintHandler: printPeriodicManualDynamicData finish";
}
QByteArray PrintHandler::getPixmapData()
{
    QPixmap pixmap = this->mPaintFrame->toPixmap();
    pixmap = pixmap.scaled(paintFrameWidthScale,paintFrameHeightScale);
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
char PrintHandler:: QStringToByte(QString s)    //s is 8 bits
{
  bool ok;
  return (char)(s.left( 8 ).toInt( &ok, 2 ));
}
void PrintHandler::writeDataCommand(QByteArray data){
    int length = data.size();
    qDebug()<<"PrintHandler: writeData data.length="<<length;

    if(length%BYTE_COUNT_OF_SECTOR!=0){
        qDebug()<<"ppppppppppppppppppppppppppppppppppppppppppppppppppppp";
        return;
    }
//    qDebug()<<"PrintHandler: writeData zaribi az 16";
    QByteArray frame;
    int frameNumber=1;
    for(int i=0;i<length;i++){
        frame.append(data.at(i));
        if( (i%MAX_FRAME_SIZE==(MAX_FRAME_SIZE-1))){ //if  frame full
                writeInPort(frame);
                frame.clear();
                frameNumber+=1;
                QString tempStr = frame;

        }else if(i==length-1){//if last Frame
            char zeroByte = 0x00;
            while (frame.size() %BYTE_COUNT_OF_SECTOR !=0) {
                frame.append(zeroByte);
            }
            writeInPort(frame);
        }
    }
}
void PrintHandler::setPaintFrame( PaintFrame *frame,int width,int height)
{
    this->mPaintFrame = frame;
    this->paintFrameHeightScale = height;
    this->paintFrameWidthScale = width;
}
void PrintHandler::pausePrint()
{
    qDebug()<<"PrintHandler: pausePrint: print mode=" <<printMode;
    if( printMode == STATIC  ){
        isPrint =false;
        qDebug()<<"PrintHandler: pausePrint: mode 2";
        intervalTimer->stop();
    }else if(printMode == DYNAMIC){
        //todo
    }
}
void PrintHandler::intervalPrintTimeout()
{
    qDebug()<<"PrintHandler: intervalPrintTimeout: "<<QTime::currentTime()<<" queue size="<<writeQueue.size();
    if(printMode == STATIC){
        isSeenZero =false;
        normalPrintCommand();
    }else if(printMode == DYNAMIC){
        isSeenZero =false;
        QByteArray temp = getPixmapData();
        bool isEqual = true;
        if(temp.size()==this->data.size()){
            for (int i=0;i<temp.size();i++){
                if(temp.at(i) != this->data.at(i))
                    isEqual=false;
            }
        }else{
            isEqual = false;
        }
        if(isEqual){
            shouldRefresh=false;
            qDebug()<<"PrintHandler: intervalPrintTimeout: whould refresh=false";
        }else{
            shouldRefresh =true;
            this->data =temp;
            this->dynamicData =temp;
            qDebug()<<"PrintHandler: intervalPrintTimeout: whould refresh=true";
        }
        normalPrintCommand();
    }
}
void PrintHandler::setPrintMode(PrintType mode){
    this->printMode = mode;
}
void PrintHandler::setData(QByteArray data){
    this->data = data;
}
void PrintHandler::setPrintInterval(long miliSecond){
//   qDebug()<<"PrintHandler: set printInterval "<<miliSecond<<" ms";
    if(miliSecond<100){
        this->printInterval = 100;
    }else
        this->printInterval = miliSecond;
}
void PrintHandler::setSectorInterval(long microSecond){
//    qDebug()<<"PrintHandler: setSectorInterval( "<<microSecond<<" us";
     if(microSecond < 180){
         this->sectorInterval = 180;
     }else
    this->sectorInterval = microSecond;
}
//===================== command function ========================
void PrintHandler::resetPointersCommand()
{
    QByteArray command;
    command.append("r000");
    writeInPort(command);
}
void PrintHandler::normalPrintCommand(){

    qDebug()<<"PrintHandler: normalPrint(); queue size:"<<writeQueue.size();
    QByteArray command;
    command.append("s000");
    writeInPort(command);

}
void PrintHandler::setManualPrintCommand(){

//    qDebug()<<"PrintHandler: setManualPrintCommand();";
    QByteArray command;
    command.append("");
    writeInPort(command);
}
void PrintHandler::setSectorIntervalCommand(long microSecond){

    QByteArray command ;//=QByteArray::number(microSecond);
    command.append("t");
    unsigned char x2 = (int)0;
    unsigned char x0 = (int)0;
    unsigned char x1 = (int)0;
    for(int i=0 ;i<microSecond ;i++){
        x0+=1;
        if((int)x0 == 0){
            x1+=1;
            if((int)x1 == 0){
                x2+=1;
            }
        }
    }
    command.append(x2);
    command.append(x1);
    command.append(x0);
    writeInPort(command);
}
//============================ port handler ===============================
void PrintHandler::readFromPort(){

//    qDebug()<< "read byte = ";
    lastDataReaded = serialPort->readAll();
    if(lastDataReaded.size()==0){
//        qDebug()<< "PrintHandler:readFromPort: not input ";
        return;
    }
        qDebug()<<"PrintHandler: readFromPort() size= "<<lastDataReaded.size();
//        qDebug()<<"PrintHandler: readFromPort() data= "<<lastDataReaded.toHex();
    int remainCount =-1;
    char zeroByte = 0x00;
//    qDebug()<< "read byte = "<<lastDataReaded[lastDataReaded.size()-1];
    if(!isPrint)
        return;
//    qDebug()<< "read byte ================== "<<QString::number(lastDataReaded[lastDataReaded.size()-1]);

    if(printMode == STATIC){
        for(int i=0;i<lastDataReaded.size();i++){
            qDebug()<< "read byte [ "<<i<<"]="<<QString::number(lastDataReaded[i]);
            if(lastDataReaded.at(lastDataReaded.size()-1) == zeroByte && isSeenZero==false){
                isSeenZero =true;
                this->printCount +=1;
                emit valueChanged(printCount);

                if( !intervalTimer->isActive()){
                    qDebug()<<"PrintHandler: readFromPort : "<<QTime::currentTime();
                    intervalTimer->start(printInterval);
                    return;
                }
            }
            if(lastDataReaded.at(lastDataReaded.size()-1) != zeroByte && isSeenZero==true){
                isSeenZero =false;
            }

        }
    }else if(printMode == DYNAMIC){
        //age 0 did
            // interval print ro start mikone
            // agar bayad refresh shavad :
                // dade baghimande ro beriz too matric
        //agar bayad refresh shavad
            //age adadi did ke az yek frame bozorgtar
                // agar writequeue khali bud
                    //yek frame benevis
        qDebug()<< "PrintHandler:readFromPort: dynamic";
        for(int i=0;i<lastDataReaded.size();i++){

            if(lastDataReaded.at(i) == zeroByte){
                this->printCount +=1;
                emit valueChanged(printCount);
                if(shouldRefresh){
                    qDebug()<< "PrintHandler:readFromPort: see 0 , send remaining data";
                    writeDataCommand(this->dynamicData); // dade haye baghi mande ro write kon

                }
                if( !intervalTimer->isActive()){
                    qDebug()<< "PrintHandler:readFromPort: see 0 , start timer";
                    intervalTimer->start(printInterval);
                    qDebug()<<"PrintHandler: readFromPort : "<<QTime::currentTime();

                }
                return;

            }
        }
        if(!shouldRefresh)
            return;
        qDebug()<< "PrintHandler:readFromPort: should refresh";
        if(writeQueue.size()>0)
            return;
        qDebug()<< "PrintHandler:readFromPort: queue empty";
        int distance = int(lastDataReaded.at(lastDataReaded.size()-1));
        if(distance > MAX_FRAME_SIZE / BYTE_COUNT_OF_SECTOR){
            QByteArray frame;
            qDebug()<< "PrintHandler:readFromPort: see "<<distance<<" , grater than frame max size";
            while (dynamicData.size()>0 && frame.size()<MAX_FRAME_SIZE) {
                frame.append(dynamicData.at(0));
                dynamicData.remove(0,1);
            }
            writeDataCommand(frame);
        }
        /*agar size write queue  0 nabashe momkene data
         * dar safe ersal bashe va ma dade jadidi ro dar saf gharar bedim va pointer save
         * az pointere print jolo biofte ke baes mishe current print kharab beshe
         * */
        //agar jaye kafi baraye ersale dade haye baghi mande be hardware bud ersal shavad
//        if(distance > dynamicData.size()/BYTE_COUNT_OF_SECTOR ){
//            QByteArray tempData = dynamicData;
//            int count = dynamicData.size();
//            for(int i=0;i<count;i++){
//                tempData.append(dynamicData.at(0));
//                tempData.remove(0,1);
//            }
//            while(tempData.size()%16 !=0){
//                tempData.append(zeroByte);
//            }

//        }else if(distance > MAX_FRAME_SIZE / BYTE_COUNT_OF_SECTOR){
//            if( dynamicData.size()>MAX_FRAME_SIZE){
//                QByteArray tempData;
//                for(int i=0;i<MAX_FRAME_SIZE;i++){
//                    tempData.append(dynamicData.at(0));
//                    tempData.remove(0,1);

//                }
//                writeInPort(tempData);
//            }else{
//                QByteArray tempData = dynamicData;
//                int count = dynamicData.size();
//                for(int i=0;i<count;i++){
//                    tempData.append(dynamicData.at(0));
//                    tempData.remove(0,1);
//                }
//                while(tempData.size()%16 !=0){
//                    tempData.append(zeroByte);
//                }

//            }

//        }

    }

}
void PrintHandler::writeTimerTimeout(){

    qDebug()<<"PrintHandler: writeTimerTimeout call"<<QTime::currentTime();
    if(writeQueue.size()>0){
        serialPort->write(writeQueue.first(),writeQueue.first().size());
        writeQueue.removeFirst();
        serialPort->flush();

    }else{
//        qDebug()<<"PrintHandler: writeTimerTimeout size=0";
        writePermission = true;
    }
}

void PrintHandler::writePortFinished(qint64 input)
{
    qDebug()<<"PrintHandler: writePortFinished: "<<QString::number(input);
    writeTimer->start(WRITE_INTERVAL);
}
void PrintHandler::writeInPort(QByteArray data){
//    qDebug()<<"PrintHandler: writeInPort call 1";
    writeQueue.append(data);
    if(writePermission){
        if(serialPort!= NULL ){
            writePermission = false;
            serialPort->write(writeQueue.first(),writeQueue.first().size());
            serialPort->flush();
            writeQueue.removeFirst();
        }
    }
}
QByteArray PrintHandler::getLastReadedData(){
    return lastDataReaded;
}
QList<QSerialPortInfo> PrintHandler::scanSerialPort()
{
//    qDebug()<<"serialPortHandler:scanSerialPort call";
    serialPort  = new QSerialPort() ;
    availableSerialPortList = QSerialPortInfo::availablePorts();
//    qDebug()<<"serialPortHandler:scanSerialPort " << availableSerialPortList.size();
//    qDebug()<<"serialPortHandler:scanSerialPort " << availableSerialPortList.at(0).portName();
//    qDebug()<<"serialPortHandler:scanSerialPort " << availableSerialPortList.at(1).portName();

    return availableSerialPortList;
}
void PrintHandler::setupSerialPort(QString name, qint32 baudrateInt
                                        , QString databitsStr, QString flowControlStr
                                        , QString parityStr, QString stopBitsStr
                                        , QSerialPort::OpenModeFlag flag)
{
    serialPort = new QSerialPort;
    scanSerialPort();
    for(int i=0;i<availableSerialPortList.size();i++){
        qDebug()<<"serialPortHandler:scanSerialPort " << availableSerialPortList.at(i).portName();
        if(availableSerialPortList.at(i).portName()==name){
            serialPort->setPort(availableSerialPortList.at(i));
            qDebug()<<"serialPortHandler:setupSerialPort: setport ";
        }
    }
    bool tempBool =serialPort->open(QIODevice::ReadWrite);
    qDebug()<<"serialPortHandler:setupSerialPort: port is open? "<<tempBool;

    serialPort->setBaudRate(baudrateInt);
//    serialPort->setBaudRate(QSerialPort::Baud115200);


    if (databitsStr =="Data5")
        serialPort->setDataBits(QSerialPort::Data5);
    else if (databitsStr =="Data6")
        serialPort->setDataBits(QSerialPort::Data6);
    else if (databitsStr =="Data7")
        serialPort->setDataBits(QSerialPort::Data7);
    else if (databitsStr =="Data8")
        serialPort->setDataBits(QSerialPort::Data8);


    if(flowControlStr == "NoFlowControl")
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
    else if (flowControlStr =="HardwareControl")
        serialPort->setFlowControl(QSerialPort::HardwareControl);
    else if (flowControlStr =="SoftwareControl")
        serialPort->setFlowControl(QSerialPort::SoftwareControl);


    if (parityStr=="NoParity")
        serialPort->setParity(QSerialPort::NoParity);
    else if(parityStr== "OddParity")
        serialPort->setParity(QSerialPort::OddParity);
    else if (parityStr=="EvenParity")
        serialPort->setParity(QSerialPort::EvenParity);
    else if (parityStr=="MarkParity")
        serialPort->setParity(QSerialPort::MarkParity);
    else if (parityStr=="SpaceParity")
        serialPort->setParity(QSerialPort::SpaceParity);


    if (databitsStr=="OneStop")
        serialPort->setStopBits(QSerialPort::OneStop);
    else if(databitsStr== "OneAndHalfStop")
        serialPort->setStopBits(QSerialPort::OneAndHalfStop);
    else if (databitsStr=="TwoStop")
        serialPort->setStopBits(QSerialPort::TwoStop);

//    connect(serialPort, &QSerialPort::readyRead, this, SLOT(readFromPort()));
//    connect(serialPort, &QSerialPort::readyRead, this, SLOT(readFromPort()));
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readFromPort()));
    connect(serialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(writePortFinished(qint64)));
//    qDebug()<< "PrintHandler: setupSerialPort baud:"<<serialPort->baudRate();
}



