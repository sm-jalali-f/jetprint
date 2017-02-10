#ifndef NEWPRINTWINDOW_H
#define NEWPRINTWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include "printsettingdialog.h"
#include "paintframe.h"
#include <QRect>
class NewPrintWindow :public QWidget
{
    Q_OBJECT
public:
    NewPrintWindow(PaintFrame *frame,QWidget *parent = 0);
private:
    QLabel *printPreviewLabel,*printCounterLabel;
    QPushButton *startStopBtn,*backToEditorBtn,*printSettingBtn;
    bool isPrinting=false;
    PaintFrame *mPaintFrame;
public slots:
    void startStopClicked();
    void settingClicked();
    void backToEditorClicked();


};

#endif // NEWPRINTWINDOW_H
