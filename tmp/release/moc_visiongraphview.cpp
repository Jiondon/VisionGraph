/****************************************************************************
** Meta object code from reading C++ file 'visiongraphview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/item/visiongraphview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visiongraphview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionGraphView_t {
    QByteArrayData data[34];
    char stringdata0[387];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionGraphView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionGraphView_t qt_meta_stringdata_VisionGraphView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VisionGraphView"
QT_MOC_LITERAL(1, 16, 11), // "signal_Move"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "pointF"
QT_MOC_LITERAL(4, 36, 12), // "signal_wheel"
QT_MOC_LITERAL(5, 49, 5), // "delta"
QT_MOC_LITERAL(6, 55, 11), // "signal_Item"
QT_MOC_LITERAL(7, 67, 8), // "ItemType"
QT_MOC_LITERAL(8, 76, 4), // "type"
QT_MOC_LITERAL(9, 81, 2), // "rf"
QT_MOC_LITERAL(10, 84, 16), // "signal_Item_poly"
QT_MOC_LITERAL(11, 101, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(12, 118, 8), // "vecPoint"
QT_MOC_LITERAL(13, 127, 17), // "signal_Item_point"
QT_MOC_LITERAL(14, 145, 16), // "signal_Item_Line"
QT_MOC_LITERAL(15, 162, 4), // "line"
QT_MOC_LITERAL(16, 167, 15), // "slot_updateItem"
QT_MOC_LITERAL(17, 183, 12), // "QPainterPath"
QT_MOC_LITERAL(18, 196, 4), // "path"
QT_MOC_LITERAL(19, 201, 15), // "slot_updatePath"
QT_MOC_LITERAL(20, 217, 8), // "XVRegion"
QT_MOC_LITERAL(21, 226, 8), // "selected"
QT_MOC_LITERAL(22, 235, 11), // "VisionItem*"
QT_MOC_LITERAL(23, 247, 4), // "item"
QT_MOC_LITERAL(24, 252, 7), // "leftTop"
QT_MOC_LITERAL(25, 260, 5), // "angle"
QT_MOC_LITERAL(26, 266, 19), // "slot_CreatePolygonF"
QT_MOC_LITERAL(27, 286, 9), // "vecPointF"
QT_MOC_LITERAL(28, 296, 18), // "slot_CombineRegion"
QT_MOC_LITERAL(29, 315, 7), // "region1"
QT_MOC_LITERAL(30, 323, 7), // "region2"
QT_MOC_LITERAL(31, 331, 20), // "XVCombineRegionsType"
QT_MOC_LITERAL(32, 352, 11), // "combineType"
QT_MOC_LITERAL(33, 364, 22) // "slotUpdateViewInfo_Pos"

    },
    "VisionGraphView\0signal_Move\0\0pointF\0"
    "signal_wheel\0delta\0signal_Item\0ItemType\0"
    "type\0rf\0signal_Item_poly\0QVector<QPointF>\0"
    "vecPoint\0signal_Item_point\0signal_Item_Line\0"
    "line\0slot_updateItem\0QPainterPath\0"
    "path\0slot_updatePath\0XVRegion\0selected\0"
    "VisionItem*\0item\0leftTop\0angle\0"
    "slot_CreatePolygonF\0vecPointF\0"
    "slot_CombineRegion\0region1\0region2\0"
    "XVCombineRegionsType\0combineType\0"
    "slotUpdateViewInfo_Pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionGraphView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    2,   75,    2, 0x06 /* Public */,
      10,    1,   80,    2, 0x06 /* Public */,
      13,    1,   83,    2, 0x06 /* Public */,
      14,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    2,   89,    2, 0x0a /* Public */,
      19,    6,   94,    2, 0x0a /* Public */,
      26,    4,  107,    2, 0x0a /* Public */,
      28,    3,  116,    2, 0x0a /* Public */,
      33,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QReal,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QRectF,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QLine,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 17,    8,   18,
    0x80000000 | 20, QMetaType::Bool, 0x80000000 | 22, 0x80000000 | 7, QMetaType::QRectF, QMetaType::QPointF, QMetaType::QReal,   21,   23,    8,    9,   24,   25,
    0x80000000 | 20, QMetaType::Bool, 0x80000000 | 22, 0x80000000 | 7, 0x80000000 | 11,   21,   23,    8,   27,
    0x80000000 | 20, 0x80000000 | 20, 0x80000000 | 20, 0x80000000 | 31,   29,   30,   32,
    QMetaType::Void,

       0        // eod
};

void VisionGraphView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionGraphView *_t = static_cast<VisionGraphView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_Move((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->signal_wheel((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->signal_Item((*reinterpret_cast< ItemType(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 3: _t->signal_Item_poly((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 4: _t->signal_Item_point((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 5: _t->signal_Item_Line((*reinterpret_cast< QLine(*)>(_a[1]))); break;
        case 6: _t->slot_updateItem((*reinterpret_cast< ItemType(*)>(_a[1])),(*reinterpret_cast< QPainterPath(*)>(_a[2]))); break;
        case 7: { XVRegion _r = _t->slot_updatePath((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< VisionItem*(*)>(_a[2])),(*reinterpret_cast< ItemType(*)>(_a[3])),(*reinterpret_cast< QRectF(*)>(_a[4])),(*reinterpret_cast< QPointF(*)>(_a[5])),(*reinterpret_cast< qreal(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< XVRegion*>(_a[0]) = _r; }  break;
        case 8: { XVRegion _r = _t->slot_CreatePolygonF((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< VisionItem*(*)>(_a[2])),(*reinterpret_cast< ItemType(*)>(_a[3])),(*reinterpret_cast< QVector<QPointF>(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< XVRegion*>(_a[0]) = _r; }  break;
        case 9: { XVRegion _r = _t->slot_CombineRegion((*reinterpret_cast< XVRegion(*)>(_a[1])),(*reinterpret_cast< XVRegion(*)>(_a[2])),(*reinterpret_cast< XVCombineRegionsType(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< XVRegion*>(_a[0]) = _r; }  break;
        case 10: _t->slotUpdateViewInfo_Pos(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionGraphView::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_Move)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisionGraphView::*_t)(qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_wheel)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VisionGraphView::*_t)(ItemType , QRectF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_Item)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VisionGraphView::*_t)(QVector<QPointF> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_Item_poly)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VisionGraphView::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_Item_point)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VisionGraphView::*_t)(QLine );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraphView::signal_Item_Line)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject VisionGraphView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_VisionGraphView.data,
      qt_meta_data_VisionGraphView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionGraphView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionGraphView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionGraphView.stringdata0))
        return static_cast<void*>(const_cast< VisionGraphView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int VisionGraphView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void VisionGraphView::signal_Move(QPointF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VisionGraphView::signal_wheel(qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VisionGraphView::signal_Item(ItemType _t1, QRectF _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VisionGraphView::signal_Item_poly(QVector<QPointF> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VisionGraphView::signal_Item_point(QPointF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VisionGraphView::signal_Item_Line(QLine _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
