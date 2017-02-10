#include "settingdialog.h"

SettingDialog::SettingDialog()
{


    QVBoxLayout *mainLayout = new QVBoxLayout;
    tabwidget = new QTabWidget;
    mGeneralWidget =new GeneralTabWidget;
    mNetworkWidget =new NetworkTabWidget;
    mTimeDateWidget =new TimeDateWidget;
    tabwidget->addTab(mGeneralWidget,tr(" General "));
    tabwidget->addTab(mNetworkWidget,tr(" Network "));
    tabwidget->addTab(mTimeDateWidget,tr(" TimeDate "));
    mainLayout->addWidget(tabwidget);
    QHBoxLayout *hLay = new QHBoxLayout;
    hLay->setAlignment(Qt::AlignRight);
    okBtn = new QPushButton("  Ok  ");
    applyBtn = new QPushButton("  Apply  ");
    cancelBtn = new QPushButton(" Cancel ");
    hLay->addWidget(okBtn);
    hLay->addWidget(cancelBtn);
    hLay->addWidget(applyBtn);
    mainLayout->addLayout(hLay);


    setLayout(mainLayout);
    this->setWindowTitle("Setting");
    this->setMinimumHeight(500);
    this->setMinimumWidth(500);

}

