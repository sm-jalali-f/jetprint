#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsItem>
#include <qdebug.h>
#include <QMouseEvent>
#include <paintItems/drawitem.h>
//#include <QtWidget>
class LineItem: public DrawItem
{
public:
    LineItem(QWidget *parent,QPointF position1,QPointF position2);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();
    bool isInside(QPoint point);
    void changeFontSize(int fontSize);

    bool onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    MouseMoveResult onMouseMove(QMouseEvent *event) ;


    void itemDropEvent(QDropEvent *event);
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    void keyboardPressed(QKeyEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF position1;
    QPointF position2;


};

#endif // LINEITEM_H
