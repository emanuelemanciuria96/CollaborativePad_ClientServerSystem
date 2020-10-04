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
    QByteArrayData data[79];
    char stringdata0[896];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SharedEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SharedEditor_t qt_meta_stringdata_SharedEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SharedEditor"
QT_MOC_LITERAL(1, 13, 14), // "openTextEditor"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "QString&"
QT_MOC_LITERAL(4, 38, 8), // "fileName"
QT_MOC_LITERAL(5, 47, 19), // "transparentForMouse"
QT_MOC_LITERAL(6, 67, 14), // "symbolsChanged"
QT_MOC_LITERAL(7, 82, 3), // "pos"
QT_MOC_LITERAL(8, 86, 1), // "s"
QT_MOC_LITERAL(9, 88, 6), // "siteId"
QT_MOC_LITERAL(10, 95, 17), // "Message::action_t"
QT_MOC_LITERAL(11, 113, 6), // "action"
QT_MOC_LITERAL(12, 120, 13), // "deleteAllText"
QT_MOC_LITERAL(13, 134, 16), // "filePathsArrived"
QT_MOC_LITERAL(14, 151, 16), // "QVector<QString>"
QT_MOC_LITERAL(15, 168, 5), // "paths"
QT_MOC_LITERAL(16, 174, 14), // "fileNameEdited"
QT_MOC_LITERAL(17, 189, 7), // "oldName"
QT_MOC_LITERAL(18, 197, 7), // "newName"
QT_MOC_LITERAL(19, 205, 12), // "fileDeletion"
QT_MOC_LITERAL(20, 218, 13), // "loginAchieved"
QT_MOC_LITERAL(21, 232, 15), // "userInfoArrived"
QT_MOC_LITERAL(22, 248, 5), // "image"
QT_MOC_LITERAL(23, 254, 8), // "nickname"
QT_MOC_LITERAL(24, 263, 4), // "name"
QT_MOC_LITERAL(25, 268, 5), // "email"
QT_MOC_LITERAL(26, 274, 22), // "remoteCursorPosChanged"
QT_MOC_LITERAL(27, 297, 12), // "removeCursor"
QT_MOC_LITERAL(28, 310, 9), // "highlight"
QT_MOC_LITERAL(29, 320, 16), // "searchUserResult"
QT_MOC_LITERAL(30, 337, 17), // "LoginInfo::type_t"
QT_MOC_LITERAL(31, 355, 4), // "type"
QT_MOC_LITERAL(32, 360, 10), // "loginError"
QT_MOC_LITERAL(33, 371, 17), // "inviteListArrived"
QT_MOC_LITERAL(34, 389, 4), // "args"
QT_MOC_LITERAL(35, 394, 19), // "inviteResultArrived"
QT_MOC_LITERAL(36, 414, 6), // "result"
QT_MOC_LITERAL(37, 421, 16), // "uriResultArrived"
QT_MOC_LITERAL(38, 438, 13), // "fsNameArrived"
QT_MOC_LITERAL(39, 452, 6), // "fsName"
QT_MOC_LITERAL(40, 459, 11), // "setNumUsers"
QT_MOC_LITERAL(41, 471, 1), // "n"
QT_MOC_LITERAL(42, 473, 12), // "hideNumUsers"
QT_MOC_LITERAL(43, 486, 12), // "returnToGrid"
QT_MOC_LITERAL(44, 499, 7), // "addUser"
QT_MOC_LITERAL(45, 507, 9), // "UserInfo&"
QT_MOC_LITERAL(46, 517, 4), // "user"
QT_MOC_LITERAL(47, 522, 10), // "removeUser"
QT_MOC_LITERAL(48, 533, 15), // "userNameArrived"
QT_MOC_LITERAL(49, 549, 9), // "connected"
QT_MOC_LITERAL(50, 559, 16), // "flushFileWriters"
QT_MOC_LITERAL(51, 576, 13), // "setCharFormat"
QT_MOC_LITERAL(52, 590, 9), // "loginSlot"
QT_MOC_LITERAL(53, 600, 8), // "username"
QT_MOC_LITERAL(54, 609, 8), // "password"
QT_MOC_LITERAL(55, 618, 7), // "process"
QT_MOC_LITERAL(56, 626, 10), // "DataPacket"
QT_MOC_LITERAL(57, 637, 3), // "pkt"
QT_MOC_LITERAL(58, 641, 11), // "requireFile"
QT_MOC_LITERAL(59, 653, 16), // "requireFileClose"
QT_MOC_LITERAL(60, 670, 17), // "requireFileRename"
QT_MOC_LITERAL(61, 688, 6), // "before"
QT_MOC_LITERAL(62, 695, 5), // "after"
QT_MOC_LITERAL(63, 701, 17), // "requireFileDelete"
QT_MOC_LITERAL(64, 719, 14), // "requireFileAdd"
QT_MOC_LITERAL(65, 734, 12), // "deleteThread"
QT_MOC_LITERAL(66, 747, 9), // "clearText"
QT_MOC_LITERAL(67, 757, 15), // "sendUpdatedInfo"
QT_MOC_LITERAL(68, 773, 19), // "sendRegisterRequest"
QT_MOC_LITERAL(69, 793, 8), // "QPixmap&"
QT_MOC_LITERAL(70, 802, 10), // "searchUser"
QT_MOC_LITERAL(71, 813, 12), // "searchFsName"
QT_MOC_LITERAL(72, 826, 12), // "submitInvite"
QT_MOC_LITERAL(73, 839, 4), // "file"
QT_MOC_LITERAL(74, 844, 16), // "sendInviteAnswer"
QT_MOC_LITERAL(75, 861, 4), // "mode"
QT_MOC_LITERAL(76, 866, 8), // "filename"
QT_MOC_LITERAL(77, 875, 9), // "submitUri"
QT_MOC_LITERAL(78, 885, 10) // "obtainUser"

    },
    "SharedEditor\0openTextEditor\0\0QString&\0"
    "fileName\0transparentForMouse\0"
    "symbolsChanged\0pos\0s\0siteId\0"
    "Message::action_t\0action\0deleteAllText\0"
    "filePathsArrived\0QVector<QString>\0"
    "paths\0fileNameEdited\0oldName\0newName\0"
    "fileDeletion\0loginAchieved\0userInfoArrived\0"
    "image\0nickname\0name\0email\0"
    "remoteCursorPosChanged\0removeCursor\0"
    "highlight\0searchUserResult\0LoginInfo::type_t\0"
    "type\0loginError\0inviteListArrived\0"
    "args\0inviteResultArrived\0result\0"
    "uriResultArrived\0fsNameArrived\0fsName\0"
    "setNumUsers\0n\0hideNumUsers\0returnToGrid\0"
    "addUser\0UserInfo&\0user\0removeUser\0"
    "userNameArrived\0connected\0flushFileWriters\0"
    "setCharFormat\0loginSlot\0username\0"
    "password\0process\0DataPacket\0pkt\0"
    "requireFile\0requireFileClose\0"
    "requireFileRename\0before\0after\0"
    "requireFileDelete\0requireFileAdd\0"
    "deleteThread\0clearText\0sendUpdatedInfo\0"
    "sendRegisterRequest\0QPixmap&\0searchUser\0"
    "searchFsName\0submitInvite\0file\0"
    "sendInviteAnswer\0mode\0filename\0submitUri\0"
    "obtainUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SharedEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      27,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  234,    2, 0x06 /* Public */,
       5,    0,  237,    2, 0x06 /* Public */,
       6,    4,  238,    2, 0x06 /* Public */,
      12,    0,  247,    2, 0x06 /* Public */,
      13,    1,  248,    2, 0x06 /* Public */,
      16,    2,  251,    2, 0x06 /* Public */,
      19,    1,  256,    2, 0x06 /* Public */,
      20,    0,  259,    2, 0x06 /* Public */,
      21,    4,  260,    2, 0x06 /* Public */,
      26,    2,  269,    2, 0x06 /* Public */,
      27,    1,  274,    2, 0x06 /* Public */,
      28,    2,  277,    2, 0x06 /* Public */,
      29,    1,  282,    2, 0x06 /* Public */,
      32,    0,  285,    2, 0x06 /* Public */,
      33,    1,  286,    2, 0x06 /* Public */,
      35,    1,  289,    2, 0x06 /* Public */,
      37,    1,  292,    2, 0x06 /* Public */,
      38,    1,  295,    2, 0x06 /* Public */,
      40,    1,  298,    2, 0x06 /* Public */,
      42,    0,  301,    2, 0x06 /* Public */,
      43,    0,  302,    2, 0x06 /* Public */,
      44,    1,  303,    2, 0x06 /* Public */,
      47,    1,  306,    2, 0x06 /* Public */,
      48,    3,  309,    2, 0x06 /* Public */,
      48,    2,  316,    2, 0x26 /* Public | MethodCloned */,
      50,    0,  321,    2, 0x06 /* Public */,
      51,    1,  322,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      52,    2,  325,    2, 0x0a /* Public */,
      55,    1,  330,    2, 0x0a /* Public */,
      58,    1,  333,    2, 0x0a /* Public */,
      59,    0,  336,    2, 0x0a /* Public */,
      60,    2,  337,    2, 0x0a /* Public */,
      63,    1,  342,    2, 0x0a /* Public */,
      64,    1,  345,    2, 0x0a /* Public */,
      65,    0,  348,    2, 0x0a /* Public */,
      66,    0,  349,    2, 0x0a /* Public */,
      67,    3,  350,    2, 0x0a /* Public */,
      68,    5,  357,    2, 0x0a /* Public */,
      70,    1,  368,    2, 0x0a /* Public */,
      71,    1,  371,    2, 0x0a /* Public */,
      72,    2,  374,    2, 0x0a /* Public */,
      74,    3,  379,    2, 0x0a /* Public */,
      77,    1,  386,    2, 0x0a /* Public */,
      78,    1,  389,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 10,    7,    8,    9,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   17,   18,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   23,   24,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    9,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   34,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, 0x80000000 | 14,   34,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, QMetaType::Int,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, QMetaType::Bool,    9,   46,   49,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    9,   46,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   53,   54,
    QMetaType::Void, 0x80000000 | 56,   57,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   61,   62,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString,   22,   24,   25,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 69,   46,   54,   24,   25,   22,
    QMetaType::Void, QMetaType::QString,   46,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   73,   46,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   75,   46,   76,
    QMetaType::Void, QMetaType::QString,   73,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void SharedEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SharedEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openTextEditor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->transparentForMouse(); break;
        case 2: _t->symbolsChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        case 3: _t->deleteAllText(); break;
        case 4: _t->filePathsArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 5: _t->fileNameEdited((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->fileDeletion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->loginAchieved(); break;
        case 8: _t->userInfoArrived((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 9: _t->remoteCursorPosChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 10: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 11: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 12: _t->searchUserResult((*reinterpret_cast< LoginInfo::type_t(*)>(_a[1]))); break;
        case 13: _t->loginError(); break;
        case 14: _t->inviteListArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 15: _t->inviteResultArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->uriResultArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 17: _t->fsNameArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->setNumUsers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->hideNumUsers(); break;
        case 20: _t->returnToGrid(); break;
        case 21: _t->addUser((*reinterpret_cast< UserInfo(*)>(_a[1]))); break;
        case 22: _t->removeUser((*reinterpret_cast< UserInfo(*)>(_a[1]))); break;
        case 23: _t->userNameArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 24: _t->userNameArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 25: _t->flushFileWriters(); break;
        case 26: _t->setCharFormat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->loginSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 28: _t->process((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 29: _t->requireFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->requireFileClose(); break;
        case 31: _t->requireFileRename((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 32: _t->requireFileDelete((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->requireFileAdd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->deleteThread(); break;
        case 35: _t->clearText(); break;
        case 36: _t->sendUpdatedInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 37: _t->sendRegisterRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QPixmap(*)>(_a[5]))); break;
        case 38: _t->searchUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 39: _t->searchFsName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 40: _t->submitInvite((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 41: _t->sendInviteAnswer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 42: _t->submitUri((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: _t->obtainUser((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 28:
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
            using _t = void (SharedEditor::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::openTextEditor)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::transparentForMouse)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , const QString & , qint32 , Message::action_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::symbolsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::deleteAllText)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::filePathsArrived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileNameEdited)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileDeletion)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginAchieved)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userInfoArrived)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteCursorPosChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeCursor)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::highlight)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(LoginInfo::type_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::searchUserResult)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginError)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteListArrived)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteResultArrived)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::uriResultArrived)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fsNameArrived)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::setNumUsers)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::hideNumUsers)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::returnToGrid)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(UserInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::addUser)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(UserInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeUser)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userNameArrived)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::flushFileWriters)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::setCharFormat)) {
                *result = 26;
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
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void SharedEditor::openTextEditor(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SharedEditor::transparentForMouse()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SharedEditor::symbolsChanged(qint32 _t1, const QString & _t2, qint32 _t3, Message::action_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SharedEditor::deleteAllText()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SharedEditor::filePathsArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SharedEditor::fileNameEdited(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SharedEditor::fileDeletion(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SharedEditor::loginAchieved()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void SharedEditor::userInfoArrived(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SharedEditor::remoteCursorPosChanged(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SharedEditor::removeCursor(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SharedEditor::highlight(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SharedEditor::searchUserResult(LoginInfo::type_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SharedEditor::loginError()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void SharedEditor::inviteListArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void SharedEditor::inviteResultArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void SharedEditor::uriResultArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void SharedEditor::fsNameArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void SharedEditor::setNumUsers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void SharedEditor::hideNumUsers()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void SharedEditor::returnToGrid()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void SharedEditor::addUser(UserInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void SharedEditor::removeUser(UserInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void SharedEditor::userNameArrived(qint32 _t1, QString & _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 25
void SharedEditor::flushFileWriters()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void SharedEditor::setCharFormat(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
