/****************************************************************************
** Meta object code from reading C++ file 'bme280.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartHomeDomotic/bme280.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bme280.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BME280_t {
    QByteArrayData data[10];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BME280_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BME280_t qt_meta_stringdata_BME280 = {
    {
QT_MOC_LITERAL(0, 0, 6), // "BME280"
QT_MOC_LITERAL(1, 7, 8), // "finished"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 19), // "receivedudateValues"
QT_MOC_LITERAL(4, 37, 11), // "temperature"
QT_MOC_LITERAL(5, 49, 8), // "humidity"
QT_MOC_LITERAL(6, 58, 8), // "pressure"
QT_MOC_LITERAL(7, 67, 22), // "addValueInroomDataPlot"
QT_MOC_LITERAL(8, 90, 30), // "receivedApplicationModeChanged"
QT_MOC_LITERAL(9, 121, 15) // "applicationMode"

    },
    "BME280\0finished\0\0receivedudateValues\0"
    "temperature\0humidity\0pressure\0"
    "addValueInroomDataPlot\0"
    "receivedApplicationModeChanged\0"
    "applicationMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BME280[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   35,    2, 0x0a /* Public */,
       7,    0,   42,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal, QMetaType::QReal,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void BME280::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BME280 *_t = static_cast<BME280 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->receivedudateValues((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3]))); break;
        case 2: _t->addValueInroomDataPlot(); break;
        case 3: _t->receivedApplicationModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BME280::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BME280::finished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject BME280::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BME280.data,
      qt_meta_data_BME280,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BME280::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BME280::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BME280.stringdata0))
        return static_cast<void*>(const_cast< BME280*>(this));
    return QObject::qt_metacast(_clname);
}

int BME280::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BME280::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
