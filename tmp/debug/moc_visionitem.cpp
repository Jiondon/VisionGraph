/****************************************************************************
** Meta object code from reading C++ file 'visionitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/control/visionitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionItem_t {
    QByteArrayData data[23];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionItem_t qt_meta_stringdata_VisionItem = {
    {
QT_MOC_LITERAL(0, 0, 10), // "VisionItem"
QT_MOC_LITERAL(1, 11, 14), // "signal_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "VisionItem*"
QT_MOC_LITERAL(4, 39, 4), // "item"
QT_MOC_LITERAL(5, 44, 8), // "selected"
QT_MOC_LITERAL(6, 53, 3), // "bIn"
QT_MOC_LITERAL(7, 57, 1), // "x"
QT_MOC_LITERAL(8, 59, 1), // "y"
QT_MOC_LITERAL(9, 61, 11), // "signal_ctrl"
QT_MOC_LITERAL(10, 73, 10), // "eventStyle"
QT_MOC_LITERAL(11, 84, 12), // "signal_press"
QT_MOC_LITERAL(12, 97, 18), // "signal_painterInfo"
QT_MOC_LITERAL(13, 116, 8), // "ItemType"
QT_MOC_LITERAL(14, 125, 4), // "type"
QT_MOC_LITERAL(15, 130, 12), // "QPainterPath"
QT_MOC_LITERAL(16, 143, 2), // "rf"
QT_MOC_LITERAL(17, 146, 15), // "selectedChanged"
QT_MOC_LITERAL(18, 162, 4), // "left"
QT_MOC_LITERAL(19, 167, 5), // "angle"
QT_MOC_LITERAL(20, 173, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(21, 190, 9), // "vecPointF"
QT_MOC_LITERAL(22, 200, 13) // "signalChanged"

    },
    "VisionItem\0signal_clicked\0\0VisionItem*\0"
    "item\0selected\0bIn\0x\0y\0signal_ctrl\0"
    "eventStyle\0signal_press\0signal_painterInfo\0"
    "ItemType\0type\0QPainterPath\0rf\0"
    "selectedChanged\0left\0angle\0QVector<QPointF>\0"
    "vecPointF\0signalChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   64,    2, 0x06 /* Public */,
       1,    4,   75,    2, 0x26 /* Public | MethodCloned */,
       1,    3,   84,    2, 0x26 /* Public | MethodCloned */,
       1,    2,   91,    2, 0x26 /* Public | MethodCloned */,
       9,    1,   96,    2, 0x06 /* Public */,
      11,    0,   99,    2, 0x06 /* Public */,
      12,    2,  100,    2, 0x06 /* Public */,
      17,    6,  105,    2, 0x06 /* Public */,
      17,    4,  118,    2, 0x06 /* Public */,
      22,    1,  127,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal, QMetaType::QReal,    4,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal,    4,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15,   14,   16,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 13, QMetaType::QRectF, QMetaType::QPointF, QMetaType::QReal,    5,    4,   14,   16,   18,   19,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 13, 0x80000000 | 20,    5,    4,   14,   21,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void VisionItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionItem *_t = static_cast<VisionItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 1: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4]))); break;
        case 2: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->signal_clicked((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->signal_ctrl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signal_press(); break;
        case 6: _t->signal_painterInfo((*reinterpret_cast< ItemType(*)>(_a[1])),(*reinterpret_cast< QPainterPath(*)>(_a[2]))); break;
        case 7: _t->selectedChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< VisionItem*(*)>(_a[2])),(*reinterpret_cast< ItemType(*)>(_a[3])),(*reinterpret_cast< QRectF(*)>(_a[4])),(*reinterpret_cast< QPointF(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6]))); break;
        case 8: _t->selectedChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< VisionItem*(*)>(_a[2])),(*reinterpret_cast< ItemType(*)>(_a[3])),(*reinterpret_cast< QVector<QPointF>(*)>(_a[4]))); break;
        case 9: _t->signalChanged((*reinterpret_cast< VisionItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionItem::*_t)(VisionItem * , bool , bool , qreal , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_ctrl)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_press)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(ItemType , QPainterPath );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signal_painterInfo)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(bool , VisionItem * , ItemType , QRectF , QPointF , qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::selectedChanged)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(bool , VisionItem * , ItemType , QVector<QPointF> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::selectedChanged)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (VisionItem::*_t)(VisionItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionItem::signalChanged)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject VisionItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisionItem.data,
      qt_meta_data_VisionItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionItem.stringdata0))
        return static_cast<void*>(const_cast< VisionItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< VisionItem*>(this));
    return QObject::qt_metacast(_clname);
}

int VisionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VisionItem::signal_clicked(VisionItem * _t1, bool _t2, bool _t3, qreal _t4, qreal _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 4
void VisionItem::signal_ctrl(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VisionItem::signal_press()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void VisionItem::signal_painterInfo(ItemType _t1, QPainterPath _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VisionItem::selectedChanged(bool _t1, VisionItem * _t2, ItemType _t3, QRectF _t4, QPointF _t5, qreal _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VisionItem::selectedChanged(bool _t1, VisionItem * _t2, ItemType _t3, QVector<QPointF> _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
