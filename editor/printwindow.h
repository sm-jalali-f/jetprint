#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <paintframe.h>
#include <serialport/printhandler.h>
#include <QByteArray>
#include <iostream>
//#include <types/printtype.h>
class JetPrintWindow : public QWidget
{
    Q_OBJECT
public:
    JetPrintWindow(QPixmap pixmap,PaintFrame *resultFrame,QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QPushButton *startPauseBtn,*stopBtn,*testBtn;
    QLabel *speedLabel;
    QLineEdit *sectorIntervalEt;

    PaintFrame *PreviewPaintFrame;
    QGroupBox *printTypeGroupBox;
    QRadioButton *sensorRadioBtn,*autoRadioBtn;
    QLineEdit *printCommandIntervalEt;

    QLabel *counterLabel;
    bool isPrint = false;
    PrintHandler *mPrintHandler;
    QByteArray generateByteData(QPixmap pixmap);
    PaintFrame *resultFrame;
    char    QStringToByte(QString);

    const int HEIGHT_SCALED = 128;
    const int WIDTH_SCALED = 128;
public slots:
    void startPauseClicked();
    void widgetDestroyed();
    void printCountChanged(int count);

};

#endif // PRINTWINDOW_H
