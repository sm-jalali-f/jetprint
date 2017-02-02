#include "rectangleitem.h"

RectangleItem::RectangleItem(QWidget *parent,QPointF position, int width, int height):DrawItem(),QGraphicsItem()
{
    this->position = position;
    this->width = width;
    this->height = height;

}

QPoint RectangleItem::getPosition()
{
    QPoint pos;
    pos.setX(position.x());
    pos.setY(position.y());
    return pos;
}

int RectangleItem::getWidth() const
{
    return this->boundingRect().width();
}

int RectangleItem::getHeight() const
{
    return this->boundingRect().height();
}

QPixmap RectangleItem::toPixmap()
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

void RectangleItem::setPosition(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

void RectangleItem::hideItem()
{
    this->hide();
}

void RectangleItem::showItem()
{
    this->show();
}

QRectF RectangleItem::boundingRect() const
{
     return QRectF(position.x(),position.y(),this->width,this->height);
}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
    painter->drawRect(position.x(),position.y(),this->width,this->height);
}
