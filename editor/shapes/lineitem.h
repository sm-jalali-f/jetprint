#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <drawitem.h>
#include <QtWidgets>
class LineItem: public QGraphicsItem,public DrawItem
{
public:
    LineItem(QWidget *parent,QPointF position1,QPointF position2);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF position1;
    QPointF position2;

};

#endif // LINEITEM_H
