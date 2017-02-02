#include "readport.h"

ReadPort::ReadPort(QSerialPort *port){
    this->serialPort = port;
    remainCount = -1;
    readTimer = new QTimer();
    QObject::connect(readTimer, SIGNAL(timeout()),this, SLOT(readData()));
//    connect(serialPort,SIGNAL(QSerialPort::readyRead), this,SLOT(readData()));
//    connect(serialPort,SIGNAL(readyRead()), this,SLOT(readData()));

}

void ReadPort::run()
{
    readTimer->setInterval(1);
    readTimer->start();
}

int ReadPort::getRemainCount()
{
    return remainCount;
}

void ReadPort::stopRead()
{
    readTimer->stop();
}

void ReadPort::readData()
{
    qDebug()<<"readPort: readData call";
    std::string data  = serialPort->readAll().toStdString();
    qDebug()<<"readPort: readData data=";//<<data;
    if(data.length()>0){

//        remainCount = std::stoi(data,nullptr,10);
//        remainCount = stoi(data,nullptr,10);
        qDebug()<<"readPort: readData count ="<<remainCount;
    }

}
