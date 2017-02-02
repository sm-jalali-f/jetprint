#ifndef VERTICALRULER_H
#define VERTICALRULER_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>
class VerticalRuler : public QGraphicsItem
{


public:
    VerticalRuler(QWidget *parent,int height,int interval);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QRectF boundingRect() const;
private:
    int heightRuler;
    int interval;
    int shortLineLength =40;
    int longLineLength =80;
};

#endif // VERTICALRULER_H
