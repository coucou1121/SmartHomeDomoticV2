/****************************************************************************
** Meta object code from reading C++ file 'dataanalyser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartHomeDomotic/DataManager/dataanalyser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataanalyser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataAnalyser_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataAnalyser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataAnalyser_t qt_meta_stringdata_DataAnalyser = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DataAnalyser"
QT_MOC_LITERAL(1, 13, 27), // "sendTankActualVolumeChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 8), // "objectID"
QT_MOC_LITERAL(4, 51, 12), // "actualVolume"
QT_MOC_LITERAL(5, 64, 27), // "ReceivedreplotWithSavedData"
QT_MOC_LITERAL(6, 92, 4), // "year"
QT_MOC_LITERAL(7, 97, 5), // "month"
QT_MOC_LITERAL(8, 103, 3) // "day"

    },
    "DataAnalyser\0sendTankActualVolumeChanged\0"
    "\0objectID\0actualVolume\0"
    "ReceivedreplotWithSavedData\0year\0month\0"
    "day"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataAnalyser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,

       0        // eod
};

void DataAnalyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataAnalyser *_t = static_cast<DataAnalyser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTankActualVolumeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->ReceivedreplotWithSavedData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataAnalyser::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataAnalyser::sendTankActualVolumeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject DataAnalyser::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DataAnalyser.data,
      qt_meta_data_DataAnalyser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataAnalyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataAnalyser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataAnalyser.stringdata0))
        return static_cast<void*>(const_cast< DataAnalyser*>(this));
    return QThread::qt_metacast(_clname);
}

int DataAnalyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataAnalyser::sendTankActualVolumeChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
