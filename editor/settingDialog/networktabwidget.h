#ifndef NETWORKTABWIDGET_H
#define NETWORKTABWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
class NetworkTabWidget:public QWidget
{
public:
    NetworkTabWidget(QWidget *parent=0);
    QComboBox *selectWifiCombo;
    QLineEdit *passwordEt;
    QCheckBox *showPassCheck;
};

#endif // NETWORKTABWIDGET_H
