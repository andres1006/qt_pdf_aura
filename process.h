/**
 *  @file    process.h
 *  @author  Santiago Hernandez / David Molina
 *  @date    10/07/2017
 *  @version 1.0
 *
 *  @brief Estima la mirada de un test con los datos de una calibración
 *
 *  @details
 *
 *  En esta clase, y más concretamente en el source, se definen los metodos necesarios para estimar la mirada.
 *  Se utilizan mínimos cuadrados para obtener una matriz de interpolación a partir de los datos de la
 *  calibración. Esa matriz se aplica a la mirada para convertir los vectores glint pupila a puntos en el
 *  monitor de estímulos.
 *
 *  Además se aplican los filtros para lograr que la medida tenga el menor ruido posible
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QtMath>
#include <qt5/QtCore/QDebug>
#include "data.h"

#include <opencv2/core/core.hpp>

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::array;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;



/**
  *  @brief Clase para estimar la mirada de una prueba a partir de los datos de una calibración
*/
class process : public QObject
{
    Q_OBJECT
public:
    QVector<double> time;    ///< Copia del tiempo de la prueba para facilitar su uso dentro de los metodos
    QVector<double> gazeRawX;       ///< Mirada sin filtrar en eje X
    QVector<double> gazeRawY;       ///< Mirada sin filtrar en eje Y

    QVector<QPointF> m_meanClbGaze;
    QVector<QPointF> m_meanClbStimuli;
    cv::Mat m_linear;
    cv::Mat m_quadraticXY;
    explicit process(QObject *parent = nullptr);
public slots:
    // Estima la mirada con los datos de *data
    Q_INVOKABLE int calculateGaze(OData *data, QString testName, QPoint=QPoint(0,0), double=NAN, double=NAN, bool=false);
    Q_INVOKABLE QString getLastError(){ return m_lastError;}
    Q_INVOKABLE void sendToDB(OData *data, QString sessionName, QString testName, QString mongoUrl, unsigned int mongoPort);
private:
    int filtradoModeloRANSAC(OData *data);
    //Funciones que se usan para calcular la mirada
    QVector<double> filtro(QVector<double>,int);
    QVector<double> corrPicos(QVector<double>,int);
    QVector<double> corrSaltos(QVector<double>,int,int);
    QVector<double> corrError(QVector<double>,QVector<double>,int);
    QVector<double> corrGauss(QVector<double>,int);

    QString m_lastError;
    QVector<double> m_leastSquaresSolution;

    //MONGO(Begin)
    bsoncxx::v_noabi::builder::stream::array arrTime;
    bsoncxx::v_noabi::builder::stream::array arrBlinks;
    bsoncxx::v_noabi::builder::stream::array arrArea;
    bsoncxx::v_noabi::builder::stream::array arrGazeX;
    bsoncxx::v_noabi::builder::stream::array arrGazeY;
    bsoncxx::v_noabi::builder::stream::array arrGazeVelocityX;
    bsoncxx::v_noabi::builder::stream::array arrGazeVelocityY;
    bsoncxx::v_noabi::builder::stream::array arrGazeRawX;
    bsoncxx::v_noabi::builder::stream::array arrGazeRawY;
    bsoncxx::v_noabi::builder::stream::array arrStimulusX;
    bsoncxx::v_noabi::builder::stream::array arrStimulusY;
    //MONGO(End)


};

#endif // PROCESS_H
