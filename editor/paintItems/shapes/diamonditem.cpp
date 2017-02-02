#include "diamonditem.h"

DiamondItem::DiamondItem(QWidget *parent, QPointF position, int xDiagonal, int yDiagonal)
    :DrawItem()
{
    this->parent = parent;
    this->xDiagonal = xDiagonal;
    this->yDiagonal = yDiagonal;
    this->position = position;
    this->itemType =  SHAPE_DIAMOND;
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
    this->hide();

}

void DiamondItem::showItem()
{

    this->show();
}
bool DiamondItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}


void DiamondItem::itemDropEvent(QDropEvent *event)
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
void DiamondItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void DiamondItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void DiamondItem::keyboardPressed(QKeyEvent *event)
{

}


MouseMoveResult DiamondItem::onMouseMove(QMouseEvent *event)
{
//    qDebug()<<"DiamondItem: onMouseMove";
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

void DiamondItem::onMouseReleased(QMouseEvent *event)
{
//    qDebug()<<"DiamondItem: onMouseReleased();";
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
}

bool DiamondItem::onMousePressed(QMouseEvent *event)
{
//    qDebug()<<"DiamondItem: onMousePressed()";
    mousePressUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
    if(this->itemState ==  PREPARE_FOR_DRAGING){
        insideX = event->pos().x()-this->getPosition().x();
        insideY = event->pos().y()-this->getPosition().y();
        return true;
    }
    return false;
}

QRectF DiamondItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),xDiagonal,yDiagonal);
}

void DiamondItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setOpacity(Qt::transparent);
    QPoint v1(position.x(),position.y()+yDiagonal/2);
    QPoint v2(position.x()+xDiagonal/2,position.y());
    QPoint v3(position.x()+xDiagonal,position.y()+yDiagonal/2);
    QPoint v4(position.x()+xDiagonal/2,position.y()+yDiagonal);
    if(!isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->drawLine(v1.x(),v1.y(),v2.x(),v2.y());
    painter->drawLine(v3.x(),v3.y(),v2.x(),v2.y());
    painter->drawLine(v3.x(),v3.y(),v4.x(),v4.y());
    painter->drawLine(v1.x(),v1.y(),v4.x(),v4.y());
    updateCornerPoint();
    if(isDrawBorder()){
//        qDebug()<<"DiamondItem: paint print border";
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}

