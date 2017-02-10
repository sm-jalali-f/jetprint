#include "editorwidget.h"
#include <exception>
//#include <shapes/shapeitem.h>
EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent)
{

    verticalLayout = new QVBoxLayout();
    mainToolsLayout = new QHBoxLayout();
    QWidget *subToolTopWidget =new QWidget();
    subMainToolLayout = new QHBoxLayout(subToolTopWidget);
//    shapeSubToolsLayout= new QHBoxLayout();
//    textSubToolsLayout= new QHBoxLayout();

    shapeBtn = new QPushButton();
//    shapeBtn->setStyleSheet("border-top: 3px Qt::transparent;border-bottom: 3px Qt::transparent;border-right: 10px Qt::transparent;border-left: 10px Qt::transparent;");
    QPixmap pixmapShape(":/res/icons/ic_circle");
    QIcon shapeIcon(pixmapShape);
    shapeBtn->setIcon(shapeIcon);
    shapeBtn->setIconSize(pixmapShape.rect().size()/1);
    shapeBtn->setFixedSize(pixmapShape.rect().size()*1.3);
    shapeBtn->setStyleSheet("background-color:#D3D3D3;color:#e3e3e3");

    textbtn = new QPushButton();
    QPixmap pixmapText(":/res/icons/ic_text");
    QIcon textIcon(pixmapText);
    textbtn->setIcon(textIcon);
    textbtn->setIconSize(pixmapText.rect().size()/1);
    textbtn->setFixedSize(pixmapText.rect().size()*1.3);
    dateBtn = new QPushButton();
    QPixmap pixmapDate(":/res/icons/ic_time_date");
    QIcon dateIcon(pixmapDate);
    dateBtn->setIcon(dateIcon);
    dateBtn->setIconSize(pixmapDate.rect().size()/1);
    dateBtn->setFixedSize(pixmapDate.rect().size()*1.3);
    barcodeBtn = new QPushButton();
    QPixmap pixmapBarcode(":/res/icons/ic_barcode");
    QIcon barcodeIcon(pixmapBarcode);
    barcodeBtn->setIcon(barcodeIcon);
    barcodeBtn->setIconSize(pixmapBarcode.rect().size()/1);
    barcodeBtn->setFixedSize(pixmapBarcode.rect().size()*1.3);
    imageBtn = new QPushButton();
    QPixmap pixmapImage(":/res/icons/ic_image");
    QIcon imageIcon(pixmapImage);
    imageBtn->setIcon(imageIcon);
    imageBtn->setIconSize(pixmapImage.rect().size()/1);
    imageBtn->setFixedSize(pixmapImage.rect().size()*1.3);
    undoBtn= new QPushButton();
    QPixmap pixmapUndo(":/res/icons/ic_undo");
    QIcon undoIcon(pixmapUndo);
    undoBtn->setIcon(undoIcon);
    undoBtn->setIconSize(pixmapUndo.rect().size()/1);
    undoBtn->setFixedSize(pixmapUndo.rect().size()*1.3);
    redoBtn= new QPushButton();
    QPixmap pixmapRedo(":/res/icons/ic_redo");
    QIcon redoIcon(pixmapRedo);
    redoBtn->setIcon(redoIcon);
    redoBtn->setIconSize(pixmapRedo.rect().size()/1);
    redoBtn->setFixedSize(pixmapRedo.rect().size()*1.3);
    saveBtn= new QPushButton();
    QPixmap pixmapSave(":/res/icons/ic_floppy_save");
    QIcon saveIcon(pixmapSave);
    saveBtn->setIcon(saveIcon);
    saveBtn->setIconSize(pixmapSave.rect().size()/1);
    saveBtn->setFixedSize(pixmapSave.rect().size()*1.3);
    printBtn= new QPushButton();
    QPixmap pixmapPrint(":/res/icons/ic_print");
    QIcon printIcon(pixmapPrint);
    printBtn->setIcon(printIcon);
    printBtn->setIconSize(pixmapPrint.rect().size()/1);
    printBtn->setFixedSize(pixmapPrint.rect().size()*1.3);

//    textbtn->setDisabled(true);
    saveBtn->setDisabled(true);
    undoBtn->setDisabled(true);
    redoBtn->setDisabled(true);


    mainToolsLayout->addWidget(shapeBtn);
    mainToolsLayout->addWidget(textbtn);
    mainToolsLayout->addWidget(imageBtn);
    mainToolsLayout->addWidget(barcodeBtn);
    mainToolsLayout->addWidget(dateBtn);
    mainToolsLayout->addWidget(undoBtn);
    mainToolsLayout->addWidget(redoBtn);
    mainToolsLayout->addWidget(saveBtn);
    mainToolsLayout->addWidget(printBtn);
    mainToolsLayout->addStretch(1);
    widget = new QWidget();

    verticalLayout->addLayout(mainToolsLayout);
    verticalLayout->addWidget(subToolTopWidget);
    verticalLayout->addWidget(widget);
    paintFrame = new PaintFrame();
    verticalLayout->addWidget(paintFrame);
//    printInfoLayout = new QVBoxLayout();
//    QLabel *infoLabel = new QLabel("اطلاعات چاپ");
//    printInfoLayout->addWidget(infoLabel);
//    verticalLayout->addLayout(printInfoLayout);
    verticalLayout->addStretch(1);


    setLayout(verticalLayout);
    connect(barcodeBtn,SIGNAL(clicked()),this,SLOT(onBarcodeBtnClicked()));
    connect(shapeBtn,SIGNAL(clicked()),this,SLOT(onShapeBtnClicked()));
    connect(textbtn,SIGNAL(clicked()),this,SLOT(onTextBtnClicked()));
    connect(printBtn,SIGNAL(clicked()),this,SLOT(showPrintWindow()));
    connect(dateBtn,SIGNAL(clicked()),this,SLOT(onDateBtnClicked()));
    connect(imageBtn,SIGNAL(clicked()),this,SLOT(onImageBtnClicked()));
    onShapeBtnClicked();
    subToolTopWidget->setFixedHeight(shapeBtn->height());
//    subMainToolLayout->SetMinimumSize(QSize(10,shapeBtn->height()))
}


void EditorWidget::showPrintWindow()
{
    JetPrintWindow *printWin = new JetPrintWindow(this->paintFrame->toPixmap(),this->paintFrame);
    printWin->show();
    qDebug()<<"pppppppppppppppppppppppp";
    this->close();
}
void EditorWidget::onShapeBtnClicked(){

    qDebug()<<"on shape btn clicked ";
    if(whichSubToolsVisible==0)
        return;

    removeOtherSubLayout(whichSubToolsVisible);
    whichSubToolsVisible = 0;
    circleBtn = new QPushButton();
    QPixmap pixmapCircle(":/res/icons/ic_circle");
    QIcon circleIcon(pixmapCircle);
    circleBtn->setIcon(circleIcon);
    circleBtn->setIconSize(pixmapCircle.rect().size()/2);
    circleBtn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);
    circleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    ovalBtn= new QPushButton();
    QPixmap pixmapOval(":/res/icons/ic_ellipse");
    QIcon ovalIcon(pixmapOval);
    ovalBtn->setIcon(ovalIcon);
    ovalBtn->setIconSize(pixmapOval.rect().size()/2);
    ovalBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    ovalBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    squareBtn= new QPushButton();
    QPixmap pixmapSquare(":/res/icons/ic_square");
    QIcon squareIcon(pixmapSquare);
    squareBtn->setIcon(squareIcon);
    squareBtn->setIconSize(pixmapSquare.rect().size()/2);
    squareBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    squareBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    rectangleBtn= new QPushButton();
    QPixmap pixmaprectangle(":/res/icons/ic_rectangle");
    QIcon rectangleIcon(pixmaprectangle);
    rectangleBtn->setIcon(rectangleIcon);
    rectangleBtn->setIconSize(pixmaprectangle.rect().size()/2);
    rectangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    rectangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    triangleBtn = new QPushButton();
    QPixmap pixmaptriangle(":/res/icons/ic_triangle");
    QIcon triangleIcon(pixmaptriangle);
    triangleBtn->setIcon(triangleIcon);
    triangleBtn->setIconSize(pixmaptriangle.rect().size()/2);
    triangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    triangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    diamondBtn = new QPushButton();
    QPixmap pixmapdiamond(":/res/icons/ic_diamonds");
    QIcon diamondIcon(pixmapdiamond);
    diamondBtn->setIcon(diamondIcon);
    diamondBtn->setIconSize(pixmapdiamond.rect().size()/2);
    diamondBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    diamondBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    parallelogramBtn = new QPushButton();
    QPixmap pixmapparallelogram(":/res/icons/ic_parallalogram");
    QIcon parallelogramIcon(pixmapparallelogram);
    parallelogramBtn->setIcon(parallelogramIcon);
    parallelogramBtn->setIconSize(pixmapparallelogram.rect().size()/2);
    parallelogramBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    parallelogramBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    lineBtn = new QPushButton();
    QPixmap pixmapline(":/res/icons/ic_line");
    QIcon lineIcon(pixmapline);
    lineBtn->setIcon(lineIcon);
    lineBtn->setIconSize(pixmapline.rect().size()/2);
    lineBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
    lineBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

    subMainToolLayout->insertWidget(0,circleBtn);
    subMainToolLayout->insertWidget(1,ovalBtn);
    subMainToolLayout->insertWidget(2,squareBtn);
    subMainToolLayout->insertWidget(3,rectangleBtn);
    subMainToolLayout->insertWidget(4,triangleBtn);
    subMainToolLayout->insertWidget(5,diamondBtn);
    subMainToolLayout->insertWidget(6,parallelogramBtn);
    subMainToolLayout->insertWidget(7,lineBtn);
    subMainToolLayout->addStretch(1);
    //===================== shape tools ===================
//    deleteShapeBtn = new QPushButton("delete");
//    deleteShapeBtn->setVisible(false);
//    magnifyShapeBtn = new QPushButton("enlarge");
//    magnifyShapeBtn->setVisible(false);
//    minifyShapeBtn = new QPushButton("minify");
//    minifyShapeBtn->setVisible(false);
//    clockRotateShapeBtn = new  QPushButton("90 clock rotate");
//    clockRotateShapeBtn->setVisible(false);
//    horizantalShapeBtn = new QPushButton("horizantal shape");
//    horizantalShapeBtn->setVisible(false);
//    fillShapeBtn = new QPushButton("fill");
//    fillShapeBtn->setVisible(false);
//    shapeSelectToolLayout = new QHBoxLayout();

//    shapeSelectToolLayout->addWidget(fillShapeBtn);
//    shapeSelectToolLayout->addWidget(horizantalShapeBtn);
//    shapeSelectToolLayout->addWidget(clockRotateShapeBtn);
//    shapeSelectToolLayout->addWidget(magnifyShapeBtn);
//    shapeSelectToolLayout->addWidget(minifyShapeBtn);
//    shapeSelectToolLayout->addWidget(deleteShapeBtn);
//    //=====================================================
//    qDebug()<<"create shape layout";
//    if(whichSubToolsVisible==1){
//        delete sizeBtn;
//        delete fontBtn;
//        delete acceptTextBtn;
//        delete deleteBtn;
//        qDebug()<<"text btn delete ";
//        qDeleteAll(textSubToolsLayout->children());
//        qDebug()<<"text childeren delete ";
//        delete textSubToolsLayout;
//        qDebug()<<"text layout delete ";
//    }

//    shapeLayout->addItem(shapeSubToolsLayout);
//    shapeLayout->addItem(shapeSelectToolLayout);
//    widget->setLayout(shapeLayout);
//    widget->setStyleSheet("background-color:#D3D3D3;");
//    whichSubToolsVisible=0;
    connect(circleBtn,SIGNAL(released()),this,SLOT(circleClicked()));
    connect(rectangleBtn,SIGNAL(released()),this,SLOT(rectangleClicked()));
    connect(ovalBtn,SIGNAL(released()),this,SLOT(ovalClicked()));
    connect(squareBtn,SIGNAL(released()),this,SLOT(squareClicked()));
    connect(lineBtn,SIGNAL(released()),this,SLOT(lineClicked()));
    connect(diamondBtn,SIGNAL(released()),this,SLOT(diamondClicked()));
    connect(parallelogramBtn,SIGNAL(released()),this,SLOT(parallelogramClicked()));
    connect(triangleBtn,SIGNAL(released()),this,SLOT(triangleClicked()));

}
//void EditorWidget::onShapeBtnClicked(){

//    qDebug()<<"on shape btn clicked ";
//    if(whichSubToolsVisible==0)
//        return;
//    QVBoxLayout *shapeLayout = new QVBoxLayout();
//    shapeSubToolsLayout  = new QHBoxLayout();
//    circleBtn = new QPushButton();
//    QPixmap pixmapCircle(":/res/icons/ic_circle");
//    QIcon circleIcon(pixmapCircle);
//    circleBtn->setIcon(circleIcon);
//    circleBtn->setIconSize(pixmapCircle.rect().size()/2);
//    circleBtn->setFixedSize(shapeBtn->size().width()/1,shapeBtn->size().height()/1.5);
//    circleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    ovalBtn= new QPushButton();
//    QPixmap pixmapOval(":/res/icons/ic_ellipse");
//    QIcon ovalIcon(pixmapOval);
//    ovalBtn->setIcon(ovalIcon);
//    ovalBtn->setIconSize(pixmapOval.rect().size()/2);
//    ovalBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    ovalBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    squareBtn= new QPushButton();
//    QPixmap pixmapSquare(":/res/icons/ic_square");
//    QIcon squareIcon(pixmapSquare);
//    squareBtn->setIcon(squareIcon);
//    squareBtn->setIconSize(pixmapSquare.rect().size()/2);
//    squareBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    squareBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    rectangleBtn= new QPushButton();
//    QPixmap pixmaprectangle(":/res/icons/ic_rectangle");
//    QIcon rectangleIcon(pixmaprectangle);
//    rectangleBtn->setIcon(rectangleIcon);
//    rectangleBtn->setIconSize(pixmaprectangle.rect().size()/2);
//    rectangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    rectangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    triangleBtn = new QPushButton();
//    QPixmap pixmaptriangle(":/res/icons/ic_triangle");
//    QIcon triangleIcon(pixmaptriangle);
//    triangleBtn->setIcon(triangleIcon);
//    triangleBtn->setIconSize(pixmaptriangle.rect().size()/2);
//    triangleBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    triangleBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    diamondBtn = new QPushButton();
//    QPixmap pixmapdiamond(":/res/icons/ic_diamonds");
//    QIcon diamondIcon(pixmapdiamond);
//    diamondBtn->setIcon(diamondIcon);
//    diamondBtn->setIconSize(pixmapdiamond.rect().size()/2);
//    diamondBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    diamondBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    parallelogramBtn = new QPushButton();
//    QPixmap pixmapparallelogram(":/res/icons/ic_parallalogram");
//    QIcon parallelogramIcon(pixmapparallelogram);
//    parallelogramBtn->setIcon(parallelogramIcon);
//    parallelogramBtn->setIconSize(pixmapparallelogram.rect().size()/2);
//    parallelogramBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    parallelogramBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    lineBtn = new QPushButton();
//    QPixmap pixmapline(":/res/icons/ic_line");
//    QIcon lineIcon(pixmapline);
//    lineBtn->setIcon(lineIcon);
//    lineBtn->setIconSize(pixmapline.rect().size()/2);
//    lineBtn->setFixedSize(shapeBtn->size().width()/1.1,shapeBtn->size().height()/1.5);
//    lineBtn->setStyleSheet("margin-left: 3px;margin-right:30px");

//    shapeSubToolsLayout->addWidget(circleBtn);
//    shapeSubToolsLayout->addWidget(ovalBtn);
//    shapeSubToolsLayout->addWidget(squareBtn);
//    shapeSubToolsLayout->addWidget(rectangleBtn);
//    shapeSubToolsLayout->addWidget(triangleBtn);
//    shapeSubToolsLayout->addWidget(diamondBtn);
//    shapeSubToolsLayout->addWidget(parallelogramBtn);
//    shapeSubToolsLayout->addWidget(lineBtn);
//    shapeSubToolsLayout->addStretch(1);
//    //===================== shape tools ===================
//    deleteShapeBtn = new QPushButton("delete");
//    deleteShapeBtn->setVisible(false);
//    magnifyShapeBtn = new QPushButton("enlarge");
//    magnifyShapeBtn->setVisible(false);
//    minifyShapeBtn = new QPushButton("minify");
//    minifyShapeBtn->setVisible(false);
//    clockRotateShapeBtn = new  QPushButton("90 clock rotate");
//    clockRotateShapeBtn->setVisible(false);
//    horizantalShapeBtn = new QPushButton("horizantal shape");
//    horizantalShapeBtn->setVisible(false);
//    fillShapeBtn = new QPushButton("fill");
//    fillShapeBtn->setVisible(false);
//    shapeSelectToolLayout = new QHBoxLayout();

//    shapeSelectToolLayout->addWidget(fillShapeBtn);
//    shapeSelectToolLayout->addWidget(horizantalShapeBtn);
//    shapeSelectToolLayout->addWidget(clockRotateShapeBtn);
//    shapeSelectToolLayout->addWidget(magnifyShapeBtn);
//    shapeSelectToolLayout->addWidget(minifyShapeBtn);
//    shapeSelectToolLayout->addWidget(deleteShapeBtn);
//    //=====================================================
//    qDebug()<<"create shape layout";
//    if(whichSubToolsVisible==1){
//        delete sizeBtn;
//        delete fontBtn;
//        delete acceptTextBtn;
//        delete deleteBtn;
//        qDebug()<<"text btn delete ";
//        qDeleteAll(textSubToolsLayout->children());
//        qDebug()<<"text childeren delete ";
//        delete textSubToolsLayout;
//        qDebug()<<"text layout delete ";
//    }

//    shapeLayout->addItem(shapeSubToolsLayout);
//    shapeLayout->addItem(shapeSelectToolLayout);
//    widget->setLayout(shapeLayout);
//    widget->setStyleSheet("background-color:#D3D3D3;");
//    whichSubToolsVisible=0;
//    connect(circleBtn,SIGNAL(released()),this,SLOT(circleClicked()));
//    connect(rectangleBtn,SIGNAL(released()),this,SLOT(rectangleClicked()));
//    connect(ovalBtn,SIGNAL(released()),this,SLOT(ovalClicked()));
//    connect(squareBtn,SIGNAL(released()),this,SLOT(squareClicked()));
//    connect(lineBtn,SIGNAL(released()),this,SLOT(lineClicked()));
//    connect(diamondBtn,SIGNAL(released()),this,SLOT(diamondClicked()));
//    connect(parallelogramBtn,SIGNAL(released()),this,SLOT(parallelogramClicked()));
//    connect(triangleBtn,SIGNAL(released()),this,SLOT(triangleClicked()));

//}
void EditorWidget::onTextBtnClicked(){
    qDebug()<<"EditorWidget::onTextBtnClicked";
    if(whichSubToolsVisible==1)
        return;
    removeOtherSubLayout(whichSubToolsVisible);
    whichSubToolsVisible = 1;
    fontBtn = new QPushButton("font");
    sizeBtn = new QPushButton("size");
    subMainToolLayout->insertWidget(0,fontBtn);
    subMainToolLayout->insertWidget(1,sizeBtn);

//    qDebug()<<"create text layout";

//    if(whichSubToolsVisible==0){
//        delete circleBtn;
//        delete rectangleBtn;
//        delete triangleBtn;
//        delete squareBtn;
//        delete lineBtn;
//        delete ovalBtn;
//        delete parallelogramBtn;
//        delete diamondBtn;
//        qDebug()<<"shape btn  delete ";
//        qDeleteAll(shapeSubToolsLayout->children());
//        qDebug()<<"shape childeren delete ";
//        delete shapeSubToolsLayout;
//        qDebug()<<"shape layout delete ";
//    }

//    widget->setLayout(textSubToolsLayout);
//    whichSubToolsVisible=1;
//    paintFrame->addTextItem(QPoint(20,20));

}

//void EditorWidget::onTextBtnClicked(){
//    qDebug()<<"text clicked";
//    if(whichSubToolsVisible==1)
//        return;
//    textSubToolsLayout = new QHBoxLayout();
//    fontBtn = new QPushButton("font");
//    sizeBtn = new QPushButton("size");
//    acceptTextBtn = new QPushButton("accept");
//    deleteBtn = new QPushButton("delete");
//    textSubToolsLayout->addWidget(fontBtn);
//    textSubToolsLayout->addWidget(sizeBtn);
//    textSubToolsLayout->addWidget(acceptTextBtn);
//    textSubToolsLayout->addWidget(deleteBtn);

//    qDebug()<<"create text layout";

//    if(whichSubToolsVisible==0){
//        delete circleBtn;
//        delete rectangleBtn;
//        delete triangleBtn;
//        delete squareBtn;
//        delete lineBtn;
//        delete ovalBtn;
//        delete parallelogramBtn;
//        delete diamondBtn;
//        qDebug()<<"shape btn  delete ";
//        qDeleteAll(shapeSubToolsLayout->children());
//        qDebug()<<"shape childeren delete ";
//        delete shapeSubToolsLayout;
//        qDebug()<<"shape layout delete ";
//    }

//    widget->setLayout(textSubToolsLayout);
//    whichSubToolsVisible=1;
//    paintFrame->addTextItem(QPoint(20,20));

//}

void EditorWidget::onDateBtnClicked()
{
    qDebug()<<"date clicked";
    paintFrame->addDateTime(QPointF(0,0),300,120);

}

void EditorWidget::onImageBtnClicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "C:/",
                                                    tr("Images (*.png *.jpg)"));
    paintFrame->addImage(QPointF(30,30),fileName);

}

void EditorWidget::removeOtherSubLayout(int whichSelect)
{
    if(whichSelect==0){
        circleBtn->hide();
        squareBtn->hide();
        rectangleBtn->hide();
        triangleBtn->hide();
        diamondBtn->hide();
        ovalBtn->hide();
        parallelogramBtn->hide();
        lineBtn->hide();
    }else if(whichSelect==1){
        fontBtn->hide();
        sizeBtn->hide();
    }
    while(!subMainToolLayout->isEmpty()) {
        delete subMainToolLayout->takeAt(0);
    }

}
void EditorWidget::onBarcodeBtnClicked()
{
    qDebug()<<"barcode clicked";
//    paintFrame->addBarcode(QPointF(20,50),200,100);
    BarcodeSelectDialog *dialog = new BarcodeSelectDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowFlags(Qt::Widget);
    dialog->show();


}
void EditorWidget::circleClicked(){
    qDebug()<<"circle clicked";
    paintFrame->addCircle(QPointF(20,50),90);

}

void EditorWidget::rectangleClicked()
{
    qDebug()<<"rectangle clicked";
    paintFrame->addRectangle(QPointF(50,50),240,80);
}

void EditorWidget::squareClicked()
{
    qDebug()<<"square clicked";
    paintFrame->addSquare(QPointF(75,50),80);
}

void EditorWidget::lineClicked()
{
    qDebug()<<"line clicked";
    paintFrame->addLine(QPointF(10,10),QPointF(40,40));
}

void EditorWidget::triangleClicked()
{
    qDebug()<<"Triangle clicked";
    paintFrame->addTriangle(QPointF(50,10),QPointF(20,50),QPointF(80,50));
}

void EditorWidget::ovalClicked()
{
    qDebug()<<"OVAL clicked";
    paintFrame->addOval(QPointF(64,64),60,20);
}

void EditorWidget::diamondClicked()
{
    qDebug()<<"diamond clicked";
    paintFrame->addDiamond(QPointF(50,10),50,20);
}

void EditorWidget::parallelogramClicked()
{
    qDebug()<<"parallelogram clicked";
    paintFrame->addParallelogram(QPointF(50,10),90,30,75);
}

