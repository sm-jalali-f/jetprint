#ifndef GENERALTABWIDGET_H
#define GENERALTABWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <QWidget>


class GeneralTabWidget: public QWidget
{
public:
    GeneralTabWidget(QWidget *parent=0);
    QLineEdit *deviceIdEt,*deviceNameEt;


};

#endif // GENERALTABWIDGET_H
