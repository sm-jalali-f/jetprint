#ifndef PRINTHANDLER_H
#define PRINTHANDLER_H

#include <QThread>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QtDebug>
#include <QString>
#include <QList>
#include <iostream>
#include <QQueue>
#include <paintframe.h>
#include <readport.h>
#include <string>
#include <types/printtype.h>
#include <QTime>
using namespace std;
class PrintHandler : public QThread
{
    Q_OBJECT


public:
    explicit PrintHandler();

    void run();//override



    void setPrintMode(PrintType mode);
    void setPrintInterval(long miliSecond);
    void setSectorInterval(long microSecond);
    void setData(QByteArray data);
    void setPaintFrame(PaintFrame *frame);

    void pausePrint();

public slots:
    void intervalPrintTimeout();

private:

//    const long FRAME_INTERVAL_TIME = 10; // 2 milisecond
    const int MAX_FRAME_SIZE = 256; // 256 BYTE
    const int BYTE_COUNT_OF_SECTOR= 16; // each sector is 16 byte
    const int PRINT_HEAD_HEIGHT_PIN= 128;
    const int WRITE_INTERVAL = 4;

    bool isPrint =false;

    //print periodic print with automatic sector interval with static data //print mode 0
    void printPeriodicAutomaticStaticData(long miliSecondInterval,QByteArray data);
    //print mode 1
    void printPeriodicAutomaticDynamicData(long miliSecondInterval,QByteArray data);
    //print mode 2
    void printPeriodicManualStaticData(long miliSecondInterval,long sectorMicroSecondInterval,QByteArray data);
    //print mode 3
    void printPeriodicManualDynamicData(long miliSecondInterval,long sectorMicroSecondInterval,QByteArray data);
    void printSensorAutomaticStaticData(QByteArray data);//print mode 4
    void printSensorAutomaticDynamicData(QByteArray data);//print mode 5
    //print mode 6
    void printSensorManualStaticData(long sectorMicroSecondInterval,QByteArray data);
    //print mode 7
    void printSensorManualDynamicData(long sectorMicroSecondInterval,QByteArray data);

    void writeDataCommand(QByteArray data);
    void resetPointersCommand();// set endPointer & savePointer & printPointer to first of memory : command =r000
    void sensorPrintCommand();// command:  ss00
    void pausePrintCommand();//pause print and pointer not change : command:f000
    void setAutoPrintCommand(); // set sector interval is automatic
    void setManualPrintCommand(); // set sector interval is manual
    void setSectorIntervalCommand(long microSecond); //set sector interval time with 2 step
    void normalPrintCommand(); //command:s000

    QByteArray generateByteFromPixmap(QPixmap pixmap);
    PaintFrame *mPaintFrame;
    int paintFrameWidthScale,paintFrameHeightScale;
    QByteArray dynamicData;
//    QByteArray getPixmapData();
    char QStringToByte(QString s);
    bool shouldRefresh =false;

    QByteArray data;
    long sectorInterval;
    long printInterval;
    PrintType printMode;
    int sectorCount;
//============================= port handler ========================
    void writeInPort(QByteArray data);
    QStringList getPortNames();
    QStringList getPortBaudRates();
    QStringList getPortDataBits();
    QStringList getPortFlowControl();
    QStringList getPortParity();
    QStringList getPortStopBits();
    QByteArray getLastReadedData();

    QList<QSerialPortInfo> scanSerialPort();
    void setupSerialPort(QString name,qint32 baudrate,QString databits
                   ,QString flowControl,QString parity,QString stopBits,QSerialPort::OpenModeFlag flag);
    QSerialPort *serialPort;
    QByteArray lastDataReaded;
//    QTimer *readTimer;
    QTimer *intervalTimer;
    QList<QSerialPortInfo> availableSerialPortList;

    QTimer *writeTimer; // this timer control the interval between send data to serial port (WRITE_INTERVAL mili second)
    bool writePermission;
    QQueue<QByteArray> writeQueue;

    int printCount=0;
    bool isSeenZero =false;
signals:
    void valueChanged(int newValue);


public slots:
    void readFromPort();
    void writeTimerTimeout();
    void writePortFinished(qint64 input);

};

#endif // PRINTHANDLER_H
