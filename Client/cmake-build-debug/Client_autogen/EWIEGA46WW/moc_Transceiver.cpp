/****************************************************************************
** Meta object code from reading C++ file 'Transceiver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Transceiver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Transceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Transceiver_t {
    QByteArrayData data[11];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Transceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Transceiver_t qt_meta_stringdata_Transceiver = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Transceiver"
QT_MOC_LITERAL(1, 12, 14), // "readyToProcess"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "DataPacket"
QT_MOC_LITERAL(4, 39, 3), // "pkt"
QT_MOC_LITERAL(5, 43, 10), // "deleteText"
QT_MOC_LITERAL(6, 54, 10), // "recvPacket"
QT_MOC_LITERAL(7, 65, 10), // "sendPacket"
QT_MOC_LITERAL(8, 76, 15), // "sendAllMessages"
QT_MOC_LITERAL(9, 92, 12), // "disconnected"
QT_MOC_LITERAL(10, 105, 23) // "terminateLastOperations"

    },
    "Transceiver\0readyToProcess\0\0DataPacket\0"
    "pkt\0deleteText\0recvPacket\0sendPacket\0"
    "sendAllMessages\0disconnected\0"
    "terminateLastOperations"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Transceiver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x0a /* Public */,
       7,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Transceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Transceiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyToProcess((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 1: _t->deleteText(); break;
        case 2: _t->recvPacket(); break;
        case 3: _t->sendPacket((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 4: _t->sendAllMessages(); break;
        case 5: _t->disconnected(); break;
        case 6: _t->terminateLastOperations(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataPacket >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataPacket >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Transceiver::*)(DataPacket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver::readyToProcess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Transceiver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Transceiver::deleteText)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Transceiver::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Transceiver.data,
    qt_meta_data_Transceiver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Transceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Transceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Transceiver.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Transceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Transceiver::readyToProcess(DataPacket _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Transceiver::deleteText()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
