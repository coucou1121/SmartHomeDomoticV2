/****************************************************************************
** Meta object code from reading C++ file 'setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartHomeDomotic/setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Setting_t {
    QByteArrayData data[26];
    char stringdata0[496];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Setting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Setting_t qt_meta_stringdata_Setting = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Setting"
QT_MOC_LITERAL(1, 8, 21), // "receivedTankIsVisible"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "objectID"
QT_MOC_LITERAL(4, 40, 9), // "isVisible"
QT_MOC_LITERAL(5, 50, 24), // "receivedTankTitleChanged"
QT_MOC_LITERAL(6, 75, 9), // "titleText"
QT_MOC_LITERAL(7, 85, 28), // "receivedTankVolumeMaxChanged"
QT_MOC_LITERAL(8, 114, 10), // "objectName"
QT_MOC_LITERAL(9, 125, 9), // "volumeMax"
QT_MOC_LITERAL(10, 135, 31), // "receivedWarningLowLevelFromTank"
QT_MOC_LITERAL(11, 167, 8), // "isActive"
QT_MOC_LITERAL(12, 176, 34), // "receivedTankWarningLowLevelCh..."
QT_MOC_LITERAL(13, 211, 8), // "lowLevel"
QT_MOC_LITERAL(14, 220, 32), // "receivedTankLiquideFillupChanged"
QT_MOC_LITERAL(15, 253, 13), // "liquideFillup"
QT_MOC_LITERAL(16, 267, 33), // "receivedTankHeightMaxLevelCha..."
QT_MOC_LITERAL(17, 301, 10), // "heightVMax"
QT_MOC_LITERAL(18, 312, 33), // "receivedTankOffsetPressureCha..."
QT_MOC_LITERAL(19, 346, 19), // "offsetPressureValue"
QT_MOC_LITERAL(20, 366, 31), // "receivedTankActualVolumeChanged"
QT_MOC_LITERAL(21, 398, 12), // "volumeActual"
QT_MOC_LITERAL(22, 411, 32), // "receivedGraphReccordTimesChanged"
QT_MOC_LITERAL(23, 444, 11), // "reccordTime"
QT_MOC_LITERAL(24, 456, 25), // "receivedOnCalibrationMode"
QT_MOC_LITERAL(25, 482, 13) // "onCalibration"

    },
    "Setting\0receivedTankIsVisible\0\0objectID\0"
    "isVisible\0receivedTankTitleChanged\0"
    "titleText\0receivedTankVolumeMaxChanged\0"
    "objectName\0volumeMax\0"
    "receivedWarningLowLevelFromTank\0"
    "isActive\0receivedTankWarningLowLevelChanged\0"
    "lowLevel\0receivedTankLiquideFillupChanged\0"
    "liquideFillup\0receivedTankHeightMaxLevelChanged\0"
    "heightVMax\0receivedTankOffsetPressureChanged\0"
    "offsetPressureValue\0receivedTankActualVolumeChanged\0"
    "volumeActual\0receivedGraphReccordTimesChanged\0"
    "reccordTime\0receivedOnCalibrationMode\0"
    "onCalibration"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Setting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x0a /* Public */,
       5,    2,   74,    2, 0x0a /* Public */,
       7,    2,   79,    2, 0x0a /* Public */,
      10,    2,   84,    2, 0x0a /* Public */,
      12,    2,   89,    2, 0x0a /* Public */,
      14,    2,   94,    2, 0x0a /* Public */,
      16,    2,   99,    2, 0x0a /* Public */,
      18,    2,  104,    2, 0x0a /* Public */,
      20,    2,  109,    2, 0x0a /* Public */,
      22,    1,  114,    2, 0x0a /* Public */,
      24,    1,  117,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Bool,   25,

       0        // eod
};

void Setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Setting *_t = static_cast<Setting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receivedTankIsVisible((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 1: _t->receivedTankTitleChanged((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->receivedTankVolumeMaxChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->receivedWarningLowLevelFromTank((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 4: _t->receivedTankWarningLowLevelChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: _t->receivedTankLiquideFillupChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 6: _t->receivedTankHeightMaxLevelChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->receivedTankOffsetPressureChanged((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: _t->receivedTankActualVolumeChanged((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 9: _t->receivedGraphReccordTimesChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 10: _t->receivedOnCalibrationMode((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Setting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Setting.data,
      qt_meta_data_Setting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Setting.stringdata0))
        return static_cast<void*>(const_cast< Setting*>(this));
    return QObject::qt_metacast(_clname);
}

int Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
