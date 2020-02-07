#ifndef VIDEOPREVIEW_H
#define VIDEOPREVIEW_H

#include <QQuickPaintedItem>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QtCore/QMutexLocker>
#include <QQuickItem>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include "qutils.h"
#include "data.h"



//openCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "opencv2/opencv.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>


//class videoPreview  : public QQuickPaintedItem{
class videoPreview  : public QQuickItem{
    Q_OBJECT
    protected:
        QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
        void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private:
        unsigned int m_NOV;

        OData *m_objData;
        QVector<QPointF> pupilCoord,pupilDim;
        QVector<bool> blink;
        QVector<QPointF> glintI,glintD;
        QVector<double> pupilAngle;

        void createTimer();
    public:
        videoPreview();
        ~videoPreview(){}
        Q_INVOKABLE void setData(OData *data);
        Q_INVOKABLE void loadLogo();
        void newPointerPosition(const int);
        void setPointerFromTo(const int from, const int to);

signals:
        void newPos(const int pos);

public slots:
    //void updateImageSlot(int x, int y, int width, int height);
    //void loadLogo();
    bool openVideo(const QString fileName);
    void updateImage();
    void stop();
    void pause();
    void play();
    void speedUp();
    void speedDown();
    private:

    int m_position;
    int m_pointerFrom;
    int m_pointerTo;

        QImage m_img;//?????
        QImage m_logo;
        QImage *m_logoa;
        QPoint m_imgPos;
        QMutex m_mutex;
        QSGSimpleTextureNode *m_node;
        QSGTexture *m_texture;
        bool m_fromVideo;
        bool m_geometryChanged;

        cv::VideoCapture m_input[2];
        //cv::VideoCapture m_input_1;

        cv::Mat m_pupilFrame;


        QVector<cv::Mat> frames;
        OTimer *m_oTimer;


        QPixmap m_image;
        boost::posix_time::ptime m_start;
        boost::posix_time::time_duration m_dur;


        int m_interval;
        double m_count;

        int m_speed;

        QVector<int> m_speeds;
        QVector<QString> m_speedLabels;

        bool m_playing;


};

#endif // VIDEOPREVIEW_H
