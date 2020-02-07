#ifndef QUTILS_H
#define QUTILS_H

#include<QString>
#include <QStandardPaths>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QObject>
#include <QSettings>
#include <QDir>
#include <QUrl>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>


//OTimer
#include <chrono>
#include <thread>
#include <future>


#include "utilsprocess.h"



/*
TODO
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority)
    Q_ENUMS(Priority)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };

    MyClass(QObject *parent = 0);
    ~MyClass();

    void setPriority(Priority priority) { m_priority = priority; }
    Priority priority() const { return m_priority; }

private:
    Priority m_priority;
};


Q_CLASSINFO("Author", "Erik Hernández")
Q_CLASSINFO("Status", "Active")

//TODO(TIMER)
 OTimer or OscannTimer is intended to be a High Performance Timer
 * This was done because the behavior of QTimer was not appropiate specilly with low values. For example, 1 millisecond
 * The performance of OTimer using chrono will be better... Additional testing is needed
 * Interval could be specified in milliseconds, microseconds and nanoseconds.
 * IMPORTANT NOTE:
 * boost::asio: It is not an option because io_service runs a method that blocks the program and the UI
 *              The timer accuracy is suitable. For ten milliseconds aprox mean 10.070 std 0.02
 *
 *
 * */
class OTimer : public QObject{
    Q_OBJECT
    std::thread m_th;
    bool m_running = false;
    std::chrono::microseconds m_interval;
public:
    OTimer(QObject *parent) : QObject(parent){}
    virtual ~OTimer(){
    }
    typedef std::chrono::microseconds Interval;
    typedef std::chrono::nanoseconds NanoInterval;
    bool isActive(){return m_running;}
    void setInterval(const Interval &interval){
        m_interval = interval;
    }
    void start(){
        Interval interval = m_interval;
        m_running = true;
        m_th = std::thread([=](){
            while (m_running == true) {
                std::this_thread::sleep_for(interval);
                emit timeoutSignal();
            }
            m_th.detach();
        });
    }
    void start(const Interval &interval){
        m_running = true;
        m_th = std::thread([=](){
            while (m_running == true) {
                std::this_thread::sleep_for(interval);
                emit timeoutSignal();
            }
            m_th.detach();
        });

    }
    void stop(){
        m_running = false;
    }
    void singleShot(const Interval &interval){
        m_running = true;
        m_th = std::thread([=](){
                std::this_thread::sleep_for(interval);
                if(m_running)
                    emit timeoutSignal();
        });
    }
    void singleShotNano(const NanoInterval &interval){
        m_running = true;
        m_th = std::thread([=](){
                std::this_thread::sleep_for(interval);
                if(m_running)
                    emit timeoutSignal();
        });
    }
signals:
    void timeoutSignal();
};

class graphType : public QObject{
    Q_OBJECT
    Q_ENUMS(eGraphType)
public:
    explicit graphType(QObject *parent = 0)  : QObject(parent){}
    enum eGraphType {
         UND = -1,
         PLOTX = 0,
         PLOTY = 1,
         SCATTER = 2,
         SCATTERCLB = 3,
         PICTURE = 4,
         PUPILAREA  = 5,
        };
};

class cameraType : public QObject{
    Q_OBJECT
    Q_ENUMS(eCameraType)
public:
    explicit cameraType(QObject *parent = 0)  : QObject(parent){}
    enum eCameraType {USB_20,DMM_37UX287_ML};
};



class testType : public QObject
{
    Q_OBJECT
    Q_ENUMS(eTestType)
public:
    explicit testType(QObject *parent = 0)  : QObject(parent){}
    enum eTestType {UND = -1, SV = 1, ASV = 2, SM = 3, ASM = 4, SC = 5, IF  = 6, FIX = 7, PL  = 8, SLL = 9, SLS = 10, OPT = 11, CLB=0};
};

class taskType : public QObject
{
    Q_OBJECT
    Q_ENUMS(eTaskType)
public:
    explicit taskType(QObject *parent = 0)  : QObject(parent){}
    enum eTaskType{
        CALIBRATION = 0,
        TEST = 1,
        UNDEF = -1
    };
};

class displayMode : public QObject
{
    Q_OBJECT
    Q_ENUMS(eDisplayMode)
public:
    explicit displayMode(QObject *parent = 0)  : QObject(parent){}
    enum eDisplayMode{MANUAL,AUTOMATIC,COMBINED};
};


class colorScheme : public QObject{
    Q_OBJECT
public:
    colorScheme(QObject *parent=0);
    Q_PROPERTY(QColor guiBG READ guiBG WRITE setGuiBG NOTIFY guiBgChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphBG READ graphBG WRITE setGraphBG NOTIFY graphBgChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphFG READ graphFG WRITE setGraphFG NOTIFY graphFgChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphGridY READ graphGridY WRITE setGraphGridY NOTIFY graphGridYChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphGridX READ graphGridX WRITE setGraphGridX NOTIFY graphGridXChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphGaze READ graphGaze WRITE setGraphGaze NOTIFY graphGazeChanged)  //bgColorChanged: It is used somewhere?????
    Q_PROPERTY(QColor graphStimulus READ graphStimulus WRITE setGraphStimulus NOTIFY graphStimulusChanged)  //bgColorChanged: It is used somewhere?????
public slots:
    QColor graphBG(){return m_graphBG;}
    QColor graphFG(){return m_graphFG;}
    QColor graphGridY(){return m_graphGridY;}
    QColor graphGridX(){return m_graphGridX;}
    QColor graphGaze(){return m_graphGaze;}
    QColor graphStimulus(){return m_graphStimulus;}
    QColor guiBG(){return m_guiBG;}
    void setGraphBG(const QColor value){m_graphBG = value;}
    void setGraphFG(const QColor value){m_graphFG = value;}
    void setGraphGridY(const QColor value){m_graphGridY = value;}
    void setGraphGridX(const QColor value){m_graphGridX = value;}
    void setGraphGaze(const QColor value){m_graphGaze = value;}
    void setGraphStimulus(const QColor value){m_graphStimulus = value;}
    void setGuiBG(const QColor value){m_guiBG = value;}
signals:
    void graphBgChanged();
    void graphFgChanged();
    void graphGridYChanged();
    void graphGridXChanged();
    void graphGazeChanged();
    void graphStimulusChanged();
    void guiBgChanged();


private:
    QColor m_graphBG;
    QColor m_graphFG;
    QColor m_graphGridY;
    QColor m_graphGridX;
    QColor m_graphGaze;
    QColor m_graphStimulus;
    QColor m_guiBG;

    QFile *m_xmlFileName;
    QXmlStreamWriter *m_xmlWriter;
    QXmlStreamReader m_xmlReader;
    unsigned int m_xmlIndex;

    bool openXmlReader();
    bool openXmlWriter();
    void readXmlElements();
};

//Oscann 4.0.7: New class
class OVersions : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString tracker READ tracker CONSTANT)
    Q_PROPERTY(QString oscann READ oscann CONSTANT)
    Q_PROPERTY(QString analizer READ analizer CONSTANT)
public:
    OVersions(QObject *parent=0){
        QDir directory("../lib/x86_64-linux-gnu");
        QStringList files = directory.entryList(QStringList() << "libotracker.so.*",QDir::Files|QDir::NoSymLinks);
        QStringList parts = files[0].split(".");
        if(parts.length() > 3)
            m_tracker = QString("%1.%2.%3").arg(parts[2]).arg(parts[3]).arg(parts[4]);
        else
            m_tracker = "0.0.0";
    }
public slots:
    QString tracker(){return m_tracker;}
    static QString oscann(){return "4.0.12";}
    static QString analizer(){return "1.0.0";}
private:
    QString m_tracker;
};






class OCTSettings : public QObject{

    Q_OBJECT
    Q_PROPERTY(int clbRecordingTime READ clbRecordingTime WRITE setClbRecordingTime NOTIFY clbRecordingTimeChanged)
    Q_PROPERTY(int tstRecordingTime READ tstRecordingTime WRITE setTstRecordingTime NOTIFY tstRecordingTimeChanged)
    Q_PROPERTY(int stimulusSize READ stimulusSize WRITE setStimulusSize NOTIFY stimulusSizeChanged)
    Q_PROPERTY(int fixedPointSize READ fixedPointSize WRITE setFixedPointSize NOTIFY fixedPointSizeChanged)
    Q_PROPERTY(int laps READ laps WRITE setLaps NOTIFY lapsChanged)
    Q_PROPERTY(int testTime READ testTime WRITE setTestTime NOTIFY testTimeChanged)
    Q_PROPERTY(float degrees2px READ degrees2px WRITE setdegrees2px NOTIFY degrees2pxChanged)
    Q_PROPERTY(double screenDistance READ screenDistance WRITE setScreenDistance NOTIFY screenDistanceChanged)
    Q_PROPERTY(double screenWidth READ screenWidth WRITE setScreenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(QPoint resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
    Q_PROPERTY(QString img1Path READ img1Path WRITE setImg1Path NOTIFY img1PathChanged)
    Q_PROPERTY(QString img2Path READ img2Path WRITE setImg2Path NOTIFY img2PathChanged)
    Q_PROPERTY(QString img3Path READ img3Path WRITE setImg3Path NOTIFY img3PathChanged)
    Q_PROPERTY(QString img4Path READ img4Path WRITE setImg4Path NOTIFY img4PathChanged)
    Q_PROPERTY(QString img5Path READ img5Path WRITE setImg5Path NOTIFY img5PathChanged)
    Q_PROPERTY(QString img6Path READ img6Path WRITE setImg6Path NOTIFY img6PathChanged)
    Q_PROPERTY(QString img7Path READ img7Path WRITE setImg7Path NOTIFY img7PathChanged)
    Q_PROPERTY(QString img8Path READ img8Path WRITE setImg8Path NOTIFY img8PathChanged)
    Q_PROPERTY(QString img9Path READ img9Path WRITE setImg9Path NOTIFY img9PathChanged)
    Q_PROPERTY(QString img10Path READ img10Path WRITE setImg10Path NOTIFY img10PathChanged)
    Q_PROPERTY(QString mongoUrl MEMBER m_mongoUrl CONSTANT)
    Q_PROPERTY(int mongoPort MEMBER m_mongoPort CONSTANT)
    //v4.0.12
    Q_PROPERTY(unsigned int mainDisplay MEMBER m_mainDisplay CONSTANT)

public:
    OCTSettings(QObject *parent=0);
//    void setUtilsProcessScreen();
public slots:
    int clbRecordingTime(){
        return m_clbRecordingTime;
    }
    int tstRecordingTime(){return m_tstRecordingTime;}
    int stimulusSize(){return m_stimulusSize;}
    int fixedPointSize(){return m_fixedPointSize;}
    int laps(){return m_laps;}
    int testTime(){return m_testTime;}
    QString img1Path(){return m_img1Path;}
    QString img2Path(){return m_img2Path;}
    QString img3Path(){return m_img3Path;}
    QString img4Path(){return m_img4Path;}
    QString img5Path(){return m_img5Path;}
    QString img6Path(){return m_img6Path;}
    QString img7Path(){return m_img7Path;}
    QString img8Path(){return m_img8Path;}
    QString img9Path(){return m_img9Path;}
    QString img10Path(){return m_img10Path;}
    //Oscann 3.0.3
    QString mongoUrl(){return m_mongoUrl;}
    unsigned int mongoPort(){return m_mongoPort;}
    //v4.0.12
    int mainDisplay(){return m_mainDisplay;}
    float degrees2px(){return m_degrees2px;}
    double screenDistance(){return m_screenDistance;}
    double screenWidth(){return m_screenWidth;}
    QPoint resolution(){return m_resolution;}
    void setClbRecordingTime(const int &newValue){m_clbRecordingTime = newValue;}
    void setTstRecordingTime(const int &newValue){m_tstRecordingTime = newValue;}
    Q_INVOKABLE void saveClbRecordingTime(){m_settings->setValue("stimulus/clbRecordingTime",m_clbRecordingTime);}
    Q_INVOKABLE void saveTstRecordingTime(){m_settings->setValue("stimulus/tstRecordingTime",m_tstRecordingTime);}
    Q_INVOKABLE void setUtilsProcessScreen();

    void setStimulusSize(const int &newValue){
        m_stimulusSize = newValue;
        m_settings->setValue("stimulus/stimulusSize",newValue);
    }
    void setFixedPointSize(const int &newValue){
        m_fixedPointSize = newValue;
        m_settings->setValue("stimulus/fixedPointSize",newValue);
    }
    void setLaps(const int &newValue){
        m_laps = newValue;
        m_settings->setValue("CalibrationTest/laps",newValue);
    }
    void setTestTime(const int &newValue){
        m_testTime = newValue;
        m_settings->setValue("CalibrationTest/testTime",newValue);
    }
    void setImg1Path(const QString &newValue){
        m_img1Path = newValue;
        m_settings->setValue("stimulus/img1Path",newValue);
    }
    void setImg2Path(const QString &newValue){
        m_img2Path = newValue;
        m_settings->setValue("stimulus/img2Path",newValue);
    }
    void setImg3Path(const QString &newValue){
        m_img3Path = newValue;
        m_settings->setValue("stimulus/img3Path",newValue);
    }
    void setImg4Path(const QString &newValue){
        m_img4Path = newValue;
        m_settings->setValue("stimulus/img4Path",newValue);
    }
    void setImg5Path(const QString &newValue){
        m_img5Path = newValue;
        m_settings->setValue("stimulus/img5Path",newValue);
    }
    void setImg6Path(const QString &newValue){
        m_img6Path = newValue;
        m_settings->setValue("stimulus/img6Path",newValue);
    }
    void setImg7Path(const QString &newValue){
        m_img7Path = newValue;
        m_settings->setValue("stimulus/img7Path",newValue);
    }
    void setImg8Path(const QString &newValue){
        m_img8Path = newValue;
        m_settings->setValue("stimulus/img8Path",newValue);
    }
    void setImg9Path(const QString &newValue){
        m_img9Path = newValue;
        m_settings->setValue("stimulus/img9Path",newValue);
    }
    void setImg10Path(const QString &newValue){
        m_img10Path = newValue;
        m_settings->setValue("stimulus/img10Path",newValue);
    }
    void setdegrees2px(const float &newValue){
        m_degrees2px=newValue;
        m_settings->setValue("stimulus/degrees2px",newValue);
    }
    void setScreenDistance(const double &newValue){
        m_screenDistance=newValue;
        m_settings->setValue("stimulus/screenDistance",newValue);
    }
    void setScreenWidth(const double &newValue){
        m_screenWidth=newValue;
        m_settings->setValue("stimulus/screenWidth",newValue);
    }
    void setResolution(const QPoint &newValue){
        m_resolution=newValue;
        m_settings->setValue("stimulus/resolution",newValue);
    }

signals:
    void clbRecordingTimeChanged(const int &newValue);
    void tstRecordingTimeChanged(const int &newValue);
    void stimulusSizeChanged(const int &newValue);
    void fixedPointSizeChanged(const int &newValue);

    void lapsChanged(const int &newValue);
    void timesChanged(const int &newValue);
    void testTimeChanged(const int &newValue);

    void img1PathChanged(const int &newValue);
    void img2PathChanged(const int &newValue);
    void img3PathChanged(const int &newValue);
    void img4PathChanged(const int &newValue);
    void img5PathChanged(const int &newValue);
    void img6PathChanged(const int &newValue);
    void img7PathChanged(const int &newValue);
    void img8PathChanged(const int &newValue);
    void img9PathChanged(const int &newValue);
    void img10PathChanged(const int &newValue);
    void degrees2pxChanged(const int &newValue);
    void screenWidthChanged(const int &newValue);
    void screenDistanceChanged(const int &newValue);
    void resolutionChanged(const int &newValue);

private:
    int m_clbRecordingTime;
    int m_tstRecordingTime;
    int m_stimulusSize;
    int m_fixedPointSize;

    //Imagenes
    QString m_img1Path;
    QString m_img2Path;
    QString m_img3Path;
    QString m_img4Path;
    QString m_img5Path;
    QString m_img6Path;
    QString m_img7Path;
    QString m_img8Path;
    QString m_img9Path;
    QString m_img10Path;
    float m_degrees2px;
    double m_screenDistance;
    double m_screenWidth;
    QPoint m_resolution;
    //PL -> laps and m_showHideTime
    int m_laps;
    //OPT
    int m_testTime;
    QSettings *m_settings;

    QString m_mongoUrl;
    unsigned int m_mongoPort;

    //v4.0.12:
    int m_mainDisplay;
};

//QGuiApplication::screens().at(1)->geometry()

class OTemporalValues : public QObject{
    Q_OBJECT
    Q_PROPERTY(int testType MEMBER m_testType READ testType WRITE setTestType NOTIFY testTypeChanged)
    Q_PROPERTY(int taskType MEMBER m_taskType READ taskType WRITE setTaskType NOTIFY taskTypeChanged)
    Q_PROPERTY(int testDisplayMode MEMBER m_testDisplayMode READ testDisplayMode WRITE setTestDisplayMode NOTIFY testDisplayModeChanged)
    Q_PROPERTY(int testVariant MEMBER m_testVariant READ testVariant WRITE setTestVariant NOTIFY testVariantChanged)
    Q_PROPERTY(int clbPoints MEMBER m_clbPoints READ clbPoints WRITE setClbPoints NOTIFY clbPointsChanged)
    Q_PROPERTY(QUrl picturesFolder MEMBER m_picturesFolder CONSTANT)
    Q_PROPERTY(QRect geometry MEMBER m_geometry CONSTANT)

public:
    explicit OTemporalValues(QObject *parent = 0) :  m_testType(-1)
                                                ,m_taskType(-1)
                                                ,m_testDisplayMode(-1)
                                                ,m_testVariant(-1)
                                                ,m_clbPoints(-1)
                                                ,m_picturesFolder(QUrl("file:///" + QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).at(0), QUrl::TolerantMode))
                                                ,m_geometry(QGuiApplication::screens().at(0)->geometry()){}
public slots:
    int testType(){return m_testType;}
    int taskType(){return m_taskType;}
    int testDisplayMode(){return m_testDisplayMode;}
    int testVariant(){return m_testVariant;}
    int clbPoints(){return m_clbPoints;}
    void setTestType(const int value){
        m_testType = value;
    }
    void setTaskType(const int value){m_taskType = value;}
    void setTestDisplayMode(const int value){m_testDisplayMode = value;}
    void setTestVariant(const int value){m_testVariant = value;}
    void setClbPoints(const int value){m_clbPoints = value;}
signals:
    void testTypeChanged(const int &newValue);
    void taskTypeChanged(const int &newValue);
    void testDisplayModeChanged(const int &newValue);
    void testVariantChanged(const int &newValue);
    void clbPointsChanged(const int &newValue);
private:
    int m_testType;
    int m_taskType;
    int m_testDisplayMode;
    int m_testVariant;
    int m_clbPoints;
    QUrl m_picturesFolder;
    QRect m_geometry;
};

class oscannCursorWrapper : public QObject
{
    Q_OBJECT
public:
    explicit oscannCursorWrapper(QObject *parent = 0)  : QObject(parent){}
public slots:
    void hideCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
    void openHandCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    }
    void closeHandCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
    }
    void sizeHCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
    }
    void sizeVCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
    }
    void restoreCursor(){
        QApplication::restoreOverrideCursor();
    }
    void arrowCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    }
    void sizeVerCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
    }
    void sizeHorCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
    }
    void sizeBDiagCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
    }
    void sizeFDiagCursor(){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
    }





};


#endif // QUTILS_H
