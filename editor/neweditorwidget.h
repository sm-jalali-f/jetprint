#ifndef NEWEDITORWIDGET_H
#define NEWEDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <paintframe.h>
#include <printwindow.h>
#include <QtDebug>
#include <barcodeselectdialog.h>
#include <QFileDialog>
#include <QTabWidget>
#include <tabWidget/barcodetabwidget.h>
#include <tabWidget/shapetabwidget.h>
#include <tabWidget/inserttabwidget.h>
#include <tabWidget/formattabwidget.h>
class NewEditorWidget: public QWidget
{
    Q_OBJECT
public:
    explicit NewEditorWidget(QWidget *parent = 0);

    ShapeTabWidget *mShapeTabWidget;
    InsertTabWidget *mInsertTabWidget;
    BarcodeTabWidget *mBarcodeTabWidget;
    FormatTabWidget *mFormatTabWidget;
    QTabWidget *tabWidget;
    QPushButton *saveBtn,*newProjectBtn,*openProjectBtn,*settingBtn;
    QPushButton *drawBtn,*insertBtn,*barcode,*formatBtn;

    QPushButton *printBtn;
    QLabel *logoLabel,*websiteInfo;
private:
    int TAB_HEIGHT =250;
};

#endif // NEWEDITORWIDGET_H
