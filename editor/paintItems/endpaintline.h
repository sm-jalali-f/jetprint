#ifndef ENDPAINTLINE_H
#define ENDPAINTLINE_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDebug>

class EndPaintLine:public QGraphicsItem
{
public:
    EndPaintLine(QWidget *parent,int height);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    void setXPos(int);
    void setHeightFrame(int height);
    QRectF boundingRect() const;
private:
    int xPos;
    int heightFrame;
    int lineSliceLength = 8;
    int lineSpaceLength = 8;
};

#endif // ENDPAINTLINE_H
