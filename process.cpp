#include "process.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <QString>
#include <QPointF>
#include <QFile>
#include "utilsprocess.h"
#include "logger.h"
#define PI 3.141592
/**
  *   @brief  Constructor por defecto
  *
  *   @param  parent es el objeto padre, necesario ya que se hereda de QObject
  *   @return void
  */
process::process(QObject *parent) : QObject(parent){}


void process::sendToDB(OData *data, QString sessionName, QString testName, QString mongoUrl, unsigned int mongoPort){
    qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    Logger::instance().log(" Sending to Mongo", Logger::kLogLevelDebug);
    qDebug()<<Q_FUNC_INFO<<" Sending to Mongo sessionName: "<<sessionName<<", testName: "<<testName;
    try{
        //MONGO(Begin)
        arrTime.clear();
        arrBlinks.clear();
        arrArea.clear();
        arrGazeX.clear();
        arrGazeY.clear();
        arrGazeVelocityX.clear();
        arrGazeVelocityY.clear();
        arrGazeRawX.clear();
        arrGazeRawY.clear();
        arrStimulusX.clear();
        arrStimulusY.clear();

        //MONGO(End)
        qDebug()<<"Step -1";
        qDebug()<<data->dataSize();
        for(int i=0;i<data->dataSize();i++){
             qDebug()<<"Step 0 ";
            qDebug()<<data->dataSize();
            arrTime<<data->m_processedData[i].time(); //TIEMPO
            qDebug()<<"Step 0.1 ";
            arrGazeX<<data->m_processedData[i].x();
            qDebug()<<"Step 0.2 ";
            arrGazeY<<data->m_processedData[i].y(); //GAZE EN DEG
            qDebug()<<"Step 0.3 ";
            arrStimulusX<<data->m_processedData[i].xS();
            qDebug()<<"Step 0.4 ";
            arrStimulusY<<data->m_processedData[i].yS(); //ESTIMULO EN DEG
            qDebug()<<"Step 0.5 ";
            qDebug()<<data->m_processedDataExtra.size();
            arrGazeVelocityX<<data->m_processedDataExtra[i].getVel().x();
            qDebug()<<"Step 0.6 ";
            arrGazeVelocityY<<data->m_processedDataExtra[i].getVel().y(); //GAZEVEL EN DEG
            qDebug()<<"Step 0.7 ";
            arrArea<<data->m_processedData[i].area(); //AREA PUPILA
            qDebug()<<"Step 0.8 ";
            arrGazeRawX<<data->m_processedDataExtra[i].getPosRaw().x();
            qDebug()<<"Step 0.9 ";
            arrGazeRawY<<data->m_processedDataExtra[i].getPosRaw().y(); //GAZE SIN FILTRAR
            qDebug()<<"Step 0.10 ";
            arrBlinks<<data->m_processedData[i].getParpadeo();
            //stream<<data->m_processedData[i].valid()<<endl;
             qDebug()<<"Step 1";
        }
        qDebug()<<"Step 2";

        mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(mongoUrl).arg(mongoPort).toLatin1().data()));
        //mongocxx::client client(mongocxx::uri("mongodb://localhost:27017"));
        qDebug()<<"Step 3";
        auto db = client["tests"];
        qDebug()<<"Step 4";
        if(testName[0] == 'T'){
            qDebug()<<"Step 4.1";
            if(testName.mid(0,4).compare("TASV") == 0)
                testName.remove(3,1);;
            mongocxx::collection coll = db[testName.split("-")[0].toLatin1().data()];
            qDebug()<<"Step 4.2";
            auto builder = bsoncxx::builder::stream::document{};
            //NOTE: The document of the patient is deleted if it exists to avoid duplicated docs
            //coll.delete_one(document{} << "patient" << sessionName.toLatin1().data() << bsoncxx::builder::stream::finalize);
            qDebug()<<"Step 4.3";
            std::tm tm;
            QString date = testName.split("-")[1];
            QString time = testName.split("-")[2];
            std::stringstream ss(QString("%3-%2-%1 %4:%5:%6")
                                 .arg(date.mid(0,2))
                                 .arg(date.mid(2,2))
                                 .arg(date.mid(4,4))
                                 .arg((time.mid(0,2).toInt()+1), 2, 10, QChar('0'))
                                 .arg(time.mid(2,2))
                                 .arg(time.mid(4,2)).toLatin1().data());
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            bsoncxx::document::value doc_value = builder
                    //<< "client" << "hm"
                    << "patient" << sessionName.toLatin1().data()
                    //<< "pathology" << data->m_pathology
                    //<< "age" << data->m_age
                    << "date" << bsoncxx::types::b_date{std::chrono::system_clock::from_time_t(std::mktime(&tm))}
                    << "time"
                    << arrTime
                    << "gazeX"
                    << arrGazeX
                    << "gazeY"
                    << arrGazeY
                    << "gazeRawX"
                    << arrGazeRawX
                    << "gazeRawY"
                    << arrGazeRawY
                    << "gazeVelocityX"
                    << arrGazeVelocityX
                    << "gazeVelocityY"
                    << arrGazeVelocityY
                    << "stimulusX"
                    << arrStimulusX
                    << "stimulusY"
                    << arrStimulusY
                    << "blinks"
                    << arrBlinks
                    << "area"
                    << arrArea
                    << bsoncxx::builder::stream::finalize;
            bsoncxx::document::view view = doc_value.view();
            bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);
            qDebug()<<"Step 5";
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }

}

/**
  *   @brief  Estima la mirada de una prueba en base a una calibración
  *
  *   @details
  *
  *   Se realiza la estimacion completa. Se comienza por preprocesar y separar los datos de la calibración
  *   y filtrarlos usando RANSAC para extraer un punto por cada zona de fijación. Con dichos puntos se
  *   puede generarla matriz de intepolación por mínimos cuadrados.
  *
  *   Los datos del test tambien se preprocesan (sacar vector glint pupila, hacer que el tiempo empiece en 0)
  *   Se aplican los filtros correspondientes para eliminar los parpadeos y el ruido. Se aplica la matriz
  *   de interpolación para obtener la estimación de la mirada en pantalla. Finalmente se cambia el origen de
  *   coordenadas al centro de la pantalla y se calculan la primera y segunda derivada de la mirada (Vel y acc)
  *
  *   Además se calcula el área de la pupila. Esta también se filtra
  *
  *   @param  *data es el puntero al objeto que almacena los datos
  *   @param  resolution es un QPoint con la resolucion de la pantalla en píxeles
  *   @param  screenDistance es la distancia del paciente a la pantalla en cm
  *   @param  screenWidth es el ancho de la pantalla en cm
  *   @return QString con el resultado (SUCCESS, WARNING o ERROR) y comentarios al respecto separados por '|'
  */
int process::calculateGaze(OData *data, QString testName, QPoint resolution,double screenDistance,double screenWidth, bool visualization){
    //esta función rellena todos los campos de data
    qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    int i=0;
    int returnValue=1;                                                      //-1: Error, 0: Warning, 1: Success
     utilsProcess::resolution=resolution;
     double xResolution = (resolution.x()/2);
     double yResolution = (resolution.y()/2);
     utilsProcess::sDist=screenDistance;
     utilsProcess::sWidth=screenWidth;
    Logger::instance().log("Starting with test " + testName.toStdString(), Logger::kLogLevelDebug);
    Logger::instance().log("Starting calculateGaze", Logger::kLogLevelDebug);
    if(data->m_calibrationData.length()<5||data->m_testData.length()<5){    //Return if test or calibration lenght is less than 5 frames
        m_lastError="Test/Calibration too short. Probably a problem while recording the eye";
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        return -1;
    }
    QVector<QRaw>::iterator iterator;
    // ---------------------------------------
    // Preprocess & separate calibration file
    // ---------------------------------------
    if(data->m_calibrationData.length()==0){
        m_lastError = "Calibration file is empty";
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        return -1;
    }
    if(data->m_calibrationData.length()*0.5 < data->clbFails()){
        m_lastError = "More than fifty percent of the calibration fail to calculate eye position";
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        return -1;
    }
    // --------------------------------------
    // Filter calibration points using RANSAC
    // --------------------------------------
    if(filtradoModeloRANSAC(data) < 0){
        m_lastError = "Bad calibration";
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        return -1;
    }
    // ------------------------------------
    // Preprocess test file: Preparar los datos de test. Eliminar saltos temporales y separar en 2 vectores
    // ------------------------------------
    double lastX, lastY;
    QVector<double> rawDataX,rawDataY;
    QVector<int> blinks;
    //TODO: NOBLK
    QVector<int> noBlkblinks;
    bool blinkDetected=false;
    QVector <int> blinkInit, blinkEnd;
    time.clear();
    iterator=data->m_testData.begin();
    int frameOk = -1;
    bool frameOkDefined = false;
    double frameOkX;
    double frameOkY;
    lastX = -1.0;
    lastY = -1.0;
    i=0;
    Logger::instance().log(" Starting for loop parsing each line ", Logger::kLogLevelDebug);
    for(iterator=data->m_testData.begin();iterator<data->m_testData.end();iterator++){
        time.push_back(iterator->getTime());
        if(iterator->getBlink()){
            blinks.push_back(1); //cargamos en blinks uno si es parpadeo
        }else{
            if(iterator->x() < 0){
                blinks.push_back(2); //cargamos en blinks dos si es pupila perdida
            }else{
                blinks.push_back(0); //cargamos en blinks cero si no parpadeo
                lastX = iterator->gaze().x();
                lastY = iterator->gaze().y();
                if(!frameOkDefined){
                    frameOkDefined = true;
                    frameOk = i;
                    frameOkX = lastX;
                    frameOkY = lastY;
                }
            }
        }
        //NOTE: lastX and lastY are -1 when the test starts in blink state
        if(lastX != -1 && lastY != -1 ){
            rawDataX.push_back(lastX);
            rawDataY.push_back(lastY);
        }
        i++;
        if(!data->blkDefined()){//TODO: NOBLK
            noBlkblinks.push_back(0);
            if(iterator->x() < 0.0 || iterator->y() < 0.0){//Ver si se ha detectado un parpadeo
                if(blinkDetected==false){
                    blinkInit.push_back(i);
                    blinkDetected=true;
                }
            }
            else{//En caso de que se detecte un parpadeo mantener la posicion anterior
                if(blinkDetected==true){
                    blinkEnd.push_back(i);
                    blinkDetected=false;
                }
            }
        }
    }
    Logger::instance().log(" End parsing each line", Logger::kLogLevelDebug);

    if(!data->blkDefined()){//TODO: NOBLK
        if(blinkDetected==true){
            blinkEnd.push_back(i); //Añadir el final si el parpadeo no acaba al final de la prueba
        }
    }
    if(frameOk > 0){
        for(i=0;i<frameOk;i++){
            rawDataX.push_front(frameOkX);
            rawDataY.push_front(frameOkY);
        }
    }
    if(!data->blkDefined()){
        Logger::instance().log(" Processing blinks because there is not a *.blk defined", Logger::kLogLevelDebug);
        unsigned int nBlinks=0;
        const int minDurParpadeo=4; //4*10ms=40ms
        const int maxDurParpadeo=105; //105*10ms=1050ms Parpadeos de >1s se consideran microsueños [wikipedia]
        int windowIni;
        int windowFin;
        int tipoParpadeo;
        int nParpadeosMalos;
        double pendienteX;
        double pendienteY;
        for(int i=0;i<blinkInit.length();i++){
            windowIni = std::max(blinkInit[i]-3,0); //Ventana limitada al incio de la prueba
            windowFin = std::min(blinkEnd[i]+5,rawDataX.length()-1); //Ventana limitada al final de la prueba
            tipoParpadeo = 2; //2=Perdida de la pupila (se pierde y reaparece de forma muy continuada), 1=Posible parpadeo (Se pierde la pupila durante un tiempo mayor sin detectarse el ojo durante ese tiempo)
            if(blinkEnd[i]-blinkInit[i]>=minDurParpadeo && blinkEnd[i]-blinkInit[i]<=maxDurParpadeo)
                tipoParpadeo=1; //Posible parpadeo si el tiempo de perdida de la pupila está comprendido en el intervalo
            //Union de parpadeos
            if(i<blinkInit.length()-1){
                nParpadeosMalos=0; //Llevar una cuenta de los no posibles parpadeos de la unión
                for(int j=i+1;j<blinkInit.length();j++){
                    if((std::max(blinkInit[j]-3,0))<=(windowFin+2)){ //Si el siguiente comienzo está antes (o muy cerca) del final de la ventana actual
                        windowFin = std::min(blinkEnd[j]+5,rawDataX.length()-1); //Unir ambas regiones (Actualizar el final de la región actual)
                        i=j; //Y no usar la región absorbida en la siguiente iteración
                        if(blinkEnd[i]-blinkInit[i]>=minDurParpadeo && blinkEnd[i]-blinkInit[i]<=maxDurParpadeo){
                            tipoParpadeo=1; //Posible parpadeo si el tiempo de perdida de la pupila está comprendido en el intervalo
                        }else{
                            nParpadeosMalos++;
                        }

                    }else{
                        break;
                    }
                }
                if(nParpadeosMalos>2){
                    tipoParpadeo=2; //Si hay varios parpadeos malos es muy posible que la detección de la pupila sea intermitente
                }
            }
            if(tipoParpadeo==1) //Solo considerar parpadeo lo que determinemos como posible parpadeo
                nBlinks++; //No es lo mismo que i porque se puede dar el caso de que se unan parpadeos
            //Para interpolacion lineal
            pendienteX=(rawDataX[windowFin]-rawDataX[windowIni])/static_cast<double>(windowFin-windowIni);
            pendienteY=(rawDataY[windowFin]-rawDataY[windowIni])/static_cast<double>(windowFin-windowIni);
            for(int j=windowIni;j<=windowFin;j++){
                blinks[j]=tipoParpadeo;
                if(windowIni<=0){
                    //Mantener posicion final (No hay punto inicial al principio)
                    rawDataX[j]=rawDataX[windowFin];
                    rawDataY[j]=rawDataY[windowFin];
                }else if(windowFin>=rawDataX.length()-1){
                    //Mantener posicion inicial (No hay punto final al final)
                    rawDataX[j]=rawDataX[windowIni];
                    rawDataY[j]=rawDataY[windowIni];
                }else{
                    //Interpolación lineal
                    rawDataX[j]=rawDataX[windowIni]+(j-windowIni)*pendienteX;
                    rawDataY[j]=rawDataY[windowIni]+(j-windowIni)*pendienteY;
                }
            }
        }
        data->countBlinks=nBlinks;
        Logger::instance().log(" Ending BLK processing", Logger::kLogLevelDebug);
    }
    double meanFPS=(static_cast<double>(data->m_testData.size())/time.back())*1000;
    if(meanFPS<100*0.8){
        std::stringstream ss;
        ss << "Average frames per second lower than 100 (This test: " << meanFPS << ").\nRepeat this test to get higher quality data.\nIf it is persistent, please contact support.";
        QString qstr=QString::fromStdString(ss.str());
        m_lastError=qstr;
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        returnValue=0;
    }
    // --------------------------------
    // Filter test data & remove blinks
    // --------------------------------
    if(rawDataX.size() < data->m_testData.size()*0.8){
        data->m_processedData.clear();
        data->m_processedDataExtra.clear();
        gazeRawX.clear(); gazeRawY.clear();
        m_lastError="Detection problems in more than twenty percent of the test";
        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
        return -1;
    }
    //TODONEXT: Filter calibration by ranges
    //          Test Quadratic Least Squares with Single Variable (Page 2)
    //          https://www.colorado.edu/amath/sites/default/files/attached-files/week9_0.pdf

    bool isClb = data->tstFileName()[0] == 'C' ? true : false;

    //data->m_calibrationRanges.length()

    QVector<double> testX;
    QVector<double> testY;
    QVector<double> auxX;
    QVector<double> auxY;
    QVector<double> validsX;
    QVector<double> validsY;
    if(isClb){
        //testX.reserve(rawDataX.size());
        //testY.reserve(rawDataX.size());
        for(int i=0;i<data->m_calibrationRanges.length();i++){
            auxX.clear();
            auxY.clear();
            validsX.clear();
            validsY.clear();
            for(int j=data->m_calibrationRanges.at(i).first;j<data->m_calibrationRanges.at(i).second;j++){
                //qDebug()<<Q_FUNC_INFO<<j<<" valid: "<<data->m_testData[j].validPto();
                if(data->m_testData[j].validPto()){
                    validsX.push_back(rawDataX.at(j));
                    validsY.push_back(rawDataY.at(j));
                }
            }
            qDebug()<<Q_FUNC_INFO<<" validsX.length(): "<<validsX.length();
            qDebug()<<Q_FUNC_INFO<<" validsY.length(): "<<validsY.length();
            //auxX = filtro(rawDataX.mid(data->m_calibrationRanges.at(i).first, data->m_calibrationRanges.at(i).second-data->m_calibrationRanges.at(i).first),4);                                                     //Filtrar la grafica sin parpadeos
            //auxY = filtro(rawDataY.mid(data->m_calibrationRanges.at(i).first, data->m_calibrationRanges.at(i).second-data->m_calibrationRanges.at(i).first),4);                                                     //El segundo parametro, indicador de la ventana del filtrado, ha de ser par
            auxX = filtro(validsX,4);                                                     //Filtrar la grafica sin parpadeos
            auxY = filtro(validsY,4);                                                     //El segundo parametro, indicador de la ventana del filtrado, ha de ser par
            testX.append(auxX);
            testY.append(auxY);
        }

    }else{
        testX = filtro(rawDataX.mid(0, rawDataX.size()),4);                                                     //Filtrar la grafica sin parpadeos
        testY = filtro(rawDataY.mid(0, rawDataY.size()),4);                                                     //El segundo parametro, indicador de la ventana del filtrado, ha de ser par
    }
    // ---------------------------
    // GAZE : Least squares interpolation
    // ---------------------------
    QVector<QPointF> gazeRaw;
    QVector<QPointF> gaze;
    for(int i = 0;i<rawDataX.length();i++){
        //VERY IMPORTANT: Least-squares polynomial multi-variable is the best
        gazeRaw.push_back(QPointF(m_quadraticXY.at<double>(0,0) + rawDataX[i] * m_quadraticXY.at<double>(1,0) + rawDataY[i] * m_quadraticXY.at<double>(2,0) + (rawDataX[i]*rawDataY[i]) * m_quadraticXY.at<double>(3,0) + (rawDataX[i]*rawDataX[i]) * m_quadraticXY.at<double>(4,0) + (rawDataY[i]*rawDataY[i]) * m_quadraticXY.at<double>(5,0),
                                  m_quadraticXY.at<double>(0,1) + rawDataX[i] * m_quadraticXY.at<double>(1,1) + rawDataY[i] * m_quadraticXY.at<double>(2,1) + (rawDataX[i]*rawDataY[i]) * m_quadraticXY.at<double>(3,1) + (rawDataX[i]*rawDataX[i]) * m_quadraticXY.at<double>(4,1) + (rawDataY[i]*rawDataY[i]) * m_quadraticXY.at<double>(5,1)));
           gaze.push_back(QPointF(m_quadraticXY.at<double>(0,0) + testX[i]    * m_quadraticXY.at<double>(1,0) + testY[i]    * m_quadraticXY.at<double>(2,0) + (testX[i]*testY[i]) * m_quadraticXY.at<double>(3,0)       + (testX[i]*testX[i])       * m_quadraticXY.at<double>(4,0) + (testY[i]*testY[i])       * m_quadraticXY.at<double>(5,0),
                                  m_quadraticXY.at<double>(0,1) + testX[i]    * m_quadraticXY.at<double>(1,1) + testY[i]    * m_quadraticXY.at<double>(2,1) + (testX[i]*testY[i]) * m_quadraticXY.at<double>(3,1)       + (testX[i]*testX[i])       * m_quadraticXY.at<double>(4,1) + (testY[i]*testY[i])       * m_quadraticXY.at<double>(5,1)));
    }
    // ---------------------------------
    // Calculate pupilArea and filter it
    // ---------------------------------
    QVector<double> pupilAreaRaw;
    for(i=0;i<gazeRaw.size();i++){                                                                //Recorrer toda la mirada y calcular el area en cada frame
        pupilAreaRaw.push_back(PI*(data->m_testData[i].width()/2)*(data->m_testData[i].height()/2));    //Area de la pupila vista por la camara. Area elipse = Pi*a*b
    }
    //Prueba filtro utilizado en pupilArea
    double meanPupilArea=std::accumulate(pupilAreaRaw.begin(),pupilAreaRaw.end(),0LL)/pupilAreaRaw.size();
    QVector<double> pupilArea;
    for(i=0;i<pupilAreaRaw.size();i++)
        pupilArea.push_back(pupilAreaRaw[i]*400/meanPupilArea);
    pupilArea=filtro(pupilArea,8);
    for(i=0;i<pupilArea.size();i++)
        pupilArea[i]=pupilArea[i]*meanPupilArea/400;
    // --------------------------------------------------------
    // Compensate screen display lag
    // --------------------------------------------------------
    //TODO
    /*
    int nFramesDelay=50;
    for(int i=gazeRawMatrix.size();i<=nFramesDelay;i--){
        //data->m_testData[i].stimulusX()=data->m_testData[i-nFramesDelay].stimulusX();
        //data->m_testData[i].stimulusY()=data->m_testData[i-nFramesDelay].stimulusY();
    }
    std::cout<<"Ahora esto "<<nFramesDelay<<std::endl;
    for(int i=nFramesDelay;i<=0;i--){
        data->m_testData[i].setStimulusX(-10);
        data->m_testData[i].setStimulusY(-10);
        std::cout<<"Change "<<i<<std::endl;
    }*/
    // --------------------------------------------------------
    // Separate and normalize gaze matrix + calculate derivates
    // --------------------------------------------------------
    //Separar la matriz de mirada en sus correspondientes vectores
    //Cambiar el centro de coordenadas para que esté en el centro de la pantalla
    //E invertir el eje Y para que sea hacia arriba positivo.
    //En este punto tambien se podría pasar/guardar copia en grados
    data->m_processedData.clear();
    data->m_processedDataExtra.clear();
    gazeRawX.clear(); gazeRawY.clear();
    QVector<double> gazeRawXd1,gazeRawYd1; //Variables temporales
    QVector<double> gazeXd1,gazeYd1;
    QVector<double> gazeRawXd2,gazeRawYd2;
    QVector<double> gazeXd2,gazeYd2;
    QVector<double> errX,errY;
    data->setResolution(resolution);
    data->setDist(screenDistance);
    data->setWidth(screenWidth);
    //Recorrer toda la matriz generada, que es lo mismo que recorrer toda la mirada
    double xS;
    double yS;
    double newStmPosX;
    double lastStmPosX = utilsProcess::px2deg(data->m_testData[0].stimulusX()-xResolution);
    double newStmPosY;
    double lastStmPosY = utilsProcess::px2deg(data->m_testData[0].stimulusY()-yResolution);
    int plotType = -1;
    int signoEstimuloX = 1; //Para calcular el error dependiendo de la dirección del estímulo
    int signoEstimuloY = 1; //Para calcular el error dependiendo de la dirección del estímulo


    qDebug()<<Q_FUNC_INFO<<" ===== ===== ===== ===== ===== ===== ===== isClb: "<<isClb;
    /*//MONGO(Begin)
    arrTime.clear();
    arrBlinks.clear();
    arrArea.clear();
    arrGazeX.clear();
    arrGazeY.clear();
    arrGazeVelocityX.clear();
    arrGazeVelocityY.clear();
    arrGazeRawX.clear();
    arrGazeRawY.clear();
    arrStimulusX.clear();
    arrStimulusY.clear();
    //MONGO(End)*/
    Logger::instance().log(" Starting For Loop calculating stuff", Logger::kLogLevelDebug);
    for(i=0;i<gazeRaw.size();i++){
        //Mirada sin filtrar(guardada en un vector de process)
        gazeRawX.push_back(utilsProcess::px2deg(gazeRaw.at(i).x()-xResolution)); //Guardar cambiando el centro de coordenadas
        gazeRawY.push_back(utilsProcess::px2deg(-(gazeRaw.at(i).y()-yResolution)));
        //Estímulos
        xS=data->m_testData[i].stimulusX();
        yS=data->m_testData[i].stimulusY();
        //Guardar en el vector de datos procesados la información de tiempo, mirada filtrada y estímulos, además cambiar el centro de coordenadas
        data->m_processedData.push_back(OProcessed(time[i],
                                        utilsProcess::px2deg(gaze.at(i).x()-xResolution),
                                        utilsProcess::px2deg(-(gaze.at(i).y()-yResolution)),
                                        gazeRawX[i],
                                        gazeRawY[i],
                                        utilsProcess::px2deg(xS-xResolution),    //
                                        utilsProcess::px2deg(-(yS-yResolution)), //
                                        pupilArea[i],
                                        blinks[i],
                                        isClb ? data->m_calibrationData[i].validPto() : true));
        //Gestion de cambio de estímulo para error y tsvProcessing
        newStmPosX = utilsProcess::px2deg(xS-xResolution);
        if(lastStmPosX != newStmPosX){
            plotType = 0;
            if(lastStmPosX>newStmPosX){
                signoEstimuloX=-1;
            }else{
                signoEstimuloX=1;
            }
        }
        lastStmPosX = newStmPosX;
        newStmPosY = utilsProcess::px2deg(yS-yResolution);
        if(lastStmPosY != newStmPosY){
            plotType = 1;
            if(lastStmPosY>newStmPosY){
                signoEstimuloY=-1;
            }else{
                signoEstimuloY=1;
            }
        }
        lastStmPosY = newStmPosY;
        if(i>0){ //Calculate first derivative - Velocity
            //Ahora mismo: px/ms
            gazeRawXd1.push_back((gazeRawX[i]-gazeRawX[i-1])/(time[i]-time[i-1]));
            gazeRawYd1.push_back((gazeRawY[i]-gazeRawY[i-1])/(time[i]-time[i-1]));
            //Ahora mismo deg/seg
            gazeXd1.push_back((data->m_processedData[i].x()-data->m_processedData[i-1].x())/((time[i]-time[i-1])/1000.0));
            gazeYd1.push_back((data->m_processedData[i].y()-data->m_processedData[i-1].y())/((time[i]-time[i-1])/1000.0));
            //gazeXd1.push_back((data->m_processedData[i].x()-data->m_processedData[i-1].x())/((time[i]-time[i-1])));
            //gazeYd1.push_back((data->m_processedData[i].y()-data->m_processedData[i-1].y())/((time[i]-time[i-1])));
        }else{
            gazeRawXd1.push_back(0);
            gazeRawYd1.push_back(0);
            gazeXd1.push_back(0);
            gazeYd1.push_back(0);
        }
        if(i>1){//Calculate second derivative - Acceleration
            //Ahora mismo: px/ms^2
            gazeRawXd2.push_back((gazeRawXd1[i]-gazeRawXd1[i-1])/(time[i]-time[i-1]));
            gazeRawYd2.push_back((gazeRawYd1[i]-gazeRawYd1[i-1])/(time[i]-time[i-1]));
            gazeXd2.push_back((gazeXd1[i]-gazeXd1[i-1])/(time[i]-time[i-1]));
            gazeYd2.push_back((gazeYd1[i]-gazeYd1[i-1])/(time[i]-time[i-1]));
        }else{
            gazeRawXd2.push_back(0);
            gazeRawYd2.push_back(0);
            gazeXd2.push_back(0);
            gazeYd2.push_back(0);
        }
        errX.push_back((data->m_processedData[i].x()-data->m_processedData[i].xS())*signoEstimuloX);
        errY.push_back((data->m_processedData[i].y()-data->m_processedData[i].yS())*signoEstimuloY);
        /*//MONGO(Begin)
        if(sendToMongo){
            //TODO: Horizontal
            arrTime<<time[i];
            arrArea<<pupilArea[i];
            arrBlinks<<blinks[i];
            arrGazeX<<utilsProcess::px2deg(gaze.at(i).x()-xResolution);
            arrGazeY<<utilsProcess::px2deg(-(gaze.at(i).y()-yResolution));
            arrGazeRawX<<gazeRawX[i];
            arrGazeRawY<<gazeRawY[i];
            arrGazeVelocityX<<gazeXd1[i];
            arrGazeVelocityY<<gazeYd1[i];
            arrStimulusX<<utilsProcess::px2deg(xS-xResolution);
            arrStimulusY<<utilsProcess::px2deg(-(yS-yResolution));
        }
        //MONGO(end)*/
    }
    qDebug()<<Q_FUNC_INFO<<" ========================================================================== "<< typeid(arrTime).name();
    //MONGO(Begin)
    /*if(sendToMongo){
        sendToDB(sessionName, testName, mongoUrl, mongoPort);
    }*/
    //MONGO(End)
    //Pasar las velocidades/acceleraciones a data. //TODO: Ver como se puede pasar arriba sin problemas
    for(i=0;i<gazeRaw.size();i++){
        data->m_processedDataExtra.push_back(OProcessedExtra(gazeXd1[i],gazeYd1[i],gazeXd2[i],gazeYd2[i],gazeRawX[i],gazeRawY[i],gazeRawXd1[i],gazeRawYd1[i],gazeRawXd2[i],gazeRawYd2[i],errX[i],errY[i]));
    }


    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    //CONTROL DE CALIDAD
    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    if (visualization==0)//solo se pasa si es procesado
    {

        QString type_test = data->m_testName.split("-")[0];

        //PUPIL DETECTION FAIL
        int contFails=0;
        int contBlinks=0;
        int contTotalerror;
        qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ blinks length: "<<blinks.length();
        for(int i=0;i<blinks.length();i++){
            if (blinks[i]==1)
                contBlinks++;
            if (blinks[i]==2)
                contFails++;
        }
        contTotalerror=contBlinks+contFails;
        qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ contador blinks y fails: "<<contBlinks<<"y "<<contFails;
        float percTotFail=((float)(contTotalerror)/(float)(blinks.length()))*100;
        float percFail=((float)contFails/(float)blinks.length())*100;
        float percBlink=((float)contBlinks/(float)blinks.length())*100;
        qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ porcentaje de fails "<<percTotFail;
        qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ porcentaje de rojo "<<percFail;
        qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ porcentaje de naranja "<<percBlink;
        if(percTotFail>25){
            m_lastError = "More than twenty five percent of the test "+ testName +" fail to calculate eye position";
            qDebug()<<Q_FUNC_INFO<<m_lastError;
            Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
            return -1;
        }

        //GLINTS FAIL
        float lim_bpeak=gazeRaw.size()*0.0003; //número de picos de más de 1000 que se considera aceptable en eje de movimiento
        float lim_speak=gazeRaw.size()*0.003;//número de picos de más de 150 que se considera aceptable en eje opuesto
        //float lim_bpeak=2; //número de picos de más de 1000 que se considera aceptable en eje de movimiento
        //float lim_speak=10;//número de picos de más de 150 que se considera aceptable en eje opuesto
        int count_speak_vel_y=0;
        int count_speak_vel_x=0;
        int count_bpeak_vel_y=0;
        int count_bpeak_vel_x=0;
        int count_outLimits_x=0;
        int count_outLimits_y=0;
        bool flag_orientation=false;//false horizontal- true vertical
        qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<type_test;

        if(type_test!="CC9"&&type_test!="TOPTVU"&&type_test!="TOPTHR"&&type_test!="TOPTVD"&&type_test!="TOPTHL"&&type_test!="TPL"&&type_test!="TIF1"&&type_test!="TIF2"&&type_test!="TIF3"&&type_test!="TIF4"&&type_test!="TIF5"&&type_test!="TIF6"&&type_test!="TIF7"&&type_test!="TIF8"&&type_test!="TIF9"&&type_test!="TIF10")
        {

            QPointF glint_left;
            QPointF glint_left_pre;
            QPointF glint_right;
            QPointF glint_right_pre;
            QPointF pupil;
            QPointF pupil_pre;
            float sum_dist_gl=0;
            float sum_dist_gr=0;
            float sum_dist_inter=0;
            double dist_left=0;
            double dist_right=0;
            double dist_pupil=0;
            double dist_inter_glints=0;
            for(i=1;i<gazeRaw.size();i++)
            {
                if (blinks[i]==0 && blinks [i-1]==0 && blinks [i-2]==0 && blinks [i-3]==0) //solo interesa la distancia si no hay fail ni parpadeo
                {
                    pupil.setX(data->m_testData[i].x()); //devuelve pos x pupila 2D.
                    pupil.setY(data->m_testData[i].y()); //devuelve pos y pupila 2D.
                    pupil_pre.setX(data->m_testData[i-1].x()); //devuelve pos x pupila 2D en la iteración anterior
                    pupil_pre.setY(data->m_testData[i-1].y()); //devuelve pos y pupila 2D en la iteración anterior
                    dist_pupil = std::sqrt(std::pow(pupil.x()-pupil_pre.x(), 2) + std::pow(pupil.y()-pupil_pre.y(), 2));
                    //if (dist_pupil>=1) qDebug()<<"mov ocular grande " <<dist_pupil<<" entre frames: "<<i<<" y "<<i-1;
                    glint_left=data->m_testData[i].glint(0);//devuelve pos del glint izq 2D.
                    glint_left_pre=data->m_testData[i-1].glint(0);//devuelve pos del glint izquierdo 2D en la iteración anterior
                    glint_right=data->m_testData[i].glint(1);//devuelve pos del glint derecho 2D
                    glint_right_pre=data->m_testData[i-1].glint(1);//devuelve pos del glint derecho 2D en la iteración anterior
                    dist_left = std::sqrt(std::pow(glint_left.x()-glint_left_pre.x(), 2) + std::pow(glint_left.y()-glint_left_pre.y(), 2));
                    dist_right = std::sqrt(std::pow(glint_right.x()-glint_right_pre.x(), 2) + std::pow(glint_right.y()-glint_right_pre.y(), 2));
                    dist_inter_glints=fabs(dist_left-dist_right);
                    double mean_dist_glints=(dist_left+dist_right)/2;
                    //qDebug()<<"mov glints " <<mean_dist_glints<<" entre frames: "<<i<<" y "<<i-1;
                    if (dist_pupil>=2)//esta haciendo notable movimiento ocular
                    {
                        if(dist_inter_glints>2*mean_dist_glints)//movimiento no justificado entre glints (penalizar)
                        {
                            sum_dist_inter+=(dist_inter_glints)*10;
                        }
                    }
                    else //pupila estatica o semi-estatica
                    {
                        if(mean_dist_glints>0.25)//no queremos tener en cuenta correcciones mínimas
                        {
                            sum_dist_gl +=dist_left;
                            sum_dist_gr +=dist_right;
                        }
                    }
                }
            }

            float coef_dist=(sum_dist_gl+sum_dist_gr+sum_dist_inter)/(gazeRaw.size()-contTotalerror);
            // la flag de headTremor sera true si no se quiere tener en cuenta este error por Parkinson
            double lim=(type_test!="TSLSH"&&type_test!="TSLSV")?0.75:1;// en los test de seguimiento lento hay mucho movimiento correcto y por eso sube el coef normal
            qDebug()<<"d_left: "<<sum_dist_gl<<"d_right: "<<sum_dist_gr<<"d_inter: "<<sum_dist_inter<<"frames en cuenta: "<<(gazeRaw.size()-contTotalerror);
            qDebug()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Coeficiente total distancia de los glints  "<<coef_dist<<" limite aplicado: "<<lim;
            qDebug()<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% head tremor deshabilitado: "<<data->getHeadTremor();

            if(coef_dist>lim && !data->getHeadTremor()) //coeficiente calculado tras el estudio de los resultados obtenidos para diferentes pruebas
            {
                m_lastError = "Glints detection problem or too much head tremor-movement in test: "+ testName;
                qDebug()<<Q_FUNC_INFO<<m_lastError;
                Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                return -1;
            }
            for(i=0;i<gazeRaw.size();i++)
            {
                if (blinks[i]==0 && blinks [i-1]==0 && blinks [i-2]==0 && blinks [i-3]==0 && blinks [i-4]==0 && blinks [i-5]==0) //solo interesa la si no hay fail ni parpadeo cerca
                {
                    if (gazeYd1[i]>150||gazeYd1[i]<-150) count_speak_vel_y++;
                    if (gazeYd1[i]>1000||gazeYd1[i]<-1000) count_bpeak_vel_y++;
                    if (gazeXd1[i]>150||gazeXd1[i]<-150) count_speak_vel_x++;
                    if (gazeXd1[i]>1000||gazeXd1[i]<-1000) count_bpeak_vel_x++;
                    if (gazeRawX[i]>25||gazeRawX[i]<-25) count_outLimits_x++;
                    if (gazeRawY[i]>15||gazeRawY[i]<-15) count_outLimits_y++;
                }
            }
            float  perc_outLimits_x=((float)(count_outLimits_x++)/(float)(gazeRaw.size()))*100;
            float  perc_outLimits_y=((float)(count_outLimits_y++)/(float)(gazeRaw.size()))*100;
            qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ % out limits x: "<<perc_outLimits_x<< "out limits y: "<<perc_outLimits_y;
            qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ % picos x: "<<count_speak_vel_x<<" , "<<count_bpeak_vel_x<< "limites picos: "<<lim_speak<<" y "<<lim_bpeak;
            qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ % picos y: "<<count_speak_vel_y<<" , "<<count_bpeak_vel_y<< "limites picos: "<<lim_speak<<" y "<<lim_bpeak;
            qDebug()<<Q_FUNC_INFO<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ tipo test que pasa QC: "<<type_test;

            if((perc_outLimits_x+perc_outLimits_y)>10)
            {
                m_lastError = " In test: "+ testName +", the patient is looking out of the stimulus screen";
                qDebug()<<Q_FUNC_INFO<<m_lastError;
                Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                return -1;
            }
            if((perc_outLimits_x+perc_outLimits_y+percTotFail)>35)
            {
                m_lastError = " In test: "+ testName +", the patient is looking out of the stimulus screen and it is not posible to detect the pupil";
                qDebug()<<Q_FUNC_INFO<<m_lastError;
                Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                return -1;
            }

            if(type_test.at(type_test.length()-1)=='H' || type_test.at(type_test.length()-1) == 'L' || type_test.at(type_test.length()-1) == 'R'){ //Si acaba en H, test horizontales o L/R, okn left/right
                if((count_bpeak_vel_x>lim_bpeak)||(count_speak_vel_y>lim_speak))
                {
                    m_lastError = "Too much movements in the wrong axis (Y) or possible reflections, ptosis problems in: "+ testName ;
                    qDebug()<<Q_FUNC_INFO<<m_lastError;
                    Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                    flag_orientation=false;
                    return -1;
                }
            }
            else if(type_test.at(type_test.length()-1)=='V' || type_test.at(type_test.length()-1)== 'U' || type_test.at(type_test.length()-1)== 'D'){ //Si acaba en V, test verticales o U/D, okn up/down
                if((count_bpeak_vel_y>lim_bpeak)||(count_speak_vel_x>lim_speak))
                {
                    m_lastError = "Too much movements in the wrong axis (X) or possible reflections, ptosis problem in: "+ testName ;
                    qDebug()<<Q_FUNC_INFO<<m_lastError;
                    Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                    flag_orientation=true;
                    return -1;
                }
            }
        }
        //PTOSIS CONTROL
        int age=data->getPatientDetails().at(1).toInt();
        float dArea;
        float area_media=0;
        int cont_frames_ok=0;
        int lim_coef;
        float sumatorio_dArea=0;
        float coef_dArea;

        if(type_test!="CC9"&&type_test!="TPL"&&type_test!="TIF1"&&type_test!="TIF2"&&type_test!="TIF3"&&type_test!="TIF4"&&type_test!="TIF5"&&type_test!="TIF6"&&type_test!="TIF7"&&type_test!="TIF8"&&type_test!="TIF9"&&type_test!="TIF10"&&type_test!="TOPTVU"&&type_test!="TOPTHR"&&type_test!="TOPTVD"&&type_test!="TOPTHL")
        {
            for(i=1;i<gazeRaw.size();i++)
            {
                if(blinks[i]==0)// no parpadeando
                {
                    area_media+=data->m_processedData[i].area();
                }
            }
            area_media=area_media/(gazeRaw.size()-contTotalerror);

            //las rectas siguientes han sido calculadas en base a un estudio realizado sobre la relación entre el area de la pupila y el coeficiente de area medido. El estudio se ha realizado con 8 pacientes jóvenes (A)

            if(type_test!="TSLSV"&&type_test!="TSLSH"&&type_test!="TSLLV"&&type_test!="TSLLH") // si es sacádico o fijación
            {
                lim_coef= 0.000715*area_media + 9.3;
            }
            else // si es seguimiento
            {
                lim_coef= 0.000475*area_media + 7.875;
            }
            if(age>60) lim_coef=lim_coef-1; // restamos un valor para tener en cuenta el tamaño de la pupila varía más cuando la edad es menor
            for(i=1;i<gazeRaw.size();i++)
            {
                if(blinks[i]==0 && blinks [i-1]==0)// no parpadeando
                {
                    dArea=(fabs(data->m_processedData[i].area()-data->m_processedData[i-1].area()));
                    //qDebug()<<dArea<<" frames: "<<i<<" y: "<<i-1;
                    sumatorio_dArea+=dArea;
                    cont_frames_ok++;
                }
            }
            coef_dArea=sumatorio_dArea/cont_frames_ok; // si este coeficiente es muy alto, significa que hay demasiado cambio de pupila y habra parpado caido
            qDebug()<<"coeficiente de Area de pupila: "<<coef_dArea<<" edad: "<<age<<" area media pupila: "<<area_media<<" limite calculado: "<<lim_coef;
            if(coef_dArea>lim_coef)
            {
               m_lastError = "Possible ptosis problem or too much fast head moves in test: "+ testName ;
               qDebug()<<Q_FUNC_INFO<<m_lastError;
               Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
                return -1;
            }
        }

    }


    //COMPROBACIÓN DE SUMATORIO DE DIVERSOS ERRORES
//    if ((coef_dist>0.6&&flag_orientation==false&&count_speak_vel_y>(lim_speak/2)&&percTotFail>15)||(coef_dist>0.6&&flag_orientation==true&&count_speak_vel_x>(lim_speak/2)&&percTotFail>15))
//    {
//        m_lastError = "There are different error sources at the test: "+testName+", that make impossible to obtain correct information for diagnostic" ;
//        qDebug()<<Q_FUNC_INFO<<m_lastError;
//        Logger::instance().log(m_lastError.toStdString(), Logger::kLogLevelError);
//        return -1;
//    }


    //FINALIZANDO PROCESAMIENTO
    Logger::instance().log(" Ending calculateGaze with value "+ std::to_string(returnValue), Logger::kLogLevelDebug);

    return returnValue;


}


/**
  *   @brief  Filtrado de la calibración aplicando RANSAC de modelos
  *
  *   @details
  *   Se toman de forma aleatoria puntos con los que reproyectar los estímulos de la prueba al entorno del glint pupila.
  *   (Se usan los minimos cuadrados para obtener un modelo del tipo a0+a1x+a2y).
  *   Respecto a los estímulos reproyectados se generan regiones circulares y se descartan aquellos puntos que quedan fuera
  *   de dichos círuclos.
  *   El mejor modelo es aquel que descarta la menor cantidad de puntos.
  *   Se generan modelos hasta que el número de descartes se estabiliza o llega a cero. (Está limitado a 1000 iteraciones)
  *   Tras calcular el mejor modelo se usa para generar un vector que indica que posiciones se han de descartar
  *
  *   @param  gazeInX posición del ojo (glintPupila) en el eje X
  *   @param  gazeInY posición del ojo (glintPupila) en el eje Y
  *   @return QVector<bool> indica si la posicion se ha de descartar (false) o está dentro del modelo (true)
  */
int process::filtradoModeloRANSAC(OData *data){
    qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    qDebug()<<Q_FUNC_INFO<<" ========= ========= ========= ========= ========= ========= ========= ========= ========= ";
    //int index;
    double ptoEstX, ptoEstY;
    double d;
    //QVector<bool> filterOut;
    QVector<QVector<double>> modelo;    //Usar minimos cuadrados para calcular la matriz de interpolacion
    QVector<QVector<double>> bestModel; //Mejor modelo, el que da el error mas bajo
    double radius=6.0*6.0;                   //Radio del circulo con el que se descartaran datos tomando como centro lo que de de meter los estimulos al modelo
    std::srand(12345);                  //Semilla aleatoria, pero siempre la misma para poder replicar resultados

    QPointF centre;

    QVector<int> range;
    QVector<int> means;
    cv::Mat xXY;
    //INFO: Two alternatives have been tested in the case where there are only one, two, three, etc. valid ranges
    //      OPT1: Repeat the whole valid ranges n times. Example: 1,2,1,2 or 1,2,3,1,2,3
    //      OPT3: Repeat each valid ranges n times. Example: 1,1,2,2,3,3 or 1,1,1,2,2,2,3,3,3,4,4,4
    //      NONE OF THEM WORK. The best option is to select the valid ranges once
    double meanStdX = 0.0, sumX = 0.0;
    double meanStdY = 0.0, sumY = 0.0;
    //se calculan los sumatorios de las desviaciones típicas en los 9 puntos de calibración
    for(int i=0;i<data->m_calibrationRanges.length();i++){
        sumX += data->m_meanStdX.at(i).second;
        sumY += data->m_meanStdY.at(i).second;
    }
    //se obtienen la desviación típica global de la calibración entera, para eje X e Y
    meanStdX = sumX / data->m_calibrationRanges.length();
    meanStdY = sumY / data->m_calibrationRanges.length();
    //std::cout<<" meanStdX:"<<meanStdX<<" meanStdY:"<<meanStdY<<std::endl;
    for(int i=0;i<data->m_calibrationRanges.length();i++){
//        std::cout<<i
//                <<": m_meanX:"<<data->m_meanStdX.at(i).first
//                <<" m_StdX:"<<data->m_meanStdX.at(i).second
//                <<": m_meanY:"<<data->m_meanStdY.at(i).first
//                <<" m_StdY:"<<data->m_meanStdY.at(i).second;
        //para cada punto de los 9 de calibración se comprueba si la desviación media total de la calibración es mucho menor que la del punto estudiado, y solo se guardan en "range" los puntos cuya desviación típica no supere la media global por más de 1.0
        if(((meanStdX-(data->m_meanStdX.at(i).second)) > -1.0)  && ((meanStdY-(data->m_meanStdY.at(i).second)) > -1.0)){
            range.push_back(i); //range es un vector de ints con el id de los puntos considerados como válidos por su valor de desviación típica
            //std::cout<<" inclued to select";
        }
        //std::cout<<std::endl;
    }
    qDebug()<<Q_FUNC_INFO<<" range.length(): "<<range.length()<<", data->m_calibrationRanges.length(): "<<data->m_calibrationRanges.length();
    cv::Mat AXY = cv::Mat_<double>(range.length(),3);
    cv::Mat bXY = cv::Mat_<double>(range.length(),2);
    if(range.length() > 2){//(Mario) por qué 2 puntos? se sale por aquí en ocasiones que parece correcta la calibración.
        //TODO TEST:
        /*for(int i=0;i<range.length();i++){
            index = data->m_calibrationRanges.at(range.at(i)).first + (rand() % static_cast<int>(data->m_calibrationRanges.at(range.at(i)).second - data->m_calibrationRanges.at(range.at(i)).first + 1));
            AXY.at<double>(i,0) = 1;
            AXY.at<double>(i,1) = data->m_calibrationData[index].gaze().x();
            AXY.at<double>(i,2) = data->m_calibrationData[index].gaze().y();
            bXY.at<double>(i,0) = utilsProcess::px2deg(data->m_calibrationData[index].stimulusX()-(1920/2));
            bXY.at<double>(i,1) = utilsProcess::px2deg(data->m_calibrationData[index].stimulusY()-(1080/2));
        }
        cv::solve(AXY,bXY,xXY,cv::DECOMP_QR);*/
        for(int i=0;i<range.length();i++){
            AXY.at<double>(i,0) = 1;
            //las posiciones medias obtenidas para cada intervalo de calibración
            AXY.at<double>(i,1) = data->m_meanStdX.at(i).first;
            AXY.at<double>(i,2) = data->m_meanStdY.at(i).first;
            //posición del estimulo en cada intervalo de calibración pasado a deg respecto al centro de la pantalla
            bXY.at<double>(i,0) = utilsProcess::px2deg(data->m_calibrationData[data->m_calibrationRanges.at(i).first].stimulusX()-(1920/2));
            bXY.at<double>(i,1) = utilsProcess::px2deg(data->m_calibrationData[data->m_calibrationRanges.at(i).first].stimulusY()-(1080/2));
        }
        cv::solve(AXY,bXY,xXY,cv::DECOMP_QR); //se aplica una factorización QR, cuyo resultado es xXY
    }else{
        return -1;

    }
    m_meanClbGaze.clear();
    m_meanClbStimuli.clear();
    double sumGazeX = 0.0, sumGazeY = 0.0;
    double sumStimuliX = 0.0, sumStimuliY = 0.0;
    int pts = 0;
    qDebug()<<Q_FUNC_INFO<<" PTO: "<<m_meanClbGaze.length()+1;
    for(int i=0;i<data->m_calibrationData.length();i++){
        //se utiliza la matriz xXY obtenida para traducir la posición del ojo en una estimación de cada punto sobre la pantalla por frame
        ptoEstX = xXY.at<double>(0,0) + xXY.at<double>(1,0)*data->m_calibrationData[i].gaze().x() + xXY.at<double>(2,0)*data->m_calibrationData[i].gaze().y();
        ptoEstY = xXY.at<double>(0,1) + xXY.at<double>(1,1)*data->m_calibrationData[i].gaze().x() + xXY.at<double>(2,1)*data->m_calibrationData[i].gaze().y();
        centre.setX(utilsProcess::px2deg(data->m_calibrationData[i].stimulusX()-(1920/2))); //centre es el punto de la pantalla donde se debe mirar para cada una de las iteraciones de la calibración, relativo al centro de la pantalla
        centre.setY(utilsProcess::px2deg(data->m_calibrationData[i].stimulusY()-(1080/2)));
        //d = pow(ptoEstX-centre.x(), 2) + pow(ptoEstY-centre.y(),2);
        d = (ptoEstX-centre.x())*(ptoEstX-centre.x()) + (ptoEstY-centre.y()) * (ptoEstY-centre.y()); //se calcula la distancia desde el punto estimado al punto central donde debería estar mirando
//        std::cout<<i<<", gazeX: "<<data->m_calibrationData[i].gaze().x()
//                    <<", ptoEstX: "<<ptoEstX
//                    <<", xS: "<<centre.x()
//                    <<", gazeY: "<<data->m_calibrationData[i].gaze().y()
//                    <<", ptoEstY: "<<ptoEstY
//                    <<", yS: "<<centre.y()
//                    <<",\t d: "<<d
//                    <<",\t radius: "<<radius;
        data->m_calibrationData[i].setValidPto(d<=radius); //se define la condición de aceptación de los puntos
        if(data->m_calibrationData[i].validPto()){ //se hacen los sumatorios de los puntos considerados válidos
            //std::cout<<", TRUE"<<std::endl;
            sumGazeX += data->m_calibrationData[i].gaze().x();
            sumGazeY += data->m_calibrationData[i].gaze().y();
            sumStimuliX += data->m_calibrationData[i].stimulusX();
            sumStimuliY += data->m_calibrationData[i].stimulusY();
            pts++;
        }else{
            //std::cout<<", FALSE"<<std::endl;
        }
        if(data->m_calibrationData[i].stimulusX() != data->m_calibrationData[i+1].stimulusX() //si existe cambio de intervalo de calibración
         ||data->m_calibrationData[i].stimulusY() != data->m_calibrationData[i+1].stimulusY()
         ||i == data->m_calibrationData.length()){
            qDebug()<<Q_FUNC_INFO<<" PTO: "<<m_meanClbGaze.length()+1<<", pts: "<<pts;
            if(pts > 50){ //ponemos un minimo de puntos válidos para evitar calibraciones malas (Mario)
                m_meanClbGaze.push_back(QPointF(sumGazeX/pts, sumGazeY/pts));//se guarda el punto medio de la mirada estimado sobre la pantalla para cada intervalo de calibración
                m_meanClbStimuli.push_back(QPointF(sumStimuliX/pts, sumStimuliY/pts));
            }
            sumGazeX = 0.0;sumGazeY = 0.0;sumStimuliX = 0.0; sumStimuliY = 0.0;pts = 0;
        }
    }
    qDebug()<<Q_FUNC_INFO<<" m_meanClbPts.length(): "<<m_meanClbGaze.length();
    for(int i=0;i<m_meanClbGaze.length();i++)
        //std::cout<<" m_meanClbGaze pto"<<i<<": "<<m_meanClbGaze.at(i).x()<<", "<<m_meanClbGaze.at(i).y()<<", at stimuli: "<<m_meanClbStimuli.at(i).x()<<", "<<m_meanClbStimuli.at(i).y()<<std::endl;
    if(m_meanClbGaze.length() > 5){ // si existen al menos 6 puntos de los 9 de calibración que han tenido suficientes puntos válidos como para obtener un valor medio y, por lo tanto, ser considerados válidos
        cv::Mat Aq = cv::Mat_<double>(m_meanClbGaze.length(),6);
        cv::Mat bq = cv::Mat_<double>(m_meanClbGaze.length(),2);
        for(int i=0;i<m_meanClbGaze.length();i++){
            Aq.at<double>(i,0) = 1;
            Aq.at<double>(i,1) = m_meanClbGaze[i].x();//punto medio de mirada en x para un intervalo de calibración de los catalogados como correctos (pueden ser 6,7,8 o 9)
            Aq.at<double>(i,2) = m_meanClbGaze[i].y();//punto medio de mirada en y para un intervalo de calibración de los catalogados como correctos (pueden ser 6,7,8 o 9)
            Aq.at<double>(i,3) = m_meanClbGaze[i].x()*m_meanClbGaze[i].y();
            Aq.at<double>(i,4) = m_meanClbGaze[i].x()*m_meanClbGaze[i].x();
            Aq.at<double>(i,5) = m_meanClbGaze[i].y()*m_meanClbGaze[i].y();
            bq.at<double>(i,0) = m_meanClbStimuli[i].x();//punto medio del estimulo para cada intervalo
            bq.at<double>(i,1) = m_meanClbStimuli[i].y();
        }
        cv::solve(Aq,bq,m_quadraticXY,cv::DECOMP_QR); // se obtiene la matriz definitiva de calibración mediante Factorización QR
    }else{
        return -1;
    }
    return 0;
}

//_________FILTERING FUNCTIONS__________//

//Full gaze filtering function
//kMin must be an even number!
QVector<double> process::filtro(QVector<double> fIn,int kMin){
    qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    Logger::instance().log(" Ending filtro function", Logger::kLogLevelDebug);
    if(!kMin%2)
        return QVector<double>();
    int ix=8;                                   //Half interval variable for peak smoothing
    int rec=1;                                  //To enter the iteration control section each two filtering loops
    int aux=1;                                  //To control the first entry to the iteration control section
    int kFin=kMin;                              //To select the final filter window
    double dev;                                 //To store the standard deviation of the error between the original gaze vector and the filtered one for each iteration
    double devMin=0.0;                          //To store the minimus standard deviation of all iterations
    QVector<double> auxV=corrPicos(fIn,20);     //High velocity peak elimination and filtration
    QVector<double> err(fIn.size());
    QVector<double> fTemp(fIn.size());          //Temporal vector to store the data of multiple filter stages
    QVector<double> fComp(fIn.size());          //Used to store the resulting vector of the "jumps" correction function
    QVector<double> fOut(fIn.size());           //Output vector of the current function used also as temporal storage
    for(int i=0;i<err.size();i++)               //Create an "error" vector by the substraction of the original gaze and the peak-corrected gaze
        err[i]=fIn[i]-auxV[i];
    for(int i=19;i<fIn.size()-ix;i++){          //Peak smoothing loop
        if(qFabs(err[i])>=15){                  //If the error calculated previously is greater than a given value "n" apply the smoothing...
            for(int j=i-ix;j<=i+ix;j++)         //...From the current position minus ix to the current position plus ix
                fIn[j]=auxV[j];
        }
    }
    err.clear();
    for(int i=kMin;i<=10;i+=2){
        //TODOPAPER: the two-leveled peak removing algorithm described in [Heuristic filtering and reliable calibration methods  for  video-based  pupil-tracking  systems]
        fTemp=corrPicos(fIn,i/2);               //Begin the filtering with a peak correction function
        fComp=corrSaltos(fTemp,10,10);          //Continue with a blink, "jumps" and other similar things filtering for future comparison
        fTemp=corrError(fIn,fComp,i);           //Compare the previous filtered function with the original one and keep the original values if the difference between both is not very large
        fOut=corrGauss(fIn,i);                  //Apply a gaussian-median filter as a final stage
        fTemp=corrPicos(fIn,i/2);               //Each full loop contains two filtering stages that are completely equal
        fComp=corrSaltos(fTemp,10,10);
        fTemp=corrError(fIn,fComp,i);
        fOut=corrGauss(fIn,i);
        rec++;
        if(rec>=2){                             //Each full loop contains two filtering stages that are completely equal
            for(int j=0;j<fOut.size();j++)
                fTemp[j]=fOut[j]-fComp[j];
            err=corrPicos(fTemp,6);             //Smooth the error function, it eliminates the large spikes that could modify the "real" value for the STD
            dev=utilsProcess::stdDev(err);
            rec=0;
            if(aux==1){                         //If this is the first STD check initialize some of the values
                aux=0;
                kFin=i;
                devMin=dev;
            }
            else if(dev<=devMin){               //Store the minimum STD if the condition is true
                kFin=i;
                devMin=dev;
            }
            else                                //If the current STD is greater than the minimun STD exit the filtering loop
                break;
        }
    }
    //Complete the filtering function applying the last optimum value for the filtering window with the minimum STD
    fTemp=corrPicos(fIn,kFin);
    fTemp=corrSaltos(fTemp,10,10);
    fTemp=corrError(fIn,fTemp,kFin);
    fTemp=corrPicos(fTemp,kFin+2);
    fOut=corrGauss(fTemp,kFin);
    Logger::instance().log(" Ending filtro function", Logger::kLogLevelDebug);
    return fOut;
}

//Function for peak elimination
QVector<double> process::corrPicos(QVector<double> fIn,int k){
    //qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    Logger::instance().log(" Starting corrPicos function", Logger::kLogLevelDebug);
    QVector<double> fOut(fIn.size()),fTemp(k);
    int ind;
    for(int i=0;i<k/2;i++)                                                          //Add values in front of the input vector in order to begin in the initial value using the filtering window
        fIn.push_front(fIn[i]);
    ind=fIn.size()-1;                                                               //Same for the end of the vector as before
    for(int i=0;i<k/2;i++)
        fIn.push_back(fIn[ind]);
    for(int i=0;i<fOut.size();i++){                                                 //Run all the values of the vector for peak smoothing
        for(int j=0;j<k;j++)                                                        //Fill the window vector for its later median filtering
                fTemp[j]=fIn[i+j];
        fOut[i]=utilsProcess::median(fTemp);                                        //Use a median filter to set the current filtered value of the peak
    }
    Logger::instance().log(" Ending corrPicos function", Logger::kLogLevelDebug);
    return fOut;                                                                    //Return the peak-corrected output vector
}

//Function for the correction of artifacts such as "jumps", blinks and other similar things
QVector<double> process::corrSaltos(QVector<double> fIn,int width,int length){
    //qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    QVector<double> fOut=fIn;
    int n;
    int i=1;
    while(i<=fIn.size()){
        n=i+1;
        if(n<fIn.size()){
            while(qFabs(fIn[i]-fIn[n])>4){                                          //If the difference between the current value and the current value plus "length" is lower than 4 pixels increase the window "n"
                n=n+length;
                if(n>=fIn.size()-1)                                                 //Stop the loop if the n value es equal or grether than the input vector size
                    break;
            }
            if(n-i<=width && n<=fIn.size()){                                        //If the "jump" width is not larger than "width" filter the current "jump"
                for(int j=i;j<=n;j++)
                    fOut[j]=fOut[i]+(fOut[n]-fOut[i])*(j-i)/(n-i);
            }
        }
        i=n;
    }
    return fOut;                                                                    //Return the final filtered output vector
}

//Function for error correction between two input vectors
QVector<double> process::corrError(QVector<double> fIn,QVector<double> fAprox,int k){
    //qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    QVector<double> err(fIn.size()),fOut=fAprox;
    int aux;    //To indicate the vector which value will be in the output for each iteration
    int ind;    //To check the error every ten values of each vector
    for(int i=0;i<fIn.size();i++)                                                   //Complete the error vector by substracting the filtered input "fAprox" to the unfiltered input "fIn"
        err[i]=fIn[i]-fAprox[i];
    for(int i=0;i<fIn.size();i++){
        aux=0;
        ind=0;
        while(ind<=10){
            if(i>1 && i<(err.size()-11)){
                if(qFabs(err[ind+i])>qFabs(err[ind+i-2]))                           //If the current error value is greater than the two-previous error value keep hte filtered value for the next process
                    aux=1;
                else                                                                //If it isn't the case keep the original value for the next process
                    aux=0;
            }
            ind++;
        }
        if((qFabs(err[i])<=5 || i<=k/2-1) && i>5){                                  //Complete the output vector with the corresponding vector values for each iteration
            if(aux==1){
                for(int j=i-6;j<=i;j++)                                             //Complete the output with the filtered vector values
                    fOut[j]=fAprox[j];
            }
            else{
                for(int j=i-6;j<=i;j++)                                             //Complete the output with the unfiltered vector values
                    fOut[j]=fIn[j];
            }
        }
    }
    return fOut;
}

//Gaussian-median filter function (copied from Matlab)
//More info about gaussian-median filter at https://en.wikipedia.org/wiki/Gaussian_filter
//Matlab gausswin: https://es.mathworks.com/help/signal/ref/gausswin.html
//Matlab convolution: https://es.mathworks.com/help/matlab/ref/conv.html
QVector<double> process::corrGauss(QVector<double> fIn,int k){
    //qDebug()<<"------------------------------------------------------------------Start Funcion: "<<Q_FUNC_INFO;
    QVector<double> w(k),fTemp(fIn.size()+k-1),fOut(fIn.size());
    QVector<int> n(k);
    int N=k-1,j,i,ind;
    double sum=0,tmp=0;
    //Matlab "gausswin" function
    for(i=0;i<=N;i++)
        n[i]=i-N/2;
    for(i=0;i<=N;i++){
        w[i]=exp(-0.5*pow(2.5*n[i]/(N/2),2));
        sum+=w[i];
    }
    for(i=0;i<=N;i++)
        w[i]=w[i]/sum;
    //Matlab "conv" function
    for(i=0;i<fTemp.size();i++){
        ind=i;
        tmp=0;
        for(j=0;j<k;j++){
            if(ind>=0 && ind<fIn.size())
                tmp+=fIn[ind]*w[j];
            ind--;
            fTemp[i]=tmp;
        }
    }
    for(i=k/2-1;i<fTemp.size()-k/2;i++)
        fOut[i-k/2+1]=fTemp[i];
    for(i=0;i<k/2-1;i++)
        fOut[i]=fOut[k/2-1];
    for(i=fOut.size()-1;i>fOut.size()-k/2;i--)
        fOut[i]=fOut[fOut.size()-k/2];
    return fOut;
}

//______END OF FILTERING FUNCTIONS______//
