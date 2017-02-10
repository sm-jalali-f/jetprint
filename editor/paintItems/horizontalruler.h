#ifndef HORIZONTALRULER_H
#define HORIZONTALRULER_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

class HorizontalRuler: public QGraphicsItem
{
public:
    HorizontalRuler(QWidget *parent,int posX,int posY,int width,int interval,int rulerWidth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QRectF boundingRect() const;
private:
    int startX;
    int startY;
    int widthRuler;
    int interval;
    int shortLineLength =20;
    int longLineLength =40;
};

#endif // HORIZONTALRULER_H
