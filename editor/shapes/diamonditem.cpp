#include "diamonditem.h"

DiamondItem::DiamondItem(QWidget *parent, QPointF position, int xDiagonal, int yDiagonal)
    :DrawItem(),QGraphicsItem()
{
    this->xDiagonal = xDiagonal;
    this->yDiagonal = yDiagonal;
    this->position = position;
}

QPoint DiamondItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int DiamondItem::getWidth() const
{
    return boundingRect().width();
}

int DiamondItem::getHeight() const
{
    return boundingRect().height();
}

QPixmap DiamondItem::toPixmap()
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

void DiamondItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void DiamondItem::hideItem()
{

}

void DiamondItem::showItem()
{

}

QRectF DiamondItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),xDiagonal,yDiagonal);
}

void DiamondItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
    QPoint v1(position.x(),position.y()+yDiagonal/2);
    QPoint v2(position.x()+xDiagonal/2,position.y());
    QPoint v3(position.x()+xDiagonal,position.y()+yDiagonal/2);
    QPoint v4(position.x()+xDiagonal/2,position.y()+yDiagonal);
    painter->drawLine(v1.x(),v1.y(),v2.x(),v2.y());
    painter->drawLine(v3.x(),v3.y(),v2.x(),v2.y());
    painter->drawLine(v3.x(),v3.y(),v4.x(),v4.y());
    painter->drawLine(v1.x(),v1.y(),v4.x(),v4.y());
}

