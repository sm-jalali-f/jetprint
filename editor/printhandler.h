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


class PrintHandler : public QThread
{
    Q_OBJECT


public:
    explicit PrintHandler();

    void run();//override



    void setPrintMode(int mode);
    void setPrintInterval(long miliSecond);
    void setSectorInterval(long microSecond);
    void setData(QByteArray data);

public slots:
    void normalPrintCommand(); //command:s000

private:
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
    //serialPortHandler *portHandler;
    QByteArray data;
    long sectorInterval;
    long printInterval;
    int printMode;
    const long FRAME_INTERVAL_TIME = 2; // 2 milisecond
    const int MAX_FRAME_SIZE = 256; // 256 BYTE
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
    void setupSerialPort(QString name,QString baudrate,QString databits
                   ,QString flowControl,QString parity,QString stopBits,QSerialPort::OpenModeFlag flag);
    QSerialPort *serialPort;
    QByteArray lastDataReaded;
    QTimer *readTimer;
    QTimer *intervalTimer;
    QList<QSerialPortInfo> availableSerialPortList;
public slots:
    void readFromPort();

};

#endif // PRINTHANDLER_H
