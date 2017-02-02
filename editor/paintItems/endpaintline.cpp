#include "endpaintline.h"

EndPaintLine::EndPaintLine(QWidget *parent,int height)
{
    this->heightFrame =height;

}

void EndPaintLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush shapeBgBrush;
    shapeBgBrush.setColor(QColor(255,255,255,255));
    scene()->setBackgroundBrush(shapeBgBrush);
    QPen shapePen;
    shapePen.setColor(QColor(Qt::red));
    shapePen.setWidth(3);

    painter->setPen(shapePen);
    painter->setOpacity(Qt::transparent);

//    qDebug()<<"EndPaintLine: paint.x= "<<x();
//    qDebug()<<"EndPaintLine: paint.xPos= "<<xPos;
    for(int i=0;i<this->heightFrame/(this->lineSliceLength+this->lineSpaceLength);i++){
        painter->drawLine(this->xPos,i*(this->lineSliceLength+this->lineSpaceLength)
                          ,this->xPos,(i*(this->lineSliceLength+this->lineSpaceLength))+this->lineSliceLength);

    }


}

QPoint EndPaintLine::getPosition()
{
    QPoint point;
    point.setX(xPos);
    point.setY(0);

    return point;
}

int EndPaintLine::getWidth() const
{
    return this->boundingRect().width();
}

int EndPaintLine::getHeight() const
{
    return this->boundingRect().height();
}

void EndPaintLine::setXPos(int x)
{
    this->xPos =x;
//    this->setX(xPos);
    this->update();
}

void EndPaintLine::setHeightFrame(int height)
{
    this->heightFrame =height;
    this->update();
}

QRectF EndPaintLine::boundingRect() const
{
    int width = 3;
    int height = this->heightFrame;
    return QRectF(xPos,0,width,height);
}

