/****************************************************************************
** Meta object code from reading C++ file 'warningreciever.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Domotique/SmartHomeDomotic/warningreciever.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'warningreciever.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WarningReceiver_t {
    QByteArrayData data[10];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WarningReceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WarningReceiver_t qt_meta_stringdata_WarningReceiver = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WarningReceiver"
QT_MOC_LITERAL(1, 16, 16), // "errorMsgRecieved"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "tanksWarning"
QT_MOC_LITERAL(4, 47, 9), // "errorText"
QT_MOC_LITERAL(5, 57, 6), // "volume"
QT_MOC_LITERAL(6, 64, 12), // "warningLevel"
QT_MOC_LITERAL(7, 77, 6), // "status"
QT_MOC_LITERAL(8, 84, 8), // "errorMsg"
QT_MOC_LITERAL(9, 93, 13) // "warningActive"

    },
    "WarningReceiver\0errorMsgRecieved\0\0"
    "tanksWarning\0errorText\0volume\0"
    "warningLevel\0status\0errorMsg\0warningActive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WarningReceiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       4,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    4,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QReal, QMetaType::QReal, QMetaType::Bool,    4,    5,    6,    7,

 // properties: name, type, flags
       8, QMetaType::QString, 0x00495103,
       5, QMetaType::QReal, 0x00495103,
       6, QMetaType::QReal, 0x00495103,
       9, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,

       0        // eod
};

void WarningReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WarningReceiver *_t = static_cast<WarningReceiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errorMsgRecieved(); break;
        case 1: _t->tanksWarning((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const qreal(*)>(_a[2])),(*reinterpret_cast< const qreal(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WarningReceiver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WarningReceiver::errorMsgRecieved)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WarningReceiver *_t = static_cast<WarningReceiver *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->errorMsg(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->volume(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->warningLevel(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->warningActive(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WarningReceiver *_t = static_cast<WarningReceiver *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setErrorMsg(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setVolume(*reinterpret_cast< qreal*>(_v)); break;
        case 2: _t->setWarningLevel(*reinterpret_cast< qreal*>(_v)); break;
        case 3: _t->setWarningActive(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WarningReceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WarningReceiver.data,
      qt_meta_data_WarningReceiver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WarningReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WarningReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WarningReceiver.stringdata0))
        return static_cast<void*>(const_cast< WarningReceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int WarningReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WarningReceiver::errorMsgRecieved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
