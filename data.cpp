#include "data.h"
#include <iostream>

//#include "utilsprocess.h"

///// ODATA
OData::OData(QObject *parent) : QObject(parent){
    qDebug()<<"Step 0";
       //m_versions = new OVersions();
    qDebug()<<"Step 1";
        m_age = 0;
    qDebug()<<"Step 2";
        m_headTremor=false;
    qDebug()<<"Step 3";
}

//Oscann 4.0.9 const int OData::open(){
int OData::open(bool processing){
    int result = 0;
    if (m_clbFullName.isEmpty() || m_tstFullName.isEmpty()){
        m_lastError = "Neither calibration nor test file was selected";
        return -1;
    }
    //Oscann 4.0.5 (Begin)
    m_csvFileName = m_tstFullName;
    m_csvFileName.replace("dat", "csv");
    //Oscann 4.0.9 QFile csvFile(m_csvFileName);
    m_csvFile = new QFile(m_csvFileName); //aqui se crea el archivo .csv
    //Oscann 4.0.9 if(csvFile.exists())
    if(m_csvFile->exists() && processing == false)
        result = 1;
    //Oscann 4.0.5 (End)
    m_blinkFileName = m_clbFullName;
    read(new QFile(m_clbFullName), m_calibrationData, true);
    m_clbFails = m_fails;
    m_blinkFileName = m_tstFullName;
    read(new QFile(m_tstFullName), m_testData);
    m_tstFails = m_fails;
    m_lastError = "Successful data loading from files " + m_clbFullName + " and " + m_tstFullName;
    return result;
}

void OData::calculateMeanAndStd(){
    qDebug()<<"---------------------------START FUNCTION: "<<Q_FUNC_INFO;
    double meanXAUX, meanYAUX, stdXAUX, stdYAUX;
    double meanX, meanY, stdX, stdY;
    meanXAUX = m_sumX/m_indices.length();
    meanYAUX = m_sumY/m_indices.length();
    stdXAUX = 0.0;
    stdYAUX = 0.0;
    for(int i=0;i<m_indices.length();i++){
        stdXAUX += std::pow(m_rawData[m_indices.at(i)].gaze().x()-meanXAUX, 2);
        stdYAUX += std::pow(m_rawData[m_indices.at(i)].gaze().y()-meanYAUX, 2);
    }
    stdXAUX = std::sqrt(stdXAUX/m_indices.length());
    stdYAUX = std::sqrt(stdYAUX/m_indices.length());

    QVector<int> indices;
    m_sumX = 0.0;
    m_sumY = 0.0;
    for(int i=m_calibrationRanges.back().first;i<m_calibrationRanges.back().second;i++){
//        std::cout<<"x: "<<m_rawData[i].gaze().x()
//                <<"\tmeanXAUX: "<<meanXAUX
//                <<"\tabsX: "<<qAbs(m_rawData[i].gaze().x()-meanXAUX)
//                <<"\tstdXAUX: "<<stdXAUX
//                <<"\ty: "<<m_rawData[i].gaze().y()
//                <<"\tmeanYAUX: "<<meanYAUX
//                <<"\tabsY: "<<qAbs(m_rawData[i].gaze().y()-meanYAUX)
//                <<"\tstdYAUX: "<<stdYAUX
//                <<"\tsumX: "<<m_sumX
//                <<"\tsumY: "<<m_sumY;
        if((qAbs(m_rawData[i].gaze().x()-meanXAUX) < (2.0*stdXAUX)) && (qAbs(m_rawData[i].gaze().y()-meanYAUX) < (2.0*stdYAUX))){
            m_sumX += m_rawData[i].gaze().x();
            m_sumY += m_rawData[i].gaze().y();
            indices.push_back(i);
            //std::cout<<" TRUE ";
        }else{
            //std::cout<<" FALSE ";
        }
        //std::cout<<std::endl;
    }
    stdX = 0.0;
    stdY = 0.0;
    if(indices.length() > 0){
        meanX = m_sumX / indices.length();
        meanY = m_sumY / indices.length();
        for(int i=0;i<indices.length();i++){
            stdX += std::pow(m_rawData[indices.at(i)].gaze().x()-meanX, 2);
            stdY += std::pow(m_rawData[indices.at(i)].gaze().y()-meanY, 2);
        }
    }


    m_meanStdX.push_back(QPair<double,double>(meanX, std::sqrt(stdX/indices.length())));
    m_meanStdY.push_back(QPair<double,double>(meanY, std::sqrt(stdY/indices.length())));
//    std::cout<<" Range: "<<m_meanStdX.length()
//             <<" meanX: "<<m_meanStdX.back().first<<", stdX: "<<m_meanStdX.back().second
//             <<" meanXAUX: "<<meanXAUX<<", stdXAUX: "<<stdXAUX
//             <<" meanY: "<<m_meanStdY.back().first<<", stdY: "<<m_meanStdY.back().second
//             <<" meanYAUX: "<<meanYAUX<<", stdYAUX: "<<stdYAUX

//             <<std::endl;


    m_sumX = 0.0;
    m_sumY = 0.0;
    m_indices.clear();
}

void OData::read(QFile *file,  QVector< QRaw > &data, bool clb){
    QString line;
    QStringList elements;
    QPointF pupil;
    QPoint stimulus;
    m_fails = 0;
    m_blinkFileName.replace("dat", "blk");
    QFile *b_file = new QFile(m_blinkFileName); //aquí se genera el .blk
    m_blinks.clear();
    m_blkDefined = false;
    if ( b_file->open(QIODevice::ReadOnly) ) {
        QTextStream t( b_file );
        line = t.readLine();
        int i = 0;
        while (!line.isNull()) {
            elements = line.split(" ");
            m_blinks.push_back(std::make_pair(atoi(elements[0].toLatin1().data()),atoi(elements[1].toLatin1().data())));
            i++;
            line = t.readLine();
        };
        m_blkDefined = true;
    }
    countBlinks = m_blinks.size();
    if ( file->open(QIODevice::ReadOnly) ) {
        data.clear(); //Borrar datos anteriores antes de cargar
        m_rawData.clear();
        if(clb){
            m_calibrationRanges.clear();
            m_meanStdX.clear();
            m_meanStdY.clear();
            m_rawData.clear();
        }
        QTextStream t( file );
        line = t.readLine();
        double msec, time=0, frequency = 10.0;
        int frame = 0;
        unsigned int blink = 0;
        bool flg_blink = false;
        int lastSX=-1, lastSY=-1;
        int rangeInit = frame;
        //TODO: use QLocale().decimalPoint()
        QChar separator(',');
        QString num("0.5");
        if(atof(num.toLatin1().data())==0.5)
            separator='.';
        bool first = true;
        boost::posix_time::ptime t1, t2;
        boost::posix_time::time_duration t3;
        m_sumX = 0.0;m_sumY = 0.0;
        while (!line.isNull()) {
             line.replace('.',separator);
                elements = line.split(" ");
                if(elements.size()!=13 && elements.size()!=12){
                    if(elements.size()==12){
                        m_lastError = "ERROR|It could be an old *.dat file. The format has changed, please reprocess it before loading.|File name: " + file->fileName();
                    }else{
                        m_lastError = "ERROR|File not supported|File name: " + file->fileName() + " " + QString::number(elements.size()) + " " + QString::number(data.size());
                    }
                    return void();
                }
                if(m_blinks.size() > 0 && (blink < m_blinks.size())){
                    if(frame >= m_blinks.at(blink).first && frame <= m_blinks.at(blink).second){
                        flg_blink = true;
                    }else{
                        flg_blink = false;
                    }
                    if(frame > m_blinks.at(blink).second)
                        blink++;
                }
                pupil.setX(atof(elements[1].replace('.',separator).toLatin1().data()));
                pupil.setY(atof(elements[2].replace('.',separator).toLatin1().data()));
                if(pupil.x() < 0.0 && pupil.y() < 0.0)
                    m_fails++;
                if(elements.size()==12){
                    //ELIMINAR ESTE SOPORTE A PRUEBAS ANTIGUAS MáS ADELANTE
                    stimulus.setX(atoi(elements[10].toLatin1().data()));
                    stimulus.setY(atoi(elements[11].toLatin1().data()));
                    data.push_back(
                        QRaw(   atol(elements[0].toLatin1().data()),
                                pupil.x(),
                                pupil.y(),
                                atof(elements[3].replace('.',separator).toLatin1().data()),
                                atof(elements[4].replace('.',separator).toLatin1().data()),
                                0,
                                atof(elements[5].replace('.',separator).toLatin1().data()),
                                atof(elements[6].replace('.',separator).toLatin1().data()),
                                atof(elements[7].replace('.',separator).toLatin1().data()),
                                atof(elements[8].replace('.',separator).toLatin1().data()),
                                stimulus.x(),
                                stimulus.y(),
                                flg_blink
                        )
                    );
                    m_rawData.push_back(
                        QRaw(   atol(elements[0].toLatin1().data()),
                                pupil.x(),
                                pupil.y(),
                                atof(elements[3].replace('.',separator).toLatin1().data()),
                                atof(elements[4].replace('.',separator).toLatin1().data()),
                                0,
                                atof(elements[5].replace('.',separator).toLatin1().data()),
                                atof(elements[6].replace('.',separator).toLatin1().data()),
                                atof(elements[7].replace('.',separator).toLatin1().data()),
                                atof(elements[8].replace('.',separator).toLatin1().data()),
                                stimulus.x(),
                                stimulus.y(),
                                flg_blink
                        )
                    );
                }else{
                    if(QString(elements[0]).contains((QLocale().decimalPoint()))){
                        if(first){
                            first = false;
                            t1 = boost::posix_time::from_iso_string(QString(elements[0]).toLatin1().data());

                        }else{
                            t3 = boost::posix_time::from_iso_string(QString(elements[0]).toLatin1().data()) - t1;
                            t2 = t1;
                            t1 = boost::posix_time::from_iso_string(QString(elements[0]).toLatin1().data());
                        }
                        msec = t3.total_microseconds()/1000.0;
                        m_micro = true;
                    }
                    else{
                        msec = atol(QString(elements[0]).toLatin1().data());
                        m_micro = false;
                    }
                    if(msec > 100.0)
                        msec = frequency;
                    time += msec;
                    stimulus.setX(atoi(elements[11].toLatin1().data()));
                    stimulus.setY(atoi(elements[12].toLatin1().data()));
                    data.push_back(
                          QRaw( time,
                                pupil.x(),
                                pupil.y(),
                                atof(elements[3].replace('.',separator).toLatin1().data()),
                                atof(elements[4].replace('.',separator).toLatin1().data()),
                                atof(elements[5].replace('.',separator).toLatin1().data()),
                                atof(elements[6].replace('.',separator).toLatin1().data()),
                                atof(elements[7].replace('.',separator).toLatin1().data()),
                                atof(elements[8].replace('.',separator).toLatin1().data()),
                                atof(elements[9].replace('.',separator).toLatin1().data()),
                                stimulus.x(),
                                stimulus.y(),
                                flg_blink
                        )
                    );
                    m_rawData.push_back(
                          QRaw( time,
                                pupil.x(),
                                pupil.y(),
                                atof(elements[3].replace('.',separator).toLatin1().data()),
                                atof(elements[4].replace('.',separator).toLatin1().data()),
                                atof(elements[5].replace('.',separator).toLatin1().data()),
                                atof(elements[6].replace('.',separator).toLatin1().data()),
                                atof(elements[7].replace('.',separator).toLatin1().data()),
                                atof(elements[8].replace('.',separator).toLatin1().data()),
                                atof(elements[9].replace('.',separator).toLatin1().data()),
                                stimulus.x(),
                                stimulus.y(),
                                flg_blink
                        )
                    );
                }
                if(clb){
                    if(pupil.x() > 0.0 && !flg_blink){
                        m_sumX += data.back().gaze().x();
                        m_sumY += data.back().gaze().y();
                        m_indices.push_back(frame);
                    }
                    if((lastSX != stimulus.x()) || (lastSY != stimulus.y())){
                        if(rangeInit != frame){
                            m_calibrationRanges.push_back(QPair<int,int>(rangeInit, frame));
                            calculateMeanAndStd();
                        }
                        rangeInit = frame;

                    }
                    lastSX = stimulus.x();
                    lastSY = stimulus.y();
                }
                line = t.readLine();
                frame++;
                frequency = time/static_cast<double>(frame);
        };
        if(clb){
            m_calibrationRanges.push_back(QPair<int,int>(rangeInit, frame));
            calculateMeanAndStd();
        }
        file->close();
    } else {
        m_lastError = "ERROR|Unable to open the file|File name: " + file->fileName();
        return void();
    }
    if(data.size()<=0){
        m_lastError = "ERROR|Trying to load an empty file|File name: " + file->fileName();
        return void();
    }
    return void();
}




void OData::setTestPath(const QString path, const QString testName){
    m_testPath = path;
    m_testName = testName;
}

//Oscann 4.0.5: New method
void OData::importCsv(){
    QFile file(m_csvFileName);
    QString decimal = ",";
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<Q_FUNC_INFO<<" importing CSV: "<<m_csvFileName;
        QString line;
        QStringList elements;
        QTextStream qTS( &file );
        line = qTS.readLine();
        qDebug()<<Q_FUNC_INFO<<" line: "<<line;
        //v4.0.12
        //elements = line.split(QLocale().decimalPoint());
        elements = line.split(decimal);
        //v4.0.12
        m_csvClb = elements[12];
        qDebug()<<Q_FUNC_INFO<<" calibration of the test in csv it can be changed: "<<m_csvClb;
        line = qTS.readLine();
        line = qTS.readLine();
        m_processedData.clear();
        while (!qTS.atEnd()){
            //elements = line.split(QLocale().decimalPoint());
            elements = line.split(decimal);
            m_processedData.push_back(OProcessed(atof(elements[0].replace(".",QLocale().decimalPoint()).toLatin1().data()),
                                                 atof(elements[1].replace(".",QLocale().decimalPoint()).toLatin1().data()),   //X
                                                 atof(elements[2].replace(".",QLocale().decimalPoint()).toLatin1().data()),   //Y
                                                 atof(elements[10].replace(".",QLocale().decimalPoint()).toLatin1().data()),  //rawX
                                                 atof(elements[11].replace(".",QLocale().decimalPoint()).toLatin1().data()),  //rawY
                                                 atof(elements[3].replace(".",QLocale().decimalPoint()).toLatin1().data()),   //stimuliX
                                                 atof(elements[4].replace(".",QLocale().decimalPoint()).toLatin1().data()),   //stimuliY
                                                 atof(elements[9].replace(".",QLocale().decimalPoint()).toLatin1().data()),
                                                 atoi(elements[12].replace(".",QLocale().decimalPoint()).toLatin1().data()),
                                                 elements.length() == 14 ? atoi(elements[13].toLatin1().data()) : true));
            OProcessedExtra *extraData = new OProcessedExtra();
            QPointF vel(atof(elements[5].replace(".",QLocale().decimalPoint()).toLatin1().data()),atof(elements[6].replace(".",QLocale().decimalPoint()).toLatin1().data()));
            QPointF posRaw(atof(elements[10].replace(".",QLocale().decimalPoint()).toLatin1().data()),atof(elements[11].replace(".",QLocale().decimalPoint()).toLatin1().data()));
            extraData->setVel(vel);
            extraData->setPosRaw(posRaw);
            m_processedDataExtra.push_back(*extraData);
            //qDebug()<<atof(elements[0].replace(".",QLocale().decimalPoint()).toLatin1().data());
            qDebug()<<m_processedData.size();
            line = qTS.readLine();
            qDebug()<<Q_FUNC_INFO<<" line: "<<line;
        }
    }


}

void OData::exportCsv(){
    //Oscann 4.0.9: QFile file(m_testPath + "/" + m_testName + ".csv");
    //Oscann 4.0.9: if(file.open(QIODevice::WriteOnly)){
    if(m_csvFile->open(QIODevice::WriteOnly)){
        qDebug()<<Q_FUNC_INFO<<" exporting CSV: "<<m_csvFile->fileName();
        //Oscann 4.0.9 QTextStream stream(&file);
        QTextStream stream(m_csvFile);
        utilsProcess::resolution=resolution;
        utilsProcess::sDist=sDist;
        utilsProcess::sWidth=sWidth;
        qDebug()<<Q_FUNC_INFO<<" m_testPath: "<<m_testPath;
        qDebug()<<Q_FUNC_INFO<<", m_testName: "<<m_testName;
        qDebug()<<Q_FUNC_INFO<<", m_clbBaseName: "<<m_clbBaseName;
        qDebug()<<Q_FUNC_INFO<<", Subject: "<<m_testPath.split("/")[m_testPath.split("/").size()-2];
        qDebug()<<Q_FUNC_INFO<<", Calibration: "<<m_clbBaseName.split(".").at(0);
        stream<<"Resolution,"<<resolution.x()<<","<<resolution.y()<<",Distance,"<<sDist<<",Width,"<<sWidth
              <<",Subject,"<<m_testPath.split("/")[m_testPath.split("/").size()-2]<<",Test,"<<m_testName<<",Calibration,"<<m_clbBaseName.split(".").at(0)
              //Oscann 4.0.7
              //<<",Oscann, "<<m_versions->oscann()
              //<<",libTracker, "<<m_versions->tracker()
              //Oscann 4.0.9 <<",Analizer, "<<OVersions::analizer()
              <<",crtime, "<<QDateTime::currentDateTime().toString("MMddyyyy-hhmmss")
              <<endl;
        stream<<"Time(ms),GazeX(deg),GazeY(deg),StimulusX(deg),StimulusY(deg),GazeVelX(deg/s),GazeVelY(deg/s),ErrorX(deg),ErrorY(deg),PupilArea(px^2),GazeRawX(deg),GazeRawY(deg),Blinks,valid"<<endl;
        for(int i=0;i<m_processedData.size();i++){
            stream<<m_processedData[i].time()<<","; //TIEMPO
            stream<<m_processedData[i].x()<<","<<m_processedData[i].y()<<","; //GAZE EN DEG
            stream<<m_processedData[i].xS()<<","<<m_processedData[i].yS()<<","; //ESTIMULO EN DEG
            stream<<m_processedDataExtra[i].getVel().x()<<","<<m_processedDataExtra[i].getVel().y()<<","; //GAZEVEL EN DEG
            stream<<m_processedDataExtra[i].getError().x()<<","<<m_processedDataExtra[i].getError().y()<<","; //ERROR EN DEG
            stream<<m_processedData[i].area()<<","; //AREA PUPILA
            stream<<m_processedDataExtra[i].getPosRaw().x()<<","<<m_processedDataExtra[i].getPosRaw().y()<<","; //GAZE SIN FILTRAR
            stream<<m_processedData[i].getParpadeo()<<",";
            stream<<m_processedData[i].valid()<<endl;
        }
        //Oscann 4.0.9 file.close();
        m_csvFile->close();
    }
}
bool OData::removeTestFolder(QString testPath){
    QDir dir_patient(testPath);
    qDebug()<<"patient path to delete: "<<testPath;
    if (dir_patient.removeRecursively())
        return true;
    else return false;
}


QString OData::folderExistance(QString test_comprobar,QString patientSession){ //pasar solo el tipo de test: TSVV, TSMH,...
    QDir dir_patient(patientSession);//(getSessionName)
    qDebug()<<"directorio del paciente: "<<patientSession<< "y numnero de archivos" <<dir_patient.count();
    QFileInfoList list_tests=dir_patient.entryInfoList();
    for(int i=0;i<dir_patient.count();i++)
    {
        qDebug()<<"comparamos: "<<list_tests[i].baseName()<<" con "<<test_comprobar;
        if (list_tests[i].baseName().contains(test_comprobar,Qt::CaseInsensitive)) //si ya esta preguntamos y borramos
        {
            qDebug()<<"test que borrar: "<<list_tests[i].absoluteFilePath();
            return list_tests[i].absoluteFilePath();
        }
    }
    return "";
}

void OData::exportFolder(QString originalDir, QString saveDir){
    QStringList tmpList=originalDir.split("/");

    QDir tmpDir(QString(saveDir+"/"+tmpList[tmpList.size()-2]+"/"+tmpList.last()));
    if(!tmpDir.exists())
        tmpDir.mkpath(".");

    QDir rawDir(QString(tmpDir.absolutePath()+"/raw"));
    if(!rawDir.exists())
        rawDir.mkpath(".");


    QStringList toCopyFiles;
    QDir exploreFiles(originalDir);
    for(int i=0;i<exploreFiles.entryList(QDir::Files|QDir::Hidden).size();i++)
        toCopyFiles.push_back(originalDir+"/"+exploreFiles.entryList(QDir::Files|QDir::Hidden).at(i));

    exploreFiles.setPath(QString(originalDir+"/raw"));
    toCopyFiles.push_back(originalDir+"/raw/"+exploreFiles.entryList(QStringList("*.avi"),QDir::Files).at(0));

    for(int i=0;i<toCopyFiles.size()-1;i++)
        QFile(QString(toCopyFiles.at(i))).copy(QString(tmpDir.absolutePath()+"/"+toCopyFiles.at(i).split("/").last()));

    QFile(QString(toCopyFiles.last())).copy(QString(tmpDir.absolutePath()+"/raw/"+toCopyFiles.last().split("/").last()));
}

/**
  *   @brief  Comprueba si se han realizado todos para la patologia
  *
  *   @param  TestsDone Test realizandos hasta ahora en la session.
  *   @return QStringList con los test que faltan
  */
QStringList OData:: checkAllTest(QStringList TestsDone){
    QStringList NoDoneTest;
    qDebug()<<"START: "<<Q_FUNC_INFO;
    for (int i=0;i<m_testPathology.length();i++){
        qDebug()<<"Esta la prueba "<<m_testPathology.at(i)<<" en los test realizados?";
        for (int j=0;j<TestsDone.length();j++){
            if(TestsDone.at(j).contains(m_testPathology.at(i))){
                qDebug()<<"El test "<<m_testPathology.at(i)<< " Se ha realizado en la session del paciente";
                break;
            }else{
                if (j == TestsDone.length()-1){
                qDebug()<<"Los test realizados no contienen el test:"<<m_testPathology.at(i);
                NoDoneTest.push_back(getTitle(m_testPathology.at(i)));
                }
            }
        }
    }
    NoDoneTest.removeDuplicates();
    return NoDoneTest;
}
QStringList OData:: getTestPathologyList(){
    QStringList m_testPathology_new;
    for(int i = 0;i<m_testPathology.length();i++){
        m_testPathology_new.push_back(getTitle(m_testPathology.at(i)));
    }
    m_testPathology_new.removeDuplicates();
    return m_testPathology_new;
}
/**
  *   @brief  Asigna un título a cada tipo de prueba
  *
  *   @param  prenombrePrueba fragmento del nombre de la prueba que indica su tipo
  *   @return QString con el nombre de la prueba
  */

QString OData::getTitle(QString prenombrePrueba){
    if(prenombrePrueba=="TSVH"){
        return "SACADAS VISUALES HORIZONTALES";
    }else if(prenombrePrueba=="TSVV"){
        return "SACADAS VISUALES VERTICALES";
    }else if(prenombrePrueba=="TSMH"){
        return "SACADAS DE MEMORIA HORIZONTALES";
    }else if(prenombrePrueba=="TSMV"){
        return "SACADAS DE MEMORIA VERTICALES";
    }else if(prenombrePrueba=="TASH" || prenombrePrueba=="TASVH"){
        return "ANTI-SACADAS VISUALES HORIZONTALES";
    }else if(prenombrePrueba=="TASV" || prenombrePrueba=="TASVV"){
        return "ANTI-SACADAS VISUALES VERTICALES";
    }else if(prenombrePrueba=="TASMH"){
        return "ANTI-SACADAS DE MEMORIA HORIZONTALES";
    }else if(prenombrePrueba=="TASMV"){
        return "ANTI-SACADAS DE MEMORIA HORIZONTALES";
    }else if(prenombrePrueba.contains("TIF")){
        return "IMAGEN FIJA";
    }else if(prenombrePrueba.contains("TSLL")){
        return "SEGUIMIENTO LENTO LINEAL";
    }else if(prenombrePrueba.contains("TSLSH")){
        return "SEGUIMIENTO LENTO SINUSOIDAL HORIZONTAL";
    }else if(prenombrePrueba.contains("TSLSV")){
        return "SEGUIMIENTO LENTO SINUSOIDAL VERTICAL";
    }else if(prenombrePrueba=="TFIX"){
        return "FIJACIÓN";
    }else if(prenombrePrueba.contains("TOPT")){
        return "OPTOCINÉTICO";
    }else if(prenombrePrueba=="TPL"){
        return "REFLEJO PUPILAR";
    }else if(prenombrePrueba=="TCS"){
        return "SACADAS COUNTERMANDING";
    }else if(prenombrePrueba=="CC9" || prenombrePrueba=="CA9"){
        return "CALIBRACIÓN";
    }else{
        return "INDEFINIDA";
    }
}
QStringList OData::getPatientDetails(){
    QStringList details;
    details.push_back(m_sessionName);
    details.push_back(QString::number(m_age));
    details.push_back(m_pathology.join(", "));
    return details;
}












