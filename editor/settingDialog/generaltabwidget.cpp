#include "generaltabwidget.h"

GeneralTabWidget::GeneralTabWidget(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QWidget *deviceIdWidget = new QWidget;
    QWidget *deviceNameWidget = new QWidget;

    QHBoxLayout *deviceIdLayout = new QHBoxLayout(deviceIdWidget);
    QHBoxLayout *deviceNameLayout = new QHBoxLayout(deviceNameWidget);

    QLabel *deviceIdLabel = new QLabel("شماره اختصاصی دستگاه: ");
    QLabel *deviceNameLabel = new QLabel("نام دستگاه :");

    deviceIdEt = new QLineEdit();
    deviceNameEt = new QLineEdit();

    deviceIdLayout->setAlignment(Qt::AlignRight);
    deviceNameLayout->setAlignment(Qt::AlignRight);

    deviceIdLayout->addWidget(deviceIdLabel);
    deviceIdLayout->addWidget(deviceIdEt);



    deviceIdLayout->addWidget(deviceIdEt);
    deviceIdLayout->addWidget(deviceIdLabel);
    deviceNameLayout->addWidget(deviceNameEt);
    deviceNameLayout->addWidget(deviceNameLabel);

    mainLayout->addWidget(deviceIdWidget);
    mainLayout->addWidget(deviceNameWidget);

    mainLayout->addStretch();
    setLayout(mainLayout);
}

