#include "myimageitem.h"

MyImageItem::MyImageItem(QWidget *parent, QPointF position, int width, int height,QString filePath)
    :DrawItem()
{
    this->parent= parent;
    this->position = position;
    this->width = width;
    this->height = height;
    QImage img(filePath);
    image = img;
    this->width = image.width();
    this->height = image.height();
    this->itemType =  IMAGE_ITEM;
}

QPoint MyImageItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int MyImageItem::getWidth() const
{
    return width;
}

int MyImageItem::getHeight() const
{
    return height;
}

QPixmap MyImageItem::toPixmap()
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

void MyImageItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
}

void MyImageItem::hideItem()
{
    this->hide();

}

void MyImageItem::showItem()
{
    this->show();

}
bool MyImageItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}

bool MyImageItem::onMousePressed(QMouseEvent *event)
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

void MyImageItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
}

MouseMoveResult MyImageItem::onMouseMove(QMouseEvent *event)
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
        updateImage();
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        updateImage();
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  LEFT_RESIZING:
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        updateImage();
        this->update();
        return  LEFT_RESIZE_PRESSED;
    case  RIGHT_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        updateImage();
        this->update();
        return  RIGHT_RESIZE_PRESSED;
    case  LEFT_TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y()+lastHeight-height);
        updateImage();
        this->update();
        return  LEFT_TOP_RESIZE_PRESSED;
    case  LEFT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        updateImage();
        this->update();
        return  LEFT_BOTTOM_RESIZE_PRESSED;

    case  RIGHT_TOP_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        updateImage();
        this->update();
        return  RIGHT_TOP_RESIZE_PRESSED;
    case  RIGHT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        updateImage();
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

void MyImageItem::itemDropEvent(QDropEvent *event)
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
void MyImageItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void MyImageItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void MyImageItem::keyboardPressed(QKeyEvent *event)
{

}


QRectF MyImageItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),width,height);
}

void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isRemoved())
        return;
    image = image.convertToFormat(QImage::Format_Mono, Qt::MonoOnly|Qt::ThresholdDither|Qt::AvoidDither);
    scene()->setBackgroundBrush(shapeBgBrush);
    painter->setOpacity(Qt::transparent);
    if(!isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->drawImage(position.x(),position.y(),image);
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}

void MyImageItem::updateImage()
{
    image = image.scaled(width,height);
    update();
}


