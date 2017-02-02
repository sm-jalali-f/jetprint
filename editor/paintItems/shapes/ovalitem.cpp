#include "ovalitem.h"

OvalItem::OvalItem(QWidget *parent, QPointF position, int xDiagonal, int yDiagonal):DrawItem()
{
    this->position = position;
    this->yDiagonal = yDiagonal;
    this->xDiagonal = xDiagonal;
    this->parent  = parent;
    this->itemType =  SHAPE_OVAL;
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
    this->hide();

}

void OvalItem::showItem()
{
    this->show();

}
bool OvalItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}


void OvalItem::itemDropEvent(QDropEvent *event)
{
    if(!isDragingItem())
        return;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {

        itemState =  NOTHING_STATE;
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
void OvalItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void OvalItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void OvalItem::keyboardPressed(QKeyEvent *event)
{

}

MouseMoveResult OvalItem::onMouseMove(QMouseEvent *event)
{
    if(!isPressedItem()){
        return whereIsPoint(QPoint(event->x(),event->y()));
    }
    int lastDiagonalX;
    int lastDiagonalY;
    switch (itemState) {
    case  BOTTOM_RESIZING:
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((-middleBottom.y() +event->pos().y()))/2;
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  TOP_RESIZING:
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastDiagonalY-yDiagonal);
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  LEFT_RESIZING:
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastDiagonalX-xDiagonal,getPosition().y());
        this->update();
        return  LEFT_RESIZE_PRESSED;
    case  RIGHT_RESIZING:
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_RESIZE_PRESSED;
    case  LEFT_TOP_RESIZING:
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((middleTop.y() -event->pos().y()))/2;
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastDiagonalX-xDiagonal,getPosition().y()+lastDiagonalY-yDiagonal);
        this->update();
        return  LEFT_TOP_RESIZE_PRESSED;
    case  LEFT_BOTTOM_RESIZING:
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((-middleBottom.y() +event->pos().y()))/2;
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastDiagonalX-xDiagonal,getPosition().y());
        this->update();
        return  LEFT_BOTTOM_RESIZE_PRESSED;

    case  RIGHT_TOP_RESIZING:
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((-middleRight.x() +event->pos().x()))/2;
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastDiagonalY-yDiagonal);
        this->update();
        return  RIGHT_TOP_RESIZE_PRESSED;
    case  RIGHT_BOTTOM_RESIZING:
        lastDiagonalY = yDiagonal;
        yDiagonal = yDiagonal + ((-middleBottom.y() +event->pos().y()))/2;
        lastDiagonalX = xDiagonal;
        xDiagonal = xDiagonal + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_BOTTOM_RESIZE_PRESSED;

    case  PREPARE_FOR_DRAGING :
        itemState =  DRAGING;
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
}

void OvalItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
}

bool OvalItem::onMousePressed(QMouseEvent *event)
{
    mousePressUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
    if(this->itemState ==  PREPARE_FOR_DRAGING){
        insideX = event->pos().x()-this->getPosition().x();
        insideY = event->pos().y()-this->getPosition().y();
        return true;
    }
    return false;

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
    if(isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);
    if(!isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->setOpacity(Qt::transparent);
    painter->drawEllipse(position.x(),position.y(),xDiagonal,yDiagonal);
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}

