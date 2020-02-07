/****************************************************************************
** Meta object code from reading C++ file 'oscannplot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "oscannplot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oscannplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OscannPlot_t {
    QByteArrayData data[84];
    char stringdata0[882];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OscannPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OscannPlot_t qt_meta_stringdata_OscannPlot = {
    {
QT_MOC_LITERAL(0, 0, 10), // "OscannPlot"
QT_MOC_LITERAL(1, 11, 11), // "zoomChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "zoomMode"
QT_MOC_LITERAL(4, 33, 12), // "beginProcess"
QT_MOC_LITERAL(5, 46, 9), // "processed"
QT_MOC_LITERAL(6, 56, 7), // "percent"
QT_MOC_LITERAL(7, 64, 7), // "autoPic"
QT_MOC_LITERAL(8, 72, 6), // "autoOK"
QT_MOC_LITERAL(9, 79, 7), // "newText"
QT_MOC_LITERAL(10, 87, 6), // "enable"
QT_MOC_LITERAL(11, 94, 8), // "showMenu"
QT_MOC_LITERAL(12, 103, 4), // "type"
QT_MOC_LITERAL(13, 108, 13), // "saccadeStatus"
QT_MOC_LITERAL(14, 122, 13), // "latencyStatus"
QT_MOC_LITERAL(15, 136, 12), // "steadyStatus"
QT_MOC_LITERAL(16, 149, 20), // "clbScatterAbleChange"
QT_MOC_LITERAL(17, 170, 17), // "sessionNameChange"
QT_MOC_LITERAL(18, 188, 14), // "onCustomReplot"
QT_MOC_LITERAL(19, 203, 20), // "updateCustomPlotSize"
QT_MOC_LITERAL(20, 224, 10), // "moveMeSlot"
QT_MOC_LITERAL(21, 235, 2), // "id"
QT_MOC_LITERAL(22, 238, 3), // "pos"
QT_MOC_LITERAL(23, 242, 6), // "mouseX"
QT_MOC_LITERAL(24, 249, 14), // "dotCatchedSlot"
QT_MOC_LITERAL(25, 264, 15), // "dotReleasedSlot"
QT_MOC_LITERAL(26, 280, 18), // "overSomeTracerSlot"
QT_MOC_LITERAL(27, 299, 11), // "pupilAtSlot"
QT_MOC_LITERAL(28, 311, 1), // "x"
QT_MOC_LITERAL(29, 313, 1), // "y"
QT_MOC_LITERAL(30, 315, 2), // "sx"
QT_MOC_LITERAL(31, 318, 2), // "sy"
QT_MOC_LITERAL(32, 321, 11), // "scatterSlot"
QT_MOC_LITERAL(33, 333, 5), // "index"
QT_MOC_LITERAL(34, 339, 4), // "init"
QT_MOC_LITERAL(35, 344, 9), // "resetPlot"
QT_MOC_LITERAL(36, 354, 10), // "updateData"
QT_MOC_LITERAL(37, 365, 7), // "setData"
QT_MOC_LITERAL(38, 373, 6), // "OData*"
QT_MOC_LITERAL(39, 380, 4), // "data"
QT_MOC_LITERAL(40, 385, 7), // "loadCsv"
QT_MOC_LITERAL(41, 393, 7), // "csvPath"
QT_MOC_LITERAL(42, 401, 11), // "checkScreen"
QT_MOC_LITERAL(43, 413, 12), // "calibScatter"
QT_MOC_LITERAL(44, 426, 7), // "getType"
QT_MOC_LITERAL(45, 434, 9), // "getDeg2Px"
QT_MOC_LITERAL(46, 444, 13), // "getCustomPlot"
QT_MOC_LITERAL(47, 458, 12), // "QCustomPlot*"
QT_MOC_LITERAL(48, 471, 14), // "openInExplorer"
QT_MOC_LITERAL(49, 486, 9), // "autoScale"
QT_MOC_LITERAL(50, 496, 5), // "autom"
QT_MOC_LITERAL(51, 502, 11), // "changeColor"
QT_MOC_LITERAL(52, 514, 9), // "setScreen"
QT_MOC_LITERAL(53, 524, 12), // "loadDistance"
QT_MOC_LITERAL(54, 537, 9), // "loadWidth"
QT_MOC_LITERAL(55, 547, 9), // "changeRaw"
QT_MOC_LITERAL(56, 557, 13), // "removeVectors"
QT_MOC_LITERAL(57, 571, 8), // "clearAll"
QT_MOC_LITERAL(58, 580, 9), // "clearPlot"
QT_MOC_LITERAL(59, 590, 11), // "setZoomMode"
QT_MOC_LITERAL(60, 602, 9), // "picExists"
QT_MOC_LITERAL(61, 612, 4), // "path"
QT_MOC_LITERAL(62, 617, 8), // "savePlot"
QT_MOC_LITERAL(63, 626, 9), // "makeVideo"
QT_MOC_LITERAL(64, 636, 8), // "keyPress"
QT_MOC_LITERAL(65, 645, 10), // "keyRelease"
QT_MOC_LITERAL(66, 656, 12), // "capturePupil"
QT_MOC_LITERAL(67, 669, 9), // "fastCalib"
QT_MOC_LITERAL(68, 679, 7), // "tstPath"
QT_MOC_LITERAL(69, 687, 11), // "searchTests"
QT_MOC_LITERAL(70, 699, 10), // "folderPath"
QT_MOC_LITERAL(71, 710, 13), // "processFolder"
QT_MOC_LITERAL(72, 724, 10), // "processCsv"
QT_MOC_LITERAL(73, 735, 12), // "setLayoutDim"
QT_MOC_LITERAL(74, 748, 5), // "width"
QT_MOC_LITERAL(75, 754, 6), // "height"
QT_MOC_LITERAL(76, 761, 14), // "setCreatingPdf"
QT_MOC_LITERAL(77, 776, 5), // "value"
QT_MOC_LITERAL(78, 782, 21), // "updatePointerPosition"
QT_MOC_LITERAL(79, 804, 17), // "setVideoPreviewer"
QT_MOC_LITERAL(80, 822, 13), // "videoPreview*"
QT_MOC_LITERAL(81, 836, 18), // "isEmptySessionName"
QT_MOC_LITERAL(82, 855, 11), // "sessionName"
QT_MOC_LITERAL(83, 867, 14) // "clbScatterAble"

    },
    "OscannPlot\0zoomChanged\0\0zoomMode\0"
    "beginProcess\0processed\0percent\0autoPic\0"
    "autoOK\0newText\0enable\0showMenu\0type\0"
    "saccadeStatus\0latencyStatus\0steadyStatus\0"
    "clbScatterAbleChange\0sessionNameChange\0"
    "onCustomReplot\0updateCustomPlotSize\0"
    "moveMeSlot\0id\0pos\0mouseX\0dotCatchedSlot\0"
    "dotReleasedSlot\0overSomeTracerSlot\0"
    "pupilAtSlot\0x\0y\0sx\0sy\0scatterSlot\0"
    "index\0init\0resetPlot\0updateData\0setData\0"
    "OData*\0data\0loadCsv\0csvPath\0checkScreen\0"
    "calibScatter\0getType\0getDeg2Px\0"
    "getCustomPlot\0QCustomPlot*\0openInExplorer\0"
    "autoScale\0autom\0changeColor\0setScreen\0"
    "loadDistance\0loadWidth\0changeRaw\0"
    "removeVectors\0clearAll\0clearPlot\0"
    "setZoomMode\0picExists\0path\0savePlot\0"
    "makeVideo\0keyPress\0keyRelease\0"
    "capturePupil\0fastCalib\0tstPath\0"
    "searchTests\0folderPath\0processFolder\0"
    "processCsv\0setLayoutDim\0width\0height\0"
    "setCreatingPdf\0value\0updatePointerPosition\0"
    "setVideoPreviewer\0videoPreview*\0"
    "isEmptySessionName\0sessionName\0"
    "clbScatterAble"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OscannPlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      61,   14, // methods
       2,  542, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  319,    2, 0x06 /* Public */,
       4,    0,  322,    2, 0x06 /* Public */,
       5,    1,  323,    2, 0x06 /* Public */,
       7,    1,  326,    2, 0x06 /* Public */,
       9,    1,  329,    2, 0x06 /* Public */,
      11,    4,  332,    2, 0x06 /* Public */,
      16,    0,  341,    2, 0x06 /* Public */,
      17,    0,  342,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  343,    2, 0x08 /* Private */,
      19,    0,  344,    2, 0x08 /* Private */,
      20,    3,  345,    2, 0x08 /* Private */,
      24,    3,  352,    2, 0x08 /* Private */,
      25,    2,  359,    2, 0x08 /* Private */,
      26,    1,  364,    2, 0x08 /* Private */,
      27,    4,  367,    2, 0x0a /* Public */,
      32,    1,  376,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      34,    7,  379,    2, 0x02 /* Public */,
      34,    6,  394,    2, 0x22 /* Public | MethodCloned */,
      34,    5,  407,    2, 0x22 /* Public | MethodCloned */,
      34,    4,  418,    2, 0x22 /* Public | MethodCloned */,
      34,    3,  427,    2, 0x22 /* Public | MethodCloned */,
      34,    2,  434,    2, 0x22 /* Public | MethodCloned */,
      35,    0,  439,    2, 0x02 /* Public */,
      36,    0,  440,    2, 0x02 /* Public */,
      37,    1,  441,    2, 0x02 /* Public */,
      40,    1,  444,    2, 0x02 /* Public */,
      42,    0,  447,    2, 0x02 /* Public */,
      43,    0,  448,    2, 0x02 /* Public */,
      44,    0,  449,    2, 0x02 /* Public */,
      45,    0,  450,    2, 0x02 /* Public */,
      46,    0,  451,    2, 0x02 /* Public */,
      48,    0,  452,    2, 0x02 /* Public */,
      49,    2,  453,    2, 0x02 /* Public */,
      49,    1,  458,    2, 0x22 /* Public | MethodCloned */,
      49,    0,  461,    2, 0x22 /* Public | MethodCloned */,
      51,    0,  462,    2, 0x02 /* Public */,
      52,    1,  463,    2, 0x02 /* Public */,
      53,    1,  466,    2, 0x02 /* Public */,
      54,    1,  469,    2, 0x02 /* Public */,
      55,    1,  472,    2, 0x02 /* Public */,
      56,    0,  475,    2, 0x02 /* Public */,
      57,    0,  476,    2, 0x02 /* Public */,
      58,    0,  477,    2, 0x02 /* Public */,
      59,    1,  478,    2, 0x02 /* Public */,
      60,    1,  481,    2, 0x02 /* Public */,
      62,    4,  484,    2, 0x02 /* Public */,
      62,    3,  493,    2, 0x22 /* Public | MethodCloned */,
      62,    2,  500,    2, 0x22 /* Public | MethodCloned */,
      63,    1,  505,    2, 0x02 /* Public */,
      64,    1,  508,    2, 0x02 /* Public */,
      65,    1,  511,    2, 0x02 /* Public */,
      66,    0,  514,    2, 0x02 /* Public */,
      67,    1,  515,    2, 0x02 /* Public */,
      69,    1,  518,    2, 0x02 /* Public */,
      71,    1,  521,    2, 0x02 /* Public */,
      72,    1,  524,    2, 0x02 /* Public */,
      73,    2,  527,    2, 0x02 /* Public */,
      76,    1,  532,    2, 0x02 /* Public */,
      78,    1,  535,    2, 0x02 /* Public */,
      79,    1,  538,    2, 0x02 /* Public */,
      81,    0,  541,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   12,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   28,   29,   30,   31,
    QMetaType::Void, QMetaType::UInt,   33,

 // methods: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QColor, QMetaType::QColor,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QColor,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Bool, QMetaType::QString,   41,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Double,
    0x80000000 | 47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::UInt,   50,   33,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QPoint, QMetaType::QString,    2,
    QMetaType::Double, QMetaType::QString,    2,
    QMetaType::Double, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Bool, QMetaType::QString,   61,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QColor,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   68,
    QMetaType::QStringList, QMetaType::QString,   70,
    QMetaType::QStringList, QMetaType::QString,   70,
    QMetaType::QStringList, QMetaType::QString,   70,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Bool,   77,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, 0x80000000 | 80,    2,
    QMetaType::Bool,

 // properties: name, type, flags
      82, QMetaType::QString, 0x00495103,
      83, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       7,
       6,

       0        // eod
};

void OscannPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OscannPlot *_t = static_cast<OscannPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->zoomChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->beginProcess(); break;
        case 2: _t->processed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->autoPic((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->newText((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->showMenu((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 6: _t->clbScatterAbleChange(); break;
        case 7: _t->sessionNameChange(); break;
        case 8: _t->onCustomReplot(); break;
        case 9: _t->updateCustomPlotSize(); break;
        case 10: _t->moveMeSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->dotCatchedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->dotReleasedSlot((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->overSomeTracerSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->pupilAtSlot((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 15: _t->scatterSlot((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 16: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QColor(*)>(_a[6])),(*reinterpret_cast< QColor(*)>(_a[7]))); break;
        case 17: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QColor(*)>(_a[6]))); break;
        case 18: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 19: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 20: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 21: _t->init((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->resetPlot(); break;
        case 23: _t->updateData(); break;
        case 24: _t->setData((*reinterpret_cast< OData*(*)>(_a[1]))); break;
        case 25: { bool _r = _t->loadCsv((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->checkScreen();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->calibScatter(); break;
        case 28: { int _r = _t->getType();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: { double _r = _t->getDeg2Px();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 30: { QCustomPlot* _r = _t->getCustomPlot();
            if (_a[0]) *reinterpret_cast< QCustomPlot**>(_a[0]) = std::move(_r); }  break;
        case 31: _t->openInExplorer(); break;
        case 32: _t->autoScale((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 33: _t->autoScale((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->autoScale(); break;
        case 35: _t->changeColor(); break;
        case 36: { QPoint _r = _t->setScreen((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 37: { double _r = _t->loadDistance((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 38: { double _r = _t->loadWidth((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->changeRaw((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->removeVectors(); break;
        case 41: _t->clearAll(); break;
        case 42: _t->clearPlot(); break;
        case 43: _t->setZoomMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: { bool _r = _t->picExists((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 45: _t->savePlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QColor(*)>(_a[4]))); break;
        case 46: _t->savePlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 47: _t->savePlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->makeVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 49: _t->keyPress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->keyRelease((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->capturePupil(); break;
        case 52: { QString _r = _t->fastCalib((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 53: { QStringList _r = _t->searchTests((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 54: { QStringList _r = _t->processFolder((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 55: { QStringList _r = _t->processCsv((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 56: _t->setLayoutDim((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 57: _t->setCreatingPdf((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 58: _t->updatePointerPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->setVideoPreviewer((*reinterpret_cast< videoPreview*(*)>(_a[1]))); break;
        case 60: { bool _r = _t->isEmptySessionName();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< OData* >(); break;
            }
            break;
        case 59:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< videoPreview* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (OscannPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::zoomChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::beginProcess)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::processed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::autoPic)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::newText)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)(int , bool , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::showMenu)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::clbScatterAbleChange)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (OscannPlot::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OscannPlot::sessionNameChange)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        OscannPlot *_t = static_cast<OscannPlot *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->sessionName(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->clbScatterAble(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        OscannPlot *_t = static_cast<OscannPlot *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSessionName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setClbScatterAble(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject OscannPlot::staticMetaObject = {
    { &QQuickPaintedItem::staticMetaObject, qt_meta_stringdata_OscannPlot.data,
      qt_meta_data_OscannPlot,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OscannPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OscannPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OscannPlot.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int OscannPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 61)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 61;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 61)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 61;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void OscannPlot::zoomChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OscannPlot::beginProcess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OscannPlot::processed(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OscannPlot::autoPic(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OscannPlot::newText(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OscannPlot::showMenu(int _t1, bool _t2, bool _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OscannPlot::clbScatterAbleChange()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void OscannPlot::sessionNameChange()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
