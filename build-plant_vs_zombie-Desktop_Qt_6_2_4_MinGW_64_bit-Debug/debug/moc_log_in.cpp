/****************************************************************************
** Meta object code from reading C++ file 'log_in.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../plant_vs_zombie/log_in.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'log_in.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_log_in_t {
    const uint offsetsAndSize[12];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_log_in_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_log_in_t qt_meta_stringdata_log_in = {
    {
QT_MOC_LITERAL(0, 6), // "log_in"
QT_MOC_LITERAL(7, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(52, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(74, 12) // "readResponse"

    },
    "log_in\0on_buttonBox_rejected\0\0"
    "on_buttonBox_accepted\0on_pushButton_clicked\0"
    "readResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_log_in[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    0,   40,    2, 0x08,    3 /* Private */,
       5,    0,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void log_in::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<log_in *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_buttonBox_rejected(); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->readResponse(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject log_in::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_log_in.offsetsAndSize,
    qt_meta_data_log_in,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_log_in_t
, QtPrivate::TypeAndForceComplete<log_in, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *log_in::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *log_in::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_log_in.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int log_in::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
