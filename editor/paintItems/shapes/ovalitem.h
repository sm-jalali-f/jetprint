#ifndef OVALITEM_H
#define OVALITEM_H
#include <paintItems/drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
//#include <QtWidgets>
class OvalItem : public DrawItem
{
public:
    OvalItem(QWidget *parent,QPointF position,int xDiagonal,int yDiagonal);
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

#endif // OVALITEM_H
