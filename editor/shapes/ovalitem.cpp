#include "ovalitem.h"

OvalItem::OvalItem(QWidget *parent, QPointF position, int xDiagonal, int yDiagonal):DrawItem(),QGraphicsItem()
{
    this->position = position;
    this->yDiagonal = yDiagonal;
    this->xDiagonal = xDiagonal;
}

QPoint OvalItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int OvalItem::getWidth() const
{
    return boundingRect().width();
}

int OvalItem::getHeight() const
{
    return boundingRect().height();
}

QPixmap OvalItem::toPixmap()
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

void OvalItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void OvalItem::hideItem()
{

}

void OvalItem::showItem()
{

}

QRectF OvalItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),xDiagonal,yDiagonal);
//    return QRectF(0,0,30,90);
}

void OvalItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
//    painter->drawEllipse(QRectF(position.x(),position.y(),position.x()+xDiagonal,position.y()+yDiagonal));
    painter->drawEllipse(position.x(),position.y(),xDiagonal,yDiagonal);
}

