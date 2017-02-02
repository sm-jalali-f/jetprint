#include "parallelogramitem.h"

ParallelogramItem::ParallelogramItem(QWidget *parent, QPointF position, int width, int height, float leftBottomVertexAngle)
    :DrawItem(),QGraphicsItem()
{
    this->position = position;
    this->width = width;
    this->height= height;
    this->leftBottomVertexAngle = leftBottomVertexAngle;

}

QPoint ParallelogramItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int ParallelogramItem::getWidth() const
{
    return width;
}

int ParallelogramItem::getHeight() const
{
    return height;
}

QPixmap ParallelogramItem::toPixmap()
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

void ParallelogramItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void ParallelogramItem::hideItem()
{

}

void ParallelogramItem::showItem()
{

}

QRectF ParallelogramItem::boundingRect() const
{
    return QRect(position.x(),position.y(),width,height);
}

void ParallelogramItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(TRANSPARENT);
    QPoint v1,v2,v3,v4;
    if(leftBottomVertexAngle <=90 ){
//        qDebug()<<"part 1";
        v1 = QPoint(position.x()+height/(qTan(qDegreesToRadians(leftBottomVertexAngle))),position.y());
        v2 = QPoint(position.x()+width,position.y());
        v3 = QPoint(position.x()+width -(height/qTan(qDegreesToRadians(leftBottomVertexAngle))),position.y()+height);
        v4 = QPoint(position.x(),position.y()+height);
    }else if(leftBottomVertexAngle > 90 && leftBottomVertexAngle <180){
//        qDebug()<<"part 2";
        v1 = QPoint(position.x(),position.y());
        v2 = QPoint( position.x() + width-height/qTan(qDegreesToRadians(180-leftBottomVertexAngle)) , position.y());
        v3 = QPoint(position.x()+width , position.y()+height);
        v4 = QPoint(position.x()+(height/(qTan(qDegreesToRadians(180-leftBottomVertexAngle)))) , position.y()+height);
    }else if(leftBottomVertexAngle > 180 && leftBottomVertexAngle <270){
//        qDebug()<<"part 3";
        leftBottomVertexAngle =180-(360- leftBottomVertexAngle);
        v1 = QPoint(position.x()+height/(qTan(qDegreesToRadians(leftBottomVertexAngle))),position.y());
        v2 = QPoint(position.x()+width,position.y());
        v3 = QPoint(position.x()+width -(height/qTan(qDegreesToRadians(leftBottomVertexAngle))),position.y()+height);
        v4 = QPoint(position.x(),position.y()+height);
    }else if(leftBottomVertexAngle > 270 && leftBottomVertexAngle <360){
//        qDebug()<<"part 4";
        leftBottomVertexAngle =180-(360- leftBottomVertexAngle);
        v1 = QPoint(position.x(),position.y());
        v2 = QPoint(position.x()+width-(height/(qTan(qDegreesToRadians(180-leftBottomVertexAngle)))) , position.y());
        v3 = QPoint(position.x()+width , position.y()+height);
        v4 = QPoint(position.x()+(height/(qTan(qDegreesToRadians(180-leftBottomVertexAngle)))) , position.y()+height);
    }
//    qDebug()<<"v1: "<<v1;
//    qDebug()<<"v2: "<<v2;
//    qDebug()<<"v3: "<<v3;
//    qDebug()<<"v4: "<<v4;
    painter->drawLine(QPointF(v1.x(),v1.y()),QPointF(v2.x(),v2.y()));
    painter->drawLine(QPointF(v2.x(),v2.y()),QPointF(v3.x(),v3.y()));
    painter->drawLine(QPointF(v3.x(),v3.y()),QPointF(v4.x(),v4.y()));
    painter->drawLine(QPointF(v4.x(),v4.y()),QPointF(v1.x(),v1.y()));
}


