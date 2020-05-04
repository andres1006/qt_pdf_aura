/****************************************************************************
** Meta object code from reading C++ file 'qutils.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qutils.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qutils.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OTimer_t {
    QByteArrayData data[3];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OTimer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OTimer_t qt_meta_stringdata_OTimer = {
    {
QT_MOC_LITERAL(0, 0, 6), // "OTimer"
QT_MOC_LITERAL(1, 7, 13), // "timeoutSignal"
QT_MOC_LITERAL(2, 21, 0) // ""

    },
    "OTimer\0timeoutSignal\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OTimer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void OTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OTimer *_t = static_cast<OTimer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeoutSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OTimer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTimer::timeoutSignal)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject OTimer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OTimer.data,
      qt_meta_data_OTimer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OTimer.stringdata0))
        return static_cast<void*>(const_cast< OTimer*>(this));
    return QObject::qt_metacast(_clname);
}

int OTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void OTimer::timeoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_graphType_t {
    QByteArrayData data[9];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graphType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graphType_t qt_meta_stringdata_graphType = {
    {
QT_MOC_LITERAL(0, 0, 9), // "graphType"
QT_MOC_LITERAL(1, 10, 10), // "eGraphType"
QT_MOC_LITERAL(2, 21, 3), // "UND"
QT_MOC_LITERAL(3, 25, 5), // "PLOTX"
QT_MOC_LITERAL(4, 31, 5), // "PLOTY"
QT_MOC_LITERAL(5, 37, 7), // "SCATTER"
QT_MOC_LITERAL(6, 45, 10), // "SCATTERCLB"
QT_MOC_LITERAL(7, 56, 7), // "PICTURE"
QT_MOC_LITERAL(8, 64, 9) // "PUPILAREA"

    },
    "graphType\0eGraphType\0UND\0PLOTX\0PLOTY\0"
    "SCATTER\0SCATTERCLB\0PICTURE\0PUPILAREA"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graphType[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    7,   18,

 // enum data: key, value
       2, uint(graphType::UND),
       3, uint(graphType::PLOTX),
       4, uint(graphType::PLOTY),
       5, uint(graphType::SCATTER),
       6, uint(graphType::SCATTERCLB),
       7, uint(graphType::PICTURE),
       8, uint(graphType::PUPILAREA),

       0        // eod
};

void graphType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject graphType::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_graphType.data,
      qt_meta_data_graphType,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *graphType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graphType::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_graphType.stringdata0))
        return static_cast<void*>(const_cast< graphType*>(this));
    return QObject::qt_metacast(_clname);
}

int graphType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_cameraType_t {
    QByteArrayData data[4];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cameraType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cameraType_t qt_meta_stringdata_cameraType = {
    {
QT_MOC_LITERAL(0, 0, 10), // "cameraType"
QT_MOC_LITERAL(1, 11, 11), // "eCameraType"
QT_MOC_LITERAL(2, 23, 6), // "USB_20"
QT_MOC_LITERAL(3, 30, 14) // "DMM_37UX287_ML"

    },
    "cameraType\0eCameraType\0USB_20\0"
    "DMM_37UX287_ML"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cameraType[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    2,   18,

 // enum data: key, value
       2, uint(cameraType::USB_20),
       3, uint(cameraType::DMM_37UX287_ML),

       0        // eod
};

void cameraType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject cameraType::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_cameraType.data,
      qt_meta_data_cameraType,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *cameraType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cameraType::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_cameraType.stringdata0))
        return static_cast<void*>(const_cast< cameraType*>(this));
    return QObject::qt_metacast(_clname);
}

int cameraType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_testType_t {
    QByteArrayData data[15];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_testType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_testType_t qt_meta_stringdata_testType = {
    {
QT_MOC_LITERAL(0, 0, 8), // "testType"
QT_MOC_LITERAL(1, 9, 9), // "eTestType"
QT_MOC_LITERAL(2, 19, 3), // "UND"
QT_MOC_LITERAL(3, 23, 2), // "SV"
QT_MOC_LITERAL(4, 26, 3), // "ASV"
QT_MOC_LITERAL(5, 30, 2), // "SM"
QT_MOC_LITERAL(6, 33, 3), // "ASM"
QT_MOC_LITERAL(7, 37, 2), // "SC"
QT_MOC_LITERAL(8, 40, 2), // "IF"
QT_MOC_LITERAL(9, 43, 3), // "FIX"
QT_MOC_LITERAL(10, 47, 2), // "PL"
QT_MOC_LITERAL(11, 50, 3), // "SLL"
QT_MOC_LITERAL(12, 54, 3), // "SLS"
QT_MOC_LITERAL(13, 58, 3), // "OPT"
QT_MOC_LITERAL(14, 62, 3) // "CLB"

    },
    "testType\0eTestType\0UND\0SV\0ASV\0SM\0ASM\0"
    "SC\0IF\0FIX\0PL\0SLL\0SLS\0OPT\0CLB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_testType[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,   13,   18,

 // enum data: key, value
       2, uint(testType::UND),
       3, uint(testType::SV),
       4, uint(testType::ASV),
       5, uint(testType::SM),
       6, uint(testType::ASM),
       7, uint(testType::SC),
       8, uint(testType::IF),
       9, uint(testType::FIX),
      10, uint(testType::PL),
      11, uint(testType::SLL),
      12, uint(testType::SLS),
      13, uint(testType::OPT),
      14, uint(testType::CLB),

       0        // eod
};

void testType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject testType::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_testType.data,
      qt_meta_data_testType,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *testType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *testType::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_testType.stringdata0))
        return static_cast<void*>(const_cast< testType*>(this));
    return QObject::qt_metacast(_clname);
}

int testType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_taskType_t {
    QByteArrayData data[5];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_taskType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_taskType_t qt_meta_stringdata_taskType = {
    {
QT_MOC_LITERAL(0, 0, 8), // "taskType"
QT_MOC_LITERAL(1, 9, 9), // "eTaskType"
QT_MOC_LITERAL(2, 19, 11), // "CALIBRATION"
QT_MOC_LITERAL(3, 31, 4), // "TEST"
QT_MOC_LITERAL(4, 36, 5) // "UNDEF"

    },
    "taskType\0eTaskType\0CALIBRATION\0TEST\0"
    "UNDEF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_taskType[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    3,   18,

 // enum data: key, value
       2, uint(taskType::CALIBRATION),
       3, uint(taskType::TEST),
       4, uint(taskType::UNDEF),

       0        // eod
};

void taskType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject taskType::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_taskType.data,
      qt_meta_data_taskType,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *taskType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *taskType::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_taskType.stringdata0))
        return static_cast<void*>(const_cast< taskType*>(this));
    return QObject::qt_metacast(_clname);
}

int taskType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_displayMode_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_displayMode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_displayMode_t qt_meta_stringdata_displayMode = {
    {
QT_MOC_LITERAL(0, 0, 11), // "displayMode"
QT_MOC_LITERAL(1, 12, 12), // "eDisplayMode"
QT_MOC_LITERAL(2, 25, 6), // "MANUAL"
QT_MOC_LITERAL(3, 32, 9), // "AUTOMATIC"
QT_MOC_LITERAL(4, 42, 8) // "COMBINED"

    },
    "displayMode\0eDisplayMode\0MANUAL\0"
    "AUTOMATIC\0COMBINED"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_displayMode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    3,   18,

 // enum data: key, value
       2, uint(displayMode::MANUAL),
       3, uint(displayMode::AUTOMATIC),
       4, uint(displayMode::COMBINED),

       0        // eod
};

void displayMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject displayMode::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_displayMode.data,
      qt_meta_data_displayMode,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *displayMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *displayMode::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_displayMode.stringdata0))
        return static_cast<void*>(const_cast< displayMode*>(this));
    return QObject::qt_metacast(_clname);
}

int displayMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_colorScheme_t {
    QByteArrayData data[24];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_colorScheme_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_colorScheme_t qt_meta_stringdata_colorScheme = {
    {
QT_MOC_LITERAL(0, 0, 11), // "colorScheme"
QT_MOC_LITERAL(1, 12, 14), // "graphBgChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "graphFgChanged"
QT_MOC_LITERAL(4, 43, 17), // "graphGridYChanged"
QT_MOC_LITERAL(5, 61, 17), // "graphGridXChanged"
QT_MOC_LITERAL(6, 79, 16), // "graphGazeChanged"
QT_MOC_LITERAL(7, 96, 20), // "graphStimulusChanged"
QT_MOC_LITERAL(8, 117, 12), // "guiBgChanged"
QT_MOC_LITERAL(9, 130, 7), // "graphBG"
QT_MOC_LITERAL(10, 138, 7), // "graphFG"
QT_MOC_LITERAL(11, 146, 10), // "graphGridY"
QT_MOC_LITERAL(12, 157, 10), // "graphGridX"
QT_MOC_LITERAL(13, 168, 9), // "graphGaze"
QT_MOC_LITERAL(14, 178, 13), // "graphStimulus"
QT_MOC_LITERAL(15, 192, 5), // "guiBG"
QT_MOC_LITERAL(16, 198, 10), // "setGraphBG"
QT_MOC_LITERAL(17, 209, 5), // "value"
QT_MOC_LITERAL(18, 215, 10), // "setGraphFG"
QT_MOC_LITERAL(19, 226, 13), // "setGraphGridY"
QT_MOC_LITERAL(20, 240, 13), // "setGraphGridX"
QT_MOC_LITERAL(21, 254, 12), // "setGraphGaze"
QT_MOC_LITERAL(22, 267, 16), // "setGraphStimulus"
QT_MOC_LITERAL(23, 284, 8) // "setGuiBG"

    },
    "colorScheme\0graphBgChanged\0\0graphFgChanged\0"
    "graphGridYChanged\0graphGridXChanged\0"
    "graphGazeChanged\0graphStimulusChanged\0"
    "guiBgChanged\0graphBG\0graphFG\0graphGridY\0"
    "graphGridX\0graphGaze\0graphStimulus\0"
    "guiBG\0setGraphBG\0value\0setGraphFG\0"
    "setGraphGridY\0setGraphGridX\0setGraphGaze\0"
    "setGraphStimulus\0setGuiBG"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_colorScheme[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       7,  154, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,
       3,    0,  120,    2, 0x06 /* Public */,
       4,    0,  121,    2, 0x06 /* Public */,
       5,    0,  122,    2, 0x06 /* Public */,
       6,    0,  123,    2, 0x06 /* Public */,
       7,    0,  124,    2, 0x06 /* Public */,
       8,    0,  125,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  126,    2, 0x0a /* Public */,
      10,    0,  127,    2, 0x0a /* Public */,
      11,    0,  128,    2, 0x0a /* Public */,
      12,    0,  129,    2, 0x0a /* Public */,
      13,    0,  130,    2, 0x0a /* Public */,
      14,    0,  131,    2, 0x0a /* Public */,
      15,    0,  132,    2, 0x0a /* Public */,
      16,    1,  133,    2, 0x0a /* Public */,
      18,    1,  136,    2, 0x0a /* Public */,
      19,    1,  139,    2, 0x0a /* Public */,
      20,    1,  142,    2, 0x0a /* Public */,
      21,    1,  145,    2, 0x0a /* Public */,
      22,    1,  148,    2, 0x0a /* Public */,
      23,    1,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::QColor,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::QColor,   17,

 // properties: name, type, flags
      15, QMetaType::QColor, 0x00495103,
       9, QMetaType::QColor, 0x00495103,
      10, QMetaType::QColor, 0x00495103,
      11, QMetaType::QColor, 0x00495103,
      12, QMetaType::QColor, 0x00495103,
      13, QMetaType::QColor, 0x00495103,
      14, QMetaType::QColor, 0x00495103,

 // properties: notify_signal_id
       6,
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

void colorScheme::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        colorScheme *_t = static_cast<colorScheme *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->graphBgChanged(); break;
        case 1: _t->graphFgChanged(); break;
        case 2: _t->graphGridYChanged(); break;
        case 3: _t->graphGridXChanged(); break;
        case 4: _t->graphGazeChanged(); break;
        case 5: _t->graphStimulusChanged(); break;
        case 6: _t->guiBgChanged(); break;
        case 7: { QColor _r = _t->graphBG();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 8: { QColor _r = _t->graphFG();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 9: { QColor _r = _t->graphGridY();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 10: { QColor _r = _t->graphGridX();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 11: { QColor _r = _t->graphGaze();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 12: { QColor _r = _t->graphStimulus();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 13: { QColor _r = _t->guiBG();
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 14: _t->setGraphBG((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 15: _t->setGraphFG((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 16: _t->setGraphGridY((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 17: _t->setGraphGridX((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 18: _t->setGraphGaze((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 19: _t->setGraphStimulus((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 20: _t->setGuiBG((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphBgChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphFgChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphGridYChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphGridXChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphGazeChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::graphStimulusChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (colorScheme::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&colorScheme::guiBgChanged)) {
                *result = 6;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        colorScheme *_t = static_cast<colorScheme *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->guiBG(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->graphBG(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->graphFG(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->graphGridY(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->graphGridX(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->graphGaze(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->graphStimulus(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        colorScheme *_t = static_cast<colorScheme *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGuiBG(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setGraphBG(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setGraphFG(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setGraphGridY(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setGraphGridX(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setGraphGaze(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setGraphStimulus(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject colorScheme::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_colorScheme.data,
      qt_meta_data_colorScheme,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *colorScheme::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *colorScheme::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_colorScheme.stringdata0))
        return static_cast<void*>(const_cast< colorScheme*>(this));
    return QObject::qt_metacast(_clname);
}

int colorScheme::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void colorScheme::graphBgChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void colorScheme::graphFgChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void colorScheme::graphGridYChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void colorScheme::graphGridXChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void colorScheme::graphGazeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void colorScheme::graphStimulusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void colorScheme::guiBgChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
struct qt_meta_stringdata_OVersions_t {
    QByteArrayData data[5];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OVersions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OVersions_t qt_meta_stringdata_OVersions = {
    {
QT_MOC_LITERAL(0, 0, 9), // "OVersions"
QT_MOC_LITERAL(1, 10, 7), // "tracker"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "oscann"
QT_MOC_LITERAL(4, 26, 8) // "analizer"

    },
    "OVersions\0tracker\0\0oscann\0analizer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OVersions[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095401,
       3, QMetaType::QString, 0x00095401,
       4, QMetaType::QString, 0x00095401,

       0        // eod
};

void OVersions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OVersions *_t = static_cast<OVersions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->tracker();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->oscann();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->analizer();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        OVersions *_t = static_cast<OVersions *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->tracker(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->oscann(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->analizer(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject OVersions::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OVersions.data,
      qt_meta_data_OVersions,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OVersions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OVersions::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OVersions.stringdata0))
        return static_cast<void*>(const_cast< OVersions*>(this));
    return QObject::qt_metacast(_clname);
}

int OVersions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_OCTSettings_t {
    QByteArrayData data[70];
    char stringdata0[978];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OCTSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OCTSettings_t qt_meta_stringdata_OCTSettings = {
    {
QT_MOC_LITERAL(0, 0, 11), // "OCTSettings"
QT_MOC_LITERAL(1, 12, 23), // "clbRecordingTimeChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "newValue"
QT_MOC_LITERAL(4, 46, 23), // "tstRecordingTimeChanged"
QT_MOC_LITERAL(5, 70, 19), // "stimulusSizeChanged"
QT_MOC_LITERAL(6, 90, 21), // "fixedPointSizeChanged"
QT_MOC_LITERAL(7, 112, 11), // "lapsChanged"
QT_MOC_LITERAL(8, 124, 12), // "timesChanged"
QT_MOC_LITERAL(9, 137, 15), // "testTimeChanged"
QT_MOC_LITERAL(10, 153, 15), // "img1PathChanged"
QT_MOC_LITERAL(11, 169, 15), // "img2PathChanged"
QT_MOC_LITERAL(12, 185, 15), // "img3PathChanged"
QT_MOC_LITERAL(13, 201, 15), // "img4PathChanged"
QT_MOC_LITERAL(14, 217, 15), // "img5PathChanged"
QT_MOC_LITERAL(15, 233, 15), // "img6PathChanged"
QT_MOC_LITERAL(16, 249, 15), // "img7PathChanged"
QT_MOC_LITERAL(17, 265, 15), // "img8PathChanged"
QT_MOC_LITERAL(18, 281, 15), // "img9PathChanged"
QT_MOC_LITERAL(19, 297, 16), // "img10PathChanged"
QT_MOC_LITERAL(20, 314, 17), // "degrees2pxChanged"
QT_MOC_LITERAL(21, 332, 18), // "screenWidthChanged"
QT_MOC_LITERAL(22, 351, 21), // "screenDistanceChanged"
QT_MOC_LITERAL(23, 373, 17), // "resolutionChanged"
QT_MOC_LITERAL(24, 391, 16), // "clbRecordingTime"
QT_MOC_LITERAL(25, 408, 16), // "tstRecordingTime"
QT_MOC_LITERAL(26, 425, 12), // "stimulusSize"
QT_MOC_LITERAL(27, 438, 14), // "fixedPointSize"
QT_MOC_LITERAL(28, 453, 4), // "laps"
QT_MOC_LITERAL(29, 458, 8), // "testTime"
QT_MOC_LITERAL(30, 467, 8), // "img1Path"
QT_MOC_LITERAL(31, 476, 8), // "img2Path"
QT_MOC_LITERAL(32, 485, 8), // "img3Path"
QT_MOC_LITERAL(33, 494, 8), // "img4Path"
QT_MOC_LITERAL(34, 503, 8), // "img5Path"
QT_MOC_LITERAL(35, 512, 8), // "img6Path"
QT_MOC_LITERAL(36, 521, 8), // "img7Path"
QT_MOC_LITERAL(37, 530, 8), // "img8Path"
QT_MOC_LITERAL(38, 539, 8), // "img9Path"
QT_MOC_LITERAL(39, 548, 9), // "img10Path"
QT_MOC_LITERAL(40, 558, 8), // "mongoUrl"
QT_MOC_LITERAL(41, 567, 9), // "mongoPort"
QT_MOC_LITERAL(42, 577, 11), // "mainDisplay"
QT_MOC_LITERAL(43, 589, 10), // "degrees2px"
QT_MOC_LITERAL(44, 600, 14), // "screenDistance"
QT_MOC_LITERAL(45, 615, 11), // "screenWidth"
QT_MOC_LITERAL(46, 627, 10), // "resolution"
QT_MOC_LITERAL(47, 638, 19), // "setClbRecordingTime"
QT_MOC_LITERAL(48, 658, 19), // "setTstRecordingTime"
QT_MOC_LITERAL(49, 678, 20), // "saveClbRecordingTime"
QT_MOC_LITERAL(50, 699, 20), // "saveTstRecordingTime"
QT_MOC_LITERAL(51, 720, 21), // "setUtilsProcessScreen"
QT_MOC_LITERAL(52, 742, 15), // "setStimulusSize"
QT_MOC_LITERAL(53, 758, 17), // "setFixedPointSize"
QT_MOC_LITERAL(54, 776, 7), // "setLaps"
QT_MOC_LITERAL(55, 784, 11), // "setTestTime"
QT_MOC_LITERAL(56, 796, 11), // "setImg1Path"
QT_MOC_LITERAL(57, 808, 11), // "setImg2Path"
QT_MOC_LITERAL(58, 820, 11), // "setImg3Path"
QT_MOC_LITERAL(59, 832, 11), // "setImg4Path"
QT_MOC_LITERAL(60, 844, 11), // "setImg5Path"
QT_MOC_LITERAL(61, 856, 11), // "setImg6Path"
QT_MOC_LITERAL(62, 868, 11), // "setImg7Path"
QT_MOC_LITERAL(63, 880, 11), // "setImg8Path"
QT_MOC_LITERAL(64, 892, 11), // "setImg9Path"
QT_MOC_LITERAL(65, 904, 12), // "setImg10Path"
QT_MOC_LITERAL(66, 917, 13), // "setdegrees2px"
QT_MOC_LITERAL(67, 931, 17), // "setScreenDistance"
QT_MOC_LITERAL(68, 949, 14), // "setScreenWidth"
QT_MOC_LITERAL(69, 964, 13) // "setResolution"

    },
    "OCTSettings\0clbRecordingTimeChanged\0"
    "\0newValue\0tstRecordingTimeChanged\0"
    "stimulusSizeChanged\0fixedPointSizeChanged\0"
    "lapsChanged\0timesChanged\0testTimeChanged\0"
    "img1PathChanged\0img2PathChanged\0"
    "img3PathChanged\0img4PathChanged\0"
    "img5PathChanged\0img6PathChanged\0"
    "img7PathChanged\0img8PathChanged\0"
    "img9PathChanged\0img10PathChanged\0"
    "degrees2pxChanged\0screenWidthChanged\0"
    "screenDistanceChanged\0resolutionChanged\0"
    "clbRecordingTime\0tstRecordingTime\0"
    "stimulusSize\0fixedPointSize\0laps\0"
    "testTime\0img1Path\0img2Path\0img3Path\0"
    "img4Path\0img5Path\0img6Path\0img7Path\0"
    "img8Path\0img9Path\0img10Path\0mongoUrl\0"
    "mongoPort\0mainDisplay\0degrees2px\0"
    "screenDistance\0screenWidth\0resolution\0"
    "setClbRecordingTime\0setTstRecordingTime\0"
    "saveClbRecordingTime\0saveTstRecordingTime\0"
    "setUtilsProcessScreen\0setStimulusSize\0"
    "setFixedPointSize\0setLaps\0setTestTime\0"
    "setImg1Path\0setImg2Path\0setImg3Path\0"
    "setImg4Path\0setImg5Path\0setImg6Path\0"
    "setImg7Path\0setImg8Path\0setImg9Path\0"
    "setImg10Path\0setdegrees2px\0setScreenDistance\0"
    "setScreenWidth\0setResolution"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OCTSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      67,   14, // methods
      23,  498, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  349,    2, 0x06 /* Public */,
       4,    1,  352,    2, 0x06 /* Public */,
       5,    1,  355,    2, 0x06 /* Public */,
       6,    1,  358,    2, 0x06 /* Public */,
       7,    1,  361,    2, 0x06 /* Public */,
       8,    1,  364,    2, 0x06 /* Public */,
       9,    1,  367,    2, 0x06 /* Public */,
      10,    1,  370,    2, 0x06 /* Public */,
      11,    1,  373,    2, 0x06 /* Public */,
      12,    1,  376,    2, 0x06 /* Public */,
      13,    1,  379,    2, 0x06 /* Public */,
      14,    1,  382,    2, 0x06 /* Public */,
      15,    1,  385,    2, 0x06 /* Public */,
      16,    1,  388,    2, 0x06 /* Public */,
      17,    1,  391,    2, 0x06 /* Public */,
      18,    1,  394,    2, 0x06 /* Public */,
      19,    1,  397,    2, 0x06 /* Public */,
      20,    1,  400,    2, 0x06 /* Public */,
      21,    1,  403,    2, 0x06 /* Public */,
      22,    1,  406,    2, 0x06 /* Public */,
      23,    1,  409,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    0,  412,    2, 0x0a /* Public */,
      25,    0,  413,    2, 0x0a /* Public */,
      26,    0,  414,    2, 0x0a /* Public */,
      27,    0,  415,    2, 0x0a /* Public */,
      28,    0,  416,    2, 0x0a /* Public */,
      29,    0,  417,    2, 0x0a /* Public */,
      30,    0,  418,    2, 0x0a /* Public */,
      31,    0,  419,    2, 0x0a /* Public */,
      32,    0,  420,    2, 0x0a /* Public */,
      33,    0,  421,    2, 0x0a /* Public */,
      34,    0,  422,    2, 0x0a /* Public */,
      35,    0,  423,    2, 0x0a /* Public */,
      36,    0,  424,    2, 0x0a /* Public */,
      37,    0,  425,    2, 0x0a /* Public */,
      38,    0,  426,    2, 0x0a /* Public */,
      39,    0,  427,    2, 0x0a /* Public */,
      40,    0,  428,    2, 0x0a /* Public */,
      41,    0,  429,    2, 0x0a /* Public */,
      42,    0,  430,    2, 0x0a /* Public */,
      43,    0,  431,    2, 0x0a /* Public */,
      44,    0,  432,    2, 0x0a /* Public */,
      45,    0,  433,    2, 0x0a /* Public */,
      46,    0,  434,    2, 0x0a /* Public */,
      47,    1,  435,    2, 0x0a /* Public */,
      48,    1,  438,    2, 0x0a /* Public */,
      49,    0,  441,    2, 0x0a /* Public */,
      50,    0,  442,    2, 0x0a /* Public */,
      51,    0,  443,    2, 0x0a /* Public */,
      52,    1,  444,    2, 0x0a /* Public */,
      53,    1,  447,    2, 0x0a /* Public */,
      54,    1,  450,    2, 0x0a /* Public */,
      55,    1,  453,    2, 0x0a /* Public */,
      56,    1,  456,    2, 0x0a /* Public */,
      57,    1,  459,    2, 0x0a /* Public */,
      58,    1,  462,    2, 0x0a /* Public */,
      59,    1,  465,    2, 0x0a /* Public */,
      60,    1,  468,    2, 0x0a /* Public */,
      61,    1,  471,    2, 0x0a /* Public */,
      62,    1,  474,    2, 0x0a /* Public */,
      63,    1,  477,    2, 0x0a /* Public */,
      64,    1,  480,    2, 0x0a /* Public */,
      65,    1,  483,    2, 0x0a /* Public */,
      66,    1,  486,    2, 0x0a /* Public */,
      67,    1,  489,    2, 0x0a /* Public */,
      68,    1,  492,    2, 0x0a /* Public */,
      69,    1,  495,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::UInt,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Double,
    QMetaType::Double,
    QMetaType::QPoint,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QPoint,    3,

 // properties: name, type, flags
      24, QMetaType::Int, 0x00495103,
      25, QMetaType::Int, 0x00495103,
      26, QMetaType::Int, 0x00495103,
      27, QMetaType::Int, 0x00495103,
      28, QMetaType::Int, 0x00495103,
      29, QMetaType::Int, 0x00495103,
      43, QMetaType::Float, 0x00495003,
      44, QMetaType::Double, 0x00495103,
      45, QMetaType::Double, 0x00495103,
      46, QMetaType::QPoint, 0x00495103,
      30, QMetaType::QString, 0x00495103,
      31, QMetaType::QString, 0x00495103,
      32, QMetaType::QString, 0x00495103,
      33, QMetaType::QString, 0x00495103,
      34, QMetaType::QString, 0x00495103,
      35, QMetaType::QString, 0x00495103,
      36, QMetaType::QString, 0x00495103,
      37, QMetaType::QString, 0x00495103,
      38, QMetaType::QString, 0x00495103,
      39, QMetaType::QString, 0x00495103,
      40, QMetaType::QString, 0x00095401,
      41, QMetaType::Int, 0x00095401,
      42, QMetaType::UInt, 0x00095401,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       6,
      17,
      19,
      18,
      20,
       7,
       8,
       9,
      10,
      11,
      12,
      13,
      14,
      15,
      16,
       0,
       0,
       0,

       0        // eod
};

void OCTSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OCTSettings *_t = static_cast<OCTSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clbRecordingTimeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->tstRecordingTimeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->stimulusSizeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->fixedPointSizeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->lapsChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->timesChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->testTimeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: _t->img1PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 8: _t->img2PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 9: _t->img3PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 10: _t->img4PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: _t->img5PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 12: _t->img6PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->img7PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: _t->img8PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 15: _t->img9PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 16: _t->img10PathChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 17: _t->degrees2pxChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 18: _t->screenWidthChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 19: _t->screenDistanceChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 20: _t->resolutionChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 21: { int _r = _t->clbRecordingTime();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 22: { int _r = _t->tstRecordingTime();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: { int _r = _t->stimulusSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 24: { int _r = _t->fixedPointSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { int _r = _t->laps();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 26: { int _r = _t->testTime();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 27: { QString _r = _t->img1Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 28: { QString _r = _t->img2Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 29: { QString _r = _t->img3Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 30: { QString _r = _t->img4Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 31: { QString _r = _t->img5Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 32: { QString _r = _t->img6Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 33: { QString _r = _t->img7Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 34: { QString _r = _t->img8Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 35: { QString _r = _t->img9Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 36: { QString _r = _t->img10Path();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 37: { QString _r = _t->mongoUrl();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 38: { uint _r = _t->mongoPort();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = _r; }  break;
        case 39: { int _r = _t->mainDisplay();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 40: { float _r = _t->degrees2px();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 41: { double _r = _t->screenDistance();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 42: { double _r = _t->screenWidth();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 43: { QPoint _r = _t->resolution();
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = _r; }  break;
        case 44: _t->setClbRecordingTime((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 45: _t->setTstRecordingTime((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 46: _t->saveClbRecordingTime(); break;
        case 47: _t->saveTstRecordingTime(); break;
        case 48: _t->setUtilsProcessScreen(); break;
        case 49: _t->setStimulusSize((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 50: _t->setFixedPointSize((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 51: _t->setLaps((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 52: _t->setTestTime((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 53: _t->setImg1Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 54: _t->setImg2Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 55: _t->setImg3Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 56: _t->setImg4Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 57: _t->setImg5Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 58: _t->setImg6Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 59: _t->setImg7Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 60: _t->setImg8Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 61: _t->setImg9Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 62: _t->setImg10Path((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 63: _t->setdegrees2px((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 64: _t->setScreenDistance((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 65: _t->setScreenWidth((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 66: _t->setResolution((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::clbRecordingTimeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::tstRecordingTimeChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::stimulusSizeChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::fixedPointSizeChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::lapsChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::timesChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::testTimeChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img1PathChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img2PathChanged)) {
                *result = 8;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img3PathChanged)) {
                *result = 9;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img4PathChanged)) {
                *result = 10;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img5PathChanged)) {
                *result = 11;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img6PathChanged)) {
                *result = 12;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img7PathChanged)) {
                *result = 13;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img8PathChanged)) {
                *result = 14;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img9PathChanged)) {
                *result = 15;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::img10PathChanged)) {
                *result = 16;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::degrees2pxChanged)) {
                *result = 17;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::screenWidthChanged)) {
                *result = 18;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::screenDistanceChanged)) {
                *result = 19;
            }
        }
        {
            typedef void (OCTSettings::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OCTSettings::resolutionChanged)) {
                *result = 20;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        OCTSettings *_t = static_cast<OCTSettings *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->clbRecordingTime(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->tstRecordingTime(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->stimulusSize(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->fixedPointSize(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->laps(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->testTime(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->degrees2px(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->screenDistance(); break;
        case 8: *reinterpret_cast< double*>(_v) = _t->screenWidth(); break;
        case 9: *reinterpret_cast< QPoint*>(_v) = _t->resolution(); break;
        case 10: *reinterpret_cast< QString*>(_v) = _t->img1Path(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->img2Path(); break;
        case 12: *reinterpret_cast< QString*>(_v) = _t->img3Path(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->img4Path(); break;
        case 14: *reinterpret_cast< QString*>(_v) = _t->img5Path(); break;
        case 15: *reinterpret_cast< QString*>(_v) = _t->img6Path(); break;
        case 16: *reinterpret_cast< QString*>(_v) = _t->img7Path(); break;
        case 17: *reinterpret_cast< QString*>(_v) = _t->img8Path(); break;
        case 18: *reinterpret_cast< QString*>(_v) = _t->img9Path(); break;
        case 19: *reinterpret_cast< QString*>(_v) = _t->img10Path(); break;
        case 20: *reinterpret_cast< QString*>(_v) = _t->m_mongoUrl; break;
        case 21: *reinterpret_cast< int*>(_v) = _t->m_mongoPort; break;
        case 22: *reinterpret_cast< uint*>(_v) = _t->m_mainDisplay; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        OCTSettings *_t = static_cast<OCTSettings *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setClbRecordingTime(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setTstRecordingTime(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setStimulusSize(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setFixedPointSize(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setLaps(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setTestTime(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setdegrees2px(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setScreenDistance(*reinterpret_cast< double*>(_v)); break;
        case 8: _t->setScreenWidth(*reinterpret_cast< double*>(_v)); break;
        case 9: _t->setResolution(*reinterpret_cast< QPoint*>(_v)); break;
        case 10: _t->setImg1Path(*reinterpret_cast< QString*>(_v)); break;
        case 11: _t->setImg2Path(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setImg3Path(*reinterpret_cast< QString*>(_v)); break;
        case 13: _t->setImg4Path(*reinterpret_cast< QString*>(_v)); break;
        case 14: _t->setImg5Path(*reinterpret_cast< QString*>(_v)); break;
        case 15: _t->setImg6Path(*reinterpret_cast< QString*>(_v)); break;
        case 16: _t->setImg7Path(*reinterpret_cast< QString*>(_v)); break;
        case 17: _t->setImg8Path(*reinterpret_cast< QString*>(_v)); break;
        case 18: _t->setImg9Path(*reinterpret_cast< QString*>(_v)); break;
        case 19: _t->setImg10Path(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject OCTSettings::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OCTSettings.data,
      qt_meta_data_OCTSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OCTSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OCTSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OCTSettings.stringdata0))
        return static_cast<void*>(const_cast< OCTSettings*>(this));
    return QObject::qt_metacast(_clname);
}

int OCTSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 67)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 67;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 67)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 67;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 23;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 23;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OCTSettings::clbRecordingTimeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OCTSettings::tstRecordingTimeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OCTSettings::stimulusSizeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OCTSettings::fixedPointSizeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OCTSettings::lapsChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OCTSettings::timesChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OCTSettings::testTimeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void OCTSettings::img1PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void OCTSettings::img2PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void OCTSettings::img3PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void OCTSettings::img4PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void OCTSettings::img5PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void OCTSettings::img6PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void OCTSettings::img7PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void OCTSettings::img8PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void OCTSettings::img9PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void OCTSettings::img10PathChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void OCTSettings::degrees2pxChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void OCTSettings::screenWidthChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void OCTSettings::screenDistanceChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void OCTSettings::resolutionChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}
struct qt_meta_stringdata_OTemporalValues_t {
    QByteArrayData data[21];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OTemporalValues_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OTemporalValues_t qt_meta_stringdata_OTemporalValues = {
    {
QT_MOC_LITERAL(0, 0, 15), // "OTemporalValues"
QT_MOC_LITERAL(1, 16, 15), // "testTypeChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "newValue"
QT_MOC_LITERAL(4, 42, 15), // "taskTypeChanged"
QT_MOC_LITERAL(5, 58, 22), // "testDisplayModeChanged"
QT_MOC_LITERAL(6, 81, 18), // "testVariantChanged"
QT_MOC_LITERAL(7, 100, 16), // "clbPointsChanged"
QT_MOC_LITERAL(8, 117, 8), // "testType"
QT_MOC_LITERAL(9, 126, 8), // "taskType"
QT_MOC_LITERAL(10, 135, 15), // "testDisplayMode"
QT_MOC_LITERAL(11, 151, 11), // "testVariant"
QT_MOC_LITERAL(12, 163, 9), // "clbPoints"
QT_MOC_LITERAL(13, 173, 11), // "setTestType"
QT_MOC_LITERAL(14, 185, 5), // "value"
QT_MOC_LITERAL(15, 191, 11), // "setTaskType"
QT_MOC_LITERAL(16, 203, 18), // "setTestDisplayMode"
QT_MOC_LITERAL(17, 222, 14), // "setTestVariant"
QT_MOC_LITERAL(18, 237, 12), // "setClbPoints"
QT_MOC_LITERAL(19, 250, 14), // "picturesFolder"
QT_MOC_LITERAL(20, 265, 8) // "geometry"

    },
    "OTemporalValues\0testTypeChanged\0\0"
    "newValue\0taskTypeChanged\0"
    "testDisplayModeChanged\0testVariantChanged\0"
    "clbPointsChanged\0testType\0taskType\0"
    "testDisplayMode\0testVariant\0clbPoints\0"
    "setTestType\0value\0setTaskType\0"
    "setTestDisplayMode\0setTestVariant\0"
    "setClbPoints\0picturesFolder\0geometry"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OTemporalValues[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       7,  124, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       5,    1,   95,    2, 0x06 /* Public */,
       6,    1,   98,    2, 0x06 /* Public */,
       7,    1,  101,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  104,    2, 0x0a /* Public */,
       9,    0,  105,    2, 0x0a /* Public */,
      10,    0,  106,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    1,  109,    2, 0x0a /* Public */,
      15,    1,  112,    2, 0x0a /* Public */,
      16,    1,  115,    2, 0x0a /* Public */,
      17,    1,  118,    2, 0x0a /* Public */,
      18,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,

 // properties: name, type, flags
       8, QMetaType::Int, 0x00495103,
       9, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00495103,
      11, QMetaType::Int, 0x00495103,
      12, QMetaType::Int, 0x00495103,
      19, QMetaType::QUrl, 0x00095401,
      20, QMetaType::QRect, 0x00095401,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       0,
       0,

       0        // eod
};

void OTemporalValues::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OTemporalValues *_t = static_cast<OTemporalValues *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testTypeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->taskTypeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->testDisplayModeChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 3: _t->testVariantChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->clbPointsChanged((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: { int _r = _t->testType();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->taskType();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: { int _r = _t->testDisplayMode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = _t->testVariant();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { int _r = _t->clbPoints();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: _t->setTestType((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 11: _t->setTaskType((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 12: _t->setTestDisplayMode((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 13: _t->setTestVariant((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 14: _t->setClbPoints((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OTemporalValues::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTemporalValues::testTypeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (OTemporalValues::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTemporalValues::taskTypeChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (OTemporalValues::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTemporalValues::testDisplayModeChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (OTemporalValues::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTemporalValues::testVariantChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (OTemporalValues::*_t)(const int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OTemporalValues::clbPointsChanged)) {
                *result = 4;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        OTemporalValues *_t = static_cast<OTemporalValues *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->testType(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->taskType(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->testDisplayMode(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->testVariant(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->clbPoints(); break;
        case 5: *reinterpret_cast< QUrl*>(_v) = _t->m_picturesFolder; break;
        case 6: *reinterpret_cast< QRect*>(_v) = _t->m_geometry; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        OTemporalValues *_t = static_cast<OTemporalValues *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTestType(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setTaskType(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setTestDisplayMode(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setTestVariant(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setClbPoints(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject OTemporalValues::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OTemporalValues.data,
      qt_meta_data_OTemporalValues,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OTemporalValues::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OTemporalValues::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OTemporalValues.stringdata0))
        return static_cast<void*>(const_cast< OTemporalValues*>(this));
    return QObject::qt_metacast(_clname);
}

int OTemporalValues::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OTemporalValues::testTypeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OTemporalValues::taskTypeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OTemporalValues::testDisplayModeChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OTemporalValues::testVariantChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OTemporalValues::clbPointsChanged(const int & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_oscannCursorWrapper_t {
    QByteArrayData data[13];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_oscannCursorWrapper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_oscannCursorWrapper_t qt_meta_stringdata_oscannCursorWrapper = {
    {
QT_MOC_LITERAL(0, 0, 19), // "oscannCursorWrapper"
QT_MOC_LITERAL(1, 20, 10), // "hideCursor"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "openHandCursor"
QT_MOC_LITERAL(4, 47, 15), // "closeHandCursor"
QT_MOC_LITERAL(5, 63, 11), // "sizeHCursor"
QT_MOC_LITERAL(6, 75, 11), // "sizeVCursor"
QT_MOC_LITERAL(7, 87, 13), // "restoreCursor"
QT_MOC_LITERAL(8, 101, 11), // "arrowCursor"
QT_MOC_LITERAL(9, 113, 13), // "sizeVerCursor"
QT_MOC_LITERAL(10, 127, 13), // "sizeHorCursor"
QT_MOC_LITERAL(11, 141, 15), // "sizeBDiagCursor"
QT_MOC_LITERAL(12, 157, 15) // "sizeFDiagCursor"

    },
    "oscannCursorWrapper\0hideCursor\0\0"
    "openHandCursor\0closeHandCursor\0"
    "sizeHCursor\0sizeVCursor\0restoreCursor\0"
    "arrowCursor\0sizeVerCursor\0sizeHorCursor\0"
    "sizeBDiagCursor\0sizeFDiagCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_oscannCursorWrapper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,

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

       0        // eod
};

void oscannCursorWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        oscannCursorWrapper *_t = static_cast<oscannCursorWrapper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hideCursor(); break;
        case 1: _t->openHandCursor(); break;
        case 2: _t->closeHandCursor(); break;
        case 3: _t->sizeHCursor(); break;
        case 4: _t->sizeVCursor(); break;
        case 5: _t->restoreCursor(); break;
        case 6: _t->arrowCursor(); break;
        case 7: _t->sizeVerCursor(); break;
        case 8: _t->sizeHorCursor(); break;
        case 9: _t->sizeBDiagCursor(); break;
        case 10: _t->sizeFDiagCursor(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject oscannCursorWrapper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_oscannCursorWrapper.data,
      qt_meta_data_oscannCursorWrapper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *oscannCursorWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *oscannCursorWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_oscannCursorWrapper.stringdata0))
        return static_cast<void*>(const_cast< oscannCursorWrapper*>(this));
    return QObject::qt_metacast(_clname);
}

int oscannCursorWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
