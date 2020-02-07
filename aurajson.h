#ifndef AURAJSON_H
#define AURAJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>

class AuraJson
{
    QString label;
    int age;
    QString hospital;
    QJsonArray studied_pathologies;
    QJsonArray result_types;
    QJsonArray analysis;

    QString filePath;
    QJsonDocument Json;


public:
    AuraJson(QString filePath, QString label, int age, QString hospital, int pathologies[], bool analysis[], bool results[]);
    void createJson();
    void writeJson();
};

#endif // AURAJSON_H
