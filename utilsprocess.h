/**
 *  @file    process.h
 *  @author  Santiago Hernandez / David Molina
 *  @date    10/07/2017
 *  @version 1.0
 *
 *  @brief Clase con funciones estáticas de proposito general
 *
 *  @details
 *
 *  Se crea esta clase para tener a mano funciones que se usan de forma general por distintas partes del programa
 *  Son medias, medianas, conversión píxeles a grados, etc.
 *
 */

#ifndef UTILSPROCESS_H
#define UTILSPROCESS_H

#include <QObject>
#include <QtMath>
#include <QDebug>
#include <QPoint>

/**
  *  @brief Clase con solo funciones estáticas. No tiene sentido crear objetos de este tipo
*/
class utilsProcess
{
    //UtilsProcess: Helper Class, ejecuta funciones basicas de analisis que se usan en process o para analizar otras pruebas
    //Así no hay varias copias de la funcion media
public:
    utilsProcess();

    template<class T> static double stdDev(QVector<T>); //Desviacion estandar
    template<class T> static double mean(QVector<T>); //Media
    template<class T> static double median(QVector<T> vIn); //Mediana
    template<class T> static QVector<T> vAbs(QVector<T>); //Hace el valor absoluto de todos los puntos de un vector

    static double px2deg(double px, double screenDistance, double pxDensity);
    static double deg2px(double deg, double screenDistance, double pxDensity);

    static double px2deg(double px);
    static double deg2px(double deg);

    static QPoint resolution;   ///< Resolución de la pantalla en píxeles
    static double sDist;        ///< Distancia del sujeto a la pantalla [cm]
    static double sWidth;       ///< Ancho del monitor de estímulos [cm]
};

// FUNCIONES estaticas con template se han de poner en el header porque si no los compiladores de c++ se lian

/**
  *   @brief  Calcula la media del vector de entrada
  *
  *   @param  vIn es el vector de datos de entrada
  *   @return double con el valor medio
  */
template<class T>
double utilsProcess::mean(QVector<T> vIn){ //Funcion que calcula la media
    if(vIn.size()<=0)
        return 0; //Si no hay elementos
    if(vIn.size()==1)
        return vIn.at(0); //Si solo hay un elemento devolver ese
    double mean=0;
    for(int i=0;i<vIn.size();i++)
        mean+=vIn[i];
    return mean/vIn.size();
}

/**
  *   @brief  Calcula la desviación típica del vector de entrada
  *
  *   @param  vIn es el vector de datos de entrada
  *   @return double con la desviación típica
  */
template<class T>
double utilsProcess::stdDev(QVector<T> vIn){//Funcion que calcula la desviacion estandar
    if(vIn.size()<=0)
        return 0; //Si no hay elementos
    if(vIn.size()==1)
        return 0; //Si solo hay un elemento no hay desviación
    double dev=0;
    double meanVal=mean(vIn);
    for(int i=0;i<vIn.size();++i)
        dev+=(vIn[i]-meanVal)*(vIn[i]-meanVal);
    return sqrt(dev/(vIn.size()-1));
}

/**
  *   @brief  Calcula la mediana del vector de entrada
  *
  *   @param  vIn es el vector de datos de entrada
  *   @return double con el valor mediano
  */
template<class T>
double utilsProcess::median(QVector<T> vIn){
    if(vIn.size()<=0)
        return 0; //Si no hay elementos
    if(vIn.size()==1)
        return vIn.at(0);
    std::sort(vIn.begin(),vIn.end());
    if(vIn.size()%2==0){
        return (vIn[vIn.size()/2.0]+vIn[vIn.size()/2-1])/2.0;
    }else{
        return vIn[vIn.size()/2.0];
    }
}

/**
  *   @brief  Aplica el valor absoluto a todos los elementos del vector de entrada
  *
  *   @param  vIn es el vector de datos de entrada
  *   @return QVector con los datos de entrada en valor absoluto
  */
template<class T> QVector<T> utilsProcess::vAbs(QVector<T> vIn){ //Valor absoluto de todos los elementos de un vector
    QVector<T> vOut;
    for(int i=0;i<vIn.length();i++)
        vOut.push_back(qAbs(vIn[i]));
    return vOut;
}

#endif // UTILSPROCESS_H
