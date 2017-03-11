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
#include <settingDialog/settingdialog.h>
#include <newprintwindow.h>
class NewEditorWidget: public QWidget
{
    Q_OBJECT
public:
    explicit NewEditorWidget(QWidget *parent = 0);


private:
    int TAB_HEIGHT =250;
    ShapeTabWidget *mShapeTabWidget;
    InsertTabWidget *mInsertTabWidget;
    BarcodeTabWidget *mBarcodeTabWidget;
    FormatTabWidget *mFormatTabWidget;
    QTabWidget *tabWidget;
    QPushButton *drawBtn,*insertBtn,*barcode,*formatBtn;
    QPushButton *settingBtn,*saveBtn,*undoBtn,*redoBtn,*openProjectBtn,*newProjectBtn;
    QPushButton *printBtn;
    QLabel *logoLabel,*websiteInfo;
    PaintFrame *mPaintframe;
    QLabel *printWidthLabel,*printHeightLabel;
public slots:
    void addCircle();
    void addRectangle();
    void addSquare();
    void addLine();
    void addTriangle();
    void addOval();
    void addDiamond();
    void addParallelogoram();
    void addText();
    void addImage();
    void addCounter();
    void addDate();
    void addTime();
    void addQrBarcode();
    void addEan13Barcode();
    void addCode128Barcode();
    void paintFrameChanged(double width,double height);
    void fontSizeChanged(int fontSize);
    void printClicked();
    void settingClicked();
    void saveClicked();
    void openProjectClicked();
    void newProjectClicked();
    void undoClicked();
    void redoClicked();


};

#endif // NEWEDITORWIDGET_H
