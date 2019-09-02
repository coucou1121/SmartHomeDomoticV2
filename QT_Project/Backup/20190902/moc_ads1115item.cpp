/****************************************************************************
** Meta object code from reading C++ file 'ads1115item.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartHomeDomotic/ADS1115/ads1115item.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ads1115item.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ADS1115Item_t {
    QByteArrayData data[5];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ADS1115Item_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ADS1115Item_t qt_meta_stringdata_ADS1115Item = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ADS1115Item"
QT_MOC_LITERAL(1, 12, 27), // "sendTankActualVolumeChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "objectID"
QT_MOC_LITERAL(4, 50, 12) // "actualVolume"

    },
    "ADS1115Item\0sendTankActualVolumeChanged\0"
    "\0objectID\0actualVolume"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ADS1115Item[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void ADS1115Item::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ADS1115Item *_t = static_cast<ADS1115Item *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTankActualVolumeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ADS1115Item::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ADS1115Item::sendTankActualVolumeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ADS1115Item::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ADS1115Item.data,
      qt_meta_data_ADS1115Item,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ADS1115Item::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ADS1115Item::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ADS1115Item.stringdata0))
        return static_cast<void*>(const_cast< ADS1115Item*>(this));
    return QThread::qt_metacast(_clname);
}

int ADS1115Item::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ADS1115Item::sendTankActualVolumeChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
