#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <paintItems/drawitem.h>
class CircleItem : public QGraphicsItem,public DrawItem
{

public:
    CircleItem(QWidget *parent, int radius = 20, QPointF center = QPointF(0,0));
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();

    QPointF center;
    int radius;
    bool ispressed=false;
    bool isPressed();
    void setIsPressed(bool isPressed);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    bool drag = false;
    QColor color;

};

#endif // CIRCLEITEM_H
