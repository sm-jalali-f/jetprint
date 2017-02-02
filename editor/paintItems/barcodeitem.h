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

#ifndef BARCODEITEM_H
#define BARCODEITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <qzint.h>
#include <zint.h>
#include <stdio.h>
#include <paintItems/drawitem.h>

#include <QDebug>
#include <QPainter>
//#include <QtWidgets>



class BarcodeItem: public DrawItem
{
public:
    BarcodeItem(QWidget *parent,QPointF position,int width,int height);

    QPoint getPosition();
    int getWidth() const;
    int getHeight() const ;
    QPixmap toPixmap();
    void setPosition(int x,int y);
    void hideItem();
    void showItem();
    bool isInside(QPoint point);

    bool onMousePressed(QMouseEvent *event);
    void onMouseReleased(QMouseEvent *event);
    MouseMoveResult onMouseMove(QMouseEvent *event) ;

    void keyboardPressed(QKeyEvent *event);

    void itemDropEvent(QDropEvent *event);
    void itemDragEnterEvent(QDragEnterEvent *event);
    void itemDragMoveEvent(QDragMoveEvent *event);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    struct zint_symbol *my_symbol;
    QPointF position;
    int width;
    int height;
//    mutable Zint::QZint bc;
//    int w,h;
//    Zint::QZint::AspectRatioMode ar;
};

#endif
