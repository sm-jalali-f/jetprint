#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T23:06:31
#
#-------------------------------------------------
QT       += core gui quick
#CONFIG  += serialport
QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets
#QT       += core gui
QT += serialport
#QT += qml quick
#QT += quick
#QT += widgets
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app


SOURCES += main.cpp\
    editorwidget.cpp \
    paintframe.cpp \
    printwindow.cpp \
    serialport/printhandler.cpp \
    paintItems/shapes/circleitem.cpp \
    paintItems/shapes/rectangleitem.cpp\
    paintItems/drawitem.cpp \
    paintItems/shapes/triangleitem.cpp \
    paintItems/shapes/ovalitem.cpp \
    paintItems/shapes/diamonditem.cpp \
    paintItems/shapes/lineitem.cpp \
    paintItems/shapes/parallelogramitem.cpp \
    paintItems/dateitem.cpp \
    paintItems/myimageitem.cpp \
#    eventDispatchers/paintframeeventdispatcher.cpp
    readport.cpp \
    actionHandler/paintaction.cpp \
    actionHandler/actionmanager.cpp \
    paintItems/textitem.cpp \
    types/drawitemtype.cpp \
    types/mousemoveresult.cpp \
    types/drawitemstate.cpp \
    paintItems/barcodeitem.cpp \
    barcodeselectdialog.cpp \
    types/printtype.cpp \
    paintItems/endpaintline.cpp \
    paintItems/verticalruler.cpp \
    paintItems/horizontalruler.cpp


HEADERS  += \
    editorwidget.h \
    paintframe.h \
    printwindow.h \
    serialport/printhandler.h \
    paintItems/shapes/circleitem.h \
    paintItems/shapes/rectangleitem.h \
    paintItems/drawitem.h \
    paintItems/shapes/triangleitem.h \
    paintItems/shapes/ovalitem.h \
    paintItems/shapes/diamonditem.h \
    paintItems/shapes/lineitem.h \
    paintItems/shapes/parallelogramitem.h \
    paintItems/dateitem.h \
    paintItems/myimageitem.h \
#    eventDispatchers/paintframeeventdispatcher.h
    readport.h \
    actionHandler/paintaction.h \
    actionHandler/actionmanager.h \
    paintItems/textitem.h \
    types/drawitemtype.h \
    types/mousemoveresult.h \
    types/drawitemstate.h \
    paintItems/barcodeitem.h \
    barcodeselectdialog.h \
    types/printtype.h \
    paintItems/endpaintline.h \
    paintItems/verticalruler.h \
    paintItems/horizontalruler.h


RESOURCES += \
    resFile.qrc\



#unix:!macx: LIBS += -L$$PWD/../../../../Downloads/zint-2.4.2/build/backend/ -lzint

#INCLUDEPATH += $$PWD/../../../../Downloads/zint-2.4.2/build/backend
#DEPENDPATH += $$PWD/../../../../Downloads/zint-2.4.2/build/backend

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Downloads/zint-2.4.2/build/backend_qt4/release/ -lQZint
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Downloads/zint-2.4.2/build/backend_qt4/debug/ -lQZint
#else:unix: LIBS += -L$$PWD/../../../../Downloads/zint-2.4.2/build/backend_qt4/ -lQZint

#INCLUDEPATH += $$PWD/../../../../Downloads/zint-2.4.2/build/backend_qt4
#DEPENDPATH += $$PWD/../../../../Downloads/zint-2.4.2/build/backend_qt4

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend_qt4/release/ -lQZint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend_qt4/debug/ -lQZint
else:unix: LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend_qt4/ -lQZint

INCLUDEPATH += $$PWD/../../../../Downloads/packages/zint/build/backend_qt4
DEPENDPATH += $$PWD/../../../../Downloads/packages/zint/build/backend_qt4

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend/release/ -lzint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend/debug/ -lzint
else:unix: LIBS += -L$$PWD/../../../../Downloads/packages/zint/build/backend/ -lzint

INCLUDEPATH += $$PWD/../../../../Downloads/packages/zint/build/backend
DEPENDPATH += $$PWD/../../../../Downloads/packages/zint/build/backend
