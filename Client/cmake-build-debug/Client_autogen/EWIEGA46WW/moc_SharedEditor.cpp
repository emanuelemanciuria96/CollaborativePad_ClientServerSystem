/****************************************************************************
** Meta object code from reading C++ file 'SharedEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SharedEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SharedEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SharedEditor_t {
    QByteArrayData data[34];
    char stringdata0[361];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SharedEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SharedEditor_t qt_meta_stringdata_SharedEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SharedEditor"
QT_MOC_LITERAL(1, 13, 14), // "symbolsChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "pos"
QT_MOC_LITERAL(4, 33, 1), // "s"
QT_MOC_LITERAL(5, 35, 6), // "siteId"
QT_MOC_LITERAL(6, 42, 17), // "Message::action_t"
QT_MOC_LITERAL(7, 60, 6), // "action"
QT_MOC_LITERAL(8, 67, 13), // "deleteAllText"
QT_MOC_LITERAL(9, 81, 16), // "filePathsArrived"
QT_MOC_LITERAL(10, 98, 16), // "QVector<QString>"
QT_MOC_LITERAL(11, 115, 5), // "paths"
QT_MOC_LITERAL(12, 121, 13), // "loginAchieved"
QT_MOC_LITERAL(13, 135, 15), // "userInfoArrived"
QT_MOC_LITERAL(14, 151, 5), // "image"
QT_MOC_LITERAL(15, 157, 8), // "nickname"
QT_MOC_LITERAL(16, 166, 4), // "name"
QT_MOC_LITERAL(17, 171, 5), // "email"
QT_MOC_LITERAL(18, 177, 22), // "remoteCursorPosChanged"
QT_MOC_LITERAL(19, 200, 12), // "removeCursor"
QT_MOC_LITERAL(20, 213, 9), // "highlight"
QT_MOC_LITERAL(21, 223, 9), // "loginSlot"
QT_MOC_LITERAL(22, 233, 8), // "QString&"
QT_MOC_LITERAL(23, 242, 8), // "username"
QT_MOC_LITERAL(24, 251, 8), // "password"
QT_MOC_LITERAL(25, 260, 7), // "process"
QT_MOC_LITERAL(26, 268, 10), // "DataPacket"
QT_MOC_LITERAL(27, 279, 3), // "pkt"
QT_MOC_LITERAL(28, 283, 17), // "requireFileSystem"
QT_MOC_LITERAL(29, 301, 11), // "requireFile"
QT_MOC_LITERAL(30, 313, 8), // "fileName"
QT_MOC_LITERAL(31, 322, 12), // "deleteThread"
QT_MOC_LITERAL(32, 335, 9), // "clearText"
QT_MOC_LITERAL(33, 345, 15) // "sendUpdatedInfo"

    },
    "SharedEditor\0symbolsChanged\0\0pos\0s\0"
    "siteId\0Message::action_t\0action\0"
    "deleteAllText\0filePathsArrived\0"
    "QVector<QString>\0paths\0loginAchieved\0"
    "userInfoArrived\0image\0nickname\0name\0"
    "email\0remoteCursorPosChanged\0removeCursor\0"
    "highlight\0loginSlot\0QString&\0username\0"
    "password\0process\0DataPacket\0pkt\0"
    "requireFileSystem\0requireFile\0fileName\0"
    "deleteThread\0clearText\0sendUpdatedInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SharedEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   89,    2, 0x06 /* Public */,
       8,    0,   98,    2, 0x06 /* Public */,
       9,    1,   99,    2, 0x06 /* Public */,
      12,    0,  102,    2, 0x06 /* Public */,
      13,    4,  103,    2, 0x06 /* Public */,
      18,    2,  112,    2, 0x06 /* Public */,
      19,    1,  117,    2, 0x06 /* Public */,
      20,    2,  120,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  125,    2, 0x0a /* Public */,
      25,    1,  130,    2, 0x0a /* Public */,
      28,    0,  133,    2, 0x0a /* Public */,
      29,    1,  134,    2, 0x0a /* Public */,
      31,    0,  137,    2, 0x0a /* Public */,
      32,    0,  138,    2, 0x0a /* Public */,
      33,    3,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 6,    3,    4,    5,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 22,   23,   24,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString,   14,   16,   17,

       0        // eod
};

void SharedEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SharedEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->symbolsChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        case 1: _t->deleteAllText(); break;
        case 2: _t->filePathsArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 3: _t->loginAchieved(); break;
        case 4: _t->userInfoArrived((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 5: _t->remoteCursorPosChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 6: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 8: _t->loginSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->process((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 10: _t->requireFileSystem(); break;
        case 11: _t->requireFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->deleteThread(); break;
        case 13: _t->clearText(); break;
        case 14: _t->sendUpdatedInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 9:
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
            using _t = void (SharedEditor::*)(qint32 , const QString & , qint32 , Message::action_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::symbolsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::deleteAllText)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::filePathsArrived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginAchieved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userInfoArrived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteCursorPosChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeCursor)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::highlight)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SharedEditor::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SharedEditor.data,
    qt_meta_data_SharedEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SharedEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SharedEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SharedEditor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SharedEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SharedEditor::symbolsChanged(qint32 _t1, const QString & _t2, qint32 _t3, Message::action_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SharedEditor::deleteAllText()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SharedEditor::filePathsArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SharedEditor::loginAchieved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SharedEditor::userInfoArrived(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SharedEditor::remoteCursorPosChanged(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SharedEditor::removeCursor(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SharedEditor::highlight(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
