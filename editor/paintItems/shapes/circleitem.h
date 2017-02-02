#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H
#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <paintItems/drawitem.h>
//#include <QtMath>
class CircleItem :public DrawItem
{

public:
    CircleItem(QWidget *parent, int radiusX = 20,int radiusY = 20, QPointF center = QPointF(0,0));
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();
    bool isInside(QPoint point);

    bool onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    MouseMoveResult  onMouseMove(QMouseEvent *event);

    void itemDropEvent(QDropEvent *event);
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    void keyboardPressed(QKeyEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QPointF center;
    int radiusX;
    int radiusY;
    QColor color;

};

#endif // CIRCLEITEM_H
