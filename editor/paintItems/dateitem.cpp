#include "dateitem.h"


DateItem::DateItem(QWidget *parent, QPointF position, int width, int height):DrawItem()
{
    this->parent = parent;
    this->position = position;
    this->width = width;
    this->height = height;
    this->itemType =  DATE_ITEM;
}

QPoint DateItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int DateItem::getWidth() const
{
    return width;
}

int DateItem::getHeight() const
{
    return height;
}

QPixmap DateItem::toPixmap()
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

void DateItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void DateItem::hideItem()
{
    this->hide();
}

void DateItem::showItem()
{
    this->show();
}

bool DateItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}


void DateItem::itemDropEvent(QDropEvent *event)
{

    if(!isDragingItem())
        return;
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        itemState =  NOTHING_STATE;
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
void DateItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void DateItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void DateItem::keyboardPressed(QKeyEvent *event)
{

}

MouseMoveResult  DateItem::onMouseMove(QMouseEvent *event)
{

    if(!isPressedItem()){
        return whereIsPoint(QPoint(event->x(),event->y()));
    }
    int lastWidth;
    int lastHeight;
    switch (itemState) {
    case  BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  LEFT_RESIZING:
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        this->update();
        return  LEFT_RESIZE_PRESSED;
    case  RIGHT_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_RESIZE_PRESSED;
    case  LEFT_TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y()+lastHeight-height);
        this->update();
        return  LEFT_TOP_RESIZE_PRESSED;
    case  LEFT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        this->update();
        return  LEFT_BOTTOM_RESIZE_PRESSED;

    case  RIGHT_TOP_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        this->update();
        return  RIGHT_TOP_RESIZE_PRESSED;
    case  RIGHT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_BOTTOM_RESIZE_PRESSED;

    case  PREPARE_FOR_DRAGING :
        itemState =  DRAGING;
        qDebug()<<"CircleItem: onMouseMove() prepare for draging";
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
//    default:
//        break;
    }
}

void DateItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
}

bool DateItem::onMousePressed(QMouseEvent *event)
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

QRectF DateItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),width,height);
}

void DateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setOpacity(Qt::transparent);
    QDateTime currentTime;

    QString date = currentTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss A");
    if(!isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->setFont(QFont("TAHOMA",25));

    painter->drawText(position.x(),position.y(),width,height,Qt::AlignCenter,date);
//    painter->drawText(position.x(),position.y(),date);
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }

}

