/****************************************************************************
** Meta object code from reading C++ file 'visionarrows_rotate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/control/visionarrows_rotate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visionarrows_rotate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VisionArrows_Rotate_t {
    QByteArrayData data[4];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VisionArrows_Rotate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VisionArrows_Rotate_t qt_meta_stringdata_VisionArrows_Rotate = {
    {
QT_MOC_LITERAL(0, 0, 19), // "VisionArrows_Rotate"
QT_MOC_LITERAL(1, 20, 16), // "signalHoverLeave"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 16) // "signalHoverEnter"

    },
    "VisionArrows_Rotate\0signalHoverLeave\0"
    "\0signalHoverEnter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VisionArrows_Rotate[] = {

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
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VisionArrows_Rotate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VisionArrows_Rotate *_t = static_cast<VisionArrows_Rotate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalHoverLeave(); break;
        case 1: _t->signalHoverEnter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VisionArrows_Rotate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionArrows_Rotate::signalHoverLeave)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VisionArrows_Rotate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VisionArrows_Rotate::signalHoverEnter)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject VisionArrows_Rotate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VisionArrows_Rotate.data,
      qt_meta_data_VisionArrows_Rotate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VisionArrows_Rotate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VisionArrows_Rotate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VisionArrows_Rotate.stringdata0))
        return static_cast<void*>(const_cast< VisionArrows_Rotate*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< VisionArrows_Rotate*>(this));
    return QObject::qt_metacast(_clname);
}

int VisionArrows_Rotate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void VisionArrows_Rotate::signalHoverLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VisionArrows_Rotate::signalHoverEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
