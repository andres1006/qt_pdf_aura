/**
 *  @file    pdfreport.h
 *  @author  Santiago Hernandez / David Molina
 *  @date    10/07/2017
 *  @version 1.0
 *
 *  @brief Genera un informe en PDF a partir de los archivos guardados de las pruebas
 *
 *  @details
 *
 *  Esta clase es la encargada de generar los reportes con los datos procesados de las pruebas de oscann.
 *  Incluye la configuración del archivo (Mediante un cuadro de díalogo al comienzo del método principal)
 *  , la carga de los datos y la preparación de estos para que su formato sea aceptado por los métodos de
 *  "pdfreporthelper".
 *
 *  Esta clase se ayuda de las funciones de "pdfreporthelper" para pintar las imágenes y textos en el pdf
 *
 *  Se crea un reporte con dos páginas para cada prueba encontrada (recursivamente) dentro de la carpeta
 *  seleccionada. La primera página, denominada "resultados", contiene las gráficas de trayectoria de
 *  mirada, datos del paciente y datos estadísticos si se encuentran. La segunda página, "extra", muestra
 *  la calibración, una captura del scatter de la prueba y el espacio libre se deja para comentarios.
 *
 *  Todas las páginas cuentan con una cabecera con el nombre de la prueba y dos logos, uno de ellos configurable
 *  por el usuario. El otro siempre es el de AURA. También siempre se imprime un pie de página con el código de
 *  la sesión, el de la prueba y el número de página.
 *
 */


#ifndef PDFREPORT_H
#define PDFREPORT_H

#include <QObject>

#include <QPdfWriter>
#include <QPainter>
//#include <QPageSize> A partir de qt 5.3
#include <QDirIterator>
#include <QDialogButtonBox>
#include <QtWidgets>

#include <pdfreporthelper.h>

#include "oscannplot.h"

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/exception/exception.hpp>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/types/value.hpp>
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>

#include "aurajson.h"




using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;


class pdfreport : public QObject
{
    Q_OBJECT
private:

    QPair<QString, QStringList> m_items;

    QVector<QPair<QString, QStringList>> m_testsParams;

    QString m_mongoUrl;
    unsigned int m_mongoPort;


    QDialog * dialogLogo; ///< Puntero al cuadro de diálogo que se muestra antes de imprimir el reporte
    //Oscann 3.0.3
    mongocxx::database m_dbDatos;
    mongocxx::database m_dbTests;
    mongocxx::client m_client;


    QVector<QPixmap> m_graps;
    QString m_patient;
    QString m_pathology;
    QStringList m_tests;

    QStringList m_allParams;


    QPixmap getImage(const unsigned int mode, const QString testName);
    QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>> getGraphsAndTables(const QString pathology, const QString patient, QString reference);
    QString validateDBElement(bsoncxx::document::element l);
    QString m_date;
    QString ImprimeInformeControl(int patologia_estudiada, int resultado);
    QString ImprimeInformeDiferencial(int patologia_estudiada1, int patologia_estudiada2, int resultado);
    QVector<int> selectConclusion(QVector<int> patologias, QVector<bool> diferenciales, QVector<int> resultadosDemencias, QVector<int> resultadosParkinson);

public:
    explicit pdfreport(QObject *parent = 0);
public slots:
    Q_INVOKABLE void setMongoInfo(const QString, const unsigned int);
    Q_INVOKABLE void newReport(QString filePathJson);
    Q_INVOKABLE QStringList dbPatients(QString pathology);
    Q_INVOKABLE QStringList availableTests(QString patient);
    Q_INVOKABLE void allParams();
    Q_INVOKABLE int testParams(QStringList test);
    Q_INVOKABLE void paramsToShow(QString test);
    Q_INVOKABLE void configLogoDialog(QAbstractButton *);
    Q_INVOKABLE void changeLogo(QAbstractButton *);

};

#endif // PDFREPORT_H
