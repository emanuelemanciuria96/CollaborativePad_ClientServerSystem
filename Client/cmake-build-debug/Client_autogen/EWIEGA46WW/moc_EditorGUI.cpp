/****************************************************************************
** Meta object code from reading C++ file 'EditorGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../EditorGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditorGUI_t {
    QByteArrayData data[33];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorGUI_t qt_meta_stringdata_EditorGUI = {
    {
QT_MOC_LITERAL(0, 0, 9), // "EditorGUI"
QT_MOC_LITERAL(1, 10, 5), // "clear"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "setNumUsers"
QT_MOC_LITERAL(4, 29, 1), // "n"
QT_MOC_LITERAL(5, 31, 9), // "userQuery"
QT_MOC_LITERAL(6, 41, 6), // "siteId"
QT_MOC_LITERAL(7, 48, 14), // "contentsChange"
QT_MOC_LITERAL(8, 63, 3), // "pos"
QT_MOC_LITERAL(9, 67, 12), // "charsRemoved"
QT_MOC_LITERAL(10, 80, 10), // "charsAdded"
QT_MOC_LITERAL(11, 91, 16), // "flushInsertQueue"
QT_MOC_LITERAL(12, 108, 11), // "setSelected"
QT_MOC_LITERAL(13, 120, 3), // "yes"
QT_MOC_LITERAL(14, 124, 22), // "handleCursorPosChanged"
QT_MOC_LITERAL(15, 147, 19), // "enableSendCursorPos"
QT_MOC_LITERAL(16, 167, 13), // "updateSymbols"
QT_MOC_LITERAL(17, 181, 1), // "s"
QT_MOC_LITERAL(18, 183, 17), // "Message::action_t"
QT_MOC_LITERAL(19, 201, 6), // "action"
QT_MOC_LITERAL(20, 208, 13), // "deleteAllText"
QT_MOC_LITERAL(21, 222, 21), // "updateRemoteCursorPos"
QT_MOC_LITERAL(22, 244, 12), // "removeCursor"
QT_MOC_LITERAL(23, 257, 9), // "highlight"
QT_MOC_LITERAL(24, 267, 11), // "exportToPdf"
QT_MOC_LITERAL(25, 279, 18), // "setCurrentFileName"
QT_MOC_LITERAL(26, 298, 8), // "filename"
QT_MOC_LITERAL(27, 307, 14), // "highlightedTip"
QT_MOC_LITERAL(28, 322, 16), // "recordUserWriter"
QT_MOC_LITERAL(29, 339, 8), // "QString&"
QT_MOC_LITERAL(30, 348, 4), // "user"
QT_MOC_LITERAL(31, 353, 10), // "connection"
QT_MOC_LITERAL(32, 364, 16) // "flushFileWriters"

    },
    "EditorGUI\0clear\0\0setNumUsers\0n\0userQuery\0"
    "siteId\0contentsChange\0pos\0charsRemoved\0"
    "charsAdded\0flushInsertQueue\0setSelected\0"
    "yes\0handleCursorPosChanged\0"
    "enableSendCursorPos\0updateSymbols\0s\0"
    "Message::action_t\0action\0deleteAllText\0"
    "updateRemoteCursorPos\0removeCursor\0"
    "highlight\0exportToPdf\0setCurrentFileName\0"
    "filename\0highlightedTip\0recordUserWriter\0"
    "QString&\0user\0connection\0flushFileWriters"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    1,  110,    2, 0x06 /* Public */,
       5,    1,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    3,  116,    2, 0x08 /* Private */,
      11,    0,  123,    2, 0x08 /* Private */,
      12,    1,  124,    2, 0x08 /* Private */,
      14,    0,  127,    2, 0x08 /* Private */,
      15,    0,  128,    2, 0x08 /* Private */,
      16,    4,  129,    2, 0x0a /* Public */,
      20,    0,  138,    2, 0x0a /* Public */,
      21,    2,  139,    2, 0x0a /* Public */,
      22,    1,  144,    2, 0x0a /* Public */,
      23,    2,  147,    2, 0x0a /* Public */,
      24,    0,  152,    2, 0x0a /* Public */,
      25,    1,  153,    2, 0x0a /* Public */,
      27,    1,  156,    2, 0x0a /* Public */,
      28,    3,  159,    2, 0x0a /* Public */,
      28,    2,  166,    2, 0x2a /* Public | MethodCloned */,
      32,    0,  171,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 18,    8,   17,    6,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 29, QMetaType::Bool,    6,   30,   31,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 29,    6,   30,
    QMetaType::Void,

       0        // eod
};

void EditorGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditorGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->setNumUsers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->userQuery((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->contentsChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->flushInsertQueue(); break;
        case 5: _t->setSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->handleCursorPosChanged(); break;
        case 7: _t->enableSendCursorPos(); break;
        case 8: _t->updateSymbols((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        case 9: _t->deleteAllText(); break;
        case 10: _t->updateRemoteCursorPos((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 11: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 12: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 13: _t->exportToPdf(); break;
        case 14: _t->setCurrentFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->highlightedTip((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->recordUserWriter((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 17: _t->recordUserWriter((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->flushFileWriters(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EditorGUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditorGUI::clear)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EditorGUI::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditorGUI::setNumUsers)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EditorGUI::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditorGUI::userQuery)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EditorGUI::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_EditorGUI.data,
    qt_meta_data_EditorGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EditorGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditorGUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EditorGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void EditorGUI::clear()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EditorGUI::setNumUsers(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EditorGUI::userQuery(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
