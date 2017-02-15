#ifndef NEWPRINTWINDOW_H
#define NEWPRINTWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include "printsettingdialog.h"
#include "paintframe.h"
#include <QRect>
#include "serialport/printhandler.h"
//#include "types/printtype.h"

class NewPrintWindow :public QWidget
{
    Q_OBJECT
public:
    NewPrintWindow(PaintFrame *frame,QWidget *parent = 0);

    const QString COMPANY_NAME = "Doti";
    const QString APPLICATION_NAME = "Jetprinter";
    const QString SPEED_TYPE_AUTO_KEY ="speedType";
    const QString INTERVAL_TYPE_AUTO_KEY ="intervalType";
    const QString INTERVAL_TIME_KEY ="intervalTime";
    const QString SPEED_VALUE_KEY ="speedValue";
    const int DEFAULT_INTERVAL_VALUE =1000;
    const int DEFAULT_SPEED_VALUE =100;

private:

    QSettings *mPrintSetting;
    QLabel *printPreviewLabel,*printCounterLabel;
    QPushButton *startStopBtn,*backToEditorBtn,*printSettingBtn;
    bool isPrinting=false;
    PaintFrame *mPaintFrame;
    PrintHandler *mPrintHandler;
    PrintSettingDialog *settingDialog;
    bool autoInterval;
    bool autoSpeed;
    int speedValue; // time between print two sector of data
    int intervalValue; // time between print of two different print
    void loadSetting(); // load autoInterval ,autoSpeed,speedValue,intervalValue from save data in storage

public slots:
    void startStopClicked();
    void settingClicked();
    void backToEditorClicked();
    void settingDialogClosed();
    void printCountChanged(int count);



};

#endif // NEWPRINTWINDOW_H
