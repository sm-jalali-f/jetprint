#include "verticalruler.h"

VerticalRuler::VerticalRuler(QWidget *parent, int height, int interval)
{
    this->interval = interval;
    this->heightRuler =height;
}

void VerticalRuler::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QRectF bgRuler(0,0,longLineLength,heightRuler);
    painter->fillRect(bgRuler,QColor(Qt::gray));
    shapePen.setColor(QColor(Qt::black));

    painter->setPen(shapePen);
    painter->drawLine(longLineLength,0,longLineLength,heightRuler);
    for(int i=0;i<heightRuler/interval;i++){
        if(i%10==0){
            painter->drawLine(0,i*interval,longLineLength,i*interval);
        }else{
            painter->drawLine(shortLineLength,i*interval,2*shortLineLength,i*interval);

        }

    }
}

QPoint VerticalRuler::getPosition()
{
    QPoint point;
    point.setX(0);
    point.setY(0);
    return point;
}

void VerticalRuler::setHeightRuler(int height)
{
    this->heightRuler =height;
    update();
}

int VerticalRuler::getWidth() const
{
    return longLineLength;
}

int VerticalRuler::getHeight() const
{
    return this->heightRuler;
}

QRectF VerticalRuler::boundingRect() const
{
    int width = longLineLength;
    int height = this->heightRuler;
    return QRectF(0,0,width,height);
}

