#ifndef OVALITEM_H
#define OVALITEM_H
#include <drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QtWidgets>
class OvalItem : public QGraphicsItem,public DrawItem
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

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF position;
    int xDiagonal;
    int yDiagonal;

};

#endif // OVALITEM_H
