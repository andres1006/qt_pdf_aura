#ifndef DATA_H
#define DATA_H

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QFile>
#include <qt5/QtCore/QTextStream>
#include <qt5/QtCore/QDateTime>


#include <qt5/QtCore/QVector>
#include <qt5/QtCore/QPoint>
#include <qt5/QtCore/QSize>
#include <qt5/QtCore/QDir>
#include <qt5/QtCore/QDirIterator>

#include <qt5/QtCore/QDebug>

#include "utilsprocess.h"

#include "qutils.h"

#define LEFT 0
#define RIGHT 1


#include <boost/date_time/posix_time/posix_time.hpp>




class OProcessed{ //Almacena las variables mas usadas (Tiempo, estimulo, mirada filtrada y area de la pupila)
public:
    //OProcessed(unsigned long time,double x, double y, double xR, double yR, double xS, double yS, double pupilArea, int prp){
    OProcessed(double time,double x, double y, double xR, double yR, double xS, double yS, double pupilArea, int prp, bool valid){
        setTime(time);
        setArea(pupilArea);
        position.setX(x);
        position.setY(y);
        raw.setX(xR);
        raw.setY(yR);
        stimulus.setX(xS);
        stimulus.setY(yS);
        parpadeo=prp;
        m_valid=valid;
    }
    OProcessed(){}
    ~OProcessed(){}
    double time(){return m_time;}
    double x(){return position.x();}
    double y(){return position.y();}
    double xR(){return raw.x();}
    double yR(){return raw.y();}
    double xS(){return stimulus.x();}
    double yS(){return stimulus.y();}
    double area(){return m_pupilArea;}
    int getParpadeo(){return parpadeo;}
    bool valid(){return m_valid;}
    void setTime(double value){m_time = value;}
    void setArea(double area){m_pupilArea=area;}
    void setX(double x){position.setX(x);}
    void setY(double y){position.setY(y);}
    void setXR(double xR){raw.setX(xR);}
    void setYR(double yR){raw.setY(yR);}
    void setXS(double xS){stimulus.setX(xS);}
    void setYS(double yS){stimulus.setY(yS);}
    void setParpadeo(int prp){parpadeo=prp;}

    private:
        QPointF raw;
        QPointF position;
        QPointF stimulus;
        double m_time;
        double m_pupilArea;
        int parpadeo;
        bool m_valid;
};

class OProcessedExtra{ //Almacena otras variables menos usadas, velocidadades y mirada sin filtrar (Solo filtro de parpadeos)
public:
    OProcessedExtra(double xd1, double yd1, double xd2, double yd2, double xRaw, double yRaw, double xd1Raw, double yd1Raw, double xd2Raw, double yd2Raw, double xerr, double yerr){
        vel.setX(xd1);
        vel.setY(yd1);
        acc.setX(xd2);
        acc.setY(yd2);
        positionRaw.setX(xRaw);
        positionRaw.setY(yRaw);
        velRaw.setX(xd1Raw);
        velRaw.setY(yd1Raw);
        accRaw.setX(xd2Raw);
        accRaw.setY(yd2Raw);
        error.setX(xerr);
        error.setY(yerr);
    }
    OProcessedExtra(){}
    ~OProcessedExtra(){}
    QPointF getVel(){return vel;}
    void setVel(QPointF vel){this->vel = vel;}
    QPointF getAcc(){return acc;}
    QPointF getPosRaw(){return positionRaw;}
    void setPosRaw(QPointF posRaw){this->positionRaw = posRaw;}
    QPointF getVelRaw(){return velRaw;}
    QPointF getAccRaw(){return accRaw;}
    QPointF getError(){return error;}
    private:
        QPointF vel;
        QPointF acc;
        QPointF positionRaw;
        QPointF velRaw;
        QPointF accRaw;
        QPointF error;
};



class QPupil{
public:
    QPupil(){}
    ~QPupil(){}
    double x(){return position.x();}
    double y(){return position.y();}
    double width(){return size.width();}
    double height(){return size.height();}
    double angle(){return pAngle;}

    void setX(double x){position.setX(x);}
    void setY(double y){position.setY(y);}
    void setHeight(double height){size.setHeight(height);}
    void setWidth(double width){size.setWidth(width);}
    void setAngle(double ang){pAngle=ang;}

    private:
    QPointF position;
    QSizeF size;
    double pAngle;
};


class QRaw{
public:
    //QRaw(int time,int x, int y): time(time), x(x), y(y){}
    QRaw(double t, double x, double y, double w, double h, double angle, double gLX, double gLY, double gRX, double gRY, int stimulusX, int stimulusY, bool b){
        time = t;
        pupil.setX(x);
        pupil.setY(y);
        pupil.setWidth(w);
        pupil.setHeight(h);
        pupil.setAngle(angle);
        glintLeft.setX(gLX);
        glintLeft.setY(gLY);
        glintRight.setX(gRX);
        glintRight.setY(gRY);
        m_stimulus.setX(stimulusX);
        m_stimulus.setY(stimulusY);
        m_gaze = QPointF(x-(gRX+gLX)/2,y-(gRY+gLY)/2);
        blink = b;
        m_validPto = true;
    }
    QRaw(){}
    ~QRaw(){}
    double getTime(){ return time;}
    void setTime(double t){time=t;}
    double x(){ return pupil.x();}
    double y(){ return pupil.y();}
    double width(){ return pupil.width();}
    double height(){ return pupil.height();}
    double angle(){return pupil.angle();}
    QPointF glint(int g){
        if(g == LEFT)
            return glintLeft;
        else
            return glintRight;
    }
    int stimulusX(){return m_stimulus.x();}
    int stimulusY(){return m_stimulus.y();}
    QPoint stimulus(){return m_stimulus;}
    void setStimulusX(int sx){m_stimulus.setX(sx);}
    void setStimulusY(int sy){m_stimulus.setY(sy);}
    QPointF gaze(){return m_gaze;}
    void setGaze(QPointF gaze){m_gaze = gaze;}
    void setValidPto(bool value){m_validPto = value;}
    bool validPto(){return m_validPto;}
    bool getBlink(){return blink;}
private:
    //unsigned long time;
    double time;
    QPupil pupil;
    QPointF glintLeft;
    QPointF glintRight;
    QPoint m_stimulus;
    QPointF m_gaze;
    bool m_validPto;
    bool blink;
};


class OData : public QObject
{
    Q_OBJECT
    friend class process;
    friend class processtsv;
    friend class OscannPlot;
    Q_PROPERTY(QString clbFileName READ clbFileName WRITE setClbFileName)
    Q_PROPERTY(QString tstFileName READ tstFileName WRITE setTstFileName)
public:
    explicit OData(QObject *parent = 0);
    //explicit OData(){m_age = 0;}
    //Oscann 4.0.9 Q_INVOKABLE const int open();
    Q_INVOKABLE int open(bool processing);
    Q_INVOKABLE QString getLastError(){ return m_lastError;}
    Q_INVOKABLE void exportCsv();
    //Oscann 4.0.5: New method
    Q_INVOKABLE void importCsv();
    Q_INVOKABLE bool removeTestFolder(QString);
    Q_INVOKABLE QString folderExistance(QString,QString); //devuelve el path del archivo repetido encontrado
    Q_INVOKABLE void exportFolder(QString,QString);
    Q_INVOKABLE void setTestPath(const QString, const QString);
    Q_INVOKABLE QString getTestPath(){return m_testPath;}
    Q_INVOKABLE void setpathology(const QString pathology, int i) {if(m_pathology.length()<3) m_pathology.append(pathology);else m_pathology.replace(i-1,pathology); }
    Q_INVOKABLE QString getpathology(int i){return m_pathology.at(i);}
    Q_INVOKABLE bool isEmptypathology(){return m_pathology.isEmpty();}
    Q_INVOKABLE void setAge(const int age){m_age=age;}
    Q_INVOKABLE int getAge(){return m_age;}
    Q_INVOKABLE bool getHeadTremor(){return m_headTremor;}
    Q_INVOKABLE void setHeadTremor(bool ischeck){m_headTremor=ischeck;}
    Q_INVOKABLE void setSessionName(QString sessionname){m_sessionName=sessionname;}
    Q_INVOKABLE QString getSessionName(){return m_sessionName;}
    Q_INVOKABLE void pushback_testPathology(QString test)
    {
        int flag=0;
        for (int i=0;i<m_testPathology.length();i++)
        {
            if(m_testPathology[i]==test)
                flag=1;
        }
        if(flag==0)m_testPathology.push_back(test);
    }
    Q_INVOKABLE void setTestPathology(QStringList tests){
        m_testPathology.clear();
        for(int i=0;i<tests.length();i++)
            m_testPathology << tests.at(i);
    }
    Q_INVOKABLE void addTestPathology(QString test){
        m_testPathology.append(test);
    }
    Q_INVOKABLE QString getTestPathology(const int i){return m_testPathology.at(i);}
    Q_INVOKABLE QStringList getTestPathologyList();
    Q_INVOKABLE QStringList checkAllTest(QStringList);
    Q_INVOKABLE QStringList getPatientDetails();
    QPoint getresolution(){return resolution;}
    double getDist(){return sDist;}
    double getWidth(){return sWidth;}
    void setResolution(QPoint pt){resolution=pt;}
    void setDist(double distance){sDist=distance;}
    void setWidth(double width){sWidth=width;}
    int dataSize() {return m_processedData.size();}

    QVector< QRaw > getData(){return m_testData;}

    QVector< QRaw > m_calibrationData;

    QVector< QPair<int, int> > m_calibrationRanges;
    QVector< QPair<double, double> > m_meanStdX;
    QVector< QPair<double, double> > m_meanStdY;

signals:
public slots:
    void setClbFileName(const QString path){
        m_clbBaseName = verifyDat(path);
        m_clbFullName = path + "/" + m_clbBaseName;
        qDebug()<<Q_FUNC_INFO<<" -> m_csvClb: "<<m_csvClb<<", m_clbBaseName: "<<m_clbBaseName<<", m_clbFullName: "<<m_clbFullName;
    }
    void setTstFileName(const QString path){
        m_tstBaseName = verifyDat(path);
        m_tstFullName = path + "/" + m_tstBaseName;
    }

    QString tstFileName() {return m_tstBaseName;}
    QString clbFileName(){return m_clbBaseName;}


    unsigned int clbFails(){return m_clbFails;}
    unsigned int tstFails() {return m_tstFails;}
    bool blkDefined() {return m_blkDefined;}
private:

    QString m_sessionName;
    int m_age;
    bool m_headTremor;
    QStringList m_pathology;
    QStringList m_testPathology;
    double m_sumX, m_sumY;

    //OVersions *m_versions;

    QFile *m_csvFile;    //Oscann 4.0.9

    unsigned int m_fails;
    bool m_blkDefined;

    QString m_lastError;
    QString m_testPath;
    QString m_testName;
    QFile *m_statisticalFile;
    void calculateMeanAndStd();
    void read(QFile *file,  QVector< QRaw > &data, bool clb=false);
    QPoint resolution;
    double sDist,sWidth;
    //QString m_errorMessage;
    QString m_clbBaseName;
    QString m_clbFullName;
    QString m_tstBaseName;
    QString m_tstFullName;

    QString m_blinkFileName;
    //Oscann 4.0.5
    QString m_csvFileName;
    //v4.0.12
    QString m_csvClb;
    std::vector<std::pair<int, int>> m_blinks;

    QVector< int > m_indices;


    unsigned int m_tstFails;
    unsigned int m_clbFails;


    QVector< QRaw > m_testData;
    unsigned long countBlinks; //Numero de parpadeos en la prueba cargada
    bool m_micro;
    QVector< QRaw > m_rawData;
    QVector< OProcessed > m_processedData;
    QVector< OProcessedExtra > m_processedDataExtra;

    QString verifyDat(const QString dir){
        QDir myDir(dir);
        myDir.setNameFilters(QStringList()<<"*.dat");
        QStringList fl = myDir.entryList(QDir::Files);
        //qDebug()<<Q_FUNC_INFO<<" fl.count(): "<<fl.count();
        if(fl.count() > 0)
            return fl.at(0).toLocal8Bit().constData();
        else
            return QString();
    }
    QString getTitle(QString);



};

#endif // DATA_H
