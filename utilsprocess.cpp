#include "utilsprocess.h"

QPoint utilsProcess::resolution;
double utilsProcess::sDist;
double utilsProcess::sWidth;

/**
  *   @brief  Constructor por defecto
  *   @return void
  */
utilsProcess::utilsProcess(){}

/**
  *   @brief  Conversión de grados a píxeles (Usando todos los parámetros)
  *
  *   @param  deg entrada en grados a convertir
  *   @param  sceenDistance distancia del sujeto a la pantalla [cm]
  *   @param  pxDensity relación entre el ancho del monitor y su resolución [px/cm]
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::deg2px(double deg, double screenDistance, double pxDensity){
    return pxDensity*screenDistance*qTan(deg*M_PI/180);
}

/**
  *   @brief  Conversión de píxeles a grados (Usando todos los parámetros)
  *
  *   @param  px entrada en píxeles a convertir
  *   @param  sceenDistance distancia del sujeto a la pantalla [cm]
  *   @param  pxDensity relación entre el ancho del monitor y su resolución [px/cm]
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::px2deg(double px, double screenDistance, double pxDensity){
    return qAtan(px/(pxDensity*screenDistance))*180/M_PI;
}

/**
  *   @brief  Conversión de grados a píxeles (Usando los parámetros estáticos)
  *
  *   @param  deg entrada en grados a convertir
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::deg2px(double deg){
//    qDebug() << "Variables:\nDistance:" << sDist << "\nWidth:" << sWidth << "\nResolution:" << resolution;
    return (sDist*resolution.x()*qTan(deg*M_PI/180))/(float)sWidth;
}

/**
  *   @brief  Conversión de grados a píxeles (Usando los parámetros estáticos)
  *
  *   @param  px entrada en píxeles a convertir
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::px2deg(double px){
//    qDebug() << "Variables:\nDistance:" << sDist << "\nWidth:" << sWidth << "\nResolution:" << resolution;
    return qAtan((px*sWidth)/(float)(sDist*resolution.x()))*180/M_PI;
}
