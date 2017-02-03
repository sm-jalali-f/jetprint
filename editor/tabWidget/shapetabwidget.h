#ifndef SHAPETABWIDGET_H
#define SHAPETABWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

class ShapeTabWidget:public QWidget
{
    Q_OBJECT
public:
    ShapeTabWidget(QWidget *parent=0);
    QPushButton *circleBtn,*ovalBtn,*squareBtn,*rectangleBtn,*triangleBtn,*diamondBtn,*parallelogramBtn,*lineBtn;

public slots:
    void circleClicked();
    void rectangleClicked();
    void squareClicked();
    void lineClicked();
    void triangleClicked();
    void ovalClicked();
    void diamondClicked();
    void parallelogramClicked();

};

#endif // SHAPETABWIDGET_H
