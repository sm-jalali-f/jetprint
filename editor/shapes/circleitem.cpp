#include "circleitem.h"

CircleItem::CircleItem(QWidget *parent,int radius , QPointF center):DrawItem(),QGraphicsItem()
{
    this->radius = radius;
    this->center = center;
    this->setToolTip(QString("QColor(%1, %2, %3)\n%4")
                  .arg(color.red()).arg(color.green()).arg(color.blue())
                  .arg("Click and drag this color onto the robot!"));
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
//    setAcceptDrops(true);
}
QRectF CircleItem::boundingRect() const
{
    return QRectF(center.x(),center.y(),radius+2,radius+2);
}
void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    this->scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(Qt::transparent);
    painter->drawEllipse(center.x(),center.y(), radius, radius);

}


QPixmap CircleItem::toPixmap()
{

    if (!this->scene()) {
        qWarning() << "[ControlItem::toPixmap] scene is null.";
        return QPixmap();
    }

    QRectF r = boundingRect();
    QPixmap pixmap(r.width(), r.height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    //painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
    painter.drawRect(r);
    this->scene()->render(&painter, QRectF(), sceneBoundingRect());
    painter.end();
    return pixmap;
}
QPoint CircleItem::getPosition(){
    QPoint point;
    point.setX(this->center.x());
    point.setY(this->center.y());
//    qDebug()<<"CircleItem: getPosition="<<this->center.x()<<","<<this->center.y();
    return point;
}
int CircleItem::getWidth() const {
//    qDebug()<<"CircleItem: getWidth="<<this->boundingRect().width();
    return this->boundingRect().width();
}
int CircleItem::getHeight() const {
//    qDebug()<<"CircleItem: getHeight="<<this->boundingRect().height();
    return this->boundingRect().height();
}

void CircleItem::setPosition(int x, int y)
{
    this->center.setX(x);
    this->center.setY(y);
    update();
}

void CircleItem::hideItem()
{
    hide();
}

void CircleItem::showItem()
{
    show();
}
