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
    QByteArrayData data[67];
    char stringdata0[734];
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
QT_MOC_LITERAL(16, 161, 12), // "fileDeletion"
QT_MOC_LITERAL(17, 174, 8), // "fileName"
QT_MOC_LITERAL(18, 183, 13), // "loginAchieved"
QT_MOC_LITERAL(19, 197, 15), // "userInfoArrived"
QT_MOC_LITERAL(20, 213, 5), // "image"
QT_MOC_LITERAL(21, 219, 8), // "nickname"
QT_MOC_LITERAL(22, 228, 4), // "name"
QT_MOC_LITERAL(23, 233, 5), // "email"
QT_MOC_LITERAL(24, 239, 22), // "remoteCursorPosChanged"
QT_MOC_LITERAL(25, 262, 12), // "removeCursor"
QT_MOC_LITERAL(26, 275, 9), // "highlight"
QT_MOC_LITERAL(27, 285, 16), // "searchUserResult"
QT_MOC_LITERAL(28, 302, 17), // "LoginInfo::type_t"
QT_MOC_LITERAL(29, 320, 4), // "type"
QT_MOC_LITERAL(30, 325, 10), // "loginError"
QT_MOC_LITERAL(31, 336, 17), // "inviteListArrived"
QT_MOC_LITERAL(32, 354, 4), // "args"
QT_MOC_LITERAL(33, 359, 19), // "inviteResultArrived"
QT_MOC_LITERAL(34, 379, 6), // "result"
QT_MOC_LITERAL(35, 386, 16), // "uriResultArrived"
QT_MOC_LITERAL(36, 403, 13), // "fsNameArrived"
QT_MOC_LITERAL(37, 417, 6), // "fsName"
QT_MOC_LITERAL(38, 424, 11), // "setNumUsers"
QT_MOC_LITERAL(39, 436, 1), // "n"
QT_MOC_LITERAL(40, 438, 12), // "hideNumUsers"
QT_MOC_LITERAL(41, 451, 9), // "loginSlot"
QT_MOC_LITERAL(42, 461, 8), // "username"
QT_MOC_LITERAL(43, 470, 8), // "password"
QT_MOC_LITERAL(44, 479, 7), // "process"
QT_MOC_LITERAL(45, 487, 10), // "DataPacket"
QT_MOC_LITERAL(46, 498, 3), // "pkt"
QT_MOC_LITERAL(47, 502, 11), // "requireFile"
QT_MOC_LITERAL(48, 514, 17), // "requireFileRename"
QT_MOC_LITERAL(49, 532, 6), // "before"
QT_MOC_LITERAL(50, 539, 5), // "after"
QT_MOC_LITERAL(51, 545, 17), // "requireFileDelete"
QT_MOC_LITERAL(52, 563, 14), // "requireFileAdd"
QT_MOC_LITERAL(53, 578, 12), // "deleteThread"
QT_MOC_LITERAL(54, 591, 9), // "clearText"
QT_MOC_LITERAL(55, 601, 15), // "sendUpdatedInfo"
QT_MOC_LITERAL(56, 617, 19), // "sendRegisterRequest"
QT_MOC_LITERAL(57, 637, 4), // "user"
QT_MOC_LITERAL(58, 642, 8), // "QPixmap&"
QT_MOC_LITERAL(59, 651, 10), // "searchUser"
QT_MOC_LITERAL(60, 662, 12), // "searchFsName"
QT_MOC_LITERAL(61, 675, 12), // "submitInvite"
QT_MOC_LITERAL(62, 688, 4), // "file"
QT_MOC_LITERAL(63, 693, 16), // "sendInviteAnswer"
QT_MOC_LITERAL(64, 710, 4), // "mode"
QT_MOC_LITERAL(65, 715, 8), // "filename"
QT_MOC_LITERAL(66, 724, 9) // "submitUri"

    },
    "SharedEditor\0symbolsChanged\0\0pos\0s\0"
    "siteId\0Message::action_t\0action\0"
    "deleteAllText\0filePathsArrived\0"
    "QVector<QString>\0paths\0fileNameEdited\0"
    "QString&\0oldName\0newName\0fileDeletion\0"
    "fileName\0loginAchieved\0userInfoArrived\0"
    "image\0nickname\0name\0email\0"
    "remoteCursorPosChanged\0removeCursor\0"
    "highlight\0searchUserResult\0LoginInfo::type_t\0"
    "type\0loginError\0inviteListArrived\0"
    "args\0inviteResultArrived\0result\0"
    "uriResultArrived\0fsNameArrived\0fsName\0"
    "setNumUsers\0n\0hideNumUsers\0loginSlot\0"
    "username\0password\0process\0DataPacket\0"
    "pkt\0requireFile\0requireFileRename\0"
    "before\0after\0requireFileDelete\0"
    "requireFileAdd\0deleteThread\0clearText\0"
    "sendUpdatedInfo\0sendRegisterRequest\0"
    "user\0QPixmap&\0searchUser\0searchFsName\0"
    "submitInvite\0file\0sendInviteAnswer\0"
    "mode\0filename\0submitUri"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SharedEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  179,    2, 0x06 /* Public */,
       8,    0,  188,    2, 0x06 /* Public */,
       9,    1,  189,    2, 0x06 /* Public */,
      12,    2,  192,    2, 0x06 /* Public */,
      16,    1,  197,    2, 0x06 /* Public */,
      18,    0,  200,    2, 0x06 /* Public */,
      19,    4,  201,    2, 0x06 /* Public */,
      24,    2,  210,    2, 0x06 /* Public */,
      25,    1,  215,    2, 0x06 /* Public */,
      26,    2,  218,    2, 0x06 /* Public */,
      27,    1,  223,    2, 0x06 /* Public */,
      30,    0,  226,    2, 0x06 /* Public */,
      31,    1,  227,    2, 0x06 /* Public */,
      33,    1,  230,    2, 0x06 /* Public */,
      35,    1,  233,    2, 0x06 /* Public */,
      36,    1,  236,    2, 0x06 /* Public */,
      38,    1,  239,    2, 0x06 /* Public */,
      40,    0,  242,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      41,    2,  243,    2, 0x0a /* Public */,
      44,    1,  248,    2, 0x0a /* Public */,
      47,    1,  251,    2, 0x0a /* Public */,
      48,    2,  254,    2, 0x0a /* Public */,
      51,    1,  259,    2, 0x0a /* Public */,
      52,    1,  262,    2, 0x0a /* Public */,
      53,    0,  265,    2, 0x0a /* Public */,
      54,    0,  266,    2, 0x0a /* Public */,
      55,    3,  267,    2, 0x0a /* Public */,
      56,    5,  274,    2, 0x0a /* Public */,
      59,    1,  285,    2, 0x0a /* Public */,
      60,    1,  288,    2, 0x0a /* Public */,
      61,    2,  291,    2, 0x0a /* Public */,
      63,    3,  296,    2, 0x0a /* Public */,
      66,    1,  303,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 6,    3,    4,    5,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   14,   15,
    QMetaType::Void, 0x80000000 | 13,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   20,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   32,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, 0x80000000 | 10,   32,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   42,   43,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   49,   50,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString,   20,   22,   23,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13, 0x80000000 | 13, 0x80000000 | 13, 0x80000000 | 58,   57,   43,   22,   23,   20,
    QMetaType::Void, QMetaType::QString,   57,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   62,   57,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   64,   57,   65,
    QMetaType::Void, QMetaType::QString,   62,

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
        case 4: _t->fileDeletion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->loginAchieved(); break;
        case 6: _t->userInfoArrived((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 7: _t->remoteCursorPosChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 8: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 10: _t->searchUserResult((*reinterpret_cast< LoginInfo::type_t(*)>(_a[1]))); break;
        case 11: _t->loginError(); break;
        case 12: _t->inviteListArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 13: _t->inviteResultArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->uriResultArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 15: _t->fsNameArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->setNumUsers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->hideNumUsers(); break;
        case 18: _t->loginSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->process((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 20: _t->requireFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->requireFileRename((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: _t->requireFileDelete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->requireFileAdd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->deleteThread(); break;
        case 25: _t->clearText(); break;
        case 26: _t->sendUpdatedInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 27: _t->sendRegisterRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QPixmap(*)>(_a[5]))); break;
        case 28: _t->searchUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->searchFsName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: _t->submitInvite((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 31: _t->sendInviteAnswer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 32: _t->submitUri((*reinterpret_cast< const QString(*)>(_a[1]))); break;
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 19:
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
            using _t = void (SharedEditor::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileDeletion)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginAchieved)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userInfoArrived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteCursorPosChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeCursor)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::highlight)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(LoginInfo::type_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::searchUserResult)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginError)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteListArrived)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteResultArrived)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::uriResultArrived)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fsNameArrived)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::setNumUsers)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::hideNumUsers)) {
                *result = 17;
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
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
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
void SharedEditor::fileDeletion(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SharedEditor::loginAchieved()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SharedEditor::userInfoArrived(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SharedEditor::remoteCursorPosChanged(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SharedEditor::removeCursor(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SharedEditor::highlight(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SharedEditor::searchUserResult(LoginInfo::type_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SharedEditor::loginError()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void SharedEditor::inviteListArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SharedEditor::inviteResultArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void SharedEditor::uriResultArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void SharedEditor::fsNameArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void SharedEditor::setNumUsers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void SharedEditor::hideNumUsers()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
