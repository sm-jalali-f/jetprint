#include "textformattab.h"

TextFormatTab::TextFormatTab(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color:#E8E8E8");
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *label = new QLabel("Font size: ");
    QLineEdit *fontEt = new QLineEdit("15");
    fontEt->setValidator( new QIntValidator(0, 100, this) );
    layout->addWidget(label);
    layout->addWidget(fontEt);
    connect(fontEt,SIGNAL(textChanged(QString)),this,SLOT(fontSizeChanged(QString)));
    setLayout(layout);
}

void TextFormatTab::fontSizeChanged(QString text)
{
    int size =text.toInt();
    emit onFontSizeChanged(size);
}


