/****************************************************************************
** Meta object code from reading C++ file 'visionrectitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/item/visionrectitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionrectitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionRectItem_t {
    QByteArrayData data[7];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionRectItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionRectItem_t qt_meta_stringdata_VisionRectItem = {
    {
QT_MOC_LITERAL(0, 0, 14), // "VisionRectItem"
QT_MOC_LITERAL(1, 15, 22), // "signal_RectSizeChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "slotIndex"
QT_MOC_LITERAL(4, 49, 5), // "index"
QT_MOC_LITERAL(5, 55, 14), // "slotArrowsItem"
QT_MOC_LITERAL(6, 70, 20) // "slotArrowsItem_leave"

    },
    "VisionRectItem\0signal_RectSizeChanged\0"
    "\0slotIndex\0index\0slotArrowsItem\0"
    "slotArrowsItem_leave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionRectItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VisionRectItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionRectItem *_t = static_cast<VisionRectItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_RectSizeChanged(); break;
        case 1: _t->slotIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotArrowsItem(); break;
        case 3: _t->slotArrowsItem_leave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionRectItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionRectItem::signal_RectSizeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject VisionRectItem::staticMetaObject = {
    { &VisionItem::staticMetaObject, qt_meta_stringdata_VisionRectItem.data,
      qt_meta_data_VisionRectItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionRectItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionRectItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionRectItem.stringdata0))
        return static_cast<void*>(const_cast< VisionRectItem*>(this));
    return VisionItem::qt_metacast(_clname);
}

int VisionRectItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VisionItem::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void VisionRectItem::signal_RectSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
