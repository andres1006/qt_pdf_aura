/****************************************************************************
** Meta object code from reading C++ file 'videopreview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "videopreview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videopreview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_videoPreview_t {
    QByteArrayData data[16];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_videoPreview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_videoPreview_t qt_meta_stringdata_videoPreview = {
    {
QT_MOC_LITERAL(0, 0, 12), // "videoPreview"
QT_MOC_LITERAL(1, 13, 6), // "newPos"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 3), // "pos"
QT_MOC_LITERAL(4, 25, 9), // "openVideo"
QT_MOC_LITERAL(5, 35, 8), // "fileName"
QT_MOC_LITERAL(6, 44, 11), // "updateImage"
QT_MOC_LITERAL(7, 56, 4), // "stop"
QT_MOC_LITERAL(8, 61, 5), // "pause"
QT_MOC_LITERAL(9, 67, 4), // "play"
QT_MOC_LITERAL(10, 72, 7), // "speedUp"
QT_MOC_LITERAL(11, 80, 9), // "speedDown"
QT_MOC_LITERAL(12, 90, 7), // "setData"
QT_MOC_LITERAL(13, 98, 6), // "OData*"
QT_MOC_LITERAL(14, 105, 4), // "data"
QT_MOC_LITERAL(15, 110, 8) // "loadLogo"

    },
    "videoPreview\0newPos\0\0pos\0openVideo\0"
    "fileName\0updateImage\0stop\0pause\0play\0"
    "speedUp\0speedDown\0setData\0OData*\0data\0"
    "loadLogo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_videoPreview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   67,    2, 0x0a /* Public */,
       6,    0,   70,    2, 0x0a /* Public */,
       7,    0,   71,    2, 0x0a /* Public */,
       8,    0,   72,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    0,   75,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    1,   76,    2, 0x02 /* Public */,
      15,    0,   79,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void videoPreview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        videoPreview *_t = static_cast<videoPreview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newPos((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: { bool _r = _t->openVideo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->updateImage(); break;
        case 3: _t->stop(); break;
        case 4: _t->pause(); break;
        case 5: _t->play(); break;
        case 6: _t->speedUp(); break;
        case 7: _t->speedDown(); break;
        case 8: _t->setData((*reinterpret_cast< OData*(*)>(_a[1]))); break;
        case 9: _t->loadLogo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OData* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (videoPreview::*_t)(const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&videoPreview::newPos)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject videoPreview::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_videoPreview.data,
      qt_meta_data_videoPreview,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *videoPreview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *videoPreview::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_videoPreview.stringdata0))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int videoPreview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
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
void videoPreview::newPos(const int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
