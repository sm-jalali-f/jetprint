#include "shapetabwidget.h"

ShapeTabWidget::ShapeTabWidget(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("background-color:#E8E8E8");

//    this->setFixedHeight();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QPushButton *shapeBtn = new QPushButton;
    QPixmap pixmapShape(":/res/icons/ic_circle");
    QIcon shapeIcon(pixmapShape);
    shapeBtn->setIcon(shapeIcon);
    shapeBtn->setIconSize(pixmapShape.rect().size()/1);
    shapeBtn->setFixedSize(pixmapShape.rect().size()*1.3);
    shapeBtn->setStyleSheet("background-color:#D3D3D3;color:#e3e3e3");
    circleBtn = new QPushButton();
    QPixmap pixmapCircle(":/res/icons/ic_circle");
    QIcon circleIcon(pixmapCircle);
    circleBtn->setIcon(circleIcon);
    circleBtn->setIconSize(pixmapCircle.rect().size()/2);
    circleBtn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);
    circleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    ovalBtn= new QPushButton();
    QPixmap pixmapOval(":/res/icons/ic_ellipse");
    QIcon ovalIcon(pixmapOval);
    ovalBtn->setIcon(ovalIcon);
    ovalBtn->setIconSize(pixmapOval.rect().size()/2);
    ovalBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    ovalBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    squareBtn= new QPushButton();
    QPixmap pixmapSquare(":/res/icons/ic_square");
    QIcon squareIcon(pixmapSquare);
    squareBtn->setIcon(squareIcon);
    squareBtn->setIconSize(pixmapSquare.rect().size()/2);
    squareBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    squareBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    rectangleBtn= new QPushButton();
    QPixmap pixmaprectangle(":/res/icons/ic_rectangle");
    QIcon rectangleIcon(pixmaprectangle);
    rectangleBtn->setIcon(rectangleIcon);
    rectangleBtn->setIconSize(pixmaprectangle.rect().size()/2);
    rectangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    rectangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    triangleBtn = new QPushButton();
    QPixmap pixmaptriangle(":/res/icons/ic_triangle");
    QIcon triangleIcon(pixmaptriangle);
    triangleBtn->setIcon(triangleIcon);
    triangleBtn->setIconSize(pixmaptriangle.rect().size()/2);
    triangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    triangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    diamondBtn = new QPushButton();
    QPixmap pixmapdiamond(":/res/icons/ic_diamonds");
    QIcon diamondIcon(pixmapdiamond);
    diamondBtn->setIcon(diamondIcon);
    diamondBtn->setIconSize(pixmapdiamond.rect().size()/2);
    diamondBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    diamondBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    parallelogramBtn = new QPushButton();
    QPixmap pixmapparallelogram(":/res/icons/ic_parallalogram");
    QIcon parallelogramIcon(pixmapparallelogram);
    parallelogramBtn->setIcon(parallelogramIcon);
    parallelogramBtn->setIconSize(pixmapparallelogram.rect().size()/2);
    parallelogramBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    parallelogramBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    lineBtn = new QPushButton();
    QPixmap pixmapline(":/res/icons/ic_line");
    QIcon lineIcon(pixmapline);
    lineBtn->setIcon(lineIcon);
    lineBtn->setIconSize(pixmapline.rect().size()/2);
    lineBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    lineBtn->setStyleSheet("margin-left: 3px;margin-right:30px");
    hLayout->addWidget(circleBtn);
    hLayout->addWidget(ovalBtn);
    hLayout->addWidget(squareBtn);
    hLayout->addWidget(rectangleBtn);
    hLayout->addWidget(triangleBtn);
    hLayout->addWidget(diamondBtn);
    hLayout->addWidget(parallelogramBtn);
    hLayout->addWidget(lineBtn);
    hLayout->addStretch(1);
    setLayout(hLayout);

}

void ShapeTabWidget::circleClicked()
{

}

void ShapeTabWidget::rectangleClicked()
{

}

void ShapeTabWidget::squareClicked()
{

}

void ShapeTabWidget::lineClicked()
{

}

void ShapeTabWidget::triangleClicked()
{

}

void ShapeTabWidget::ovalClicked()
{

}

void ShapeTabWidget::diamondClicked()
{

}

void ShapeTabWidget::parallelogramClicked()
{

}

