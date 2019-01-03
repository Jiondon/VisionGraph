/****************************************************************************
** Meta object code from reading C++ file 'visionchainitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/item/visionchainitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionchainitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionChainItem_t {
    QByteArrayData data[8];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionChainItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionChainItem_t qt_meta_stringdata_VisionChainItem = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VisionChainItem"
QT_MOC_LITERAL(1, 16, 11), // "signalMouse"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "x"
QT_MOC_LITERAL(4, 31, 1), // "y"
QT_MOC_LITERAL(5, 33, 14), // "signalSelected"
QT_MOC_LITERAL(6, 48, 8), // "selected"
QT_MOC_LITERAL(7, 57, 5) // "index"

    },
    "VisionChainItem\0signalMouse\0\0x\0y\0"
    "signalSelected\0selected\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionChainItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    3,    4,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    6,    7,

       0        // eod
};

void VisionChainItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionChainItem *_t = static_cast<VisionChainItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMouse((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 1: _t->signalSelected((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionChainItem::*_t)(qreal , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionChainItem::signalMouse)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisionChainItem::*_t)(bool , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionChainItem::signalSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject VisionChainItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisionChainItem.data,
      qt_meta_data_VisionChainItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionChainItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionChainItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionChainItem.stringdata0))
        return static_cast<void*>(const_cast< VisionChainItem*>(this));
    if (!strcmp(_clname, "VisionItem"))
        return static_cast< VisionItem*>(const_cast< VisionChainItem*>(this));
    return QObject::qt_metacast(_clname);
}

int VisionChainItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VisionChainItem::signalMouse(qreal _t1, qreal _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VisionChainItem::signalSelected(bool _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
