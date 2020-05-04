//#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include "aurajson.h"
#include "process.h"
#include "data.h"

#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>



#include "pdfreport.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

/*
Prueba con Json. Los archivos necesarios para esta parte son: AuraJson.cpp/.h
*//*
    QString filepath = "/home/MargaretHamilton/PruebaJSON/datos.json";

    int patologia[] = {2,5};

    bool analisis[4] = {1,0,1,0};

    bool resultados[3] = {1,0,0};



    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(Json.toJson());
    file.close();


    AuraJson json(filepath,"AURA10",25,"HUCV",patologia,analisis,resultados);
    json.createJson();
    json.writeJson();*/


/*
Prueba subida datos a Mongo DB: los archivos necesarios para esta parte son: logger.cpp/.h, data.cpp/.h, process.cpp/.h, qutils.cpp/.h y utilsprocess.cpp/.h
*/
/*
    OData *data = new OData();
    process *procesamiento = new process();

    data->setClbFileName("/home/jhonatan/Escritorio/C/PATOLOGIAS/temp/ControlesGrupoA/paciente_grupoA_1/CC9-04202018-132505"); // datos de la calibración asociada a una prueba.
    data->setTstFileName("/home/jhonatan/Escritorio/C/PATOLOGIAS/temp/ControlesGrupoA/paciente_grupoA_1/TSLSH-04202018-132616"); // datos de la prueba
    data->open(0);
    data->importCsv();
    qDebug()<<"m_processedData.size() =";
    qDebug()<<data->dataSize();
    procesamiento->sendToDB(data,"paciente_grupoA_1","TSLSH-04202018-132616","localhost",27017);

*/

/*
Prueba generacion de pdf: archivos necesarios pdfreport.cpp/.h, oscannplot.cpp/.h, qcustomplot.cpp/.h, videopreview.cpp/.h
*/

    qDebug("step 1...");
    pdfreport *pdf = new pdfreport;
    qDebug("step 2...");
    pdf->setMongoInfo("localhost",27017);
    qDebug("step 3...");
    QStringList qml_patients = pdf->dbPatients(argv[1]); //Patologias
    qDebug("step 4...");
    QStringList qml_pdf_tests = pdf->availableTests(argv[2]); //paciente
    qDebug("step 5...");
    pdf->allParams();
    qDebug("step 6...");
    int n_test = pdf->testParams(qml_pdf_tests);
    qDebug("step 7...");
    pdf->newReport(argv[3]); //Ruta a la carpeta del paciente
    qDebug("step 8...");

}
