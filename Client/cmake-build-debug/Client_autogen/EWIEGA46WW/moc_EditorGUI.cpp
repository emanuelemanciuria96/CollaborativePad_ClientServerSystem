/****************************************************************************
** Meta object code from reading C++ file 'EditorGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../EditorGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditorGUI_t {
    QByteArrayData data[14];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorGUI_t qt_meta_stringdata_EditorGUI = {
    {
QT_MOC_LITERAL(0, 0, 9), // "EditorGUI"
QT_MOC_LITERAL(1, 10, 14), // "contentsChange"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "pos"
QT_MOC_LITERAL(4, 30, 12), // "charsRemoved"
QT_MOC_LITERAL(5, 43, 10), // "charsAdded"
QT_MOC_LITERAL(6, 54, 16), // "flushInsertQueue"
QT_MOC_LITERAL(7, 71, 11), // "setSelected"
QT_MOC_LITERAL(8, 83, 3), // "yes"
QT_MOC_LITERAL(9, 87, 13), // "updateSymbols"
QT_MOC_LITERAL(10, 101, 1), // "s"
QT_MOC_LITERAL(11, 103, 6), // "siteId"
QT_MOC_LITERAL(12, 110, 17), // "Message::action_t"
QT_MOC_LITERAL(13, 128, 6) // "action"

    },
    "EditorGUI\0contentsChange\0\0pos\0"
    "charsRemoved\0charsAdded\0flushInsertQueue\0"
    "setSelected\0yes\0updateSymbols\0s\0siteId\0"
    "Message::action_t\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,
       7,    1,   42,    2, 0x08 /* Private */,
       9,    4,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 12,    3,   10,   11,   13,

       0        // eod
};

void EditorGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorGUI *_t = static_cast<EditorGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->contentsChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->flushInsertQueue(); break;
        case 2: _t->setSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateSymbols((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObject EditorGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditorGUI.data,
      qt_meta_data_EditorGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EditorGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditorGUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int EditorGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
