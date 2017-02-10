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
    QString SPEED_TYPE_KEY ="speedType";
    QString INTERVAL_TYPE_KEY ="intervalType";
    QString INTERVAL_TIME_KEY ="intervalTime";
    QString SPEED_VALUE_KEY ="speedValue";

public slots:
    void autoIntervalSelected();
    void manualIntervalSelected();
    void autoSpeedSelected();
    void manualSpeedSelected();



};

#endif // PRINTSETTINGDIALOG_H
