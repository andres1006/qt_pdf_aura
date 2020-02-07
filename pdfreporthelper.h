/**
 *  @file    pdfreporthelper.h
 *  @author  Santiago Hernandez
 *  @date    10/07/2017
 *  @version 1.0
 *
 *  @brief Ayuda a generar el pdf imprimiendo la información de entrada en páginas con formato ya especificado
 *
 *  @details
 *
 *  Esta clase es la que realmente imprime y pinta sobre el reporte PDF que se está creando en "pdfreport"
 *  El objetivo de esta clase es ofrecer funciones con las que imprimir cada página con un formato ya creado
 *  y así facilitar tanto la generación como la modificación del formato
 *
 *  También sirve para almacenar algunas variables de configuración como los tamaños de los encabezados, o
 *  más importante, el número de página
 *
 *  Los métodos creados se pueden considerar modulares porque una función que pinta una página llama a pintar a otros
 *  métodos que generar distintos elementos de la página (Cabecera, pie, tablas, títulos, etc)
 */

#ifndef PDFREPORTHELPER_H
#define PDFREPORTHELPER_H

#include <QPdfWriter>
#include <QPainter>
#include <QFontMetrics>
#include <QStaticText>

class pdfReportHelper
{
    QPainter painter;       ///< Sistema de QT para pintar elementos gráficos sobre la salida indicada, en este caso el PDF
    int mm2pp;           ///< Relación entre milimetros y puntos. Sirve para convertir entre estas 2 unidades a la hora de pintar
    int currentPageNumber;  ///< Contador con el número de página actual (Se indica en los piés de página)

    //-------Header values
    int hHeight;            ///< Altura máxima del encabezado [mm]
    int hPadding;           ///< Margenes de separación de los elementos en el encabezado [mm]
    QString hTitle;         ///< Cadena de texto con el título que debe ir en el encabezado
    QImage hImgLogo1;       ///< Imagen del logo izquierdo
    QImage hImgLogo2;       ///< Imagen del logo derecho

    //-------Footer values
    int fHeight;            ///< Altura máxima del pie de página (Empezando desde abajo) [mm]
    int fPadding;           ///< Margenes de separación de los elementos en el pié [mm]
    QString fLeftText;      ///< Cadena de texto a imprimir en la parte izquierda del pié de página


    QPoint m_refPto;


public:
    pdfReportHelper(QPdfWriter&);
    void newPDF(QPdfWriter&,QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>>,QStringList = QStringList(), bool=false);
    void drawTable(QStringList, QStringList, QRect);
    //NOTE: QStaticText can only represent text, so only HTML tags which alter the layout or appearance of the text will be respected.
    //      Adding an image to the input HTML, for instance, will cause the image to be included as part of the layout, affecting the
    //      positions of the text glyphs, but it will not be displayed. The result will be an empty area the size of the image in the output.
    //      Similarly, using tables will cause the text to be laid out in table format, but the borders will not be drawn.
    //void drawWebTable(QPdfWriter&, QStringList, QStringList, QRect);
    void drawCell(int rowWidth,
                  int rowHeight,
                  bool bold,
                  QString text,
                  bool fill,
                  Qt::AlignmentFlag);
    void newPage(QPdfWriter&,bool = true);
    void drawSimpleList(QStringList, QRect);
    //-------Header functions
    void configHeader(int, int, QImage, QImage, QString="Default title");
    void setHeaderTitle(QString);
    void drawHeader_2logos(QPdfWriter&);
    //-------Header functions
    void configFooter(int, int, QString="Default text");
    void setFooterText(QString);
    void drawFooterSimple(QPdfWriter&);
};


#endif // PDFREPORTHELPER_H
