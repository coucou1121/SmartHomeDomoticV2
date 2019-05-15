/****************************************************************************
** Meta object code from reading C++ file 'smtp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Domotique/SmartHomeDomotic/smtp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smtp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Smtp_t {
    QByteArrayData data[14];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Smtp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Smtp_t qt_meta_stringdata_Smtp = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Smtp"
QT_MOC_LITERAL(1, 5, 6), // "status"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 9), // "connected"
QT_MOC_LITERAL(4, 23, 12), // "disconnected"
QT_MOC_LITERAL(5, 36, 12), // "bytesWritten"
QT_MOC_LITERAL(6, 49, 5), // "bytes"
QT_MOC_LITERAL(7, 55, 9), // "readyRead"
QT_MOC_LITERAL(8, 65, 12), // "stateChanged"
QT_MOC_LITERAL(9, 78, 23), // "QTcpSocket::SocketState"
QT_MOC_LITERAL(10, 102, 11), // "socketState"
QT_MOC_LITERAL(11, 114, 13), // "errorReceived"
QT_MOC_LITERAL(12, 128, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(13, 152, 11) // "socketError"

    },
    "Smtp\0status\0\0connected\0disconnected\0"
    "bytesWritten\0bytes\0readyRead\0stateChanged\0"
    "QTcpSocket::SocketState\0socketState\0"
    "errorReceived\0QTcpSocket::SocketError\0"
    "socketError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Smtp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   52,    2, 0x0a /* Public */,
       4,    0,   53,    2, 0x0a /* Public */,
       5,    1,   54,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x08 /* Private */,
      11,    1,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void Smtp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Smtp *_t = static_cast<Smtp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->status((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->connected(); break;
        case 2: _t->disconnected(); break;
        case 3: _t->bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->readyRead(); break;
        case 5: _t->stateChanged((*reinterpret_cast< QTcpSocket::SocketState(*)>(_a[1]))); break;
        case 6: _t->errorReceived((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Smtp::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Smtp::status)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Smtp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Smtp.data,
      qt_meta_data_Smtp,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Smtp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Smtp::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Smtp.stringdata0))
        return static_cast<void*>(const_cast< Smtp*>(this));
    return QObject::qt_metacast(_clname);
}

int Smtp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Smtp::status(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
