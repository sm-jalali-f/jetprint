#ifndef PRINTSETTINGDIALOG_H
#define PRINTSETTINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QSettings>
//#include <QSee

class PrintSettingDialog : public QDialog
{
    Q_OBJECT

public:
    PrintSettingDialog();
    const QString COMPANY_NAME = "Doti";
    const QString APPLICATION_NAME = "Jetprinter";
    const QString SPEED_TYPE_AUTO_KEY ="speedType";
    const QString INTERVAL_TYPE_AUTO_KEY ="intervalType";
    const QString INTERVAL_TIME_KEY ="intervalTime";
    const QString SPEED_VALUE_KEY ="speedValue";
    const int DEFAULT_INTERVAL_VALUE =1000;
    const int DEFAULT_SPEED_VALUE =100;
private:
    QGroupBox *printSpeedBox,*intervalBox;
    QRadioButton *autoPrintSpeedRadio,*manualPrintSpeedRadio;
    QLineEdit *speedEt;
    QRadioButton *manualIntervalRadio,*autoIntervalRadio;
    QLineEdit *intervalEt;
    QLabel *miliSecondLabel,*microSecondLabel;

    QSettings *printSetting;
    QPushButton *cancelBtn,*applyBtn,*okBtn;
    void loadSetting();
    void saveSetting();


public slots:
    void autoIntervalSelected();
    void manualIntervalSelected();
    void autoSpeedSelected();
    void manualSpeedSelected();

    void applyClicked();
    void okClicked();
    void cancelClicked();


};

#endif // PRINTSETTINGDIALOG_H
