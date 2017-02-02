#ifndef READPORT_H
#define READPORT_H

#include <QThread>
#include <QtSerialPort>
#include <QDebug>
#include <iostream>
using namespace std;
class ReadPort : public QObject
{
//    Q_OBJECT
public:
    ReadPort(QSerialPort *port);
    void run();
    int getRemainCount();
    void stopRead();
public  slots:
    void readData();
private:
    QSerialPort *serialPort;
    int remainCount;
    QTimer *readTimer;
};

#endif // READPORT_H
