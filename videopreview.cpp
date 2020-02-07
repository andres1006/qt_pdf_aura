#include "videopreview.h"

videoPreview::videoPreview(){
    setFlag(QQuickItem::ItemHasContents);
    m_logo = QImage(":qml/qtcam/videocapturefilter_QML/images/oscannblue.png");
    m_position = 0;
    m_texture = NULL;
    m_fromVideo = false;
    m_oTimer = NULL;
    m_pointerFrom = 0;
}



QSGNode *videoPreview::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *){
    //m_start = boost::posix_time::microsec_clock::local_time();
    QMutexLocker lock(&m_mutex);
    Q_UNUSED(lock);
    //NOTE Erik: QImage::Format_RGB888 must be used.
    //           The image retraived from the video in RGB: 8UC3. This cannot be changed
    //           m_input->set( CV_CAP_PROP_FORMAT, CV_8UC1 ) does not work
    m_node = static_cast<QSGSimpleTextureNode *>(oldNode);
    if (!m_node) {
        m_node = new QSGSimpleTextureNode();
    }
    if(m_texture)
        delete m_texture;
    if(m_fromVideo){
        m_texture = window()->createTextureFromImage(QImage(m_pupilFrame.data, m_pupilFrame.cols, m_pupilFrame.rows, QImage::Format_RGB888), QQuickWindow::TextureCanUseAtlas);
    }
    else{
        m_texture = window()->createTextureFromImage(m_logo);
    }
    m_node->setTexture(m_texture);
    m_node->setRect(boundingRect());
    //m_dur = boost::posix_time::microsec_clock::local_time() - m_start;
    //qDebug()<<Q_FUNC_INFO<<" -> microseconds: "<<m_dur.total_microseconds()<<", m_position: "<<m_position<<", m_fromMemory: "<<m_fromMemory;
    return m_node;
}

void videoPreview::setPointerFromTo(const int from, const int to){
    if(!m_fromVideo)
        return void();
    m_pointerFrom = from;
    m_pointerTo = to;
    m_position = from;
    if(m_NOV > 1){
        for(int i=0;i<m_NOV;i++)
        m_input[i].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom/2);
    }else{
        m_input[0].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom);
    }
}

void videoPreview::newPointerPosition(const int value){
    //qDebug()<<Q_FUNC_INFO<<" value: "<<value;
    if(!m_fromVideo)
        return void();
    m_position = value;
    if(m_NOV > 1){
        for(int i=0;i<m_NOV;i++)
            m_input[i].set(cv::CAP_PROP_POS_FRAMES, m_position/2);
    }else{
        m_input[0].set(cv::CAP_PROP_POS_FRAMES, m_position);
    }
    updateImage();
}

void videoPreview::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry){
    m_geometryChanged = true;
    update();
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
}

void videoPreview::createTimer(){
    if(m_oTimer)
        delete m_oTimer;
    m_oTimer = new OTimer(this);
    connect(m_oTimer, SIGNAL(timeoutSignal()), this, SLOT(updateImage()));
    m_oTimer->start(std::chrono::microseconds(m_speeds.at(m_speed)));
}
void videoPreview::speedDown(){
    if(m_oTimer)
        m_oTimer->stop();
    m_oTimer = NULL;
    if(m_speed > 0)
        m_speed--;
    createTimer();
    m_playing = true;
}
void videoPreview::speedUp(){
    if(m_oTimer)
        m_oTimer->stop();
    m_oTimer = NULL;
    if(m_speed < m_speeds.length())
        m_speed++;
    createTimer();
    m_playing = true;
}

void videoPreview::pause(){
    if(m_oTimer)
        m_oTimer->stop();
    m_playing = false;

}


void videoPreview::stop(){
    if(!m_fromVideo)
        return void();
    if(m_oTimer)
        m_oTimer->stop();
    m_playing = false;
    m_speed = 6;
    m_position = m_pointerFrom;
    if(m_NOV > 1){
        m_pointerTo = (double) m_input[0].get(cv::CAP_PROP_FRAME_COUNT);
        m_pointerTo += (double) m_input[1].get(cv::CAP_PROP_FRAME_COUNT);
        for(int i=0;i<m_NOV;i++)
            m_input[i].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom/2);
    }else{
        m_pointerTo = (double) m_input[0].get(cv::CAP_PROP_FRAME_COUNT);
        m_input[0].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom);
    }
    m_fromVideo = true;
    updateImage();
}
void videoPreview::play(){
    if(!m_playing){
        createTimer();
        m_playing = true;
    }
}
void videoPreview::loadLogo(){
    m_fromVideo = false;
}
bool videoPreview::openVideo(const QString fileName){
    QFileInfoList avis=QDir(QString(fileName+"/raw/")).entryInfoList(QStringList("*.avi"),QDir::Files);
    m_NOV = avis.length();
    int eachNano;
    m_fromVideo = false;
    switch(m_NOV){
    case 1:
        m_input[0] = cv::VideoCapture(QString(fileName+"/raw/"+fileName.split("/").last()+".avi").toLatin1().data());
        if(m_input[0].get(cv::CAP_PROP_FPS) == 0)
            m_input[0] = cv::VideoCapture(QString(fileName+"/raw/"+fileName.split("/").last()+"_0.avi").toLatin1().data());
        eachNano = (1000.0 / (m_input[0].get(cv::CAP_PROP_FPS))) * 1000;
        break;
    case 2:
        m_input[0] = cv::VideoCapture(QString(fileName+"/raw/"+fileName.split("/").last()+"_0.avi").toLatin1().data());
        m_input[1] = cv::VideoCapture(QString(fileName+"/raw/"+fileName.split("/").last()+"_1.avi").toLatin1().data());
        eachNano = (1000.0 / (m_input[0].get(cv::CAP_PROP_FPS)*2)) * 1000;
        break;
    }
    avis.clear();
    if(m_NOV == 0)
        return m_fromVideo;
    m_speeds.clear();
    m_speedLabels.clear();
    m_speeds.push_back(eachNano*20);
    m_speedLabels.push_back("0.05");
    m_speeds.push_back(eachNano*10);
    m_speedLabels.push_back("0.1");
    m_speeds.push_back(eachNano*8);
    m_speedLabels.push_back("0.125");
    m_speeds.push_back(eachNano*5);
    m_speedLabels.push_back("0.2");
    m_speeds.push_back(eachNano*4);
    m_speedLabels.push_back("0.25");
    m_speeds.push_back(eachNano*2);
    m_speedLabels.push_back("0.5");
    m_speeds.push_back(eachNano);
    m_speedLabels.push_back("1");
    m_speeds.push_back(eachNano/2);
    m_speedLabels.push_back("2");
    m_speeds.push_back(eachNano/3);
    m_speedLabels.push_back("3");
    m_speeds.push_back(eachNano/4);
    m_speedLabels.push_back("4");
    m_speeds.push_back(eachNano/5);
    m_speedLabels.push_back("5");
    m_speeds.push_back(eachNano/6);
    m_speedLabels.push_back("6");
    m_speeds.push_back(eachNano/7);
    m_speedLabels.push_back("7");
    m_speeds.push_back(eachNano/8);
    m_speedLabels.push_back("8");
    m_speed = 6;
    m_pointerFrom = 0;
    if(m_NOV > 1){
        m_pointerTo = (double) m_input[0].get(cv::CAP_PROP_FRAME_COUNT);
        m_pointerTo += (double) m_input[1].get(cv::CAP_PROP_FRAME_COUNT);
    }else{
        m_pointerTo = (double) m_input[0].get(cv::CAP_PROP_FRAME_COUNT);
    }
    m_fromVideo = true;
    updateImage();
    return m_fromVideo;
}

void videoPreview::updateImage(){
    //m_start = boost::posix_time::microsec_clock::local_time();
    //TODO CRITICAL INFO: These two lines are extremely time-consuming as well as High CPU usage
    //m_input.set(CV_CAP_PROP_POS_FRAMES, m_position);
    //m_input.read(m_pupilFrame);
    if(m_fromVideo){
        if(m_NOV == 1){
            m_input[0] >> m_pupilFrame;
        }else if(m_NOV == 2){
            if(m_position % 2 == 0){
                m_input[0] >> m_pupilFrame;
            }else{
                m_input[1] >> m_pupilFrame;
            }
        }
        //if(pupilCoord[m_position].x()!=-1 && pupilCoord[m_position].y()!=-1 && !pupilCoord.isEmpty() && !m_pupilFrame.empty()){
        if(blink[m_position] == 0){
            if(!m_pupilFrame.empty()){
                if(pupilCoord[m_position].x() != -1){
                    cv::ellipse(m_pupilFrame,cv::Point(pupilCoord[m_position].x(),pupilCoord[m_position].y()),cv::Size(pupilDim[m_position].x()/2,pupilDim[m_position].y()/2),pupilAngle[m_position],0,360,cv::Scalar(0,0,255));
                    cv::circle(m_pupilFrame,cv::Point(pupilCoord[m_position].x(),pupilCoord[m_position].y()),3,cv::Scalar(0,0,255),-1);
                    cv::circle(m_pupilFrame,cv::Point(glintD[m_position].x(),glintD[m_position].y()),8,cv::Scalar(50,150,255));
                    cv::circle(m_pupilFrame,cv::Point(glintI[m_position].x(),glintI[m_position].y()),8,cv::Scalar(0,255,0));
                }
            }
        }
        if(!m_pupilFrame.empty()){
            cv::putText(m_pupilFrame, QString("%1x").arg(m_speedLabels.at(m_speed)).toLatin1().data(), cv::Point(m_pupilFrame.size().width-128,m_pupilFrame.size().height-20), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255,255,255),1,1);
            update();
        }
        emit newPos(m_position);
        if(++m_position > m_pointerTo){
            m_position = m_pointerFrom;
            if(m_NOV > 1){
                for(int i=0;i<m_NOV;i++)
                    m_input[i].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom/2);
            }else{
                m_input[0].set(cv::CAP_PROP_POS_FRAMES, m_pointerFrom);
            }
        }
    }else{
        stop();
    }
}
void videoPreview::setData(OData *data){
    QRaw valueRaw;
    pupilCoord.clear();
    pupilDim.clear();
    pupilAngle.clear();
    glintI.clear();
    glintD.clear();
    blink.clear();
    QVectorIterator< QRaw > itemsRaw(data->getData());
    while(itemsRaw.hasNext()){
        valueRaw = itemsRaw.next();
        pupilCoord.push_back(QPointF(valueRaw.x(),valueRaw.y()));
        pupilDim.push_back(QPointF(valueRaw.width(),valueRaw.height()));
        pupilAngle.push_back(valueRaw.angle());
        glintI.push_back(valueRaw.glint(LEFT));
        glintD.push_back(valueRaw.glint(RIGHT));
        blink.push_back(valueRaw.getBlink());
    }
}
