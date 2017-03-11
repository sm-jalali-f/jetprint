/***************************************************************************
 *   Copyright (C) 2008 by BogDan Vatra                                    *
 *   bogdan@licentia.eu                                                    *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include <QDebug>
#include <qrgb.h>
#include "barcodeitem.h"

BarcodeItem::BarcodeItem(QWidget *parent,QPointF position, int width, int height,int length,unsigned char* code,int barcodeType):DrawItem()
{
    this->parent = parent;
    this->position = position;
    this->width = width;
    this->height = height;
    this->itemType = BARCODE_ITEM;
    this->barcodeType =barcodeType;
    this->codeLength =length;
    qDebug()<<"BarcodeItem:BarcodeItem: before setup";
    setupBarcode(barcodeType,width,height,code,length);
    qDebug()<<"BarcodeItem:BarcodeItem: after setup";

}


QPoint BarcodeItem::getPosition()
{
    QPoint pos;
    pos.setX(position.x());
    pos.setY(position.y());
    return pos;
}

int BarcodeItem::getWidth() const
{
    return this->boundingRect().width();
}

int BarcodeItem::getHeight() const
{
    return this->boundingRect().height();
}

QPixmap BarcodeItem::toPixmap()
{
    if (!scene()) {
        qWarning() << "[ControlItem::toPixmap] scene is null.";
        return QPixmap();
    }

    QRectF r = boundingRect();
    QPixmap pixmap(r.width(), r.height());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
//    painter.drawRect(position.x(),position.y(),this->width,this->height);
    painter.drawRect(r);
    scene()->render(&painter, QRectF(), sceneBoundingRect());
    painter.end();
    return pixmap;
}

void BarcodeItem::setPosition(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

void BarcodeItem::hideItem()
{
    this->hide();
}

void BarcodeItem::showItem()
{
    this->show();
}
bool BarcodeItem::isInside(QPoint point)
{
    if( point.x()< this->getPosition().x()+this->getWidth()
                    && point.x() > this->getPosition().x()
                    && point.y() > this->getPosition().y()
                    && point.y() < this->getPosition().y()+this->getHeight()){
        return true;
    }
    return false;
}

void BarcodeItem::changeFontSize(int fontSize)
{

}



void BarcodeItem::itemDropEvent(QDropEvent *event)
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
void BarcodeItem::itemDragEnterEvent(QDragEnterEvent *event)
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
void BarcodeItem::itemDragMoveEvent(QDragMoveEvent *event)
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

void BarcodeItem::keyboardPressed(QKeyEvent *event)
{

}

MouseMoveResult  BarcodeItem::onMouseMove(QMouseEvent *event)
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
        this->updateBarcodeSize();
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        this->updateBarcodeSize();
        this->update();
        return  TOP_RESIZE_PRESSED;
    case  LEFT_RESIZING:
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        this->updateBarcodeSize();
        this->update();
        return  LEFT_RESIZE_PRESSED;
    case  RIGHT_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        this->updateBarcodeSize();
        this->update();
        return  RIGHT_RESIZE_PRESSED;
    case  LEFT_TOP_RESIZING:
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y()+lastHeight-height);
        this->updateBarcodeSize();
        this->update();
        return  LEFT_TOP_RESIZE_PRESSED;
    case  LEFT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((middleLeft.x() -event->pos().x()))/2;
        setPosition(getPosition().x()+lastWidth-width,getPosition().y());
        this->updateBarcodeSize();
        this->update();
        return  LEFT_BOTTOM_RESIZE_PRESSED;

    case  RIGHT_TOP_RESIZING:
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        lastHeight = height;
        height = height + ((middleTop.y() -event->pos().y()))/2;
        setPosition(getPosition().x(),getPosition().y()+lastHeight-height);
        this->updateBarcodeSize();
        this->update();
        return  RIGHT_TOP_RESIZE_PRESSED;
    case  RIGHT_BOTTOM_RESIZING:
        lastHeight = height;
        height = height + ((-middleBottom.y() +event->pos().y()))/2;
        lastWidth = width;
        width = width + ((-middleRight.x() +event->pos().x()))/2;
        this->updateBarcodeSize();
        this->update();
        return  RIGHT_BOTTOM_RESIZE_PRESSED;

    case  PREPARE_FOR_DRAGING :
        itemState =  DRAGING;
//        qDebug()<<"CircleItem: onMouseMove() prepare for draging";
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
//       return whereIsPoint(QPoint(event->x(),event->y()));
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

void BarcodeItem::onMouseReleased(QMouseEvent *event)
{
    mouseReleaseUpdateState(QPoint(event->pos().x(),event->pos().y()));
    this->update();
//    if(!isDragingItem() && isPressedItem()){
//        this->isSelect =true;
//        this->isPressed= false;
//    }
}

bool BarcodeItem::onMousePressed(QMouseEvent *event)
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
//        insideY = evemnt->pos().y()-this->getPosition().y();
////        isPressed = true;
//        return true;

//    }
////    this->isSelect =false;
//    return false;
}

QRectF BarcodeItem::boundingRect() const
{
     return QRectF(position.x(),position.y(),this->width,this->height);
}

void BarcodeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isRemoved())
        return;
    QImage image("out.png");

    width = image.width();
    height= image.height();
//    qDebug()<<image.byteCount();
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
    //    bc.render(*painter,boundingRect(),ar);
}

void BarcodeItem::setupBarcode(int type, int width, int height, unsigned char *c,int length)
{
    qDebug()<<"BarcodeItem:setupBarcode: start";
    my_symbol = ZBarcode_Create();
    my_symbol->input_mode = UNICODE_MODE;
    my_symbol->symbology = type ;
    my_symbol->bitmap_height=height;
    my_symbol->bitmap_width =width;
    my_symbol->width=width;
    my_symbol->height=height;
    my_symbol->scale =5;
    qDebug()<<"BarcodeItem:setupBarcode: before encode";

    ZBarcode_Encode(my_symbol, c,length);
//    ZBarcode_Encode_File(my_symbol, "pic.png");
    qDebug()<<"BarcodeItem:setupBarcode: after encode";

    ZBarcode_Print(my_symbol, 0);
    qDebug()<<"BarcodeItem:setupBarcode: after print";

//    ZBarcode_Encode_and_Print(my_symbol, c,length,0);
//    ZBarcode_Encode_File_and_Print(my_symbol, "pic.png",0);

//    qDebug()<<my_symbol->width;
//    qDebug()<<my_symbol->height;
    ZBarcode_Delete(my_symbol);
    qDebug()<<"BarcodeItem:setupBarcode: end";

//    this->update();
}

void BarcodeItem::updateBarcodeSize()
{
    setupBarcode(barcodeType,width,height,code,codeLength);
}


