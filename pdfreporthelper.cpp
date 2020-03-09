#include "pdfreporthelper.h"

#include<QDebug>

/**
  *   @brief  Constructor del objeto. Prepara la configuración
  *
  *   @details
  *   Se crea (y sobreescribe) el fichero PDF. Se cofigura el tamaño, colores y se inicializa el número de página
  *   y la conversión de milimetros a puntos, ya que es más facil hacer la configuración en mm
  *
  *   @param  &pdfWriter elemento de salida que guarda los cambios al fichero PDF correspondiente
  */
pdfReportHelper::pdfReportHelper(QPdfWriter& pdfWriter)
{
    painter.begin(&pdfWriter);
    ////Open PDF document

    ////Config pdf and painter
    pdfWriter.setPageSize(QPagedPaintDevice::A4); //Ver como se puede hacer sin qt 5.3
    painter.setPen(QPen(Qt::black,17));
    painter.setBrush(QBrush(QColor(255,255,255))); //Fondo de tablas Blanco

    //NOTE: Both operators are int
    mm2pp=pdfWriter.height()/pdfWriter.heightMM(); //Milimetros a puntos
    currentPageNumber=0;
}

void pdfReportHelper::newPDF(QPdfWriter &pdfWr,
                             QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>> info,
                             QStringList simpleList,
                             bool repeatList){
    int hGraph=62;
    double tableHeight;
    int p1Padding = 5;
    QRect limitRectangle(p1Padding*mm2pp,(hHeight+p1Padding)*mm2pp,200*mm2pp,65*mm2pp);
    QFont font = painter.font();
    font.setPointSize(11);
    painter.setFont(font);
    int item = 0;
    int page = 0;
    int itemsPerPage = 3;
    int space;

    int ymm = hHeight+simpleList.size()*15;

    for(int i=0;i<info.first.length();i++, item++){
        if(item%itemsPerPage == 0){
            newPage(pdfWr);
            if(page == 0){
                itemsPerPage = 1;
                item = 0;
                space = 0;
                drawSimpleList(simpleList, limitRectangle);
            }else if(repeatList){
                itemsPerPage = 3;
                item=0;
                drawSimpleList(simpleList, limitRectangle);
                ymm = hHeight + 10;
            }else{
                itemsPerPage = 3;
                item=0;
                space = 28;
                ymm = hHeight + 10;
            }

            page++;
        }
        if(item > 0){
            tableHeight = (info.second.first.at(i-1).size()+info.second.second.at(i-1).size())*7.75;
            ymm += tableHeight;
        }
        painter.drawImage(QRect(p1Padding*mm2pp,                                        //X
                                ymm*mm2pp,  //Y
                               (pdfWr.widthMM()-p1Padding*17)*mm2pp,                   //width
                               hGraph*mm2pp),                                          //height
                               QImage(info.first.at(i).toImage())); //Referencia desde el pie de pag (+ grafica anterior)
                        //staValues              //cntsValues
        drawTable(info.second.first.at(i), info.second.second.at(i),QRect(p1Padding*mm2pp + (pdfWr.widthMM()-p1Padding*17)*mm2pp + 16,
                                                                                       ymm*mm2pp,
                                                                                       pdfWr.width()/3 + 500,                   //width
                                                                                       150));
    }
}



///////////////////////////////////////////////////////
/// MAIN REPORT FUNCTIONS --
///////////////////////////////////////////////////////


/**
  *   @brief  Pinta una tabla genérica
  *
  *   @details
  *   Esta función crea una tabla simple en la posición indicada con los datos de entrada.
  *   Para el funcionamiento se requiere que los datos tengan un formato esperado. Se introduce una lista de cadenas donde
  *   cada cadena de la lista representa una fila. Y cada fila se divide en columnas en función de la división de
  *   la cadena por los separadores '|'.
  *
  *   El rectangulo de entrada determina la posición de la esquina superior izquierda y el ancho de la tabla. El largo
  *   depende del tamaño de la lista de cadenas de entrada.
  *
  *   @param  &pdfWr elemento de salida que guarda los cambios al fichero PDF correspondiente
  *   @param  tbInput lista de cadenas para la tabla. Se espera un formato especificado en details
  *   @param  tbRect rectangulo que especifica la posición y dimensiones
  *   @return  void
  */
void pdfReportHelper::drawTable(QStringList staValues,QStringList cntsValues,QRect tbRect){
    //qDebug()<<Q_FUNC_INFO<<" -----=====----- -----=====----- -----=====----- -----=====----- -----=====----- ";
    QStringList rowText;
    int tbNcols;
    bool bold;
    int staI, cntsI;
    QFont font = painter.font(); //Reducir tamanio de letra
    //Erik: font.setPointSize(10);
    font.setPointSize(5);
    font.setBold(true);
    painter.setFont(font);
    //Erik
    painter.setPen(QPen(Qt::black,8));

    QFontMetrics fontM(painter.font());
    int tbRowHeight=fontM.height()+mm2pp;                                           //La altura de la columna depende del tamaño de letra
    int rowNameWidth = 1300;
    m_refPto=tbRect.topLeft()+QPoint(rowNameWidth,0);                               //Posicion de la fila respecto del origen de tabla
    //qDebug()<<Q_FUNC_INFO<<QString(" Uno m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
    drawCell(tbRect.width()-rowNameWidth,tbRowHeight,true,"Datos Temporales", true, Qt::AlignCenter);
    m_refPto-=QPoint(tbRect.width(),0);                     //Posicion de la fila respecto del origen de tabla
    m_refPto+=QPoint(rowNameWidth,tbRowHeight);                     //Posicion de la fila respecto del origen de tabla
    //qDebug()<<Q_FUNC_INFO<<QString(" Dos m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
    drawCell((tbRect.width()-rowNameWidth)/2,tbRowHeight,true,"Valor Medido", false, Qt::AlignCenter);
    drawCell((tbRect.width()-rowNameWidth)/2,tbRowHeight,true,"Valor Referencia", false, Qt::AlignCenter);
    m_refPto=tbRect.topLeft()+QPoint(rowNameWidth,tbRowHeight*2);                     //Posicion de la fila respecto del origen de tabla
    for(staI=0; staI<staValues.size();staI++){ //Rows
        rowText=staValues[staI].split("|");                                            //Separar el texto en columnas
        if(staI>0)
            drawCell(rowNameWidth,tbRowHeight,true,rowText[0], false, Qt::AlignRight);
        qDebug()<<Q_FUNC_INFO<<" staValues["<<staI<<"]: "<<staValues[staI]<<", rowText[0]: "<<rowText[0];
        tbNcols=rowText.size()-1;
        for(int j=0; j<tbNcols; j++){ //Colums
            bold = staI>0 ? false : true;
            drawCell((tbRect.width()-rowNameWidth)/tbNcols,tbRowHeight,bold,rowText[j+1], false, Qt::AlignCenter);
            //qDebug()<<Q_FUNC_INFO<<QString(" for j m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
        }
        m_refPto=tbRect.topLeft()+QPoint(0,tbRowHeight*(staI+3)); //Posicion de la fila respecto del origen de tabla
        //qDebug()<<Q_FUNC_INFO<<QString(" for staI m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
    }
    if(cntsValues.size() > 0){
        m_refPto=tbRect.topLeft()+QPoint(rowNameWidth,tbRowHeight*(staI+2) + 64); //Posicion de la fila respecto del origen de tabla
        drawCell(tbRect.width()-rowNameWidth,tbRowHeight,true,"Conteos", true, Qt::AlignCenter);
        m_refPto=tbRect.topLeft()+QPoint(0,tbRowHeight*(staI+3) + 64);
        //qDebug()<<Q_FUNC_INFO<<QString(" Middle m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
        //m_refPto=tbRect.topLeft()+QPoint(0,tbRowHeight*(i+2)); //Posicion de la fila respecto del origen de tabla
        for(cntsI=0; cntsI<cntsValues.size();cntsI++){ //Rows
            rowText=cntsValues[cntsI].split("|");                                            //Separar el texto en columnas
            //qDebug()<<Q_FUNC_INFO<<" cntsValues["<<cntsI<<"]: "<<cntsValues[cntsI]<<", rowText[0]: "<<rowText[0];
            drawCell(rowNameWidth,tbRowHeight,true,rowText[0], false, Qt::AlignRight);
            tbNcols=rowText.size()-1;
            int widths[3] = {(tbRect.width()-rowNameWidth)/(tbNcols-1), (tbRect.width()-rowNameWidth)/(tbNcols+1), (tbRect.width()-rowNameWidth)/(tbNcols+1)};
            for(int j=0; j<tbNcols; j++){ //Colums: They are three: one for the patient and two for the reference
                drawCell(widths[j],tbRowHeight,false,rowText[j+1], false, Qt::AlignCenter);
                //qDebug()<<Q_FUNC_INFO<<QString(" for j2 m_refPto (%1,%2)) width: %3").arg(m_refPto.x()).arg(m_refPto.y()).arg(widths[j]);
            }
            m_refPto=tbRect.topLeft()+QPoint(0,tbRowHeight*(staI+cntsI+4) + 64); //Posicion de la fila respecto del origen de tabla
            //qDebug()<<Q_FUNC_INFO<<QString(" for cntsI m_refPto (%1,%2))").arg(m_refPto.x()).arg(m_refPto.y());
        }
    }
}


void pdfReportHelper::drawCell(int rowWidth,
                               int rowHeight,
                               bool bold,
                               QString text,
                               bool fill,
                               Qt::AlignmentFlag hAlign

                               ){
    QFont font = painter.font();
    font.setBold(bold);
    painter.setFont(font);
    QRect tbSubRect (m_refPto,QSize(rowWidth,rowHeight)); //Posicion de la celda respecto del origen de celda anterior
    QRect tbTextRect(m_refPto+QPoint(mm2pp,0),QSize(tbSubRect.width()-2*mm2pp,rowHeight)); //Celda con margenes para el texto
    painter.drawRect(tbSubRect); //Pintar al pdf la celda y su contenido
    if(fill)
        painter.fillRect(tbSubRect, QColor(200,200,200)); //Pintar al pdf la celda y su contenido
    painter.drawText(tbTextRect, hAlign | Qt::AlignVCenter, text);
    m_refPto += QPoint(rowWidth, 0);
}



///////////////////////////////////////////////////////
/// FUNCIONES PARA AYUDA AL PINTADO (new page, list) --
///////////////////////////////////////////////////////

/**
  *   @brief  Crea e inicializa una página estandar (con encabezado y pie)
  *
  *   @details
  *   Se genera una nueva página. Se pinta el encabezado y pie de página y se actualiza el número de páginas
  *
  *   @param  &pdfWr elemento de salida que guarda los cambios al fichero PDF correspondiente
  *   @param  enableHeaderFooter indica si se ha de pintar o no el encabezado y pie de página
  *   @return  void
  */
void pdfReportHelper::newPage(QPdfWriter& pdfWr,bool enableHeaderFooter){
    if(currentPageNumber>0){
        pdfWr.newPage();
    }
    currentPageNumber++;
    if(enableHeaderFooter){
        drawHeader_2logos(pdfWr);
        drawFooterSimple(pdfWr);
    }
}

/**
  *   @brief  Pinta una lista simple donde la definición de cada elemento está en negrita
  *
  *   @details
  *   Se pinta una lista en el espacio determinado. Se utiliza la opción de QStaticText por interpretar HTML
  *   Se espera una lista de cadenas con formato "Texto A|Texto B" que quedarán como:
  *   Texto A: Texto B, donde Texto A está en negrita.
  *
  *   Nota: La lista solo se limita en anchura. La altura queda a merced del número de lineas en la lista
  *
  *   @param  simpleList lista de cadenas que conforman el texto a imprimir
  *   @param  limitRectangle rectangulo que representa la posición y anchura máxima de la lista
  *   @return  void
  */
void pdfReportHelper::drawSimpleList(QStringList simpleList, QRect limitRectangle){
    QString textAux = "<table cellspacing=\"32\">"; //Contiene la lista configurada en HTML
    for(int i=0;i<simpleList.size();i++){ //Insertar cada linea a la lista
        QStringList splited=simpleList[i].split("|");
        if(splited.length() == 1){
            textAux += "<tr>";
            textAux += "<td></td>";
            textAux += "<td></td>";
            textAux += "<td>"+splited.at(0)+"</td>";
            textAux += "</tr>";
        }
        else{
            textAux += "<tr>";
            textAux += "<td style=\"text-align:right\"><b>" + splited.at(0) + "</b></td>";
            if(splited.at(0).compare("&nbsp;") != 0)
                textAux += "<td>:</td>";
            else
                textAux += "<td>&nbsp;</td>";
            textAux += "<td>" + splited.at(1) + "</td>";
            textAux += "</tr>";
        }
    }
    textAux += "</table>";
    QStaticText text; //Static text esta pensado para texto estatico, pero permite la interpretacion como html y por eso lo usamos aquí
    text.setTextWidth(limitRectangle.width()); //Se limita el ancho del texto al tamaño del rectangulo
    text.setText(textAux); //Se introduce la lista HTML como texto
    painter.drawStaticText(limitRectangle.topLeft(), text); //Y se imprime mediante el painter
}

/////////////////////////////////////////////////////
/// HEADER --
/////////////////////////////////////////////////////

/**
  *   @brief  Guarda los nuevos parámetros para el encabezado
  *
  *   @param  height altura del encabezado [mm]
  *   @param  padding separación entre elementos [mm]
  *   @param  imglogo1 imagen del logo izquierdo
  *   @param  imglogo2 imagen del logo derecho
  *   @param  title titulo del encabezado
  *   @return  void
  */
void pdfReportHelper::configHeader(int height, int padding, QImage imglogo1, QImage imglogo2, QString title){
    hHeight=height;
    hPadding=padding;
    hImgLogo1=imglogo1;
    hImgLogo2=imglogo2;
    hTitle=title;
}

/**
  *   @brief  Guarda un nuevo título para el encabezado
  *
  *   @details Normalmente solo interesa cambiar el título
  *
  *   @param  title titulo del encabezado
  *   @return  void
  */
void pdfReportHelper::setHeaderTitle(QString title){
    hTitle=title;
}

/**
  *   @brief  Pinta un encabezado con dos logos
  *
  *   @details
  *   Se pinta el encabezado estandar con dos logos, uno a cada lado, y un título centrado
  *   Se separa el encabezado del informe con una línea sólida negra
  *   Utiliza los parámetros guardados en la clase. Se ha de modificarlos antes de llamar a esta función si se quiere,
  *   por ejemplo, cambiar el título
  *
  *   @param  &pdfWr elemento de salida que guarda los cambios al fichero PDF correspondiente
  *   @return  void
  */
void pdfReportHelper::drawHeader_2logos(QPdfWriter& pdfWr){
    // Se encajan imágenes 16:9, si el logo tiene este formato se asegura que saldrá bien.
    //TODO LOGO IMPORTANT
    //double logoWidth=(hHeight-2*hPadding)*1.77777;
    int logoWidth=(hHeight-2*hPadding)*2;
    //double logoHeight=(hHeight-2*hPadding);
    int logoHeight=(hHeight-2*hPadding);
    painter.drawImage(QRect(hPadding*mm2pp,hPadding*mm2pp,logoWidth*mm2pp,logoHeight*mm2pp),hImgLogo1);
    painter.drawImage(QRect((pdfWr.widthMM()-hPadding-logoWidth)*mm2pp,hPadding*mm2pp,logoWidth*mm2pp,logoHeight*mm2pp),hImgLogo2);

    QFont font = painter.font(); //Cambiar tamanio de fuente para el título
    font.setPointSize(21);
    //QFont font("Courier",21);
    painter.setFont(font);

    //Se reserva el rectangulo entre los 2 logos para el titulo
    painter.drawText(QRect((hPadding*2+logoWidth)*mm2pp,hPadding*mm2pp,(pdfWr.widthMM()-hPadding*4-logoWidth*2)*mm2pp,logoHeight*mm2pp),
                     Qt::AlignCenter| Qt::AlignBottom | Qt::TextWordWrap,hTitle); //Qt::AlignJustify o AlignVCenter tambien exisite

    painter.drawLine(1,hHeight*mm2pp,pdfWr.width(),hHeight*mm2pp); //Linea separacion
}

/////////////////////////////////////////////////////
/// FOOTER --
/////////////////////////////////////////////////////

/**
  *   @brief  Guarda los nuevos parámetros para el pié de página
  *
  *   @param  height altura del pié de página [mm]
  *   @param  padding separación entre elementos [mm]
  *   @param  leftText texto del pié de página
  *   @return  void
  */
void pdfReportHelper::configFooter(int height, int padding, QString leftText){
    fHeight=height;
    fPadding=padding;
    fLeftText=leftText;
}

/**
  *   @brief  Actualiza el texto del pié de página
  *
  *   @details Normalmente solo interesa cambiar este texto
  *
  *   @param  leftText texto del pié de página
  *   @return  void
  */
void pdfReportHelper::setFooterText(QString leftText){
    fLeftText=leftText;
}

/**
  *   @brief  Pinta un pié de página con texto y número
  *
  *   @details
  *   Se pinta el pié de página estandar con el número de página a la izquieda y un texto configurable a la derecha
  *   Se separa el pié de página del resto del informe por una línea sólida negra
  *   Utiliza los parámetros guardados en la clase. Se ha de modificarlos antes de llamar a esta función si se quiere,
  *   por ejemplo, cambiar el título
  *
  *   @param  &pdfWr elemento de salida que guarda los cambios al fichero PDF correspondiente
  *   @return  void
  */
void pdfReportHelper::drawFooterSimple(QPdfWriter& pdfWr){
    painter.drawLine(1,(pdfWr.height()-(fHeight*mm2pp)),pdfWr.width(),(pdfWr.height()-(fHeight*mm2pp)));

    QFont font = painter.font(); //Cambiar el tamaño de la fuente
        font.setPointSize(11);
        painter.setFont(font);

    painter.drawText(QRect(fPadding*mm2pp,(pdfWr.heightMM()-(fHeight-fPadding))*mm2pp,pdfWr.width(),(fHeight-2*fPadding)*mm2pp),
                     Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, fLeftText);

    painter.drawText(QRect(fPadding*mm2pp,(pdfWr.heightMM()-(fHeight-fPadding))*mm2pp,(pdfWr.widthMM()-2*fPadding)*mm2pp,(fHeight-2*fPadding)*mm2pp),
                     Qt::AlignRight | Qt::AlignVCenter | Qt::TextWordWrap, QString::number(currentPageNumber));

}
