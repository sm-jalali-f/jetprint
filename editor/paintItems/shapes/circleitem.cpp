#include "circleitem.h"
#include <QtWidgets>

CircleItem::CircleItem(QWidget *parent,int radiusX,int radiusY , QPointF center):DrawItem()
{
    this->parent = parent;
    this->radiusX = radiusX;
    this->radiusY = radiusY;
    this->center = center;
    this->itemType = SHAPE_CIRCLE;
    setToolTip(QString("right click to select Circle.\nleft click and move to drag Circle"));

    setAcceptedMouseButtons(Qt::LeftButton);



}
QRectF CircleItem::boundingRect() const
{
    return QRectF(center.x()-2,center.y()-2,radiusX+2,radiusY+2);
}
void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(this->isRemoved())
        return;
    scene()->setBackgroundBrush(shapeBgBrush);

    painter->setOpacity(Qt::transparent);
    if(!this->isDragingItem())
        painter->setPen(shapePen);
    else
        painter->setPen(dragPen);
    painter->drawEllipse(center.x(),center.y(), radiusX, radiusY);
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
        QImage rotateImage(":/res/icons/ic_rotate");
        rotateImage = rotateImage.scaled(IC_ROTATE_SIZE,IC_ROTATE_SIZE);
        rotateRect = QRectF(middleTop.x()-rotateImage.width()/2
                             ,middleTop.y()-(1.5*rotateImage.height())
                             ,IC_ROTATE_SIZE,IC_ROTATE_SIZE);
        painter->drawImage(QPointF(rotateRect.x(),rotateRect.y()),rotateImage);
    }

}


QPixmap CircleItem::toPixmap()
{

    if (!scene()) {
        qWarning() << "[ControlItem::toPixmap] scene is null.";
        return QPixmap();
    }

    QRectF r = boundingRect();
    QPixmap pixmap(r.width(), r.height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    //painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
    painter.drawRect(r);
    scene()->render(&painter, QRectF(), sceneBoundingRect());
    painter.end();
    return pixmap;
}
QPoint CircleItem::getPosition(){
    QPoint point;
    point.setX(this->center.x());
    point.setY(this->center.y());
//    qDebug()<<"CircleItem: getPosition="<<this->center.x()<<","<<this->center.y();
    return point;
}
int CircleItem::getWidth() const {
//    qDebug()<<"CircleItem: getWidth="<<this->boundingRect().width();
    return this->boundingRect().width();
}
int CircleItem::getHeight() const {
//    qDebug()<<"CircleItem: getHeight="<<this->boundingRect().height();
    return this->boundingRect().height();
}

void CircleItem::setPosition(int x, int y)
{
    this->center.setX(x);
    this->center.setY(y);
    update();
}

void CircleItem::hideItem()
{
    this->hide();
}

void CircleItem::showItem()
{
    this->show();
}

bool CircleItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}



bool CircleItem::onMousePressed(QMouseEvent *event)
{
    mousePressUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
    if(this->itemState == PREPARE_FOR_DRAGING){
        insideX = event->pos().x()-this->getPosition().x();
        insideY = event->pos().y()-this->getPosition().y();
        return true;
    }else if(this->itemState == ROTATING){
        qDebug()<<"CircleItem: mousepressed : rotating";
        rotateClickedPos = QPoint(event->pos());
    }
    return false;
}

void CircleItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
//    if(!isDraging && isPressed){
//        this->isSelect =true;
//        this->isPressed= false;
//    }
}

MouseMoveResult  CircleItem::onMouseMove(QMouseEvent *event)
{
//    if(isInRotateArea(QPoint(event->x(),event->y())))
//        qDebug()<<"inside rotate area****************";
    if(!isPressedItem()){
        return whereIsPoint(QPoint(event->x(),event->y()));
    }
    int lastRadiusX;
    int lastRadiusY;
    switch (itemState) {
    case  ROTATING:{
        int angle = qAtan((event->pos().y()-rotateClickedPos.y())/(event->pos().x()-rotateClickedPos.x()));
        this->setRotation(angle);
        this->update();
        return  ROTATE ;
    }
    case  BOTTOM_RESIZING:
        lastRadiusY = radiusY;
        radiusY = radiusY + ((-middleBottom.y() +event->pos().y()))/2;
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  TOP_RESIZING:
        lastRadiusY = radiusY;
        radiusY = radiusY + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastRadiusY-radiusY);
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  LEFT_RESIZING:
        lastRadiusX = radiusX;
        radiusX = radiusX + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastRadiusX-radiusX,getPosition().y());
        this->update();
        return  LEFT_RESIZE_PRESSED;
    case  RIGHT_RESIZING:
        lastRadiusX = radiusX;
        radiusX = radiusX + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_RESIZE_PRESSED;
    case  LEFT_TOP_RESIZING:
        lastRadiusY = radiusY;
        radiusY = radiusY + ((middleTop.y() -event->pos().y()))/2;
        lastRadiusX = radiusX;
        radiusX = radiusX + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastRadiusX-radiusX,getPosition().y()+lastRadiusY-radiusY);
        this->update();
        return  LEFT_TOP_RESIZE_PRESSED;
    case  LEFT_BOTTOM_RESIZING:
        lastRadiusY = radiusY;
        radiusY = radiusY + ((-middleBottom.y() +event->pos().y()))/2;
        lastRadiusX = radiusX;
        radiusX = radiusX + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastRadiusX-radiusX,getPosition().y());
        this->update();
        return  LEFT_BOTTOM_RESIZE_PRESSED;

    case  RIGHT_TOP_RESIZING:
        lastRadiusX = radiusX;
        radiusX = radiusX + ((-middleRight.x() +event->pos().x()))/2;
        lastRadiusY = radiusY;
        radiusY = radiusY + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastRadiusY-radiusY);
        this->update();
        return  RIGHT_TOP_RESIZE_PRESSED;
    case  RIGHT_BOTTOM_RESIZING:
        lastRadiusY = radiusY;
        radiusY = radiusY + ((-middleBottom.y() +event->pos().y()))/2;
        lastRadiusX = radiusX;
        radiusX = radiusX + ((-middleRight.x() +event->pos().x()))/2;
        this->update();
        return  RIGHT_BOTTOM_RESIZE_PRESSED;

    case  PREPARE_FOR_DRAGING :
        itemState =  DRAGING;
        qDebug()<<"CircleItem: onMouseMove() prepare for draging";
        QPixmap tempPixMap =this->toPixmap();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        QPoint circleCenter(this->getPosition().x(),this->getPosition().y());

        dataStream << this->toPixmap() << QPoint(event->pos() - circleCenter);
        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(parent);
        drag->setMimeData(mimeData);
        drag->setPixmap(tempPixMap);
        drag->setHotSpot(event->pos() - circleCenter);

        drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        return  IN_DRAGING_MODE;

//    default:
//        break;
    }

}
void CircleItem::itemDropEvent(QDropEvent *event)
{

    qDebug()<<"CircleItem: itemDropEvent();";
    if(!isDragingItem())
        return;

    qDebug()<<"CircleItem: itemDropEvent(); is draging";
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        qDebug()<<"CircleItem: itemDropEvent(); has format";
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
void CircleItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void CircleItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void CircleItem::keyboardPressed(QKeyEvent *event)
{

}
