#include "inserttabwidget.h"

InsertTabWidget::InsertTabWidget(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("background-color:#E8E8E8");

    QHBoxLayout *mainLayout = new QHBoxLayout;

    addTextBtn = new QPushButton();
    QPixmap pixmapText(":/res/icons/ic_text");
    QIcon textIcon(pixmapText);
    addTextBtn->setIcon(textIcon);
    addTextBtn->setIconSize(pixmapText.rect().size()/1.3);
    addTextBtn->setFixedSize(pixmapText.rect().size()*1.1);
    addTextBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    addDateBtn = new QPushButton();
    QPixmap pixmapDate(":/res/icons/ic_date");
    QIcon dateIcon(pixmapDate);
    addDateBtn->setIcon(dateIcon);
    addDateBtn->setIconSize(pixmapDate.rect().size()/(4*1.3));
    addDateBtn->setFixedSize(pixmapDate.rect().size()*(1.1*0.25));
    addDateBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    addImageBtn = new QPushButton();
    QPixmap pixmapImage(":/res/icons/ic_image");
    QIcon imageIcon(pixmapImage);
    addImageBtn->setIcon(imageIcon);
    addImageBtn->setIconSize(pixmapImage.rect().size()/1.3);
    addImageBtn->setFixedSize(pixmapImage.rect().size()*1.1);
    addImageBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    addCounterBtn = new QPushButton();
    QPixmap pixmapCounter(":/res/icons/ic_counter");
    QIcon counterIcon(pixmapCounter);
    addCounterBtn->setIcon(counterIcon);
    addCounterBtn->setIconSize(pixmapCounter.rect().size()/(4*1.3));
    addCounterBtn->setFixedSize(pixmapCounter.rect().size()*(1.1*0.25));
    addCounterBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    addTimeBtn = new QPushButton();
    QPixmap pixmapTime(":/res/icons/ic_time");
    QIcon timeIcon(pixmapTime);
    addTimeBtn->setIcon(timeIcon);
    addTimeBtn->setIconSize(pixmapTime.rect().size()/(4*1.3));
    addTimeBtn->setFixedSize(pixmapTime.rect().size()*(0.25*1.1));
    addTimeBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    mainLayout->addWidget(addTextBtn);
    mainLayout->addWidget(addImageBtn);
    mainLayout->addWidget(addCounterBtn);
    mainLayout->addWidget(addDateBtn);
    mainLayout->addWidget(addTimeBtn);
    mainLayout->addStretch();

    setLayout(mainLayout);

}

