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
    QByteArrayData data[48];
    char stringdata0[502];
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
QT_MOC_LITERAL(12, 121, 14), // "fileNameEdited"
QT_MOC_LITERAL(13, 136, 8), // "QString&"
QT_MOC_LITERAL(14, 145, 7), // "oldName"
QT_MOC_LITERAL(15, 153, 7), // "newName"
QT_MOC_LITERAL(16, 161, 13), // "loginAchieved"
QT_MOC_LITERAL(17, 175, 15), // "userInfoArrived"
QT_MOC_LITERAL(18, 191, 5), // "image"
QT_MOC_LITERAL(19, 197, 8), // "nickname"
QT_MOC_LITERAL(20, 206, 4), // "name"
QT_MOC_LITERAL(21, 211, 5), // "email"
QT_MOC_LITERAL(22, 217, 22), // "remoteCursorPosChanged"
QT_MOC_LITERAL(23, 240, 12), // "removeCursor"
QT_MOC_LITERAL(24, 253, 9), // "highlight"
QT_MOC_LITERAL(25, 263, 16), // "searchUserResult"
QT_MOC_LITERAL(26, 280, 17), // "LoginInfo::type_t"
QT_MOC_LITERAL(27, 298, 4), // "type"
QT_MOC_LITERAL(28, 303, 10), // "loginError"
QT_MOC_LITERAL(29, 314, 9), // "loginSlot"
QT_MOC_LITERAL(30, 324, 8), // "username"
QT_MOC_LITERAL(31, 333, 8), // "password"
QT_MOC_LITERAL(32, 342, 7), // "process"
QT_MOC_LITERAL(33, 350, 10), // "DataPacket"
QT_MOC_LITERAL(34, 361, 3), // "pkt"
QT_MOC_LITERAL(35, 365, 17), // "requireFileSystem"
QT_MOC_LITERAL(36, 383, 11), // "requireFile"
QT_MOC_LITERAL(37, 395, 8), // "fileName"
QT_MOC_LITERAL(38, 404, 17), // "requireFileRename"
QT_MOC_LITERAL(39, 422, 6), // "before"
QT_MOC_LITERAL(40, 429, 5), // "after"
QT_MOC_LITERAL(41, 435, 12), // "deleteThread"
QT_MOC_LITERAL(42, 448, 9), // "clearText"
QT_MOC_LITERAL(43, 458, 15), // "sendUpdatedInfo"
QT_MOC_LITERAL(44, 474, 10), // "searchUser"
QT_MOC_LITERAL(45, 485, 4), // "user"
QT_MOC_LITERAL(46, 490, 6), // "submit"
QT_MOC_LITERAL(47, 497, 4) // "file"

    },
    "SharedEditor\0symbolsChanged\0\0pos\0s\0"
    "siteId\0Message::action_t\0action\0"
    "deleteAllText\0filePathsArrived\0"
    "QVector<QString>\0paths\0fileNameEdited\0"
    "QString&\0oldName\0newName\0loginAchieved\0"
    "userInfoArrived\0image\0nickname\0name\0"
    "email\0remoteCursorPosChanged\0removeCursor\0"
    "highlight\0searchUserResult\0LoginInfo::type_t\0"
    "type\0loginError\0loginSlot\0username\0"
    "password\0process\0DataPacket\0pkt\0"
    "requireFileSystem\0requireFile\0fileName\0"
    "requireFileRename\0before\0after\0"
    "deleteThread\0clearText\0sendUpdatedInfo\0"
    "searchUser\0user\0submit\0file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SharedEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  119,    2, 0x06 /* Public */,
       8,    0,  128,    2, 0x06 /* Public */,
       9,    1,  129,    2, 0x06 /* Public */,
      12,    2,  132,    2, 0x06 /* Public */,
      16,    0,  137,    2, 0x06 /* Public */,
      17,    4,  138,    2, 0x06 /* Public */,
      22,    2,  147,    2, 0x06 /* Public */,
      23,    1,  152,    2, 0x06 /* Public */,
      24,    2,  155,    2, 0x06 /* Public */,
      25,    1,  160,    2, 0x06 /* Public */,
      28,    0,  163,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      29,    2,  164,    2, 0x0a /* Public */,
      32,    1,  169,    2, 0x0a /* Public */,
      35,    0,  172,    2, 0x0a /* Public */,
      36,    1,  173,    2, 0x0a /* Public */,
      38,    2,  176,    2, 0x0a /* Public */,
      41,    0,  181,    2, 0x0a /* Public */,
      42,    0,  182,    2, 0x0a /* Public */,
      43,    3,  183,    2, 0x0a /* Public */,
      44,    1,  190,    2, 0x0a /* Public */,
      46,    2,  193,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 6,    3,    4,    5,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   18,   19,   20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   30,   31,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   39,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString,   18,   20,   21,
    QMetaType::Void, QMetaType::QString,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   47,   45,

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
        case 3: _t->fileNameEdited((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->loginAchieved(); break;
        case 5: _t->userInfoArrived((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->remoteCursorPosChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 7: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 9: _t->searchUserResult((*reinterpret_cast< LoginInfo::type_t(*)>(_a[1]))); break;
        case 10: _t->loginError(); break;
        case 11: _t->loginSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->process((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 13: _t->requireFileSystem(); break;
        case 14: _t->requireFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->requireFileRename((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->deleteThread(); break;
        case 17: _t->clearText(); break;
        case 18: _t->sendUpdatedInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 19: _t->searchUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->submit((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
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
        case 12:
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
            using _t = void (SharedEditor::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileNameEdited)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginAchieved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userInfoArrived)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteCursorPosChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeCursor)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::highlight)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(LoginInfo::type_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::searchUserResult)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginError)) {
                *result = 10;
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
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
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
void SharedEditor::fileNameEdited(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SharedEditor::loginAchieved()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SharedEditor::userInfoArrived(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SharedEditor::remoteCursorPosChanged(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SharedEditor::removeCursor(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SharedEditor::highlight(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SharedEditor::searchUserResult(LoginInfo::type_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SharedEditor::loginError()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
