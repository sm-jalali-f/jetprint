/****************************************************************************
** Meta object code from reading C++ file 'printsettingdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../editor/printsettingdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printsettingdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PrintSettingDialog_t {
    QByteArrayData data[9];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrintSettingDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrintSettingDialog_t qt_meta_stringdata_PrintSettingDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PrintSettingDialog"
QT_MOC_LITERAL(1, 19, 20), // "autoIntervalSelected"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "manualIntervalSelected"
QT_MOC_LITERAL(4, 64, 17), // "autoSpeedSelected"
QT_MOC_LITERAL(5, 82, 19), // "manualSpeedSelected"
QT_MOC_LITERAL(6, 102, 12), // "applyClicked"
QT_MOC_LITERAL(7, 115, 9), // "okClicked"
QT_MOC_LITERAL(8, 125, 13) // "cancelClicked"

    },
    "PrintSettingDialog\0autoIntervalSelected\0"
    "\0manualIntervalSelected\0autoSpeedSelected\0"
    "manualSpeedSelected\0applyClicked\0"
    "okClicked\0cancelClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrintSettingDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PrintSettingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PrintSettingDialog *_t = static_cast<PrintSettingDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->autoIntervalSelected(); break;
        case 1: _t->manualIntervalSelected(); break;
        case 2: _t->autoSpeedSelected(); break;
        case 3: _t->manualSpeedSelected(); break;
        case 4: _t->applyClicked(); break;
        case 5: _t->okClicked(); break;
        case 6: _t->cancelClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PrintSettingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PrintSettingDialog.data,
      qt_meta_data_PrintSettingDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PrintSettingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrintSettingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PrintSettingDialog.stringdata0))
        return static_cast<void*>(const_cast< PrintSettingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PrintSettingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
