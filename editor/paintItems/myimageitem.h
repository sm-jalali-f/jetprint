#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H
#include <paintItems/drawitem.h>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
//#include <QtWidgets>
class MyImageItem:public DrawItem
{
public:
    MyImageItem(QWidget *parent,QPointF position,int width,int height,QString filePath);
    QPoint getPosition();
    int getWidth() const;
    int getHeight() const ;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();
    bool isInside(QPoint point);

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
    QPointF position;
    int width;
    int height;
    QImage image;

    void updateImage();
};

#endif // MYIMAGEITEM_H
