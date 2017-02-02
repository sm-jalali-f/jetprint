#ifndef BARCODESELECTDIALOG_H
#define BARCODESELECTDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QString>
#include <qzint.h>
#include <zint.h>
#include <stdio.h>
class BarcodeSelectDialog : public QWidget
{
    Q_OBJECT
public:
    explicit BarcodeSelectDialog(QWidget *parent = 0);

signals:

public slots:
    void barcodeTypeChanged();

private:
    int barcodeWidth,barcodeHeight;
    void setupBarcode(int type,int width,int height,unsigned char* encode);
    struct zint_symbol *my_symbol;
    QString imagePath;
    QGraphicsPixmapItem *imageItem;
    QGraphicsScene *imageScene;
    QGraphicsView *imageView;
    QComboBox *barcodeTypeCombo;
    QPushButton *generateBtn;
    QLineEdit *encodeDataEt;
    QLineEdit *barcodeWidthEt,*barcodeHeightEt;

};

#endif // BARCODESELECTDIALOG_H
