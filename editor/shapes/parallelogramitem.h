#ifndef PARALLELOGRAMITEM_H
#define PARALLELOGRAMITEM_H
#include <drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QtWidgets>
#include <QtCore/qmath.h>
class ParallelogramItem : public QGraphicsItem,public DrawItem
{
public:
    ParallelogramItem(QWidget *parent,QPointF position,int width,int height,float leftBottomVertexAngle);
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
    float leftBottomVertexAngle;
    int width;
    int height;
};

#endif // PARALLELOGRAMITEM_H
