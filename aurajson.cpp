#include "aurajson.h"


AuraJson::AuraJson(QString filePath, QString label, int age, QString hospital, int pathologies[], bool analysis[], bool results[])
{
    this->filePath = filePath;
    this->label = label;
    this->age = age;
    this->hospital = hospital;
    int length = sizeof(pathologies)/sizeof(pathologies[0]);
    for(int i = 0; i<length;i++){
        this->studied_pathologies.append(pathologies[i]);
    }
    length = sizeof(results)/sizeof(results[0]);
    for(int i = 0; i<length;i++){
        this->result_types.append(results[i]);
    }
    length = sizeof(analysis)/sizeof(analysis[0]);
    for(int i = 0; i<length;i++){
        this->analysis.append(analysis[i]);
    }
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
    Json.setObject(data);
}

void AuraJson::writeJson(){
    QFile file(this->filePath);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(this->Json.toJson());
    file.close();
}
