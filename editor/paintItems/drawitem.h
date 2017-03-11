#ifndef DRAWITEM_H
#define DRAWITEM_H

#include <QPoint>
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QGraphicsItem>
#include "types/drawitemtype.h"
#include "types/mousemoveresult.h"
#include "types/drawitemstate.h"
#include <QtDebug>
#include <QGraphicsScene>
#include <QMimeData>
#include <QDrag>
#include <QWidget>
class DrawItem :public QGraphicsItem
{
public:
    DrawItem();
    virtual QPoint getPosition() = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setPosition(int x,int y) = 0;
    virtual QPixmap toPixmap() = 0;
    virtual void changeFontSize(int fontSize) = 0;
    void hideItem();
    void showItem();
    bool isRemoved();
    virtual bool isInside(QPoint point) = 0;

    virtual bool onMousePressed(QMouseEvent *event) = 0; // return true if this item is pressed else return false
    virtual void onMouseReleased(QMouseEvent *event) = 0;
    //return 2 if enter to draging and if mouse isnside item return 1 else return 0
    virtual MouseMoveResult onMouseMove(QMouseEvent *event) = 0;


    virtual void itemDropEvent(QDropEvent *event) = 0;
    virtual void itemDragEnterEvent(QDragEnterEvent *event) = 0 ;
    virtual void itemDragMoveEvent(QDragMoveEvent *event) = 0;

    virtual void keyboardPressed(QKeyEvent *event) =0;
//    virtual void paintSelectBorder() =0;

    DrawItemType getItemType();
    bool isPressedItem();
    bool isDragingItem( );
    bool isSelectedItem();
    bool isInTopResizeArea(QPoint point);
    bool isInBottomResizeArea(QPoint point);
    bool isInLeftResizeArea(QPoint point);
    bool isInRightResizeArea(QPoint point);
    bool isInRightTopResizeArea(QPoint point);
    bool isInRightBottomResizeArea(QPoint point);
    bool isInLeftBottomResizeArea(QPoint point);
    bool isInLeftTopResizeArea(QPoint point);
    bool isInRotateArea(QPoint point);

    MouseMoveResult whereIsPoint(QPoint);
    void paintSelectBorder(QPainter *painter, QPointF leftTop
                           , QPointF rightTop,QPointF leftBottom,QPointF rightBottom);
    void updateCornerPoint();
    DrawItemState getItemState();
    void unSelect();
protected:
    QPoint rotateClickedPos;
    static const int IC_ROTATE_SIZE = 24;
    QRectF rotateRect;
    bool isDrawBorder();
    void mousePressUpdateState(QPoint point);
    void mouseReleaseUpdateState(QPoint point);
    int id;
    QWidget *parent;
    int insideX,insideY; // kojaye item press shode

//    bool isPressed;
//    bool isSelect;
//    bool isDraging;
//    bool isDeleted;
    DrawItemState itemState;

    QPen shapePen;
    QPen dragPen;
    QBrush shapeBgBrush;
    DrawItemType itemType;
    int borderCircleRadius = 6;
    QPointF middleLeft,middleRight,middleTop,middleBottom;
    QPointF leftTop,rightTop,leftBottom,rightBottom;

};

#endif // DRAWITEM_H
