/****************************************************************************
** Meta object code from reading C++ file 'SharedEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SharedEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SharedEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SharedEditor_t {
    QByteArrayData data[93];
    char stringdata0[1083];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SharedEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SharedEditor_t qt_meta_stringdata_SharedEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SharedEditor"
QT_MOC_LITERAL(1, 13, 10), // "hideEditor"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "QString&"
QT_MOC_LITERAL(4, 34, 8), // "fileName"
QT_MOC_LITERAL(5, 43, 14), // "openTextEditor"
QT_MOC_LITERAL(6, 58, 19), // "transparentForMouse"
QT_MOC_LITERAL(7, 78, 14), // "symbolsChanged"
QT_MOC_LITERAL(8, 93, 3), // "pos"
QT_MOC_LITERAL(9, 97, 1), // "s"
QT_MOC_LITERAL(10, 99, 6), // "siteId"
QT_MOC_LITERAL(11, 106, 15), // "QTextCharFormat"
QT_MOC_LITERAL(12, 122, 6), // "format"
QT_MOC_LITERAL(13, 129, 17), // "Message::action_t"
QT_MOC_LITERAL(14, 147, 6), // "action"
QT_MOC_LITERAL(15, 154, 13), // "deleteAllText"
QT_MOC_LITERAL(16, 168, 16), // "filePathsArrived"
QT_MOC_LITERAL(17, 185, 16), // "QVector<QString>"
QT_MOC_LITERAL(18, 202, 5), // "paths"
QT_MOC_LITERAL(19, 208, 14), // "fileNameEdited"
QT_MOC_LITERAL(20, 223, 7), // "oldName"
QT_MOC_LITERAL(21, 231, 7), // "newName"
QT_MOC_LITERAL(22, 239, 12), // "fileDeletion"
QT_MOC_LITERAL(23, 252, 13), // "loginAchieved"
QT_MOC_LITERAL(24, 266, 15), // "userInfoArrived"
QT_MOC_LITERAL(25, 282, 5), // "image"
QT_MOC_LITERAL(26, 288, 8), // "nickname"
QT_MOC_LITERAL(27, 297, 4), // "name"
QT_MOC_LITERAL(28, 302, 5), // "email"
QT_MOC_LITERAL(29, 308, 22), // "remoteCursorPosChanged"
QT_MOC_LITERAL(30, 331, 12), // "removeCursor"
QT_MOC_LITERAL(31, 344, 9), // "highlight"
QT_MOC_LITERAL(32, 354, 16), // "searchUserResult"
QT_MOC_LITERAL(33, 371, 17), // "LoginInfo::type_t"
QT_MOC_LITERAL(34, 389, 4), // "type"
QT_MOC_LITERAL(35, 394, 10), // "loginError"
QT_MOC_LITERAL(36, 405, 21), // "loginErrorAlreadyConn"
QT_MOC_LITERAL(37, 427, 17), // "inviteListArrived"
QT_MOC_LITERAL(38, 445, 4), // "args"
QT_MOC_LITERAL(39, 450, 19), // "inviteResultArrived"
QT_MOC_LITERAL(40, 470, 6), // "result"
QT_MOC_LITERAL(41, 477, 16), // "uriResultArrived"
QT_MOC_LITERAL(42, 494, 13), // "fsNameArrived"
QT_MOC_LITERAL(43, 508, 6), // "fsName"
QT_MOC_LITERAL(44, 515, 11), // "setNumUsers"
QT_MOC_LITERAL(45, 527, 1), // "n"
QT_MOC_LITERAL(46, 529, 12), // "hideNumUsers"
QT_MOC_LITERAL(47, 542, 12), // "returnToGrid"
QT_MOC_LITERAL(48, 555, 7), // "addUser"
QT_MOC_LITERAL(49, 563, 9), // "UserInfo&"
QT_MOC_LITERAL(50, 573, 4), // "user"
QT_MOC_LITERAL(51, 578, 10), // "removeUser"
QT_MOC_LITERAL(52, 589, 15), // "userNameArrived"
QT_MOC_LITERAL(53, 605, 9), // "connected"
QT_MOC_LITERAL(54, 615, 16), // "flushFileWriters"
QT_MOC_LITERAL(55, 632, 13), // "setCharFormat"
QT_MOC_LITERAL(56, 646, 11), // "getAligment"
QT_MOC_LITERAL(57, 658, 6), // "short&"
QT_MOC_LITERAL(58, 665, 1), // "a"
QT_MOC_LITERAL(59, 667, 15), // "remoteAlignment"
QT_MOC_LITERAL(60, 683, 13), // "Qt::Alignment"
QT_MOC_LITERAL(61, 697, 21), // "usernameAlreadyExists"
QT_MOC_LITERAL(62, 719, 17), // "serverUnavailable"
QT_MOC_LITERAL(63, 737, 18), // "updateUserListInfo"
QT_MOC_LITERAL(64, 756, 12), // "errorArrived"
QT_MOC_LITERAL(65, 769, 7), // "message"
QT_MOC_LITERAL(66, 777, 9), // "loginSlot"
QT_MOC_LITERAL(67, 787, 8), // "username"
QT_MOC_LITERAL(68, 796, 8), // "password"
QT_MOC_LITERAL(69, 805, 7), // "process"
QT_MOC_LITERAL(70, 813, 10), // "DataPacket"
QT_MOC_LITERAL(71, 824, 3), // "pkt"
QT_MOC_LITERAL(72, 828, 11), // "requireFile"
QT_MOC_LITERAL(73, 840, 16), // "requireFileClose"
QT_MOC_LITERAL(74, 857, 17), // "requireFileRename"
QT_MOC_LITERAL(75, 875, 6), // "before"
QT_MOC_LITERAL(76, 882, 5), // "after"
QT_MOC_LITERAL(77, 888, 17), // "requireFileDelete"
QT_MOC_LITERAL(78, 906, 14), // "requireFileAdd"
QT_MOC_LITERAL(79, 921, 12), // "deleteThread"
QT_MOC_LITERAL(80, 934, 9), // "clearText"
QT_MOC_LITERAL(81, 944, 15), // "sendUpdatedInfo"
QT_MOC_LITERAL(82, 960, 19), // "sendRegisterRequest"
QT_MOC_LITERAL(83, 980, 8), // "QPixmap&"
QT_MOC_LITERAL(84, 989, 10), // "searchUser"
QT_MOC_LITERAL(85, 1000, 12), // "searchFsName"
QT_MOC_LITERAL(86, 1013, 12), // "submitInvite"
QT_MOC_LITERAL(87, 1026, 4), // "file"
QT_MOC_LITERAL(88, 1031, 16), // "sendInviteAnswer"
QT_MOC_LITERAL(89, 1048, 4), // "mode"
QT_MOC_LITERAL(90, 1053, 8), // "filename"
QT_MOC_LITERAL(91, 1062, 9), // "submitUri"
QT_MOC_LITERAL(92, 1072, 10) // "obtainUser"

    },
    "SharedEditor\0hideEditor\0\0QString&\0"
    "fileName\0openTextEditor\0transparentForMouse\0"
    "symbolsChanged\0pos\0s\0siteId\0QTextCharFormat\0"
    "format\0Message::action_t\0action\0"
    "deleteAllText\0filePathsArrived\0"
    "QVector<QString>\0paths\0fileNameEdited\0"
    "oldName\0newName\0fileDeletion\0loginAchieved\0"
    "userInfoArrived\0image\0nickname\0name\0"
    "email\0remoteCursorPosChanged\0removeCursor\0"
    "highlight\0searchUserResult\0LoginInfo::type_t\0"
    "type\0loginError\0loginErrorAlreadyConn\0"
    "inviteListArrived\0args\0inviteResultArrived\0"
    "result\0uriResultArrived\0fsNameArrived\0"
    "fsName\0setNumUsers\0n\0hideNumUsers\0"
    "returnToGrid\0addUser\0UserInfo&\0user\0"
    "removeUser\0userNameArrived\0connected\0"
    "flushFileWriters\0setCharFormat\0"
    "getAligment\0short&\0a\0remoteAlignment\0"
    "Qt::Alignment\0usernameAlreadyExists\0"
    "serverUnavailable\0updateUserListInfo\0"
    "errorArrived\0message\0loginSlot\0username\0"
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
      52,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      35,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  274,    2, 0x06 /* Public */,
       5,    1,  277,    2, 0x06 /* Public */,
       6,    0,  280,    2, 0x06 /* Public */,
       7,    5,  281,    2, 0x06 /* Public */,
      15,    0,  292,    2, 0x06 /* Public */,
      16,    1,  293,    2, 0x06 /* Public */,
      19,    2,  296,    2, 0x06 /* Public */,
      22,    1,  301,    2, 0x06 /* Public */,
      23,    0,  304,    2, 0x06 /* Public */,
      24,    4,  305,    2, 0x06 /* Public */,
      29,    2,  314,    2, 0x06 /* Public */,
      30,    1,  319,    2, 0x06 /* Public */,
      31,    2,  322,    2, 0x06 /* Public */,
      32,    1,  327,    2, 0x06 /* Public */,
      35,    0,  330,    2, 0x06 /* Public */,
      36,    0,  331,    2, 0x06 /* Public */,
      37,    1,  332,    2, 0x06 /* Public */,
      39,    1,  335,    2, 0x06 /* Public */,
      41,    1,  338,    2, 0x06 /* Public */,
      42,    1,  341,    2, 0x06 /* Public */,
      44,    1,  344,    2, 0x06 /* Public */,
      46,    0,  347,    2, 0x06 /* Public */,
      47,    0,  348,    2, 0x06 /* Public */,
      48,    1,  349,    2, 0x06 /* Public */,
      51,    1,  352,    2, 0x06 /* Public */,
      52,    3,  355,    2, 0x06 /* Public */,
      52,    2,  362,    2, 0x26 /* Public | MethodCloned */,
      54,    0,  367,    2, 0x06 /* Public */,
      55,    1,  368,    2, 0x06 /* Public */,
      56,    1,  371,    2, 0x06 /* Public */,
      59,    2,  374,    2, 0x06 /* Public */,
      61,    0,  379,    2, 0x06 /* Public */,
      62,    0,  380,    2, 0x06 /* Public */,
      63,    4,  381,    2, 0x06 /* Public */,
      64,    1,  390,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      66,    2,  393,    2, 0x0a /* Public */,
      69,    1,  398,    2, 0x0a /* Public */,
      72,    1,  401,    2, 0x0a /* Public */,
      73,    0,  404,    2, 0x0a /* Public */,
      74,    2,  405,    2, 0x0a /* Public */,
      77,    1,  410,    2, 0x0a /* Public */,
      78,    1,  413,    2, 0x0a /* Public */,
      79,    0,  416,    2, 0x0a /* Public */,
      80,    0,  417,    2, 0x0a /* Public */,
      81,    3,  418,    2, 0x0a /* Public */,
      82,    5,  425,    2, 0x0a /* Public */,
      84,    1,  436,    2, 0x0a /* Public */,
      85,    1,  439,    2, 0x0a /* Public */,
      86,    2,  442,    2, 0x0a /* Public */,
      88,    3,  447,    2, 0x0a /* Public */,
      91,    1,  454,    2, 0x0a /* Public */,
      92,    1,  457,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 11, 0x80000000 | 13,    8,    9,   10,   12,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   20,   21,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   25,   26,   27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,   10,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   38,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, 0x80000000 | 17,   38,
    QMetaType::Void, QMetaType::QString,   43,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 49,   50,
    QMetaType::Void, 0x80000000 | 49,   50,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, QMetaType::Bool,   10,   50,   53,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,   10,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 57,   58,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 60,    8,   58,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString, QMetaType::QString,   25,   26,   27,   28,
    QMetaType::Void, QMetaType::QString,   65,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   67,   68,
    QMetaType::Void, 0x80000000 | 70,   71,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   75,   76,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::QString, QMetaType::QString,   25,   27,   28,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 83,   50,   68,   27,   28,   25,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   87,   50,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   89,   50,   90,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void SharedEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SharedEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideEditor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->openTextEditor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->transparentForMouse(); break;
        case 3: _t->symbolsChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< const QTextCharFormat(*)>(_a[4])),(*reinterpret_cast< Message::action_t(*)>(_a[5]))); break;
        case 4: _t->deleteAllText(); break;
        case 5: _t->filePathsArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 6: _t->fileNameEdited((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->fileDeletion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->loginAchieved(); break;
        case 9: _t->userInfoArrived((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 10: _t->remoteCursorPosChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 11: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 12: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 13: _t->searchUserResult((*reinterpret_cast< LoginInfo::type_t(*)>(_a[1]))); break;
        case 14: _t->loginError(); break;
        case 15: _t->loginErrorAlreadyConn(); break;
        case 16: _t->inviteListArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 17: _t->inviteResultArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->uriResultArrived((*reinterpret_cast< const QVector<QString>(*)>(_a[1]))); break;
        case 19: _t->fsNameArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->setNumUsers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->hideNumUsers(); break;
        case 22: _t->returnToGrid(); break;
        case 23: _t->addUser((*reinterpret_cast< UserInfo(*)>(_a[1]))); break;
        case 24: _t->removeUser((*reinterpret_cast< UserInfo(*)>(_a[1]))); break;
        case 25: _t->userNameArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 26: _t->userNameArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 27: _t->flushFileWriters(); break;
        case 28: _t->setCharFormat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->getAligment((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 30: _t->remoteAlignment((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::Alignment(*)>(_a[2]))); break;
        case 31: _t->usernameAlreadyExists(); break;
        case 32: _t->serverUnavailable(); break;
        case 33: _t->updateUserListInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 34: _t->errorArrived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: _t->loginSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 36: _t->process((*reinterpret_cast< DataPacket(*)>(_a[1]))); break;
        case 37: _t->requireFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->requireFileClose(); break;
        case 39: _t->requireFileRename((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 40: _t->requireFileDelete((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->requireFileAdd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->deleteThread(); break;
        case 43: _t->clearText(); break;
        case 44: _t->sendUpdatedInfo((*reinterpret_cast< const QPixmap(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 45: _t->sendRegisterRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QPixmap(*)>(_a[5]))); break;
        case 46: _t->searchUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 47: _t->searchFsName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 48: _t->submitInvite((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 49: _t->sendInviteAnswer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 50: _t->submitUri((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 51: _t->obtainUser((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        case 36:
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::hideEditor)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::openTextEditor)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::transparentForMouse)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , const QString & , qint32 , const QTextCharFormat & , Message::action_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::symbolsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::deleteAllText)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::filePathsArrived)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileNameEdited)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fileDeletion)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginAchieved)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userInfoArrived)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteCursorPosChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeCursor)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::highlight)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(LoginInfo::type_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::searchUserResult)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginError)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::loginErrorAlreadyConn)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteListArrived)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::inviteResultArrived)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QVector<QString> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::uriResultArrived)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::fsNameArrived)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::setNumUsers)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::hideNumUsers)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::returnToGrid)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(UserInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::addUser)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(UserInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::removeUser)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(qint32 , QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::userNameArrived)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::flushFileWriters)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::setCharFormat)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(short & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::getAligment)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(int , Qt::Alignment );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::remoteAlignment)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::usernameAlreadyExists)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::serverUnavailable)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QPixmap & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::updateUserListInfo)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (SharedEditor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharedEditor::errorArrived)) {
                *result = 34;
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
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    }
    return _id;
}

// SIGNAL 0
void SharedEditor::hideEditor(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SharedEditor::openTextEditor(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SharedEditor::transparentForMouse()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SharedEditor::symbolsChanged(qint32 _t1, const QString & _t2, qint32 _t3, const QTextCharFormat & _t4, Message::action_t _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SharedEditor::deleteAllText()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SharedEditor::filePathsArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SharedEditor::fileNameEdited(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SharedEditor::fileDeletion(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SharedEditor::loginAchieved()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void SharedEditor::userInfoArrived(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SharedEditor::remoteCursorPosChanged(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SharedEditor::removeCursor(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SharedEditor::highlight(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SharedEditor::searchUserResult(LoginInfo::type_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void SharedEditor::loginError()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void SharedEditor::loginErrorAlreadyConn()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void SharedEditor::inviteListArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void SharedEditor::inviteResultArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void SharedEditor::uriResultArrived(const QVector<QString> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void SharedEditor::fsNameArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void SharedEditor::setNumUsers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void SharedEditor::hideNumUsers()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void SharedEditor::returnToGrid()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void SharedEditor::addUser(UserInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void SharedEditor::removeUser(UserInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void SharedEditor::userNameArrived(qint32 _t1, QString & _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 27
void SharedEditor::flushFileWriters()
{
    QMetaObject::activate(this, &staticMetaObject, 27, nullptr);
}

// SIGNAL 28
void SharedEditor::setCharFormat(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void SharedEditor::getAligment(short & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void SharedEditor::remoteAlignment(int _t1, Qt::Alignment _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void SharedEditor::usernameAlreadyExists()
{
    QMetaObject::activate(this, &staticMetaObject, 31, nullptr);
}

// SIGNAL 32
void SharedEditor::serverUnavailable()
{
    QMetaObject::activate(this, &staticMetaObject, 32, nullptr);
}

// SIGNAL 33
void SharedEditor::updateUserListInfo(const QPixmap & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void SharedEditor::errorArrived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
