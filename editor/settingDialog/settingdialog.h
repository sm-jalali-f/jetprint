#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <settingDialog/generaltabwidget.h>
#include <settingDialog/networktabwidget.h>
#include <settingDialog/timedatewidget.h>
class SettingDialog : public QDialog
{

public:
    SettingDialog();
    QTabWidget *tabwidget;
    TimeDateWidget *mTimeDateWidget;
    GeneralTabWidget *mGeneralWidget;
    NetworkTabWidget *mNetworkWidget;
    QPushButton *applyBtn,*okBtn,*cancelBtn;
};

#endif // SETTINGDIALOG_H
