#include <qutils.h>

//COLOR-SCHEME
colorScheme::colorScheme(QObject *parent)  : QObject(parent){
    if(!openXmlReader()){
        openXmlWriter();
        openXmlReader();
    }
}


void colorScheme::readXmlElements(){
    m_xmlReader.readNext();
    while(!m_xmlReader.atEnd()){
        if(m_xmlReader.isStartElement()){
            if(m_xmlReader.name() == "gui"){
                while(!m_xmlReader.atEnd()){
                    if(m_xmlReader.isEndElement()){
                        m_xmlReader.readNext();
                        break;
                    }else if(m_xmlReader.isStartElement()){
                        if(m_xmlReader.name() == "bg"){
                            m_guiBG = QColor(m_xmlReader.attributes().value("color").toString());
                            m_xmlReader.readNext();
                        }
                    }
                    m_xmlReader.readNext();
                }
            }else if(m_xmlReader.name() == "graph"){
                while(!m_xmlReader.atEnd()){
                    if(m_xmlReader.isEndElement()){
                        m_xmlReader.readNext();
                        break;
                    }else if(m_xmlReader.isStartElement()){
                        if(m_xmlReader.name() == "bg"){
                            m_graphBG = QColor(m_xmlReader.attributes().value("color").toString());
                            m_xmlReader.readNext();
                       }
                       else if(m_xmlReader.name() == "fg"){
                            m_graphFG = QColor(m_xmlReader.attributes().value("color").toString());
                            m_xmlReader.readNext();
                       }
                        else if(m_xmlReader.name() == "gridY"){
                             m_graphGridY = QColor(m_xmlReader.attributes().value("color").toString());
                             m_xmlReader.readNext();
                        }
                        else if(m_xmlReader.name() == "gridX"){
                             m_graphGridX = QColor(m_xmlReader.attributes().value("color").toString());
                             m_xmlReader.readNext();
                        }
                        else if(m_xmlReader.name() == "stimulus"){
                             m_graphStimulus = QColor(m_xmlReader.attributes().value("color").toString());
                             m_xmlReader.readNext();
                        }
                        else if(m_xmlReader.name() == "gaze"){
                             m_graphGaze = QColor(m_xmlReader.attributes().value("color").toString());
                             m_xmlReader.readNext();
                        }
                    }
                    m_xmlReader.readNext();
                }
            }
        }
        m_xmlReader.readNext();
    }
}


bool colorScheme::openXmlWriter(){
    QString fileName = QString("%1/%2").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg("colorscheme.xml");
    if(!QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).exists())
        QDir().mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]);
    m_xmlFileName = new QFile(fileName);
    if(m_xmlFileName->open(QIODevice::WriteOnly)){
        m_xmlWriter = new QXmlStreamWriter(m_xmlFileName);
        m_xmlWriter->setAutoFormatting(true);
        m_xmlWriter->writeStartDocument();
        m_xmlWriter->writeStartElement("scheme");
        //----- ----- ----- ----- ----- ----- ----- ----- ----- GUI
        m_xmlWriter->writeStartElement("gui");
            m_xmlWriter->writeStartElement("bg");
                m_xmlWriter->writeAttribute("color", "#203746");    //#013861,
                m_xmlWriter->writeEndElement();
        m_xmlWriter->writeEndElement();
        //----- ----- ----- ----- ----- ----- ----- ----- ----- GUI
        //----- ----- ----- ----- ----- ----- ----- ----- ----- graph
        m_xmlWriter->writeStartElement("graph");
        m_xmlWriter->writeStartElement("bg");
            m_xmlWriter->writeAttribute("color", "#1c303d");    //#012540
        m_xmlWriter->writeEndElement();
        m_xmlWriter->writeStartElement("fg");
            m_xmlWriter->writeAttribute("color", "transparent");    //#012540
        m_xmlWriter->writeEndElement();
            m_xmlWriter->writeStartElement("gridY");
                m_xmlWriter->writeAttribute("color", "#ffffff");
            m_xmlWriter->writeEndElement();
            m_xmlWriter->writeStartElement("gridX");
                m_xmlWriter->writeAttribute("color", "#ffffff");
            m_xmlWriter->writeEndElement();
            m_xmlWriter->writeStartElement("stimulus");
                m_xmlWriter->writeAttribute("color", "#3b464e");
            m_xmlWriter->writeEndElement();
            m_xmlWriter->writeStartElement("gaze");
                m_xmlWriter->writeAttribute("color", "#00ccff");
            m_xmlWriter->writeEndElement();
        m_xmlWriter->writeEndElement();
        //----- ----- ----- ----- ----- ----- ----- ----- ----- graph
        m_xmlWriter->writeEndElement();
        m_xmlWriter->writeEndDocument();
        m_xmlFileName->close();
        return true;
    }
    return false;
}


bool colorScheme::openXmlReader(){
    QString fileName = QString("%1/%2").arg(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).arg("colorscheme.xml");
    if(!QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]).exists())
        QDir().mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation)[0]);
    m_xmlFileName = new QFile(fileName);
    if(m_xmlFileName->open(QIODevice::ReadOnly)){
        //m_xmlReader = new QXmlStreamReader(m_xmlFileName);
        m_xmlReader.setDevice(m_xmlFileName);
        readXmlElements();
        return true;
    }
    return false;
}



OCTSettings::OCTSettings(QObject *parent)  : QObject(parent){
    m_settings = new QSettings(QApplication::applicationDirPath() + "/demosettings.ini", QSettings::IniFormat);
    m_clbRecordingTime = m_settings->value("stimulus/clbRecordingTime","-1").toInt();
    if(m_clbRecordingTime == -1)
        setClbRecordingTime(1500);
    m_tstRecordingTime = m_settings->value("stimulus/tstRecordingTime","-1").toInt();
    if(m_tstRecordingTime == -1)
        setTstRecordingTime(1500);
    m_stimulusSize = m_settings->value("stimulus/stimulusSize","-1").toInt();
    if(m_stimulusSize==-1)
        setStimulusSize(20);
    m_fixedPointSize = m_settings->value("stimulus/fixedPointSize","-1").toInt();
    if(m_fixedPointSize==-1)
        setFixedPointSize(20);
    //Calibration and test variables
    m_degrees2px = m_settings->value("stimulus/degrees2px","-1").toFloat();
    m_laps = m_settings->value("CalibrationTest/laps","-1").toInt(); //PL
    if(m_laps==-1)
        setLaps(3);
    m_testTime = m_settings->value("CalibrationTest/testTime","-1").toInt(); //PL
    if(m_testTime==-1)
        setTestTime(30);
    m_img1Path = m_settings->value("stimulus/img1Path","null").toString();
    if(m_img1Path=="null")
        setImg1Path("Default image");
    m_img2Path = m_settings->value("stimulus/img2Path","null").toString();
    if(m_img2Path=="null")
        setImg2Path("Default image");
    m_img3Path = m_settings->value("stimulus/img3Path","null").toString();
    if(m_img3Path=="null")
        setImg3Path("Default image");
    m_img4Path = m_settings->value("stimulus/img4Path","null").toString();
    if(m_img4Path=="null")
        setImg4Path("Default image");
    m_img5Path = m_settings->value("stimulus/img5Path","null").toString();
    if(m_img5Path=="null")
        setImg5Path("Default image");
    m_img6Path = m_settings->value("stimulus/img6Path","null").toString();
    if(m_img6Path=="null")
        setImg6Path("Default image");
    m_img7Path = m_settings->value("stimulus/img7Path","null").toString();
    if(m_img7Path=="null")
        setImg7Path("Default image");
    m_img8Path = m_settings->value("stimulus/img8Path","null").toString();
    if(m_img8Path=="null")
        setImg8Path("Default image");
    m_img9Path = m_settings->value("stimulus/img9Path","null").toString();
    if(m_img9Path=="null")
        setImg9Path("Default image");
    m_img10Path = m_settings->value("stimulus/img10Path","null").toString();
    if(m_img10Path=="null")
        setImg10Path("Default image");
    if(m_resolution == QPoint(1920,1080))
        setResolution(QPoint(1920,1080));
    m_resolution = m_settings->value("stimulus/resolution",QPoint(1920,1080)).toPoint();
    if(m_screenDistance == 60)
        setScreenDistance(60);
    m_screenDistance = m_settings->value("stimulus/screenDistance",60).toDouble();
    if(m_screenWidth == 48)
        setScreenWidth(48);
    m_screenWidth = m_settings->value("stimulus/screenWidth",48).toDouble();
    //m_mongoUrl = m_settings->value("Mongo/url","aurarobotix.ddns.net").toString();
    //m_mongoUrl = m_settings->value("Mongo/url","127.0.0.1").toString();
    m_mongoUrl = m_settings->value("Mongo/url","192.168.1.150").toString();
    //m_mongoPort = m_settings->value("Mongo/port",27017).toDouble();
    m_mongoPort = m_settings->value("Mongo/port",27017).toUInt();
    m_mainDisplay = m_settings->value("Display/main",0).toInt();
    setUtilsProcessScreen();
}

void OCTSettings::setUtilsProcessScreen(){
    utilsProcess::resolution=m_resolution;
    utilsProcess::sWidth=m_screenWidth;
    utilsProcess::sDist=m_screenDistance;
    //qDebug() << "QVars:" << utilsProcess::sDist << "," << utilsProcess::sWidth << "," << utilsProcess::resolution;
}

/*int OCTSettings::clbRecordingTime(){
    return m_clbRecordingTime;
}*/

