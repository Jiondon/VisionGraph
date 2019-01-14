/****************************************************************************
** Meta object code from reading C++ file 'visiongraph_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/visiongraph_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visiongraph_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionGraph__t {
    QByteArrayData data[56];
    char stringdata0[754];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionGraph__t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionGraph__t qt_meta_stringdata_VisionGraph_ = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VisionGraph_"
QT_MOC_LITERAL(1, 13, 19), // "signal_itemFinished"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "VisionItem*"
QT_MOC_LITERAL(4, 46, 4), // "item"
QT_MOC_LITERAL(5, 51, 20), // "slot_selected_action"
QT_MOC_LITERAL(6, 72, 16), // "slot_drag_action"
QT_MOC_LITERAL(7, 89, 16), // "slot_zoom_action"
QT_MOC_LITERAL(8, 106, 15), // "slot_fit_action"
QT_MOC_LITERAL(9, 122, 24), // "slot_mousePainter_action"
QT_MOC_LITERAL(10, 147, 22), // "slot_mouseClear_action"
QT_MOC_LITERAL(11, 170, 16), // "slot_save_action"
QT_MOC_LITERAL(12, 187, 16), // "slot_rect_action"
QT_MOC_LITERAL(13, 204, 19), // "slot_ellipse_action"
QT_MOC_LITERAL(14, 224, 16), // "slot_poly_action"
QT_MOC_LITERAL(15, 241, 21), // "slot_poly_elli_action"
QT_MOC_LITERAL(16, 263, 17), // "slot_point_action"
QT_MOC_LITERAL(17, 281, 16), // "slot_line_action"
QT_MOC_LITERAL(18, 298, 20), // "slot_polyLine_action"
QT_MOC_LITERAL(19, 319, 17), // "slot_open_project"
QT_MOC_LITERAL(20, 337, 17), // "slot_front_action"
QT_MOC_LITERAL(21, 355, 16), // "slot_next_action"
QT_MOC_LITERAL(22, 372, 17), // "slot_clear_action"
QT_MOC_LITERAL(23, 390, 22), // "slot_removeItem_action"
QT_MOC_LITERAL(24, 413, 12), // "slot_addItem"
QT_MOC_LITERAL(25, 426, 8), // "ItemType"
QT_MOC_LITERAL(26, 435, 4), // "type"
QT_MOC_LITERAL(27, 440, 2), // "rf"
QT_MOC_LITERAL(28, 443, 12), // "slot_addPoly"
QT_MOC_LITERAL(29, 456, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(30, 473, 9), // "vecPointF"
QT_MOC_LITERAL(31, 483, 13), // "slot_addPoint"
QT_MOC_LITERAL(32, 497, 6), // "pointF"
QT_MOC_LITERAL(33, 504, 12), // "slot_addLine"
QT_MOC_LITERAL(34, 517, 4), // "line"
QT_MOC_LITERAL(35, 522, 14), // "slot_mouseMove"
QT_MOC_LITERAL(36, 537, 10), // "slot_Press"
QT_MOC_LITERAL(37, 548, 9), // "bSelected"
QT_MOC_LITERAL(38, 558, 3), // "bIn"
QT_MOC_LITERAL(39, 562, 1), // "x"
QT_MOC_LITERAL(40, 564, 1), // "y"
QT_MOC_LITERAL(41, 566, 10), // "slot_wheel"
QT_MOC_LITERAL(42, 577, 5), // "delta"
QT_MOC_LITERAL(43, 583, 16), // "slot_SizeChanged"
QT_MOC_LITERAL(44, 600, 11), // "currentSize"
QT_MOC_LITERAL(45, 612, 1), // "w"
QT_MOC_LITERAL(46, 614, 1), // "h"
QT_MOC_LITERAL(47, 616, 17), // "slot_valueChanged"
QT_MOC_LITERAL(48, 634, 2), // "qR"
QT_MOC_LITERAL(49, 637, 19), // "slot_SceneMouseMove"
QT_MOC_LITERAL(50, 657, 20), // "slot_actionTriggered"
QT_MOC_LITERAL(51, 678, 8), // "QAction*"
QT_MOC_LITERAL(52, 687, 6), // "action"
QT_MOC_LITERAL(53, 694, 27), // "slot_SpinBox_ViewRegionSize"
QT_MOC_LITERAL(54, 722, 21), // "slot_GraphTypeChanged"
QT_MOC_LITERAL(55, 744, 9) // "GraphType"

    },
    "VisionGraph_\0signal_itemFinished\0\0"
    "VisionItem*\0item\0slot_selected_action\0"
    "slot_drag_action\0slot_zoom_action\0"
    "slot_fit_action\0slot_mousePainter_action\0"
    "slot_mouseClear_action\0slot_save_action\0"
    "slot_rect_action\0slot_ellipse_action\0"
    "slot_poly_action\0slot_poly_elli_action\0"
    "slot_point_action\0slot_line_action\0"
    "slot_polyLine_action\0slot_open_project\0"
    "slot_front_action\0slot_next_action\0"
    "slot_clear_action\0slot_removeItem_action\0"
    "slot_addItem\0ItemType\0type\0rf\0"
    "slot_addPoly\0QVector<QPointF>\0vecPointF\0"
    "slot_addPoint\0pointF\0slot_addLine\0"
    "line\0slot_mouseMove\0slot_Press\0bSelected\0"
    "bIn\0x\0y\0slot_wheel\0delta\0slot_SizeChanged\0"
    "currentSize\0w\0h\0slot_valueChanged\0qR\0"
    "slot_SceneMouseMove\0slot_actionTriggered\0"
    "QAction*\0action\0slot_SpinBox_ViewRegionSize\0"
    "slot_GraphTypeChanged\0GraphType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionGraph_[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  184,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  187,    2, 0x08 /* Private */,
       6,    0,  188,    2, 0x08 /* Private */,
       7,    0,  189,    2, 0x08 /* Private */,
       8,    0,  190,    2, 0x08 /* Private */,
       9,    0,  191,    2, 0x08 /* Private */,
      10,    0,  192,    2, 0x08 /* Private */,
      11,    0,  193,    2, 0x08 /* Private */,
      12,    0,  194,    2, 0x08 /* Private */,
      13,    0,  195,    2, 0x08 /* Private */,
      14,    0,  196,    2, 0x08 /* Private */,
      15,    0,  197,    2, 0x08 /* Private */,
      16,    0,  198,    2, 0x08 /* Private */,
      17,    0,  199,    2, 0x08 /* Private */,
      18,    0,  200,    2, 0x08 /* Private */,
      19,    0,  201,    2, 0x08 /* Private */,
      20,    0,  202,    2, 0x08 /* Private */,
      21,    0,  203,    2, 0x08 /* Private */,
      22,    0,  204,    2, 0x08 /* Private */,
      23,    0,  205,    2, 0x08 /* Private */,
      24,    2,  206,    2, 0x08 /* Private */,
      28,    2,  211,    2, 0x08 /* Private */,
      31,    1,  216,    2, 0x08 /* Private */,
      33,    1,  219,    2, 0x08 /* Private */,
      35,    1,  222,    2, 0x08 /* Private */,
      36,    5,  225,    2, 0x08 /* Private */,
      41,    1,  236,    2, 0x08 /* Private */,
      43,    1,  239,    2, 0x08 /* Private */,
      43,    2,  242,    2, 0x08 /* Private */,
      47,    1,  247,    2, 0x08 /* Private */,
      49,    2,  250,    2, 0x08 /* Private */,
      50,    1,  255,    2, 0x08 /* Private */,
      53,    1,  258,    2, 0x08 /* Private */,
      54,    1,  261,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25, QMetaType::QRectF,   26,   27,
    QMetaType::Void, 0x80000000 | 29, 0x80000000 | 25,   30,   26,
    QMetaType::Void, QMetaType::QPointF,   32,
    QMetaType::Void, QMetaType::QLine,   34,
    QMetaType::Void, QMetaType::QPointF,   32,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal, QMetaType::QReal,    4,   37,   38,   39,   40,
    QMetaType::Void, QMetaType::QReal,   42,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   45,   46,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   39,   40,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, 0x80000000 | 55,   26,

       0        // eod
};

void VisionGraph_::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionGraph_ *_t = static_cast<VisionGraph_ *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_itemFinished((*reinterpret_cast< VisionItem*(*)>(_a[1]))); break;
        case 1: _t->slot_selected_action(); break;
        case 2: _t->slot_drag_action(); break;
        case 3: _t->slot_zoom_action(); break;
        case 4: _t->slot_fit_action(); break;
        case 5: _t->slot_mousePainter_action(); break;
        case 6: _t->slot_mouseClear_action(); break;
        case 7: _t->slot_save_action(); break;
        case 8: _t->slot_rect_action(); break;
        case 9: _t->slot_ellipse_action(); break;
        case 10: _t->slot_poly_action(); break;
        case 11: _t->slot_poly_elli_action(); break;
        case 12: _t->slot_point_action(); break;
        case 13: _t->slot_line_action(); break;
        case 14: _t->slot_polyLine_action(); break;
        case 15: _t->slot_open_project(); break;
        case 16: _t->slot_front_action(); break;
        case 17: _t->slot_next_action(); break;
        case 18: _t->slot_clear_action(); break;
        case 19: _t->slot_removeItem_action(); break;
        case 20: _t->slot_addItem((*reinterpret_cast< ItemType(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 21: _t->slot_addPoly((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< ItemType(*)>(_a[2]))); break;
        case 22: _t->slot_addPoint((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 23: _t->slot_addLine((*reinterpret_cast< QLine(*)>(_a[1]))); break;
        case 24: _t->slot_mouseMove((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 25: _t->slot_Press((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 26: _t->slot_wheel((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 27: _t->slot_SizeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->slot_SizeChanged((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 29: _t->slot_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->slot_SceneMouseMove((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 31: _t->slot_actionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 32: _t->slot_SpinBox_ViewRegionSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->slot_GraphTypeChanged((*reinterpret_cast< GraphType(*)>(_a[1]))); break;
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
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionGraph_::*_t)(VisionItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionGraph_::signal_itemFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject VisionGraph_::staticMetaObject = {
    { &VisionGraph_Base::staticMetaObject, qt_meta_stringdata_VisionGraph_.data,
      qt_meta_data_VisionGraph_,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionGraph_::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionGraph_::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionGraph_.stringdata0))
        return static_cast<void*>(const_cast< VisionGraph_*>(this));
    return VisionGraph_Base::qt_metacast(_clname);
}

int VisionGraph_::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VisionGraph_Base::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void VisionGraph_::signal_itemFinished(VisionItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
