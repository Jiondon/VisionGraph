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
    QByteArrayData data[58];
    char stringdata0[789];
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
QT_MOC_LITERAL(14, 224, 18), // "slot_circle_action"
QT_MOC_LITERAL(15, 243, 15), // "slot_arc_action"
QT_MOC_LITERAL(16, 259, 16), // "slot_poly_action"
QT_MOC_LITERAL(17, 276, 21), // "slot_poly_elli_action"
QT_MOC_LITERAL(18, 298, 17), // "slot_point_action"
QT_MOC_LITERAL(19, 316, 16), // "slot_line_action"
QT_MOC_LITERAL(20, 333, 20), // "slot_polyLine_action"
QT_MOC_LITERAL(21, 354, 17), // "slot_open_project"
QT_MOC_LITERAL(22, 372, 17), // "slot_front_action"
QT_MOC_LITERAL(23, 390, 16), // "slot_next_action"
QT_MOC_LITERAL(24, 407, 17), // "slot_clear_action"
QT_MOC_LITERAL(25, 425, 22), // "slot_removeItem_action"
QT_MOC_LITERAL(26, 448, 12), // "slot_addItem"
QT_MOC_LITERAL(27, 461, 8), // "ItemType"
QT_MOC_LITERAL(28, 470, 4), // "type"
QT_MOC_LITERAL(29, 475, 2), // "rf"
QT_MOC_LITERAL(30, 478, 12), // "slot_addPoly"
QT_MOC_LITERAL(31, 491, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(32, 508, 9), // "vecPointF"
QT_MOC_LITERAL(33, 518, 13), // "slot_addPoint"
QT_MOC_LITERAL(34, 532, 6), // "pointF"
QT_MOC_LITERAL(35, 539, 12), // "slot_addLine"
QT_MOC_LITERAL(36, 552, 4), // "line"
QT_MOC_LITERAL(37, 557, 14), // "slot_mouseMove"
QT_MOC_LITERAL(38, 572, 10), // "slot_Press"
QT_MOC_LITERAL(39, 583, 9), // "bSelected"
QT_MOC_LITERAL(40, 593, 3), // "bIn"
QT_MOC_LITERAL(41, 597, 1), // "x"
QT_MOC_LITERAL(42, 599, 1), // "y"
QT_MOC_LITERAL(43, 601, 10), // "slot_wheel"
QT_MOC_LITERAL(44, 612, 5), // "delta"
QT_MOC_LITERAL(45, 618, 16), // "slot_SizeChanged"
QT_MOC_LITERAL(46, 635, 11), // "currentSize"
QT_MOC_LITERAL(47, 647, 1), // "w"
QT_MOC_LITERAL(48, 649, 1), // "h"
QT_MOC_LITERAL(49, 651, 17), // "slot_valueChanged"
QT_MOC_LITERAL(50, 669, 2), // "qR"
QT_MOC_LITERAL(51, 672, 19), // "slot_SceneMouseMove"
QT_MOC_LITERAL(52, 692, 20), // "slot_actionTriggered"
QT_MOC_LITERAL(53, 713, 8), // "QAction*"
QT_MOC_LITERAL(54, 722, 6), // "action"
QT_MOC_LITERAL(55, 729, 27), // "slot_SpinBox_ViewRegionSize"
QT_MOC_LITERAL(56, 757, 21), // "slot_GraphTypeChanged"
QT_MOC_LITERAL(57, 779, 9) // "GraphType"

    },
    "VisionGraph_\0signal_itemFinished\0\0"
    "VisionItem*\0item\0slot_selected_action\0"
    "slot_drag_action\0slot_zoom_action\0"
    "slot_fit_action\0slot_mousePainter_action\0"
    "slot_mouseClear_action\0slot_save_action\0"
    "slot_rect_action\0slot_ellipse_action\0"
    "slot_circle_action\0slot_arc_action\0"
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
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  194,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  197,    2, 0x08 /* Private */,
       6,    0,  198,    2, 0x08 /* Private */,
       7,    0,  199,    2, 0x08 /* Private */,
       8,    0,  200,    2, 0x08 /* Private */,
       9,    0,  201,    2, 0x08 /* Private */,
      10,    0,  202,    2, 0x08 /* Private */,
      11,    0,  203,    2, 0x08 /* Private */,
      12,    0,  204,    2, 0x08 /* Private */,
      13,    0,  205,    2, 0x08 /* Private */,
      14,    0,  206,    2, 0x08 /* Private */,
      15,    0,  207,    2, 0x08 /* Private */,
      16,    0,  208,    2, 0x08 /* Private */,
      17,    0,  209,    2, 0x08 /* Private */,
      18,    0,  210,    2, 0x08 /* Private */,
      19,    0,  211,    2, 0x08 /* Private */,
      20,    0,  212,    2, 0x08 /* Private */,
      21,    0,  213,    2, 0x08 /* Private */,
      22,    0,  214,    2, 0x08 /* Private */,
      23,    0,  215,    2, 0x08 /* Private */,
      24,    0,  216,    2, 0x08 /* Private */,
      25,    0,  217,    2, 0x08 /* Private */,
      26,    2,  218,    2, 0x08 /* Private */,
      30,    2,  223,    2, 0x08 /* Private */,
      33,    1,  228,    2, 0x08 /* Private */,
      35,    1,  231,    2, 0x08 /* Private */,
      37,    1,  234,    2, 0x08 /* Private */,
      38,    5,  237,    2, 0x08 /* Private */,
      43,    1,  248,    2, 0x08 /* Private */,
      45,    1,  251,    2, 0x08 /* Private */,
      45,    2,  254,    2, 0x08 /* Private */,
      49,    1,  259,    2, 0x08 /* Private */,
      51,    2,  262,    2, 0x08 /* Private */,
      52,    1,  267,    2, 0x08 /* Private */,
      55,    1,  270,    2, 0x08 /* Private */,
      56,    1,  273,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27, QMetaType::QRectF,   28,   29,
    QMetaType::Void, 0x80000000 | 31, 0x80000000 | 27,   32,   28,
    QMetaType::Void, QMetaType::QPointF,   34,
    QMetaType::Void, QMetaType::QLine,   36,
    QMetaType::Void, QMetaType::QPointF,   34,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Bool, QMetaType::QReal, QMetaType::QReal,    4,   39,   40,   41,   42,
    QMetaType::Void, QMetaType::QReal,   44,
    QMetaType::Void, QMetaType::QString,   46,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   47,   48,
    QMetaType::Void, QMetaType::Int,   50,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   41,   42,
    QMetaType::Void, 0x80000000 | 53,   54,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void, 0x80000000 | 57,   28,

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
        case 10: _t->slot_circle_action(); break;
        case 11: _t->slot_arc_action(); break;
        case 12: _t->slot_poly_action(); break;
        case 13: _t->slot_poly_elli_action(); break;
        case 14: _t->slot_point_action(); break;
        case 15: _t->slot_line_action(); break;
        case 16: _t->slot_polyLine_action(); break;
        case 17: _t->slot_open_project(); break;
        case 18: _t->slot_front_action(); break;
        case 19: _t->slot_next_action(); break;
        case 20: _t->slot_clear_action(); break;
        case 21: _t->slot_removeItem_action(); break;
        case 22: _t->slot_addItem((*reinterpret_cast< ItemType(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 23: _t->slot_addPoly((*reinterpret_cast< QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< ItemType(*)>(_a[2]))); break;
        case 24: _t->slot_addPoint((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 25: _t->slot_addLine((*reinterpret_cast< QLine(*)>(_a[1]))); break;
        case 26: _t->slot_mouseMove((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 27: _t->slot_Press((*reinterpret_cast< VisionItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< qreal(*)>(_a[4])),(*reinterpret_cast< qreal(*)>(_a[5]))); break;
        case 28: _t->slot_wheel((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 29: _t->slot_SizeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->slot_SizeChanged((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 31: _t->slot_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->slot_SceneMouseMove((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 33: _t->slot_actionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 34: _t->slot_SpinBox_ViewRegionSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->slot_GraphTypeChanged((*reinterpret_cast< GraphType(*)>(_a[1]))); break;
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
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VisionItem* >(); break;
            }
            break;
        case 33:
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
    { &QFrame::staticMetaObject, qt_meta_stringdata_VisionGraph_.data,
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
    return QFrame::qt_metacast(_clname);
}

int VisionGraph_::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
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
