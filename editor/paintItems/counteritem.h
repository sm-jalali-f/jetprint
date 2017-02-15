#ifndef COUNTERITEM_H
#define COUNTERITEM_H

#include <paintItems/drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QDateTime>
class CounterItem :public DrawItem
{
public:
    CounterItem(QWidget *parent,QPointF position,int width,int height);
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
    void setStartCounter(int start);
    void incrementCounter();
private:
    QPointF position;
    int width;
    int height;
    int counter =1;

};

#endif // COUNTERITEM_H
