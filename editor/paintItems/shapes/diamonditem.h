#ifndef DIAMONDITEM_H
#define DIAMONDITEM_H
#include <paintItems/drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
//#include <QtWidgets>
class DiamondItem:public DrawItem
{
public:
    DiamondItem(QWidget *parent,QPointF position,int xDiagonal,int yDiagonal);

    QPoint getPosition();
    int getWidth() const;
    int getHeight() const ;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();
    bool isInside(QPoint point);

    bool onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    MouseMoveResult onMouseMove(QMouseEvent *event) ;


    void itemDropEvent(QDropEvent *event);
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    void keyboardPressed(QKeyEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF position;
    int xDiagonal;
    int yDiagonal;
};

#endif // DIAMONDITEM_H
