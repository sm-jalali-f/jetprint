/****************************************************************************
** Meta object code from reading C++ file 'inserttabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editor/tabWidget/inserttabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inserttabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InsertTabWidget_t {
    QByteArrayData data[12];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InsertTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InsertTabWidget_t qt_meta_stringdata_InsertTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "InsertTabWidget"
QT_MOC_LITERAL(1, 16, 16), // "onTextBtnClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "onImageBtnClicked"
QT_MOC_LITERAL(4, 52, 19), // "onCounterBtnClicked"
QT_MOC_LITERAL(5, 72, 16), // "onDateBtnClicked"
QT_MOC_LITERAL(6, 89, 16), // "onTimeBtnClicked"
QT_MOC_LITERAL(7, 106, 14), // "TextBtnClicked"
QT_MOC_LITERAL(8, 121, 15), // "ImageBtnClicked"
QT_MOC_LITERAL(9, 137, 17), // "CounterBtnClicked"
QT_MOC_LITERAL(10, 155, 14), // "DateBtnClicked"
QT_MOC_LITERAL(11, 170, 14) // "TimeBtnClicked"

    },
    "InsertTabWidget\0onTextBtnClicked\0\0"
    "onImageBtnClicked\0onCounterBtnClicked\0"
    "onDateBtnClicked\0onTimeBtnClicked\0"
    "TextBtnClicked\0ImageBtnClicked\0"
    "CounterBtnClicked\0DateBtnClicked\0"
    "TimeBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InsertTabWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InsertTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InsertTabWidget *_t = static_cast<InsertTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTextBtnClicked(); break;
        case 1: _t->onImageBtnClicked(); break;
        case 2: _t->onCounterBtnClicked(); break;
        case 3: _t->onDateBtnClicked(); break;
        case 4: _t->onTimeBtnClicked(); break;
        case 5: _t->TextBtnClicked(); break;
        case 6: _t->ImageBtnClicked(); break;
        case 7: _t->CounterBtnClicked(); break;
        case 8: _t->DateBtnClicked(); break;
        case 9: _t->TimeBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InsertTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InsertTabWidget::onTextBtnClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (InsertTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InsertTabWidget::onImageBtnClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (InsertTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InsertTabWidget::onCounterBtnClicked)) {
                *result = 2;
            }
        }
        {
            typedef void (InsertTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InsertTabWidget::onDateBtnClicked)) {
                *result = 3;
            }
        }
        {
            typedef void (InsertTabWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InsertTabWidget::onTimeBtnClicked)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject InsertTabWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InsertTabWidget.data,
      qt_meta_data_InsertTabWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InsertTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InsertTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InsertTabWidget.stringdata0))
        return static_cast<void*>(const_cast< InsertTabWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int InsertTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void InsertTabWidget::onTextBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void InsertTabWidget::onImageBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void InsertTabWidget::onCounterBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void InsertTabWidget::onDateBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void InsertTabWidget::onTimeBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
