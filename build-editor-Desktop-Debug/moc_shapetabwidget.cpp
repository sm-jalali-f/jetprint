/****************************************************************************
** Meta object code from reading C++ file 'shapetabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editor/tabWidget/shapetabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shapetabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShapeTabWidget_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShapeTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShapeTabWidget_t qt_meta_stringdata_ShapeTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ShapeTabWidget"
QT_MOC_LITERAL(1, 15, 13), // "circleClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 16), // "rectangleClicked"
QT_MOC_LITERAL(4, 47, 13), // "squareClicked"
QT_MOC_LITERAL(5, 61, 11), // "lineClicked"
QT_MOC_LITERAL(6, 73, 15), // "triangleClicked"
QT_MOC_LITERAL(7, 89, 11), // "ovalClicked"
QT_MOC_LITERAL(8, 101, 14), // "diamondClicked"
QT_MOC_LITERAL(9, 116, 20) // "parallelogramClicked"

    },
    "ShapeTabWidget\0circleClicked\0\0"
    "rectangleClicked\0squareClicked\0"
    "lineClicked\0triangleClicked\0ovalClicked\0"
    "diamondClicked\0parallelogramClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShapeTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShapeTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShapeTabWidget *_t = static_cast<ShapeTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->circleClicked(); break;
        case 1: _t->rectangleClicked(); break;
        case 2: _t->squareClicked(); break;
        case 3: _t->lineClicked(); break;
        case 4: _t->triangleClicked(); break;
        case 5: _t->ovalClicked(); break;
        case 6: _t->diamondClicked(); break;
        case 7: _t->parallelogramClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ShapeTabWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ShapeTabWidget.data,
      qt_meta_data_ShapeTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShapeTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShapeTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShapeTabWidget.stringdata0))
        return static_cast<void*>(const_cast< ShapeTabWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ShapeTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
