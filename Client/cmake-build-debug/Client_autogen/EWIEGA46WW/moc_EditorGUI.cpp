/****************************************************************************
** Meta object code from reading C++ file 'EditorGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../EditorGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditorGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditorGUI_t {
    QByteArrayData data[16];
    char stringdata0[155];
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
QT_MOC_LITERAL(3, 17, 14), // "contentsChange"
QT_MOC_LITERAL(4, 32, 3), // "pos"
QT_MOC_LITERAL(5, 36, 12), // "charsRemoved"
QT_MOC_LITERAL(6, 49, 10), // "charsAdded"
QT_MOC_LITERAL(7, 60, 16), // "flushInsertQueue"
QT_MOC_LITERAL(8, 77, 11), // "setSelected"
QT_MOC_LITERAL(9, 89, 3), // "yes"
QT_MOC_LITERAL(10, 93, 13), // "updateSymbols"
QT_MOC_LITERAL(11, 107, 1), // "s"
QT_MOC_LITERAL(12, 109, 6), // "siteId"
QT_MOC_LITERAL(13, 116, 17), // "Message::action_t"
QT_MOC_LITERAL(14, 134, 6), // "action"
QT_MOC_LITERAL(15, 141, 13) // "deleteAllText"

    },
    "EditorGUI\0clear\0\0contentsChange\0pos\0"
    "charsRemoved\0charsAdded\0flushInsertQueue\0"
    "setSelected\0yes\0updateSymbols\0s\0siteId\0"
    "Message::action_t\0action\0deleteAllText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   45,    2, 0x08 /* Private */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    1,   53,    2, 0x08 /* Private */,
      10,    4,   56,    2, 0x0a /* Public */,
      15,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 13,    4,   11,   12,   14,
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
        case 1: _t->contentsChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->flushInsertQueue(); break;
        case 3: _t->setSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->updateSymbols((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        case 5: _t->deleteAllText(); break;
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
    }
}

QT_INIT_METAOBJECT const QMetaObject EditorGUI::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
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
    return QMainWindow::qt_metacast(_clname);
}

int EditorGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void EditorGUI::clear()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
