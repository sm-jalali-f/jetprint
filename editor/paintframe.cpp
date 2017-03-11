#include "paintframe.h"
#include <QtDebug>
#include <QBrush>
#include <paintItems/shapes/circleitem.h>
PaintFrame::PaintFrame(QWidget *parent) : QGraphicsView(parent)
{
    qDebug()<<"PaintFrame: start of constructor";
    isPressedObject = false;
    isDraging = false;
    hasDynamicItem = false;

    endLineDivider = new EndPaintLine(this,fixedHeight);
    qDebug()<<"PaintFrame: created EndPaintLine";

    this->setFixedSize(fixedWidth,fixedHeight);
    scene = new QGraphicsScene(0,0,fixedWidth,fixedHeight );
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ensureVisible(0,0,fixedWidth,fixedHeight,0,0);
    this->setBackgroundBrush(QColor(255, 255, 255));
    scene->setBackgroundBrush(QColor(100,102,123));
    qDebug()<<"PaintFrame: before add EndPaintLine";

    scene->addItem(endLineDivider);
    qDebug()<<"PaintFrame: after add EndPaintLine";

    endLineDivider->show();



    vRuler = new VerticalRuler(this,fixedHeight-RULER_WIDTH,RULER_WIDTH);
    scene->addItem(vRuler);
    vRuler->show();
    qDebug()<<"PaintFrame: added vertical ruller";

    hRuler = new HorizontalRuler(this,RULER_WIDTH,vRuler->getLastLine().y(),fixedWidth-RULER_WIDTH,vRuler->getInterval(),fixedHeight-vRuler->getLastLine().y());
    scene->addItem(hRuler);
    hRuler->show();

    drawDividerLine(minimumEndLineX);
    qDebug()<<"PaintFrame: added divider line";

    this->show();

    qDebug()<<"PaintFrame: end of constructor";


}

void PaintFrame::addBarcode(QPointF position,int width,int height,unsigned char* code,int length,int typeBarcode)
{
    qDebug()<<"PaintFrame:addBarcode: start";
    unsigned char c[] ={0x61,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62,0x61,0x62};
    BarcodeItem *barcode = new BarcodeItem(this,position,width,height,13,c,typeBarcode);
    barcode->setAcceptHoverEvents(true);
    scene->addItem(barcode);
    barcode->show();
    itemList.append(barcode);
    drawDividerLine(findEndPaint());


}
void PaintFrame::addCircle(QPointF position,int radius){

    CircleItem *circleItem = new CircleItem(this,radius,radius,position);
    circleItem->setAcceptHoverEvents(true);
    scene->addItem(circleItem);
    circleItem->show();
    itemList.append(circleItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addRectangle(QPointF position, int width, int height)
{
    RectangleItem *rectItem = new RectangleItem(this,position,width,height);
    rectItem->setAcceptHoverEvents(true);
    scene->addItem(rectItem);
    rectItem->show();
    itemList.append(rectItem);
    drawDividerLine(findEndPaint());

}

void PaintFrame::addSquare(QPointF position, int width)
{
    RectangleItem *rectItem = new RectangleItem(this,position,width,width);
    rectItem->setAcceptHoverEvents(true);
    scene->addItem(rectItem);
    rectItem->show();
    itemList.append(rectItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addLine(QPointF position1,QPointF position2)
{
    LineItem *lineItem = new LineItem(this,position1,position2);
    lineItem->setAcceptHoverEvents(true);
    scene->addItem(lineItem);
    lineItem->show();
    itemList.append(lineItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addOval(QPointF position, int firstDiagonal, int secondDiagonal)
{
    qDebug()<<"PaintFrame: addOval();";
    OvalItem *ovalItem = new OvalItem(this,position,firstDiagonal,secondDiagonal);
    ovalItem->setAcceptHoverEvents(true);
    scene->addItem(ovalItem);
    ovalItem->show();
    itemList.append(ovalItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addDiamond(QPointF position, int firstDiagonal, int secondDiagonal)
{
    DiamondItem *diamondItem = new DiamondItem(this,position,firstDiagonal,secondDiagonal);
    diamondItem->setAcceptHoverEvents(true);
    scene->addItem(diamondItem);
    diamondItem->show();
    itemList.append(diamondItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addTriangle(QPointF position1, QPointF position2, QPointF position3)
{
    TriangleItem *triangleItem = new TriangleItem(this,position1,position2,position3);
    triangleItem->setAcceptHoverEvents(true);
    scene->addItem(triangleItem);
    triangleItem->show();
    itemList.append(triangleItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addParallelogram(QPointF position, int width, int height, float leftBottomAngle)
{
    ParallelogramItem *parallelogramItem = new ParallelogramItem(this,position,width,height,leftBottomAngle);
    parallelogramItem->setAcceptHoverEvents(true);
    scene->addItem(parallelogramItem);
    parallelogramItem->show();
    itemList.append(parallelogramItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addDateTime(QPointF position, int width, int height)
{
    this->hasDynamicItem = true;
    DateItem *dateItem = new DateItem(this,position,width,height,DATE_TIME_ITEM);
    dateItem->setAcceptHoverEvents(true);
    scene->addItem(dateItem);
    dateItem->show();
    itemList.append(dateItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addDate(QPointF position, int width, int height)
{
    this->hasDynamicItem = true;
    DateItem *dateItem = new DateItem(this,position,width,height,DATE_ITEM);
    dateItem->setAcceptHoverEvents(true);
    scene->addItem(dateItem);
    dateItem->show();
    itemList.append(dateItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addTime(QPointF position, int width, int height)
{
    this->hasDynamicItem = true;
    DateItem *dateItem = new DateItem(this,position,width,height,TIME_ITEM);
    dateItem->setAcceptHoverEvents(true);
    scene->addItem(dateItem);
    dateItem->show();
    itemList.append(dateItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addImage(QPointF position, QString filePath)
{
    MyImageItem *imageItem = new MyImageItem(this,position,90,90,filePath);

    imageItem->setAcceptHoverEvents(true);
    scene->addItem(imageItem);
    imageItem->show();
    itemList.append(imageItem);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addTextItem(QPointF point)
{
    TextItem *text = new TextItem(this,point,240,40);
    text->setAcceptHoverEvents(true);
    scene->addItem(text);
    text->show();
    itemList.append(text);
    drawDividerLine(findEndPaint());
}

void PaintFrame::addCounterItem(QPointF point)
{
    CounterItem *counter= new CounterItem (this,point,240,40);
    counter->setAcceptHoverEvents(true);
    scene->addItem(counter);
    counter->show();
    itemList.append(counter);
    drawDividerLine(findEndPaint());
}
void PaintFrame::drawDividerLine(int x)
{
    qDebug()<<"PaintFrame:drawDividerLine: start";

    if(x<=0)
        return;
    bool firstCall =false;
    if(endLinePosX==-1){
        firstCall= true;
    }
    endLineDivider->setXPos(x);
    qDebug()<<"PaintFrame:drawDividerLine: seted pos x";

    if(vRuler!=NULL){
        qDebug()<<"PaintFrame:drawDividerLine: vRuler not null";
        vRuler->getInterval();
        qDebug()<<"PaintFrame:drawDividerLine: vRuler not null";

        if(vRuler->getInterval()!=0){
            qDebug()<<"PaintFrame:drawDividerLine: in if";
            double tempWidth = 1.0;
//            qDebug()<<"PaintFrame drawDividerLine tempwidth="<<tempWidth;
            tempWidth = (endLinePosX-RULER_WIDTH);
//            qDebug()<<"PaintFrame drawDividerLine tempwidth="<<tempWidth;
            tempWidth = tempWidth/vRuler->getInterval();
//            qDebug()<<"PaintFrame drawDividerLine tempwidth="<<tempWidth;
            double tempHeight = 1.0*vRuler->REAL_FIXED_HEIGHT;
//            qDebug()<<"PaintFrame drawDividerLine tempwidth="<<tempWidth;
            emit paintFrameChanged(tempWidth,tempHeight);
//            qDebug()<<"PaintFrame drawDividerLine tempwidth="<<tempWidth;
        }else{
            qDebug()<<"PaintFrame:drawDividerLine: else ";

        }
    }else{
        qDebug()<<"PaintFrame:drawDividerLine: vruler null";
    }
    qDebug()<<"PaintFrame:drawDividerLine: end";

}

int PaintFrame::findEndPaint()
{
    int x = minimumEndLineX;
    //find max x of all item
    for(int i=0;i<itemList.size();i++){
//        qDebug()<<"PaintFrame: findEndPaint.item.x= "<<itemList.at(i)->getPosition().x();
//        qDebug()<<"PaintFrame: findEndPaint.item.width= "<<itemList.at(i)->boundingRect();
        if(itemList.at(i)->getPosition().x() > x ){
            x =itemList.at(i)->getPosition().x() ;
        }
        if(itemList.at(i)->getPosition().x()+itemList.at(i)->getWidth() > x){
            x =itemList.at(i)->getPosition().x() +itemList.at(i)->getWidth();
        }
    }
//    qDebug()<<"PaintFrame: findEndPaint.endline.x= "<<x;
    //if x grater than width of paintframe :
    x += endLineMargine;
    if(x>maximumEndLineX)
        x =maximumEndLineX;
    endLinePosX =x;
    return x;
}


void PaintFrame::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event;
    for (int i = 0; i < itemList.size(); i++) {
        if(itemList.at(i)->getItemType()== TEXT_ITEM){
            qDebug()<<"keeeeey pressed text";
            itemList.at(i)->keyboardPressed(event);
        }else{
            if(event->key()==16777223){
                qDebug()<<"list before size ="<<itemList.size();
                if(itemList.at(i)->isSelectedItem())
                    itemList.at(i)->hideItem();
                qDebug()<<"list after size ="<<itemList.size();

            }
        }
    }
}



QPixmap PaintFrame::toPixmap()
{    
    QGraphicsView* view = new QGraphicsView(scene,this);
    QPixmap pixMap = QPixmap::grabWidget(this);
    return pixMap;
}

QPixmap PaintFrame::getPrintPixmap()
{
    QRect frame(RULER_WIDTH+3,1,endLinePosX-RULER_WIDTH-3,fixedHeight-hRuler->getHeight()-1);
    return this->grab(frame);

}

bool PaintFrame::isDynamic()
{
    return hasDynamicItem;
}

void PaintFrame::unSelectAllItem()
{
    for(int i=0;i<itemList.size();i++){
        itemList.at(i)->unSelect();
    }
}

void PaintFrame::fontSizeChanged(int fontSize)
{
    for(int i=0;i<itemList.size();i++){
        if(itemList.at(i)->getItemType()==TEXT_ITEM){
            itemList.at(i)->changeFontSize(fontSize);
        }
    }
}

void PaintFrame::mousePressEvent(QMouseEvent *event)
{
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        bool res =itemList.at(i)->onMousePressed(event);
        if(res){
            setCursor(Qt::ClosedHandCursor);
        }
    }
}

void PaintFrame::mouseMoveEvent(QMouseEvent *event){
//    qDebug()<<"PaintFrame: mouseMoveEvent(); pos"<<event->pos();
    MouseMoveResult mouseShape =NOTHING;
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        MouseMoveResult res = itemList.at(i)->onMouseMove(event);
        if(res == NOTHING)
            continue;
        mouseShape = res;

    }
    updateCursor(mouseShape);

}

void PaintFrame::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"PaintFrame: mouseReleaseEvent() pos"<<event->pos();
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        itemList.at(i)->onMouseReleased(event);
    }

}

void PaintFrame::dropEvent(QDropEvent *event)
{
    qDebug()<<"PaintFrame: dropEvent(); pos"<<event->pos();
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        itemList.at(i)->itemDropEvent(event);
    }
    drawDividerLine(findEndPaint());
}

void PaintFrame::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"PaintFrame: dragEnterEvent(); pos"<<event->pos();
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        itemList.at(i)->itemDragEnterEvent(event);
    }
}

void PaintFrame::dragMoveEvent(QDragMoveEvent *event)
{
    for(int i=itemList.size()-1;i>-1;i--){
        if(itemList.at(i)->isRemoved())
            continue;
        itemList.at(i)->itemDragMoveEvent(event);
    }
}

void PaintFrame::updateCursor(MouseMoveResult mouseShape)
{
    if(mouseShape==NOTHING)
        setCursor(Qt::ArrowCursor);
    else if(mouseShape ==INSIDE)
        setCursor(Qt::OpenHandCursor);
    else if(mouseShape ==ROTATE)
        setCursor(Qt::CrossCursor);
    else if(mouseShape ==IN_DRAGING_MODE)
        setCursor(Qt::ClosedHandCursor);
    else if(mouseShape == TOP_RESIZE)
        setCursor(Qt::SizeVerCursor);
    else if(mouseShape == TOP_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == LEFT_RESIZE)
        setCursor(Qt::SizeHorCursor);
    else if(mouseShape == LEFT_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == RIGHT_RESIZE)
        setCursor(Qt::SizeHorCursor);
    else if(mouseShape == RIGHT_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == BOTTOM_RESIZE)
        setCursor(Qt::SizeVerCursor);
    else if(mouseShape == BOTTOM_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);

    else if(mouseShape == LEFT_TOP_RESIZE)
        setCursor(Qt::SizeFDiagCursor);
    else if(mouseShape == LEFT_TOP_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == RIGHT_TOP_RESIZE)
        setCursor(Qt::SizeBDiagCursor);
    else if(mouseShape == RIGHT_TOP_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == LEFT_BOTTOM_RESIZE)
        setCursor(Qt::SizeBDiagCursor);
    else if(mouseShape == LEFT_BOTTOM_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
    else if(mouseShape == RIGHT_BOTTOM_RESIZE)
        setCursor(Qt::SizeFDiagCursor);
    else if(mouseShape == RIGHT_BOTTOM_RESIZE_PRESSED)
        setCursor(Qt::CrossCursor);
}

