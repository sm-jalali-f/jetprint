#include "triangleitem.h"

TriangleItem::TriangleItem(QWidget *parent, QPointF position1, QPointF position2, QPointF position3)
    :DrawItem()
{
    this->parent = parent;
    this->position1 =position1;
    this->position2 =position2;
    this->position3 =position3;
    this->itemType =  SHAPE_TRIANGLE;

}

QPoint TriangleItem::getPosition()
{
    return getLeftTopPoint();
}

int TriangleItem::getWidth() const
{
    return (getRightBottomPoint().x()-getLeftTopPoint().x());
}

int TriangleItem::getHeight() const
{
    return (getRightBottomPoint().y()-getLeftTopPoint().y());
}

QPixmap TriangleItem::toPixmap()
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

void TriangleItem::setPosition(int x, int y)
{
    QPoint leftTop;
    leftTop = getLeftTopPoint();
    int diffX = x- leftTop.x();
    int diffY = y - leftTop.y();
    qDebug()<<"pos1:"<<position1;
    qDebug()<<"pos2:"<<position2;
    qDebug()<<"pos3:"<<position3;
    position1.setX(position1.x()+diffX);
    position2.setX(position2.x()+diffX);
    position3.setX(position3.x()+diffX);
    position1.setY(position1.y()+diffY);
    position2.setY(position2.y()+diffY);
    position3.setY(position3.y()+diffY);

}

void TriangleItem::hideItem()
{
    this->hide();
}

void TriangleItem::showItem()
{
    this->show();
}

bool TriangleItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}


void TriangleItem::itemDropEvent(QDropEvent *event)
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
void TriangleItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void TriangleItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void TriangleItem::keyboardPressed(QKeyEvent *event)
{

}

MouseMoveResult TriangleItem::onMouseMove(QMouseEvent *event)
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

void TriangleItem::onMouseReleased(QMouseEvent *event)
{
//    if(!isDraging && isPressed){
//        this->isSelect =true;
//        this->isPressed= false;
//    }
}

bool TriangleItem::onMousePressed(QMouseEvent *event)
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

QRectF TriangleItem::boundingRect() const
{
    QPointF leftTop = getLeftTopPoint();
    return QRectF(leftTop.x(),leftTop.y(),getWidth(),getHeight());
}

void TriangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setOpacity(Qt::transparent);
    if(!isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->drawLine(QLine(position1.x(),position1.y(),position2.x(),position2.y()));
    painter->drawLine(QLine(position1.x(),position1.y(),position3.x(),position3.y()));
    painter->drawLine(QLine(position3.x(),position3.y(),position2.x(),position2.y()));
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}

QPoint TriangleItem::getLeftTopPoint() const
{
    int minX,minY;
    if(position1.x()<position2.x()){
        if(position1.x()<position3.x())
            minX = position1.x();
        else
            minX = position3.x();
    }else{
        if(position2.x()<position3.x())
            minX = position2.x();
        else
            minX = position3.x();
    }
    if(position1.y()<position2.y()){
        if(position1.y()<position3.y())
            minY = position1.y();
        else
            minY = position3.y();
    }else{
        if(position2.y()<position3.y())
            minY = position2.y();
        else
            minY = position3.y();
    }
    return QPoint(minX,minY);
}

QPoint TriangleItem::getRightBottomPoint() const
{
    int maxX,maxY;
    if(position1.x()>position2.x()){
        if(position1.x()>position3.x())
            maxX = position1.x();
        else
            maxX = position3.x();
    }else{
        if(position2.x()>position3.x())
            maxX = position2.x();
        else
            maxX = position3.x();
    }
    if(position1.y()>position2.y()){
        if(position1.y()>position3.y())
            maxY = position1.y();
        else
            maxY = position3.y();
    }else{
        if(position2.y()>position3.y())
            maxY = position2.y();
        else
            maxY = position3.y();
    }
    return QPoint(maxX,maxY);
}
