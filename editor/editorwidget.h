#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <paintframe.h>
#include <printwindow.h>
#include <QtDebug>
#include <barcodeselectdialog.h>
#include <QFileDialog>

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditorWidget(QWidget *parent = 0);

signals:

public slots:
    void onBarcodeBtnClicked();
    void onShapeBtnClicked();
    void onTextBtnClicked();
    void onDateBtnClicked();
    void onImageBtnClicked();


private :
    QPushButton *shapeBtn,*textbtn,*dateBtn,*barcodeBtn,*imageBtn,*undoBtn,*redoBtn,*saveBtn,*printBtn;
    QPushButton *circleBtn,*ovalBtn,*squareBtn,*rectangleBtn,*triangleBtn,*diamondBtn,*parallelogramBtn,*lineBtn;
    QPushButton *fontBtn,*sizeBtn,*acceptTextBtn,*deleteBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout,*printInfoLayout;
    QHBoxLayout *mainToolsLayout,*shapeSubToolsLayout,*textSubToolsLayout;

    QHBoxLayout *shapeSelectToolLayout;
    QPushButton *fillShapeBtn,*horizantalShapeBtn,*clockRotateShapeBtn,*deleteShapeBtn,*minifyShapeBtn,*magnifyShapeBtn;

    PaintFrame *paintFrame;
    int whichSubToolsVisible = -1; //shape =0 ,text =1 ,image = 2,barcode =3,time = 4,date=5,save=6,undo =7,redo=8,print=9
public slots:
    void circleClicked();
    void rectangleClicked();
    void squareClicked();
    void lineClicked();
    void triangleClicked();
    void ovalClicked();
    void diamondClicked();
    void parallelogramClicked();



    void showPrintWindow();
};

#endif // EDITORWIDGET_H
