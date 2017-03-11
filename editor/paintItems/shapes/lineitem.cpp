#include "lineitem.h"

LineItem::LineItem(QWidget *parent, QPointF position1,QPointF position2):DrawItem()
{
    this->position1 = position1;
    this->position2 = position2;
    this->parent  = parent;
    this->itemType =  SHAPE_LINE;

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
    this->hide();
}

void LineItem::showItem()
{
    this->show();
}
bool LineItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}

void LineItem::changeFontSize(int fontSize)
{

}



void LineItem::itemDropEvent(QDropEvent *event)
{
    if(!isDragingItem())
        return;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

//        isDraging = false;
//        isPressed = false;
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;
        this->setPosition(event->pos().x()-insideX,event->pos().y()-insideY);

        if (event->source() == parent) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }

    } else {
        event->ignore();
    }

}
void LineItem::itemDragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == parent) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
void LineItem::itemDragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == parent) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void LineItem::keyboardPressed(QKeyEvent *event)
{

}

MouseMoveResult LineItem::onMouseMove(QMouseEvent *event)
{
    if(!isPressedItem()){
        return whereIsPoint(QPoint(event->x(),event->y()));
    }

//    isDraging =true;

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPoint circleCenter(this->getPosition().x(),this->getPosition().y());

    dataStream << this->toPixmap() << QPoint(event->pos() - circleCenter);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(parent);
    drag->setMimeData(mimeData);
    drag->setPixmap(this->toPixmap());
    drag->setHotSpot(event->pos() - circleCenter);

    drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    return  IN_DRAGING_MODE;
}

void LineItem::onMouseReleased(QMouseEvent *event)
{
//    if(!isDraging && isPressed){
//        this->isSelect =true;
//        this->isPressed= false;
//    }
}

bool LineItem::onMousePressed(QMouseEvent *event)
{
    if(isInside(QPoint(event->pos().x(),event->pos().y()))){
        insideX = event->pos().x()-this->getPosition().x();
        insideY = event->pos().y()-this->getPosition().y();
//        isPressed = true;
        return true;

    }
//    this->isSelect =false;
    return false;
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
    if(isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setPen(shapePen);
    painter->setOpacity(Qt::transparent);
    if(!isDragingItem()){
        painter->drawLine(position1.x(),position1.y(),position2.x(),position2.y());
    }else{
        painter->setPen(dragPen);
        painter->drawLine(position1.x(),position1.y(),position2.x(),position2.y());
    }

    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}
