/****************************************************************************
** Meta object code from reading C++ file 'editorwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editor/editorwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditorWidget_t {
    QByteArrayData data[16];
    char stringdata0[241];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorWidget_t qt_meta_stringdata_EditorWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "EditorWidget"
QT_MOC_LITERAL(1, 13, 19), // "onBarcodeBtnClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "onShapeBtnClicked"
QT_MOC_LITERAL(4, 52, 16), // "onTextBtnClicked"
QT_MOC_LITERAL(5, 69, 16), // "onDateBtnClicked"
QT_MOC_LITERAL(6, 86, 17), // "onImageBtnClicked"
QT_MOC_LITERAL(7, 104, 13), // "circleClicked"
QT_MOC_LITERAL(8, 118, 16), // "rectangleClicked"
QT_MOC_LITERAL(9, 135, 13), // "squareClicked"
QT_MOC_LITERAL(10, 149, 11), // "lineClicked"
QT_MOC_LITERAL(11, 161, 15), // "triangleClicked"
QT_MOC_LITERAL(12, 177, 11), // "ovalClicked"
QT_MOC_LITERAL(13, 189, 14), // "diamondClicked"
QT_MOC_LITERAL(14, 204, 20), // "parallelogramClicked"
QT_MOC_LITERAL(15, 225, 15) // "showPrintWindow"

    },
    "EditorWidget\0onBarcodeBtnClicked\0\0"
    "onShapeBtnClicked\0onTextBtnClicked\0"
    "onDateBtnClicked\0onImageBtnClicked\0"
    "circleClicked\0rectangleClicked\0"
    "squareClicked\0lineClicked\0triangleClicked\0"
    "ovalClicked\0diamondClicked\0"
    "parallelogramClicked\0showPrintWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void EditorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorWidget *_t = static_cast<EditorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBarcodeBtnClicked(); break;
        case 1: _t->onShapeBtnClicked(); break;
        case 2: _t->onTextBtnClicked(); break;
        case 3: _t->onDateBtnClicked(); break;
        case 4: _t->onImageBtnClicked(); break;
        case 5: _t->circleClicked(); break;
        case 6: _t->rectangleClicked(); break;
        case 7: _t->squareClicked(); break;
        case 8: _t->lineClicked(); break;
        case 9: _t->triangleClicked(); break;
        case 10: _t->ovalClicked(); break;
        case 11: _t->diamondClicked(); break;
        case 12: _t->parallelogramClicked(); break;
        case 13: _t->showPrintWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EditorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditorWidget.data,
      qt_meta_data_EditorWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditorWidget.stringdata0))
        return static_cast<void*>(const_cast< EditorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
