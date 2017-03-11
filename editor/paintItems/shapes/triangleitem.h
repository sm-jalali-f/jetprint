#ifndef TRIANGLEITEM_H
#define TRIANGLEITEM_H
#include <paintItems/drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
//#include <QtWidgets>
class TriangleItem : public DrawItem
{
public:
    TriangleItem(QWidget *parent,QPointF position1,QPointF position2,QPointF position3);
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


    void itemDropEvent(QDropEvent *event) ;
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    void keyboardPressed(QKeyEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPointF position1;
    QPointF position2;
    QPointF position3;
    QPoint getLeftTopPoint() const;
    QPoint getRightBottomPoint() const;

};

#endif // TRIANGLEITEM_H
