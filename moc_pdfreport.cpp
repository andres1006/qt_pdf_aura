/****************************************************************************
** Meta object code from reading C++ file 'pdfreport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pdfreport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pdfreport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pdfreport_t {
    QByteArrayData data[16];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pdfreport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pdfreport_t qt_meta_stringdata_pdfreport = {
    {
QT_MOC_LITERAL(0, 0, 9), // "pdfreport"
QT_MOC_LITERAL(1, 10, 12), // "setMongoInfo"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "newReport"
QT_MOC_LITERAL(4, 34, 12), // "filePathJson"
QT_MOC_LITERAL(5, 47, 10), // "dbPatients"
QT_MOC_LITERAL(6, 58, 9), // "pathology"
QT_MOC_LITERAL(7, 68, 14), // "availableTests"
QT_MOC_LITERAL(8, 83, 7), // "patient"
QT_MOC_LITERAL(9, 91, 9), // "allParams"
QT_MOC_LITERAL(10, 101, 10), // "testParams"
QT_MOC_LITERAL(11, 112, 4), // "test"
QT_MOC_LITERAL(12, 117, 12), // "paramsToShow"
QT_MOC_LITERAL(13, 130, 16), // "configLogoDialog"
QT_MOC_LITERAL(14, 147, 16), // "QAbstractButton*"
QT_MOC_LITERAL(15, 164, 10) // "changeLogo"

    },
    "pdfreport\0setMongoInfo\0\0newReport\0"
    "filePathJson\0dbPatients\0pathology\0"
    "availableTests\0patient\0allParams\0"
    "testParams\0test\0paramsToShow\0"
    "configLogoDialog\0QAbstractButton*\0"
    "changeLogo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pdfreport[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x0a /* Public */,
       3,    1,   64,    2, 0x0a /* Public */,
       5,    1,   67,    2, 0x0a /* Public */,
       7,    1,   70,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,
      13,    1,   80,    2, 0x0a /* Public */,
      15,    1,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UInt,    2,    2,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::QStringList, QMetaType::QString,    6,
    QMetaType::QStringList, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QStringList,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 14,    2,

       0        // eod
};

void pdfreport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pdfreport *_t = static_cast<pdfreport *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMongoInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const uint(*)>(_a[2]))); break;
        case 1: _t->newReport((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { QStringList _r = _t->dbPatients((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 3: { QStringList _r = _t->availableTests((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 4: _t->allParams(); break;
        case 5: { int _r = _t->testParams((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->paramsToShow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->configLogoDialog((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 8: _t->changeLogo((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject pdfreport::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_pdfreport.data,
      qt_meta_data_pdfreport,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *pdfreport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pdfreport::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_pdfreport.stringdata0))
        return static_cast<void*>(const_cast< pdfreport*>(this));
    return QObject::qt_metacast(_clname);
}

int pdfreport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
