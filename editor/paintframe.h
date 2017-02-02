#ifndef PAINTFRAME_H
#define PAINTFRAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <paintItems/shapes/circleitem.h>
#include <paintItems/shapes/rectangleitem.h>
#include <paintItems/shapes/lineitem.h>
#include <paintItems/shapes/triangleitem.h>
#include <paintItems/shapes/ovalitem.h>
#include <paintItems/shapes/diamonditem.h>
#include <paintItems/shapes/parallelogramitem.h>
#include <paintItems/dateitem.h>
#include <paintItems/barcodeitem.h>
#include <paintItems/myimageitem.h>
#include <paintItems/textitem.h>
#include <types/drawitemtype.h>
#include <types/mousemoveresult.h>
#include <QHash>
#include <qzint.h>
#include <paintItems/endpaintline.h>
#include <paintItems/verticalruler.h>
#include <paintItems/horizontalruler.h>
//#include

class PaintFrame : public QGraphicsView
{
public:

    PaintFrame(QWidget *parent = 0);
    QGraphicsScene *scene;
    void addBarcode(QPointF position,int width,int height);
    void addCircle(QPointF position,int radius);

    void addRectangle(QPointF position,int width,int height);
    void addSquare(QPointF position,int width);
    void addLine(QPointF position1,QPointF position2);
    void addOval(QPointF position,int firstDiagonal,int secondDiagonal);
    void addDiamond(QPointF position,int firstDiagonal,int secondDiagonal);
    void addTriangle(QPointF position1,QPointF position2,QPointF position3);
    void addParallelogram(QPointF position,int width,int height,float leftBottomAngle);
    void addDateTime(QPointF position,int width,int height);
    void addImage(QPointF position,QString filePath);
    void addTextItem(QPointF point);
    void keyPressEvent(QKeyEvent *event);

    int findEndPaint();
    void drawDividerLine(int x);
    QPixmap toPixmap() ;
    QPixmap getPrintPixmap();
    bool isDynamic();
protected:
    QVector<DrawItem*> itemList;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

private:
    int fixedWidth = 18*128;
    int fixedHeight = 6*128;
    int minimumEndLineX =100;
    int maximumEndLineX =fixedWidth-3;
    int endLineMargine =10;
    EndPaintLine *endLineDivider;
    int endLinePosX =-1;

    bool hasDynamicItem;
    bool isPressedObject;
    bool isDraging;
    int insideX,insideY; // for handle where point of object pressed , so when drop in best point of page

    void updateCursor(MouseMoveResult type);
    VerticalRuler *vRuler;
    HorizontalRuler *hRuler;

};

#endif // PAINTFRAME_H
