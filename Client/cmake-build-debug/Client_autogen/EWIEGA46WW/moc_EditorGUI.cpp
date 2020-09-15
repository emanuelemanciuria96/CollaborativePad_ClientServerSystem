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
    QByteArrayData data[24];
    char stringdata0[283];
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
QT_MOC_LITERAL(10, 93, 22), // "handleCursorPosChanged"
QT_MOC_LITERAL(11, 116, 19), // "enableSendCursorPos"
QT_MOC_LITERAL(12, 136, 13), // "updateSymbols"
QT_MOC_LITERAL(13, 150, 1), // "s"
QT_MOC_LITERAL(14, 152, 6), // "siteId"
QT_MOC_LITERAL(15, 159, 17), // "Message::action_t"
QT_MOC_LITERAL(16, 177, 6), // "action"
QT_MOC_LITERAL(17, 184, 13), // "deleteAllText"
QT_MOC_LITERAL(18, 198, 21), // "updateRemoteCursorPos"
QT_MOC_LITERAL(19, 220, 12), // "removeCursor"
QT_MOC_LITERAL(20, 233, 9), // "highlight"
QT_MOC_LITERAL(21, 243, 11), // "exportToPdf"
QT_MOC_LITERAL(22, 255, 18), // "setCurrentFileName"
QT_MOC_LITERAL(23, 274, 8) // "filename"

    },
    "EditorGUI\0clear\0\0contentsChange\0pos\0"
    "charsRemoved\0charsAdded\0flushInsertQueue\0"
    "setSelected\0yes\0handleCursorPosChanged\0"
    "enableSendCursorPos\0updateSymbols\0s\0"
    "siteId\0Message::action_t\0action\0"
    "deleteAllText\0updateRemoteCursorPos\0"
    "removeCursor\0highlight\0exportToPdf\0"
    "setCurrentFileName\0filename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   80,    2, 0x08 /* Private */,
       7,    0,   87,    2, 0x08 /* Private */,
       8,    1,   88,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    4,   93,    2, 0x0a /* Public */,
      17,    0,  102,    2, 0x0a /* Public */,
      18,    2,  103,    2, 0x0a /* Public */,
      19,    1,  108,    2, 0x0a /* Public */,
      20,    2,  111,    2, 0x0a /* Public */,
      21,    0,  116,    2, 0x0a /* Public */,
      22,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, 0x80000000 | 15,    4,   13,   14,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void EditorGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorGUI *_t = static_cast<EditorGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->contentsChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->flushInsertQueue(); break;
        case 3: _t->setSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->handleCursorPosChanged(); break;
        case 5: _t->enableSendCursorPos(); break;
        case 6: _t->updateSymbols((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< Message::action_t(*)>(_a[4]))); break;
        case 7: _t->deleteAllText(); break;
        case 8: _t->updateRemoteCursorPos((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 9: _t->removeCursor((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->highlight((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 11: _t->exportToPdf(); break;
        case 12: _t->setCurrentFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (EditorGUI::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EditorGUI::clear)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject EditorGUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EditorGUI.data,
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
    return QWidget::qt_metacast(_clname);
}

int EditorGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
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
