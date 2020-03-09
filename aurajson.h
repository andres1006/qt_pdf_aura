#ifndef AURAJSON_H
#define AURAJSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QFile>
#include <QList>
#include <iostream>
#include <fstream>
#include <QDebug>

class AuraJson: public QObject
{
    Q_OBJECT
private:
    QString label;
    int age;
    QString hospital;

    QJsonArray studied_pathologies;
    QJsonArray result_types;
    QJsonArray analysis;

    QJsonArray resultados_IA_demencias;
    QJsonArray resultados_IA_parkinson;
    int resultados_IA_EHM;

    int estado;

    QString filePath;
    QJsonDocument Json;


public:
    explicit AuraJson(QObject *parent = nullptr);
    Q_INVOKABLE void inicializateJson(QString filePath, QString label, int age, QString hospital, QList<QString> pathologies, QList<bool> analysis, QList<bool> results);
    Q_INVOKABLE void createJson();
    Q_INVOKABLE void writeJson();
    Q_INVOKABLE void readJson(QString filePath);
    Q_INVOKABLE QString getLabel(){return label;}
    Q_INVOKABLE QString getHospital(){return hospital;}
    Q_INVOKABLE int getAge(){return age;}
    Q_INVOKABLE QVector<int> getPathologies();
    Q_INVOKABLE QVector<bool> getResults_types();
    Q_INVOKABLE QVector<bool> getIA_analysis();
    Q_INVOKABLE int getEstado(){return estado;}
    Q_INVOKABLE QVector<int> getResultados_IA_demencias();
    Q_INVOKABLE QVector<int> getResultados_IA_parkinson();
    Q_INVOKABLE int getResultados_IA_EHM(){return resultados_IA_EHM;}
    Q_INVOKABLE void setEstado(int e){estado = e;}
    Q_INVOKABLE void setResultados_IA_demencias(QVector<int> resultados);
    Q_INVOKABLE void setResultados_IA_parkinson(QVector<int> resultados);
    Q_INVOKABLE void setResultados_IA_EHM(int resultados);

};

#endif // AURAJSON_H
