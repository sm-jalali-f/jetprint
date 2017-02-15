#include "drawitem.h"
DrawItem::DrawItem(){
    shapePen.setColor(QColor(Qt::black));
    shapePen.setWidth(40);
    dragPen.setColor(QColor(Qt::gray));
    dragPen.setWidth(10);
    shapeBgBrush.setColor(QColor(255,255,255,255));
    itemState =  NOTHING_STATE;
//    isPressed = false;
//    isDraging = false;
//    isSelect = false;
//    isDeleted = false;
}

void DrawItem::hideItem()
{
//    isDeleted=true;
    itemState =  REMOVED;
}

void DrawItem::showItem()
{
    itemState =  NOTHING_STATE;
//    isDeleted = false;

}

bool DrawItem::isRemoved()
{
    if(itemState ==  REMOVED)
        return true;
    return false;

}

DrawItemType DrawItem::getItemType()
{
    return itemType;
}

bool DrawItem::isPressedItem()
{
    if(itemState ==  NOTHING_STATE)
        return false;
    if(itemState ==  SELECTED)
        return false;
    if(itemState ==  REMOVED)
        return false;
    return true;
}

bool DrawItem::isDragingItem()
{
    if(itemState ==  DRAGING)
        return true;
    return false;
}

bool DrawItem::isSelectedItem()
{
    if(itemState ==  SELECTED)
        return true;
    return false;
}

bool DrawItem::isInTopResizeArea(QPoint pos)
{
    if(pos.x() > middleTop.x() - borderCircleRadius && pos.x() < middleTop.x()+ borderCircleRadius
            && pos.y() > middleTop.y()-borderCircleRadius && pos.y() <middleTop.y()+borderCircleRadius)
        return true;

    return false;

}

bool DrawItem::isInBottomResizeArea(QPoint point)
{
    if(point.x() > middleBottom.x() - borderCircleRadius && point.x() < middleBottom.x()+ borderCircleRadius
            && point.y() > middleBottom.y()-borderCircleRadius && point.y() <middleBottom.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInLeftResizeArea(QPoint point)
{
    if(point.x() > middleLeft.x() - borderCircleRadius && point.x() < middleLeft.x()+ borderCircleRadius
            && point.y() > middleLeft.y()-borderCircleRadius && point.y() <middleLeft.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInRightResizeArea(QPoint point)
{
    if(point.x() > middleRight.x() - borderCircleRadius && point.x() < middleRight.x()+ borderCircleRadius
            && point.y() > middleRight.y()-borderCircleRadius && point.y() <middleRight.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInRightTopResizeArea(QPoint point)
{
    if(point.x() > rightTop.x() - borderCircleRadius && point.x() < rightTop.x()+ borderCircleRadius
            && point.y() > rightTop.y()-borderCircleRadius && point.y() <rightTop.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInRightBottomResizeArea(QPoint point)
{
    if(point.x() > rightBottom.x() - borderCircleRadius && point.x() < rightBottom.x()+ borderCircleRadius
            && point.y() > rightBottom.y()-borderCircleRadius && point.y() <rightBottom.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInLeftBottomResizeArea(QPoint point)
{
    if(point.x() > leftBottom.x() - borderCircleRadius && point.x() < leftBottom.x()+ borderCircleRadius
            && point.y() > leftBottom.y()-borderCircleRadius && point.y() <leftBottom.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInLeftTopResizeArea(QPoint point)
{
    if(point.x() > leftTop.x() - borderCircleRadius && point.x() < leftTop.x()+ borderCircleRadius
            && point.y() > leftTop.y()-borderCircleRadius && point.y() <leftTop.y()+borderCircleRadius)
        return true;

    return false;
}

bool DrawItem::isInRotateArea(QPoint point)
{
    if( point.x()< rotateRect.x()+rotateRect.width()
                    && point.x() > rotateRect.x()
                    && point.y() > rotateRect.y()
                    && point.y() < rotateRect.y()+rotateRect.height()){
        return true;

    }
//    qDebug()<<"DrawItem: isInRotateArea Nope";
    return false;

}

MouseMoveResult DrawItem::whereIsPoint(QPoint point)
{

    if(isInTopResizeArea(point))
        return  TOP_RESIZE;
    else if(isInBottomResizeArea(point))
        return  BOTTOM_RESIZE;
    else if(isInLeftResizeArea(point))
        return  LEFT_RESIZE;
    else if(isInRightResizeArea(point))
        return  RIGHT_RESIZE;
    else if(isInLeftTopResizeArea(point))
        return  LEFT_TOP_RESIZE;
    else if(isInRightTopResizeArea(point))
        return  RIGHT_TOP_RESIZE;
    else if(isInLeftBottomResizeArea(point))
        return  LEFT_BOTTOM_RESIZE;
    else if(isInRightBottomResizeArea(point))
        return  RIGHT_BOTTOM_RESIZE;
    else if(isInside(point))
        return  INSIDE;
    else if(isInRotateArea(point))
        return  ROTATE;
    return  NOTHING;
}
void DrawItem::paintSelectBorder(QPainter *painter, QPointF leftTop, QPointF rightTop, QPointF leftBottom, QPointF rightBottom)
{
//    painter
    painter->setPen(QColor(Qt::red));

    painter->drawEllipse(QPoint(leftTop.x(),leftTop.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(rightBottom.x(),rightBottom.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(leftBottom.x(),leftBottom.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(rightTop.x(),rightTop.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(middleLeft.x(),middleLeft.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(middleBottom.x(),middleBottom.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(middleRight.x(),middleRight.y()),borderCircleRadius,borderCircleRadius);
    painter->drawEllipse(QPoint(middleTop.x(),middleTop.y()),borderCircleRadius,borderCircleRadius);
    int margin =(int)(borderCircleRadius/2) +2;
    // draw top line
    painter->drawLine(QPointF(leftTop.x()+margin,leftTop.y()),QPointF(middleTop.x()-margin,middleTop.y()));
    painter->drawLine(QPointF(middleTop.x()+margin,middleTop.y()),QPointF(rightTop.x()-margin,rightTop.y()));
    //draw bottom line
    painter->drawLine(QPointF(leftBottom.x()+margin,leftBottom.y()),QPointF(middleBottom.x()-margin,middleBottom.y()));
    painter->drawLine(QPointF(middleBottom.x()+margin,middleBottom.y()),QPointF(rightBottom.x()-margin,rightBottom.y()));
    //draw left line
    painter->drawLine(QPointF(leftTop.x(),leftTop.y()+margin),QPointF(middleLeft.x(),middleLeft.y()-margin));
    painter->drawLine(QPointF(middleLeft.x(),middleLeft.y()+margin),QPointF(leftBottom.x(),leftBottom.y()-margin));
    //draw right line
    painter->drawLine(QPointF(rightTop.x(),rightTop.y()+margin),QPointF(middleRight.x(),middleRight.y()-margin));
    painter->drawLine(QPointF(middleRight.x(),middleRight.y()+margin),QPointF(rightBottom.x(),rightBottom.y()-margin));
}

void DrawItem::updateCornerPoint()
{
    leftTop = QPointF(getPosition().x(),getPosition().y());
    rightTop = QPointF(getPosition().x()+boundingRect().width(),getPosition().y());
    leftBottom = QPointF(getPosition().x(),getPosition().y()+boundingRect().height());
    rightBottom = QPointF(getPosition().x()+boundingRect().width()
                          ,getPosition().y()+boundingRect().height());

    middleLeft = QPointF(leftTop.x(),(int)((leftTop.y()+leftBottom.y())/2));
    middleRight = QPointF(rightTop.x(),(int)((rightTop.y()+rightBottom.y())/2));
    middleBottom = QPointF((int)((leftBottom.x()+rightBottom.x())/2),leftBottom.y());
    middleTop = QPointF((int)((leftTop.x()+rightTop.x())/2),leftTop.y());
}

DrawItemState DrawItem::getItemState()
{
    return itemState;
}

void DrawItem::unSelect()
{
    if(itemState!=REMOVED)
        itemState=NOTHING_STATE;
}

bool DrawItem::isDrawBorder()
{
    if(itemState==NOTHING_STATE || itemState == PREPARE_FOR_DRAGING
            || itemState == DRAGING || itemState == REMOVED)
        return false;
    return true;
}

void DrawItem::mousePressUpdateState(QPoint point)
{
    MouseMoveResult res = whereIsPoint(point);
    switch (res) {
    case  ROTATE:
        itemState =   ROTATING;
    case  NOTHING:
        itemState =  NOTHING_STATE;
        break;
    case  TOP_RESIZE:
        itemState =  TOP_RESIZING;
        break;
    case  LEFT_RESIZE :
        itemState =  LEFT_RESIZING;
        break;
    case  RIGHT_RESIZE :
        itemState =  RIGHT_RESIZING;
        break;
    case  BOTTOM_RESIZE :
        itemState =  BOTTOM_RESIZING;
        break;
    case  LEFT_TOP_RESIZE :
        itemState =  LEFT_TOP_RESIZING;
        break;
    case  LEFT_BOTTOM_RESIZE :
        itemState =  LEFT_BOTTOM_RESIZING;
        break;
    case  RIGHT_TOP_RESIZE :
        itemState =  RIGHT_TOP_RESIZING;
        break;
    case  RIGHT_BOTTOM_RESIZE :
        itemState =  RIGHT_BOTTOM_RESIZING;
        break;
    case  INSIDE:
        itemState =  PREPARE_FOR_DRAGING;
    default:
        break;
    }
}

void DrawItem:: mouseReleaseUpdateState(QPoint point)
{


    switch (itemState) {
        case  PREPARE_FOR_DRAGING:
            itemState =  SELECTED;
            break;
        case  TOP_RESIZING :
            itemState =  SELECTED;
            break;

        case  RIGHT_RESIZING :
            itemState =  SELECTED;
            break;

        case  LEFT_RESIZING :
            itemState =  SELECTED;
            break;

        case  BOTTOM_RESIZING :
            itemState =  SELECTED;
            break;

        case  LEFT_TOP_RESIZING :
            itemState =  SELECTED;
            break;

        case  LEFT_BOTTOM_RESIZING :
            itemState =  SELECTED;
            break;

        case  RIGHT_TOP_RESIZING :
            itemState =  SELECTED;
            break;

        case  RIGHT_BOTTOM_RESIZING :
            itemState =  SELECTED;
            break;


    }

//    case  TOP_RESIZING:

//        break;
//    case  LEFT_RESIZING :

//        break;
//    case  RIGHT_RESIZING :

//        break;
//    case  BOTTOM_RESIZING :

//        break;
//    case  LEFT_TOP_RESIZING :

//        break;
//    case  LEFT_BOTTOM_RESIZING :

//        break;
//    case  RIGHT_TOP_RESIZING :

//        break;
//    case  RIGHT_BOTTOM_RESIZING :

//        break;
//    case  PREPARE_FOR_DRAGING:
//        itemState =  SELECTED;
//        break;
//    case  SELECTED :

//        break;
//    }

}
