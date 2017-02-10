#include "printsettingdialog.h"

PrintSettingDialog::PrintSettingDialog()
{
    QFont customfont( "", 17);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

//    QWidget *speedWidget = new QWidget;
//    QVBoxLayout *speedLayout = new QVBoxLayout(speedWidget);
    QVBoxLayout *speedLayout = new QVBoxLayout();
    printSpeedBox = new QGroupBox(tr("print speed"));
    autoPrintSpeedRadio = new QRadioButton (tr("auto print speed"));
    manualPrintSpeedRadio = new QRadioButton(tr("manual print speed"));
    speedLayout->addWidget(autoPrintSpeedRadio);
    speedLayout->addWidget(manualPrintSpeedRadio);
    QWidget *speedTempWidget = new QWidget;
    QHBoxLayout *speedTempLayout = new QHBoxLayout(speedTempWidget);
    speedEt = new QLineEdit();
    microSecondLabel = new QLabel("  us  ");
    speedTempLayout->addWidget(speedEt);
    speedTempLayout->addWidget(microSecondLabel);
    speedLayout->addWidget(speedTempWidget);
    printSpeedBox->setLayout(speedLayout);

//    QWidget *intervalWidget = new QWidget;
    QVBoxLayout *intervalLayout = new QVBoxLayout();
    intervalBox = new QGroupBox(tr("print interval"));
    autoIntervalRadio = new QRadioButton(tr("auto interval"));
    manualIntervalRadio= new QRadioButton(tr("manual interval"));
    intervalLayout->addWidget(autoIntervalRadio);
    intervalLayout->addWidget(manualIntervalRadio);
    QWidget *intervalTempWidget = new QWidget;
    QHBoxLayout *intervalTempLayout = new QHBoxLayout(intervalTempWidget);
    intervalEt= new QLineEdit();
    miliSecondLabel = new QLabel("  ms  ");
    intervalTempLayout->addWidget(intervalEt);
    intervalTempLayout->addWidget(miliSecondLabel);
    intervalLayout->addWidget(intervalTempWidget);
    intervalBox->setLayout(intervalLayout);

    mainLayout->addWidget(printSpeedBox);
    mainLayout->addWidget(intervalBox);

    autoPrintSpeedRadio->setChecked(true);
    speedEt->setDisabled(true);
    microSecondLabel->setDisabled(true);
    manualIntervalRadio->setChecked(true);
    intervalEt->setDisabled(false);
    miliSecondLabel->setDisabled(false);

    connect(autoIntervalRadio,SIGNAL(toggled(bool)),this,SLOT(autoIntervalSelected()));
    connect(manualIntervalRadio,SIGNAL(toggled(bool)),this,SLOT(manualIntervalSelected()));
    connect(autoPrintSpeedRadio,SIGNAL(toggled(bool)),this,SLOT(autoSpeedSelected()));
    connect(manualPrintSpeedRadio,SIGNAL(toggled(bool)),this,SLOT(manualSpeedSelected()));

    printSpeedBox->setFont(customfont);
    intervalBox->setFont(customfont);
    microSecondLabel->setFont(customfont);
    miliSecondLabel->setFont(customfont);
    autoPrintSpeedRadio->setFont(customfont);
    autoIntervalRadio->setFont(customfont);
    manualIntervalRadio->setFont(customfont);
    manualPrintSpeedRadio->setFont(customfont);
    speedEt->setFont(customfont);
    intervalEt->setFont(customfont);

    this->setFixedSize(800,800);

    QWidget *btnWidget = new QWidget;
    QHBoxLayout *btnLayout = new QHBoxLayout(btnWidget);
    btnLayout->setAlignment(Qt::AlignRight);
    applyBtn = new QPushButton(" apply ");
    okBtn = new QPushButton("  ok  ");
    cancelBtn = new QPushButton("  cancel  ");
    btnLayout->addWidget(applyBtn);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    btnLayout->addStretch(1);

    applyBtn->setFocus();
    mainLayout->addWidget(btnWidget);
    mainLayout->addStretch(1);

    setLayout(mainLayout);


}

void PrintSettingDialog::autoIntervalSelected()
{
    intervalEt->setDisabled(true);
    miliSecondLabel->setDisabled(true);
}

void PrintSettingDialog::manualIntervalSelected()
{
    intervalEt->setDisabled(false);
    miliSecondLabel->setDisabled(false);
}

void PrintSettingDialog::autoSpeedSelected()
{
    speedEt->setDisabled(true);
    microSecondLabel->setDisabled(true);
}

void PrintSettingDialog::manualSpeedSelected()
{
    speedEt->setDisabled(false);
    microSecondLabel->setDisabled(false);

}

