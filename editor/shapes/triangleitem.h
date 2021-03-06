#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H
#include <drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QtWidgets>
class TriangleItem : public QGraphicsItem,public DrawItem
{
public:
    TriangleItem(QWidget *parent,QPointF position1,QPointF position2,QPointF position3);
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
    QPointF position3;
    QPoint getLeftTopPoint() const;
    QPoint getRightBottomPoint() const;

};

#endif // TRIANGLEITEM_H
