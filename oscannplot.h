#ifndef OSCANNPLOT_H
#define OSCANNPLOT_H

#include <QtQuick>
#include <QColor>
#include <QMouseEvent>

#include "qcustomplot.h"
#include "data.h"
#include "utilsprocess.h"
#include "iostream"
#include "qutils.h"
#include "videopreview.h"


//#include "oscann_adaptor.h"
//#include "oscann_interface.h"

//openCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/opencv.hpp"

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>

class OscannPlot : public QQuickPaintedItem
{
    Q_OBJECT
    friend class videoPreview;
     Q_PROPERTY(QString sessionName READ sessionName WRITE setSessionName NOTIFY sessionNameChange)
    Q_PROPERTY(bool clbScatterAble READ clbScatterAble WRITE setClbScatterAble NOTIFY clbScatterAbleChange)
public:
    OscannPlot(QQuickItem *parent = nullptr);
    virtual ~OscannPlot();
    void paint( QPainter* painter );
    Q_INVOKABLE void init(bool, int, bool=true, QString="", QString="", QColor=QColor(0,0,0), QColor=QColor(0,0,0));
    Q_INVOKABLE void resetPlot(){x.clear();y.clear();time.clear();xS.clear();yS.clear();}
    Q_INVOKABLE void updateData();
    Q_INVOKABLE void setData(OData *data);
    Q_INVOKABLE bool loadCsv(QString csvPath);
    //Oscann 3.0.3
    QString loadFromDB(const QString patient, const QString test, const QString url, const unsigned int port);
    Q_INVOKABLE bool checkScreen(){return screenSet;}
    Q_INVOKABLE void calibScatter();
    Q_INVOKABLE int getType(){return m_graphType;}
    Q_INVOKABLE double getDeg2Px(){return ratioPxDeg;}
    Q_INVOKABLE QCustomPlot *getCustomPlot(){return m_CustomPlot;}
    //v4.0.13
    Q_INVOKABLE void openInExplorer();
    Q_INVOKABLE void autoScale(bool autom=false, unsigned int index=99);
    Q_INVOKABLE void changeColor();
    Q_INVOKABLE QPoint setScreen(QString);
    Q_INVOKABLE double loadDistance(QString);
    Q_INVOKABLE double loadWidth(QString);
    Q_INVOKABLE void changeRaw(bool);
    Q_INVOKABLE void removeVectors();
    Q_INVOKABLE void clearAll();
    Q_INVOKABLE void clearPlot();
    Q_INVOKABLE void setZoomMode(int);
    Q_INVOKABLE bool picExists(QString path){return QFile(path).exists();}
    Q_INVOKABLE void savePlot(int,int,int=18,QColor=Qt::white);
    Q_INVOKABLE void makeVideo(QString);
    void calcPic();
    Q_INVOKABLE void keyPress(int);
    Q_INVOKABLE void keyRelease(int);
    Q_INVOKABLE void capturePupil();
    Q_INVOKABLE QString fastCalib(QString tstPath);
    Q_INVOKABLE QStringList searchTests(QString folderPath);                                //v4.0.12 new
    Q_INVOKABLE QStringList processFolder(QString folderPath);
    Q_INVOKABLE QStringList processCsv(QString folderPath);
    Q_INVOKABLE void setLayoutDim(int width,int height);
    Q_INVOKABLE void setCreatingPdf(const bool value);
    Q_INVOKABLE void updatePointerPosition(int pos);
    Q_INVOKABLE void setVideoPreviewer(videoPreview *);
    void setClbScatterAble(const bool newValue){m_clbScatterAble=newValue;}
    bool clbScatterAble(){return m_clbScatterAble;}
    void setSessionName(QString sessionName){ m_sessionName = sessionName;}
    QString sessionName() const {return m_sessionName;}
    Q_INVOKABLE bool isEmptySessionName(){return m_sessionName.isEmpty();}
    //Oscann 3.0.3
    QPixmap getImage(int,int,int=18,QColor=Qt::white);
signals:
    void zoomChanged(int zoomMode);
    void beginProcess();
    void processed(double percent);
    void autoPic(bool autoOK);
    void newText(bool enable);
    // ShowMenu sends a signal to processing qml file to pop a menu
    // Type is 0 when plotMenu must be pop or 1 for saccadeMenu
    void showMenu(int type, bool saccadeStatus, bool latencyStatus, bool steadyStatus);
    void clbScatterAbleChange();
    void sessionNameChange();


private:

    QPointF m_scatterRangeX;
    QPointF m_scatterRangeY;



    QStringList m_sessionSorted;    //v4.0.12
    QDirIterator *m_mainFolder;     //v4.0.12
    QString m_folderPath;           //v4.0.12

    bool m_preview;

    videoPreview *m_videoPreviewer;

    bool m_clbScatterAble;

    OTimer *m_oTimer;

    boost::posix_time::ptime m_start;
    boost::posix_time::time_duration m_dur;

    //Erik
    bool m_videoAvailable;
    QVector<double> m_plotKeys;
    cv::Mat m_pupilFrame;
    bool m_earlyReleased;
    bool m_zooming;

    OData *m_objData;

    QCustomPlot* m_CustomPlot;
    //aura::GUIInterface *guiIface;
    //aura::DetectorInterface *detectorIface;
    //aura::DisplayCTInterface *displayCTIface;

    QVector<double> x,y,time;
    QVector<double> xS,yS;
    QVector<double> xR,yR;
    QVector<double> pupilArea;
    QVector<int> blinks;
    QVector<bool> valid;
    graphType GT;

    colorScheme CS;


    int m_graphType;

    QString testDir,testName, m_sessionName;

    //bool sacVisible;

    //QCPItemRect *selectedSac;

    QPointF testDim;
    QPointF m_mouse,prev;
    QPoint resolution;
    double screenWidth;
    double screenDistance;
    double ratioPxDeg;
    bool screenSet;
    bool px2Deg;

    bool rightPressed,leftPressed,moveInd;
    bool ctrlPressed;
    int zoomMode,prevZoom,prevMid,ind;

    QPointF minRange,maxRange;

    QCPItemText *title;
    QString unitIndex;

    QCPItemText *stadisticalLegend;

    QCPItemText *pointerLabel;
    QCPItemTracer *pointer;
    int m_tracerPosition;

    QVector<QCPItemTracer*> m_dots;

    QCPItemRect *zoomInd,*keepInd;
    QCPItemRect *margins;
    double xPix,yPix;

    QCPItemPixmap *pic;
    QPixmap picture;
    QString picDir,imgDir;
    int lastColor;

    cv::VideoWriter *outputVideo;
    cv::VideoCapture *inputVideo;

    bool showPointer;
    bool showRaw;
    bool csvLoaded;

    QTimer moveTimer,keyTimer;

    void scatter(QVector<double>,QVector<double>,QString="Funcion",QColor=Qt::black,QColor=Qt::black,double sizing=2.0);
    void plot(QVector<double>, QVector<double>, unsigned int style, QString="Funcion", QColor=QColor(0,204,255), int width=2);
    void plotBlinks(int);
    void addPicture(QString);
    void pupilLightVar();
    void heatMap();
    void indexPoint(QPointF);
    void calcCoord();

    void sortDirectories();   //v4.0.12 new



//Erik
    void removeEvents(QCPItemTracer*);
    void installEvents(QCPItemTracer*);
    void setXYScaleFactor(double, double, bool);
    QPointF m_topLeft;
    QPointF m_bottomRight;
    bool m_movingDot;
    int m_movingDotId;
    bool m_movingOnPlot;
    QPointF m_picturePosition;

    bool m_overTraceId;

    QCPItemTracer *m_tracerSelected;

    //QVector<QCPItemTracer*> m_newOptions;


    //Erik
    bool f_playing;
    bool m_creatingPdf;

    int m_wheel;
    int m_graphIndex;

    double m_xFactorInit;
    double m_xFactor;


    void trackerPosCorrection(int *pos, int mouseX);

    void calibrationXY();

protected:
    void routeMouseEvents( QMouseEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mouseDoubleClickEvent( QMouseEvent* event );
    virtual void mouseWheelEvent( QWheelEvent* event );

    void routeHoverEvents( QHoverEvent *event );
    virtual void wheelEvent(QWheelEvent *event);



private slots:
    void onCustomReplot();
    void updateCustomPlotSize();
    void moveMeSlot(int id, int pos,int mouseX);
    void dotCatchedSlot(int, int, int);
    void dotReleasedSlot(QPoint, int);
    void overSomeTracerSlot(bool);
    //TODODEBUG: void quit();

public Q_SLOTS:
    void pupilAtSlot(double x, double y, double sx, double sy);
    void scatterSlot(unsigned int index);
};

#endif // OSCANNPLOT_H
