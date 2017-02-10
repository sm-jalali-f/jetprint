#include "networktabwidget.h"

NetworkTabWidget::NetworkTabWidget(QWidget *parent)
{
    selectWifiCombo = new QComboBox;
    selectWifiCombo->addItem("doti");
    selectWifiCombo->addItem("hooshravan");
    selectWifiCombo->addItem("fruitgah");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignRight);
    QLabel *selectWifiLabel = new QLabel("انتخاب شبکه: ");
    QLabel *PasswordLabel = new QLabel("رمز عبور: ");
    passwordEt = new QLineEdit();
    showPassCheck = new QCheckBox("نمایش رمز عبور ");


    mainLayout->addWidget(selectWifiLabel);
    mainLayout->addWidget(selectWifiCombo);
    mainLayout->addWidget(PasswordLabel);
    mainLayout->addWidget(passwordEt);
    mainLayout->addWidget(showPassCheck);

    mainLayout->addStretch();

    setLayout(mainLayout);
}

