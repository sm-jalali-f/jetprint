#include "lineitem.h"

LineItem::LineItem(QWidget *parent, QPointF position1,QPointF position2):DrawItem(),QGraphicsItem()
{
    this->position1 = position1;
    this->position2 = position2;

}

QPoint LineItem::getPosition()
{
    QPoint point;
    if(position1.x()<position2.x())
        point.setX(position1.x());
    else
        point.setX(position2.x());
    if(position1.y()<position2.y())
        point.setY(position1.y());
    else
        point.setY(position2.y());

    return point;
}

int LineItem::getWidth() const
{
    return this->boundingRect().width();
}

int LineItem::getHeight() const
{
    return this->boundingRect().height();
}

QPixmap LineItem::toPixmap()
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

void LineItem::setPosition(int x, int y)
{
    int diffX = x - getPosition().x();
    int diffY = y - getPosition().y();
    position2.setX(diffX+position2.x());
    position2.setY(diffY+position2.y());
    position1.setX(diffX+position1.x());
    position1.setY(diffY+position1.y());
}

void LineItem::hideItem()
{

}

void LineItem::showItem()
{

}

QRectF LineItem::boundingRect() const
{
    int width = position2.x()-position1.x();
    int height = position2.y()-position1.y();
    if(position1.x()<position2.x() && position1.y()<position2.y())
        return QRectF(position1.x(),position1.y(),width,height);
    else if(position1.x()<position2.x() && position1.y()>position2.y())
        return QRectF(position1.x(),position2.y(),width,height);
    else if(position1.x()>position2.x() && position1.y()<position2.y())
        return QRectF(position2.x(),position1.y(),width,height);
    else if(position1.x()>position2.x() && position1.y()>position2.y())
        return QRectF(position2.x(),position2.y(),width,height);
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
    painter->drawLine(position1.x(),position1.y(),position2.x(),position2.y());
}
