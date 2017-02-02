#include "horizontalruler.h"

HorizontalRuler::HorizontalRuler(QWidget *parent, int startX,int width,int height, int interval)
{
    this->widthRuler =width;
    this->startX =startX;
    this->setX(startX);
    this->setY(height-longLineLength);
    this->interval =interval;
    this->pageHeight =height;
}

void HorizontalRuler::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush shapeBgBrush;
    shapeBgBrush.setColor(QColor(255,255,255,255));
    scene()->setBackgroundBrush(shapeBgBrush);
    QPen shapePen;
    shapePen.setColor(QColor(Qt::gray));
    shapePen.setBrush(QBrush(Qt::gray));
//    shapePen.setfi
    shapePen.setWidth(3);

    painter->setPen(shapePen);
    painter->setOpacity(Qt::transparent);
    QRectF bgRuler(startX,pageHeight-longLineLength,widthRuler,longLineLength);
    painter->fillRect(bgRuler,QColor(Qt::gray));
    shapePen.setColor(QColor(Qt::black));

    painter->setPen(shapePen);
    qDebug()<<"ssssssssssssssssssssssssssssssssssss111";
    qDebug()<<widthRuler;
    qDebug()<<interval;
    for(int i=0;i<widthRuler/interval;i++){
        qDebug()<<i;
        if(i%10==0){
            painter->drawLine(i*interval+startX,pageHeight-longLineLength,i*interval+startX,pageHeight-longLineLength+shortLineLength);
        }else{
            painter->drawLine(i*interval+startX,pageHeight-longLineLength,i*interval+startX,pageHeight-longLineLength+longLineLength);

        }

    }
}

QPoint HorizontalRuler::getPosition()
{
    QPoint point;
    point.setX(this->x());
    point.setY(this->y());
    return point;
}

int HorizontalRuler::getWidth() const
{
    return widthRuler;
}

int HorizontalRuler::getHeight() const
{
    return longLineLength;
}

QRectF HorizontalRuler::boundingRect() const
{
    int height = longLineLength;
    int width = this->widthRuler;
    return QRectF(0,0,width,height);
}
