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
    VerticalRuler(QWidget *parent,int height,int rulerWidth);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint getPosition();
    void setHeightRuler(int height);
    int getWidth() const;
    int getHeight() const;
    QRectF boundingRect() const;
    int getInterval();
    QPoint getLastLine();
    int REAL_FIXED_HEIGHT = 18; // height of print is 18 milimeter
private:

    int heightRuler;
    int interval;
    int shortLineLength =20;
    int longLineLength =40;
    QPoint lastLinePos;
};

#endif // VERTICALRULER_H
