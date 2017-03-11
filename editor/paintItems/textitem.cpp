#include "textitem.h"


TextItem::TextItem(QWidget *parent, QPointF position,int width,int height):DrawItem()
{
    this->parent = parent;
    this->position = position;
    this->width = width;
    this->height = height;
    this->itemType =  TEXT_ITEM;
    buildKeyboardHash();
    fontSize =15;

}

QPoint TextItem::getPosition()
{
    return QPoint(position.x(),position.y());
}

int TextItem::getWidth() const
{
    return width;
}

int TextItem::getHeight() const
{
    return height;
}

QPixmap TextItem::toPixmap()
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

void TextItem::setPosition(int x, int y)
{
    this->position.setX(x);
    this->position.setY(y);
    this->update();
}

void TextItem::hideItem()
{
    this->hide();

}

void TextItem::showItem()
{
    this->show();
}

bool TextItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}

bool TextItem::onMousePressed(QMouseEvent *event)
{
    mousePressUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
    if(this->itemState ==  PREPARE_FOR_DRAGING){
        insideX = event->pos().x()-this->getPosition().x();
        insideY = event->pos().y()-this->getPosition().y();
        return true;
    }
    return false;
//    if(isInside(QPoint(event->pos().x(),event->pos().y()))){
//        insideX = event->pos().x()-this->getPosition().x();
//        insideY = event->pos().y()-this->getPosition().y();
////        isPressed = true;
//        return true;

//    }
//    this->isSelect =false;

//    return false;
}

void TextItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
//    if(!isDraging && isPressed){
//        this->isSelect =true;
//        this->isPressed= false;
//    }
}

MouseMoveResult TextItem::onMouseMove(QMouseEvent *event)
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

//    if(!isPressedItem()){
//        return whereIsPoint(QPoint(event->x(),event->y()));
//    }

////    isDraging =true;

//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//    QPoint circleCenter(this->getPosition().x(),this->getPosition().y());

//    dataStream << this->toPixmap() << QPoint(event->pos() - circleCenter);
//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData("application/x-dnditemdata", itemData);

//    QDrag *drag = new QDrag(parent);
//    drag->setMimeData(mimeData);
//    drag->setPixmap(this->toPixmap());
//    drag->setHotSpot(event->pos() - circleCenter);

//    drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
//    return  IN_DRAGING_MODE;
}

void TextItem::keyboardPressed(QKeyEvent *event)
{

    qDebug()<<"TextItem: "<<event->key();
    if(isSelectedItem()){
        qDebug()<<"TextItem: IsSelect =true";
        if(event->key() == 16777219 )
            text = text.left(text.length()-1);
        else if((event->key()>64 && event->key()<91)
                || (event->key()>47 && event->key()<58)
                || (event->key()==32) )
            text.append(event->text());
        else if(keyboardHash->contains(event->key())){
            text.append(keyboardHash->value(event->key()));
        }

        this->update();
    }
}


void TextItem::itemDropEvent(QDropEvent *event)
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

void TextItem::itemDragEnterEvent(QDragEnterEvent *event)
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

void TextItem::itemDragMoveEvent(QDragMoveEvent *event)
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

QRectF TextItem::boundingRect() const
{
    return QRectF(position.x(),position.y(),width,height);
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    painter->setFont(QFont("TAHOMA",fontSize));
    painter->drawText(position.x(),position.y(),width,height,Qt::AlignCenter,this->text);
    updateCornerPoint();
    if(isDrawBorder()){
        this->paintSelectBorder(painter,leftTop,rightTop,leftBottom,rightBottom);
    }
}

void TextItem::changeFontSize(int fontSize)
{
    this->fontSize =fontSize;
    this->update();
}

void TextItem::buildKeyboardHash()
{
    this->keyboardHash = new QHash<int,QString>;
    this->keyboardHash->insert(1575,"ا");
    this->keyboardHash->insert(1576,"ب");
    this->keyboardHash->insert(1662,"پ");
    this->keyboardHash->insert(1578,"ت");
    this->keyboardHash->insert(1579,"ث");
    this->keyboardHash->insert(1580,"ج");
    this->keyboardHash->insert(1670,"چ");
    this->keyboardHash->insert(1581,"ح");
    this->keyboardHash->insert(1582,"خ");
    this->keyboardHash->insert(1583,"د");
    this->keyboardHash->insert(1584,"ذ");
    this->keyboardHash->insert(1585,"ر");
    this->keyboardHash->insert(1586,"ز");
    this->keyboardHash->insert(1688,"ژ");
    this->keyboardHash->insert(1587,"س");
    this->keyboardHash->insert(1588,"ش");
    this->keyboardHash->insert(1589,"ص");
    this->keyboardHash->insert(1590,"ض");
    this->keyboardHash->insert(1591,"ط");
    this->keyboardHash->insert(1592,"ظ");
    this->keyboardHash->insert(1593,"ع");
    this->keyboardHash->insert(1594,"غ");
    this->keyboardHash->insert(1601,"ف");
    this->keyboardHash->insert(1602,"ق");
    this->keyboardHash->insert(1705,"ک");
    this->keyboardHash->insert(1711,"گ");
    this->keyboardHash->insert(1604,"ل");
    this->keyboardHash->insert(1605,"م");
    this->keyboardHash->insert(1606,"ن");
    this->keyboardHash->insert(1608,"و");
    this->keyboardHash->insert(1607,"ه");
    this->keyboardHash->insert(1740,"ی");
    this->keyboardHash->insert(1574,"ئ");
    this->keyboardHash->insert(1570,"آ");
//    this->keyboardHash->insert();


}




