/****************************************************************************
** Meta object code from reading C++ file 'globalEnumatedAndExtern.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SmartHomeDomotic/globalEnumatedAndExtern.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'globalEnumatedAndExtern.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GlobalEnumatedAndExtern_t {
    QByteArrayData data[8];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlobalEnumatedAndExtern_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlobalEnumatedAndExtern_t qt_meta_stringdata_GlobalEnumatedAndExtern = {
    {
QT_MOC_LITERAL(0, 0, 23), // "GlobalEnumatedAndExtern"
QT_MOC_LITERAL(1, 24, 16), // "E_TankObjectName"
QT_MOC_LITERAL(2, 41, 5), // "TANK1"
QT_MOC_LITERAL(3, 47, 5), // "TANK2"
QT_MOC_LITERAL(4, 53, 5), // "TANK3"
QT_MOC_LITERAL(5, 59, 5), // "TANK4"
QT_MOC_LITERAL(6, 65, 5), // "TANK5"
QT_MOC_LITERAL(7, 71, 5) // "TANK6"

    },
    "GlobalEnumatedAndExtern\0E_TankObjectName\0"
    "TANK1\0TANK2\0TANK3\0TANK4\0TANK5\0TANK6"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlobalEnumatedAndExtern[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    6,   18,

 // enum data: key, value
       2, uint(GlobalEnumatedAndExtern::TANK1),
       3, uint(GlobalEnumatedAndExtern::TANK2),
       4, uint(GlobalEnumatedAndExtern::TANK3),
       5, uint(GlobalEnumatedAndExtern::TANK4),
       6, uint(GlobalEnumatedAndExtern::TANK5),
       7, uint(GlobalEnumatedAndExtern::TANK6),

       0        // eod
};

void GlobalEnumatedAndExtern::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject GlobalEnumatedAndExtern::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GlobalEnumatedAndExtern.data,
      qt_meta_data_GlobalEnumatedAndExtern,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GlobalEnumatedAndExtern::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlobalEnumatedAndExtern::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GlobalEnumatedAndExtern.stringdata0))
        return static_cast<void*>(const_cast< GlobalEnumatedAndExtern*>(this));
    return QObject::qt_metacast(_clname);
}

int GlobalEnumatedAndExtern::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
