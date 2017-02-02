#include "triangleitem.h"

TriangleItem::TriangleItem(QWidget *parent, QPointF position1, QPointF position2, QPointF position3)
    :DrawItem(),QGraphicsItem()
{
    this->position1 =position1;
    this->position2 =position2;
    this->position3 =position3;

}

QPoint TriangleItem::getPosition()
{
    return getLeftTopPoint();
}

int TriangleItem::getWidth() const
{
    return (getRightBottomPoint().x()-getLeftTopPoint().x());
}

int TriangleItem::getHeight() const
{
    return (getRightBottomPoint().y()-getLeftTopPoint().y());
}

QPixmap TriangleItem::toPixmap()
{
    if (!scene()) {
        qWarning() << "[ControlItem::toPixmap] scene is null.";
        return QPixmap();
    }

    QRectF r = boundingRect();
    QPixmap pixmap(r.width(), r.height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.drawRect(r);
    scene()->render(&painter, QRectF(), sceneBoundingRect());
    painter.end();
    return pixmap;
}

void TriangleItem::setPosition(int x, int y)
{
    QPoint leftTop;
    leftTop = getLeftTopPoint();
    int diffX = x- leftTop.x();
    int diffY = y - leftTop.y();
    qDebug()<<"pos1:"<<position1;
    qDebug()<<"pos2:"<<position2;
    qDebug()<<"pos3:"<<position3;
    position1.setX(position1.x()+diffX);
    position2.setX(position2.x()+diffX);
    position3.setX(position3.x()+diffX);
    position1.setY(position1.y()+diffY);
    position2.setY(position2.y()+diffY);
    position3.setY(position3.y()+diffY);
    qDebug()<<"updated pos1:"<<position1;
    qDebug()<<"updated pos2:"<<position2;
    qDebug()<<"updated pos3:"<<position3;



}

void TriangleItem::hideItem()
{

}

void TriangleItem::showItem()
{

}

QRectF TriangleItem::boundingRect() const
{
    QPointF leftTop = getLeftTopPoint();
    return QRectF(leftTop.x(),leftTop.y(),getWidth(),getHeight());
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
    painter->drawLine(QLine(position1.x(),position1.y(),position2.x(),position2.y()));
    painter->drawLine(QLine(position1.x(),position1.y(),position3.x(),position3.y()));
    painter->drawLine(QLine(position3.x(),position3.y(),position2.x(),position2.y()));
}

QPoint TriangleItem::getLeftTopPoint() const
{
    int minX,minY;
    if(position1.x()<position2.x()){
        if(position1.x()<position3.x())
            minX = position1.x();
        else
            minX = position3.x();
    }else{
        if(position2.x()<position3.x())
            minX = position2.x();
        else
            minX = position3.x();
    }
    if(position1.y()<position2.y()){
        if(position1.y()<position3.y())
            minY = position1.y();
        else
            minY = position3.y();
    }else{
        if(position2.y()<position3.y())
            minY = position2.y();
        else
            minY = position3.y();
    }
    return QPoint(minX,minY);
}

QPoint TriangleItem::getRightBottomPoint() const
{
    int maxX,maxY;
    if(position1.x()>position2.x()){
        if(position1.x()>position3.x())
            maxX = position1.x();
        else
            maxX = position3.x();
    }else{
        if(position2.x()>position3.x())
            maxX = position2.x();
        else
            maxX = position3.x();
    }
    if(position1.y()>position2.y()){
        if(position1.y()>position3.y())
            maxY = position1.y();
        else
            maxY = position3.y();
    }else{
        if(position2.y()>position3.y())
            maxY = position2.y();
        else
            maxY = position3.y();
    }
    return QPoint(maxX,maxY);
}
