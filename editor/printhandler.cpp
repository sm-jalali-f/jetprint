#include "printhandler.h"

PrintHandler::PrintHandler()
{
    serialPort = new QSerialPort();
    scanSerialPort();
    setupSerialPort("COM1","Baud9600","Data8","NoFlowControl","NoParity","OneStop",QSerialPort::ReadWrite);
    readTimer = new QTimer();
    intervalTimer = new QTimer();
    connect(readTimer, SIGNAL(timeout()),this, SLOT(readFromPort()));
    readTimer->start(1);


}
void PrintHandler::run(){
    qDebug()<<"PrintHandler: run call";
    switch (printMode) {
    case 0:

        break;
    case 1:

        break;
    case 2:
        qDebug()<<"PrintHandler: run 2 selected";
        printPeriodicManualStaticData(printInterval,sectorInterval,data);
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:

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
    setManualPrintCommand();
    this->msleep(FRAME_INTERVAL_TIME);
    setSectorIntervalCommand(sectorMicroSecondInterval);
    this->msleep(FRAME_INTERVAL_TIME);
    writeDataCommand(data);
    this->msleep(FRAME_INTERVAL_TIME);

    intervalTimer = new QTimer(this);
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(normalPrintCommand()));



}
void PrintHandler::normalPrintCommand(){

    qDebug()<<"PrintHandler: normalPrint();";
     QByteArray command;
    command.append("s000");
    writeInPort(command);

}
void PrintHandler::setManualPrintCommand(){

    QByteArray command;
    command.append("r000");
    writeInPort(command);
}
void PrintHandler::setSectorIntervalCommand(long microSecond){

    QByteArray command;
    command.append("s000");
    writeInPort(command);
}

void PrintHandler::writeDataCommand(QByteArray data){
    qDebug()<<"PrintHandler: writeData call";
    int length = data.size();
    if(length%16!=0)
        return;
    QByteArray frame;
    for(int i=0;i<length;i++){
        frame.append(data.at(i));
        if(i==length-1 || (i%MAX_FRAME_SIZE==(MAX_FRAME_SIZE-1))){ //if last Frame or frame full
                writeInPort(frame);
//                qDebug()<<"PrintHandler: writeData frame="+frame;
                frame.clear();
                this->msleep(FRAME_INTERVAL_TIME);
        }
    }
}
void PrintHandler::setPrintMode(int mode){
    this->printMode = mode;
}

void PrintHandler::setData(QByteArray data){
    this->data = data;
}
void PrintHandler::setPrintInterval(long miliSecond){
    this->printInterval = miliSecond;
}
void PrintHandler::setSectorInterval(long microSecond){
    this->sectorInterval = microSecond;
}
//============================ port handler ===============================

void PrintHandler::readFromPort(){

    lastDataReaded = serialPort->readAll();
    if(lastDataReaded.size()>0){
        qDebug()<<"serialPortHandler: readFromPort ="<<lastDataReaded;
        if(lastDataReaded.at(0)==0x30 && printMode==2)
            intervalTimer->start(printInterval);
    }

}

void PrintHandler::writeInPort(QByteArray data){
//    qDebug()<<"serialPortHandler:writeInPort call";
    if(serialPort!= NULL ){
        serialPort->write(data,data.size());
        serialPort->flush();
        serialPort->waitForBytesWritten(data.size());
    }
}
QByteArray PrintHandler::getLastReadedData(){
    return lastDataReaded;
}

QList<QSerialPortInfo> PrintHandler::scanSerialPort()
{
    qDebug()<<"serialPortHandler:scanSerialPort call";
    serialPort  = new QSerialPort() ;
    availableSerialPortList = QSerialPortInfo::availablePorts();
    return availableSerialPortList;
}
void PrintHandler::setupSerialPort(QString name, QString baudrateStr
                                        , QString databitsStr, QString flowControlStr
                                        , QString parityStr, QString stopBitsStr
                                        , QSerialPort::OpenModeFlag flag)
{



    serialPort = new QSerialPort;
    scanSerialPort();
    for(int i=0;i<availableSerialPortList.size();i++){
        if(availableSerialPortList.at(i).portName()==name){
            serialPort->setPort(availableSerialPortList.at(i));
        }
    }
    bool tempBool =serialPort->open(flag);
    qDebug()<<"serialPortHandler:setupSerialPort: port is open? "<<tempBool;
    if(baudrateStr == "Baud1200")
        serialPort->setBaudRate(QSerialPort::Baud1200);
    else if(baudrateStr =="Baud2400")
        serialPort->setBaudRate(QSerialPort::Baud2400);
    else if(baudrateStr == "Baud4800")
        serialPort->setBaudRate(QSerialPort::Baud4800);
    else if(baudrateStr =="Baud9600")
        serialPort->setBaudRate(QSerialPort::Baud9600);
    else if (baudrateStr =="Baud19200")
        serialPort->setBaudRate(QSerialPort::Baud19200);
    else if (baudrateStr =="Baud38400")
        serialPort->setBaudRate(QSerialPort::Baud38400);
    else if (baudrateStr =="Baud57600")
        serialPort->setBaudRate(QSerialPort::Baud57600);
    else if (baudrateStr =="Baud115200")
        serialPort->setBaudRate(QSerialPort::Baud115200);


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
}



