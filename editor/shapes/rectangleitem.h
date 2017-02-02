#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H
#include <drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QtWidgets>
class RectangleItem : public QGraphicsItem,public DrawItem
{
public:
    RectangleItem(QWidget *parent,QPointF position,int width,int height);
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
    int width;
    int height;
};

#endif // RECTANGLEITEM_H
