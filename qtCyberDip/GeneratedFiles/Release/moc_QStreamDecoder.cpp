/****************************************************************************
** Meta object code from reading C++ file 'QStreamDecoder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../QStreamDecoder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QStreamDecoder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QStreamDecoder_t {
    QByteArrayData data[11];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QStreamDecoder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QStreamDecoder_t qt_meta_stringdata_QStreamDecoder = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QStreamDecoder"
QT_MOC_LITERAL(1, 15, 14), // "decodeFinished"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "result"
QT_MOC_LITERAL(4, 38, 7), // "isAudio"
QT_MOC_LITERAL(5, 46, 11), // "decodeFrame"
QT_MOC_LITERAL(6, 58, 14), // "unsigned char*"
QT_MOC_LITERAL(7, 73, 5), // "bytes"
QT_MOC_LITERAL(8, 79, 4), // "size"
QT_MOC_LITERAL(9, 84, 12), // "lastRendered"
QT_MOC_LITERAL(10, 97, 7) // "process"

    },
    "QStreamDecoder\0decodeFinished\0\0result\0"
    "isAudio\0decodeFrame\0unsigned char*\0"
    "bytes\0size\0lastRendered\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QStreamDecoder[] = {

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
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   39,    2, 0x0a /* Public */,
       5,    2,   46,    2, 0x2a /* Public | MethodCloned */,
      10,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Bool,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

void QStreamDecoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QStreamDecoder *_t = static_cast<QStreamDecoder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->decodeFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->decodeFrame((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->decodeFrame((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QStreamDecoder::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QStreamDecoder::decodeFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QStreamDecoder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QStreamDecoder.data,
      qt_meta_data_QStreamDecoder,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QStreamDecoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QStreamDecoder::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QStreamDecoder.stringdata0))
        return static_cast<void*>(const_cast< QStreamDecoder*>(this));
    return QObject::qt_metacast(_clname);
}

int QStreamDecoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void QStreamDecoder::decodeFinished(bool _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
