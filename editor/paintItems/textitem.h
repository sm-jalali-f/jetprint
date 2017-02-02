#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <paintItems/drawitem.h>
#include <QDebug>
#include <QPainter>
//#include <QtWidgets>
class TextItem : public DrawItem
{
public:
    TextItem(QWidget *parent,QPointF position,int width,int height);
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

    void keyboardPressed(QKeyEvent *event);

    void itemDropEvent(QDropEvent *event);
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    void paintSelectBorder(QPainter *painter, QPointF leftTop, QPointF rightTop,QPointF leftBottom,QPointF rightBottom);
private:
    QString text = "Text";
    QPointF position;
    int width;
    int height;
    void buildKeyboardHash();
    QHash<int,QString> *keyboardHash;
};

#endif // TEXTITEM_H
