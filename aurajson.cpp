#include "aurajson.h"

AuraJson::AuraJson(QObject *parent) : QObject(parent){}

void AuraJson::inicializateJson(QString filePath, QString label, int age, QString hospital, QList<QString> pathologies, QList<bool> analysis, QList<bool> results)
{
    this->filePath = filePath;
    this->label = label;
    this->age = age;
    this->hospital = hospital;

    int patologia;
    bool valor;
    QList<int> patologias;

    if (pathologies.contains("Alzheimer Disease"))
        patologias.append(2);
    if (pathologies.contains("Parkinson disease"))
        patologias.append(3);
    if (pathologies.contains("Frontotemporal dementia"))
        patologias.append(5);
    if (pathologies.contains("Minimal Hepatic Encephalopathy"))
        patologias.append(8);
    if (pathologies.contains("Mild Cognitive Impairment"))
        patologias.append(9);
    if (pathologies.contains("Parkinsonisms"))
        patologias.append(10);

    for(int i = 0; i<patologias.length();i++){
        patologia = patologias[i];
        this->studied_pathologies.append(patologia);
    }

    for(int i = 0; i<results.length();i++){
        valor = results[i];
        this->result_types.append(valor);
    }

    for(int i = 0; i<analysis.length();i++){
        valor = analysis[i];
        this->analysis.append(valor);
    }

    resultados_IA_demencias = {-1,-1,-1,-1,-1,-1};
    resultados_IA_parkinson = {-1,-1,-1};
    resultados_IA_EHM = -1;

    estado = 0;
}

void AuraJson::readJson(QString filePath){
    //QByteArray FP = filePath.toLocal8Bit();
    //const char *fp = FP.data();
    //std::ifstream basic_ifstream(fp);

    QString val;
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    this->filePath = filePath;

    Json = QJsonDocument::fromJson(val.toUtf8());
    //qDebug() << Json.toJson();
    QJsonObject data = Json.object();

    label = data["Label"].toString();
    //qDebug() << "ETIQUETA   ::::::::::::   " << label;
    age = data["Age"].toInt();
    //qDebug() << "EDAD   ::::::::::::   " << age;
    hospital = data["Hospital"].toString();
    studied_pathologies = data["Pathologies_Studied"].toArray();
    //qDebug() << "PATOLOGIAS   ::::::::::::   " << studied_pathologies;
    QJsonObject results = data["Results_types"].toObject();
    this->result_types.append(results["PDF_Report"]);
    this->result_types.append(results["Zscore"]);
    this->result_types.append(results["AI"]);
    //qDebug() << "TIPOS DE RESULTADOS   ::::::::::::   " << result_types;
    QJsonObject differentials = data["Analysis_types_for_AI"].toObject();
    this->analysis.append(differentials["AD vs FTD"]);
    this->analysis.append(differentials["AD vs MCI"]);
    this->analysis.append(differentials["FTD vs MCI"]);
    this->analysis.append(differentials["PD vs PKS"]);
    //qDebug() << "Analysis_types_for_AI   ::::::::::::   " << analysis;
    resultados_IA_demencias = data["resultados_IA_demencias"].toArray();
    resultados_IA_parkinson = data["resultados_IA_parkinson"].toArray();
    resultados_IA_EHM = data["resultados_IA_EHM"].toInt();

    estado = data["estado"].toInt();
}

void AuraJson::createJson(){
    QJsonObject data;
    QJsonObject Results_types;
    QJsonObject Analysis_types;

    data.insert("Label", this->label);
    data.insert("Age", this->age);
    data.insert("Hospital", this->hospital);
    data.insert("Pathologies_Studied", this->studied_pathologies);

    Analysis_types.insert("AD vs FTD", this->analysis[0]);
    Analysis_types.insert("AD vs MCI", this->analysis[1]);
    Analysis_types.insert("FTD vs MCI", this->analysis[2]);
    Analysis_types.insert("PD vs PKS", this->analysis[3]);
    data.insert("Analysis_types_for_AI", Analysis_types);

    Results_types.insert("PDF_Report", this->result_types[0]);
    Results_types.insert("Zscore", this->result_types[1]);
    Results_types.insert("AI", this->result_types[2]);
    data.insert("Results_types", Results_types);

    data.insert("resultados_IA_demencias",this->resultados_IA_demencias);
    data.insert("resultados_IA_parkinson",this->resultados_IA_parkinson);
    data.insert("resultados_IA_EHM",this->resultados_IA_EHM);

    data.insert("estado",this->estado);

    Json.setObject(data);
    qDebug() << Json;
}

void AuraJson::writeJson(){
    QFile file(this->filePath);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(this->Json.toJson());
    file.close();
}

QVector<int> AuraJson::getPathologies(){
    QVector<int> pathologies;
    for(int i = 0; i < studied_pathologies.size(); i++){
        pathologies.append(studied_pathologies[i].toInt());
    }
    return pathologies;
}

QVector<bool> AuraJson::getResults_types(){
    QVector<bool> results;
    for(int i = 0; i < result_types.size(); i++)
        results.append(result_types[i].toBool());
    return results;
}

QVector<bool> AuraJson::getIA_analysis(){
    QVector<bool> analysis_IA;
    for(int i = 0; i < analysis.size(); i++)
        analysis_IA.append(analysis[i].toBool());
    return analysis_IA;
}

QVector<int> AuraJson::getResultados_IA_demencias(){
    QVector<int> resultados;
    for(int i = 0; i < resultados_IA_demencias.size(); i++){
        resultados.append(resultados_IA_demencias[i].toInt());
    }
    return resultados;
}
QVector<int> AuraJson::getResultados_IA_parkinson(){
    QVector<int> resultados;
    for(int i = 0; i < resultados_IA_parkinson.size(); i++){
        resultados.append(resultados_IA_parkinson[i].toInt());
    }
    return resultados;
}

void AuraJson::setResultados_IA_demencias(QVector<int> resultados){
    qDebug() << "longitud resultados: " << resultados.length();
    qDebug() << "longitud resultados IA: " << resultados_IA_demencias.size();
    if (resultados.length() == resultados_IA_demencias.size()){
        for(int i = 0; i<resultados.length();i++){
            this->resultados_IA_demencias[i] = resultados[i];
            qDebug() << "resultado insertado: " << resultados[i];
        }
    }
}
void AuraJson::setResultados_IA_parkinson(QVector<int> resultados){
    if (resultados.length() == resultados_IA_parkinson.size()){
        for(int i = 0; i<resultados.length();i++){
            this->resultados_IA_parkinson[i] = resultados[i];
        }
    }
}
void AuraJson::setResultados_IA_EHM(int resultados){
    this->resultados_IA_EHM = resultados;
}
