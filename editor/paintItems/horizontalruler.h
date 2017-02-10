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
    HorizontalRuler(QWidget *parent,int startX,int width,int height,int interval,int rulerWidth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QRectF boundingRect() const;
private:
    int startX;
    int widthRuler;
    int interval;
    int shortLineLength =20;
    int longLineLength =40;
    int pageHeight;
};

#endif // HORIZONTALRULER_H
