#include "oscannplot.h"
#include "qcustomplot.h"
#include <QDate>
#include "QString"

template<class T>
double median(QVector<T>);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

OscannPlot::OscannPlot( QQuickItem* parent ) : QQuickPaintedItem( parent ), m_CustomPlot( nullptr ){
    setFlag( QQuickItem::ItemHasContents, true );
    setAcceptedMouseButtons( Qt::AllButtons );
    connect( this, &QQuickPaintedItem::widthChanged, this, &OscannPlot::updateCustomPlotSize );
    connect( this, &QQuickPaintedItem::heightChanged, this, &OscannPlot::updateCustomPlotSize );



    //new GUIInterfaceAdaptor(this);
    //QDBusConnection connection = QDBusConnection::sessionBus();
    //connection.registerObject("/OscannPlot", this);
    //connection.registerService("aura.OscannInterface");

    //detectorIface = new aura::DetectorInterface("aura.oscann.pupil","/Detector",QDBusConnection::sessionBus(),this);
    //connect(detectorIface, SIGNAL(pupilAtDBus(double, double, double, double)), this, SLOT(pupilAtSlot(double, double, double, double)));

    //displayCTIface = new aura::DisplayCTInterface("org.oscann.dct",
    //                                   "/main",
    //                                   QDBusConnection::sessionBus(),
    //                                 this);
    //connect(displayCTIface, SIGNAL(scatterDBus(unsigned int)), this, SLOT(scatterSlot(unsigned int)));


    m_CustomPlot = new QCustomPlot();
    m_graphIndex = 0;


    //Valores por defecto
    testDim=QPointF(0,0);
    resolution=QPoint(0,0);
    screenSet=false;
    px2Deg=false;

    m_mouse=QPointF(0,0);
    prev=QPointF(0,0);

    setZoomMode(-1);
    rightPressed=false;
    leftPressed=false;
    moveInd=false;
    ctrlPressed=false;

    showPointer=false;
    showRaw=false;
    csvLoaded=false;

    m_objData = nullptr;
    m_graphType=GT.UND;
    moveTimer.setSingleShot(true);
    keyTimer.setSingleShot(true);

    setCreatingPdf(false);

    //Preconfiguracion
    m_CustomPlot->xAxis2->setVisible(true);
    m_CustomPlot->yAxis2->setVisible(true);
    m_CustomPlot->xAxis->setLabel("X Axis");
    m_CustomPlot->yAxis->setLabel("Y Axis");
    m_CustomPlot->axisRect()->setupFullAxesBox();
    m_CustomPlot->setNoAntialiasingOnDrag(true);

    m_CustomPlot->legend->setFont(QFont("Helvetica",12));
    //BACKGROUNDCOLOR:m_CustomPlot->legend->setBrush(QBrush(QColor(230,230,230)));
    m_CustomPlot->legend->setBrush(QBrush(Qt::transparent));
    //Erik: m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    m_CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom);
    m_CustomPlot->axisRect()->setBackground(CS.graphBG()); //CIFACE-PLOT-BACKGROUND
    m_CustomPlot->setBackground(QColor(CS.graphFG())); //CIFACE-PLOT-FOREGROUND
    m_CustomPlot->legend->setBorderPen(QPen(QColor(Qt::transparent)));

    //xAxis
    m_CustomPlot->xAxis->setLabelColor(Qt::white);
    m_CustomPlot->xAxis->setLabelFont(QFont("Helvetica",10));
    m_CustomPlot->xAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->xAxis->setTickLabelFont(QFont("Helvetica",10));
    m_CustomPlot->xAxis->grid()->setPen(QPen(CS.graphGridX(),0.05));
    m_CustomPlot->xAxis->grid()->setZeroLinePen(QPen(CS.graphGridX(),0.05));
    m_CustomPlot->xAxis->grid()->setSubGridPen(QPen(CS.graphGridX(),0.2,Qt::DashLine));
    //yAxis
    m_CustomPlot->yAxis->setLabelColor(Qt::white);
    m_CustomPlot->yAxis->setLabelFont(QFont("Helvetica",10));
    m_CustomPlot->yAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->yAxis->setTickLabelFont(QFont("Helvetica",10));
    m_CustomPlot->yAxis->grid()->setPen(QPen(CS.graphGridY(),0.05));
    m_CustomPlot->yAxis->grid()->setZeroLinePen(QPen(CS.graphGridY(),0.05));
    m_CustomPlot->yAxis->grid()->setSubGridPen(QPen(CS.graphGridY(),0.2,Qt::DashLine));
    m_CustomPlot->axisRect()->setAutoMargins(QCP::msNone);
    m_CustomPlot->axisRect()->setMargins(QMargins(90,10,40,42));

    setAcceptHoverEvents(true);//Erik remove
    //installEventFilter(this);//Erik

    onCustomReplot();
    //Erik
    m_tracerPosition = 0;

    f_playing = false;

    m_movingOnPlot = false;

    m_wheel = 0;



    m_earlyReleased = false;

}

OscannPlot::~OscannPlot(){
    m_CustomPlot->clearPlottables();
    m_CustomPlot->clearItems();
    delete m_CustomPlot;
    m_CustomPlot = nullptr;
}

void OscannPlot::setLayoutDim(int width, int height){
    m_CustomPlot->rect().setWidth(width);
    m_CustomPlot->rect().setHeight(height);
}

//__________________TIPOS DE PLOT__________________//

void OscannPlot::scatter(QVector<double> xData,QVector<double> yData,QString name,QColor begin,QColor end,double sizing){
    m_dots.clear();
    QString index("(deg)");
    QPen pen, validPen;
    if(m_graphType == GT.SCATTERCLB)
        index=QString("(px)");
    else if(!px2Deg){
        index=QString("(px)");
        for(int i=0;i<xData.size();i++){
            xData[i]=utilsProcess::deg2px(xData[i],screenDistance,resolution.x()/screenWidth);
            yData[i]=utilsProcess::deg2px(yData[i],screenDistance,resolution.x()/screenWidth);
        }
    }
    m_CustomPlot->addGraph();
    //m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setData(xData,yData);
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setPen(QPen(begin,0.5));
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setName(name);
    //m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setLineStyle(QCPGraph::lsNone);


    if(m_graphType == GT.SCATTER){
        calibrationXY();
    }


    /*for(int i=0;i<xData.size();i++){
        dot = new QCPItemTracer(m_CustomPlot);
        dot->position->setCoords(xData[i],yData[i]);
        if(blinks[i] >= 1 && m_graphType != GT.SCATTERCLB && m_graphType != GT.SCATTER && !name.contains("stimulus",Qt::CaseInsensitive)){
            dot->setStyle(QCPItemTracer::tsSquare);
            pen.setWidthF(sizing);
            pen.setColor(QColor(255-begin.red()-(end.red()-begin.red())*i/xData.size(),
                                255-begin.green()-(end.green()-begin.green())*i/xData.size(),
                                255-begin.blue()-(end.blue()-begin.blue())*i/xData.size()));
            pen.setStyle(Qt::SolidLine);

             dot->setPen(pen);
             dot->setSize(8);
             dot->setBrush(QBrush(QColor(255-begin.red()-(end.red()-begin.red())*i/xData.size(),
                                         255-begin.green()-(end.green()-begin.green())*i/xData.size(),
                                         255-begin.blue()-(end.blue()-begin.blue())*i/xData.size())));
            //dot->setPen(QPen(QColor(255-begin.red()-(end.red()-begin.red())*i/xData.size(),
            //                        255-begin.green()-(end.green()-begin.green())*i/xData.size(),
            //                        255-begin.blue()-(end.blue()-begin.blue())*i/xData.size()),sizing));
        }
        else if(m_graphType == GT.SCATTER){
            calibrationXY();
        }else{//GT.PICTURE
            dot->setPen(QPen(QColor(begin.red()+(end.red()-begin.red())*i/xData.size(),
                                            begin.green()+(end.green()-begin.green())*i/xData.size(),
                                            begin.blue()+(end.blue()-begin.blue())*i/xData.size()),sizing));
                    dot->setBrush(QBrush(QColor(begin.red()+(end.red()-begin.red())*i/xData.size(),
                                            begin.green()+(end.green()-begin.green())*i/xData.size(),
                                            begin.blue()+(end.blue()-begin.blue())*i/xData.size())));

        }
        dot->setId(i);
        dot->setType(-1);
        //installEventFilter(dot);
        m_dots.push_back(dot);
    }*/
    if(m_graphType != GT.SCATTER){
        //Recuadro de margenes de la pantalla
        margins=new QCPItemRect(m_CustomPlot);
        margins->setPen(QPen(Qt::black,2,Qt::DashLine));
        margins->topLeft->setCoords(-testDim.x()/2,testDim.y()/2);
        margins->bottomRight->setCoords(testDim.x()/2,-testDim.y()/2);
    }
    //Ejes
    m_CustomPlot->xAxis->setLabel("X Position "+index);
    m_CustomPlot->yAxis->setLabel("Y Position "+index);
    if(m_graphType != GT.SCATTER){
        m_CustomPlot->xAxis->setRange(-0.55*testDim.x(),0.55*testDim.x());
        m_CustomPlot->yAxis->setRange(0.55*testDim.y(),-0.55*testDim.y());
    }
}

void OscannPlot::calibrationXY(){
    QCPItemTracer *dot;
    QCPItemTracer *validdot;
    QCPItemTracer *stmdot;
    double lastXS = xS[0];
    double lastYS = yS[0];
    int color = 0;
    QPen pen, validPen, stmPen;
    QVector<QColor> colors;
    colors.push_back(Qt::red);
    colors.push_back(QColor("orange"));
    colors.push_back(QColor("#800000"));//Marron
    colors.push_back(Qt::green);
    colors.push_back(Qt::blue);
    colors.push_back(QColor("#4b0082"));//Indigo
    colors.push_back(Qt::yellow);
    colors.push_back(QColor("#00ffff"));//Cyan
    colors.push_back(QColor("#ff00ff"));//Magenta

    double xMin = 99;
    double xMax = -99;
    double yMin = 99;
    double yMax = -99;

    qDebug()<<" xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.size(): "<<x.size();
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setData(x,y);

    for(int i=0;i<x.size();i++){
        //qDebug()<<Q_FUNC_INFO<<" x: "<<x[i]<<", y: "<<y[i];
        if(blinks[i] == 0){
            dot = new QCPItemTracer(m_CustomPlot);
            dot->position->setCoords(x[i], y[i]);
            dot->setStyle(QCPItemTracer::tsCircle);
            pen.setWidthF(0.5);
            if(lastXS != xS[i] || lastYS != yS[i] ){
                color++;
                stmdot = new QCPItemTracer(m_CustomPlot);
                stmdot->position->setCoords(lastXS, lastYS);
                stmdot->setStyle(QCPItemTracer::tsCircle);
                stmPen.setWidthF(1.0);
                stmPen.setColor(QColor(Qt::black));
                stmPen.setStyle(Qt::SolidLine);
                stmdot->setPen(stmPen);
                stmdot->setSize(30*6);
            }
            lastXS = xS[i];
            lastYS = yS[i];
            pen.setColor(QColor(colors.at(color)));
            pen.setStyle(Qt::SolidLine);
             dot->setPen(pen);
             dot->setSize(16);
             if(x[i] < xMin)
                 xMin = x[i];
             if(x[i] > xMax)
                 xMax = x[i];
             if(y[i] < yMin)
                 yMin = y[i];
             if(y[i] > yMax)
                 yMax = y[i];
             if(valid[i]){
                 validPen.setWidthF(2.0);
                 validPen.setColor(colors.at(color));
                 validPen.setStyle(Qt::SolidLine);
                 validdot = new QCPItemTracer(m_CustomPlot);
                 validdot->position->setCoords(x[i],y[i]);
                 validdot->setStyle(QCPItemTracer::tsPlus);
                 validdot->setPen(validPen);
                 validdot->setSize(8);
                 m_dots.push_back(validdot);
             }
             dot->setId(i);
             dot->setType(-1);
             //installEventFilter(dot);
             m_dots.push_back(dot);
        }
    }
    m_scatterRangeX.setX(xMin);
    m_scatterRangeX.setY(xMax);
    m_scatterRangeY.setX(yMin);
    m_scatterRangeY.setY(yMax);
    stmdot = new QCPItemTracer(m_CustomPlot);
    stmdot->position->setCoords(lastXS, lastYS);
    stmdot->setStyle(QCPItemTracer::tsCircle);
    stmPen.setWidthF(1.0);
    stmPen.setColor(QColor(Qt::black));
    stmPen.setStyle(Qt::SolidLine);
    stmdot->setPen(stmPen);
    stmdot->setSize(30*6);
    //qDebug()<<Q_FUNC_INFO<<"xMin: "<<xMin<<", xMax: "<<xMax<<", yMin: "<<yMin<<", yMax: "<<yMax;
    m_CustomPlot->xAxis->setRange(xMin+(xMin*0.1),xMax+(xMax*0.1));
    m_CustomPlot->yAxis->setRange(yMin+(yMin*0.1),yMax+(yMax*0.2));
}

void OscannPlot::plot(QVector<double> xData,QVector<double> yData, unsigned int style,QString name,QColor color,int width){
    QString index("(deg)");

    if(!px2Deg && m_graphType != GT.PUPILAREA){
        index=QString("(px)");
        for(int i=0;i<yData.size();i++)
            yData[i]=utilsProcess::deg2px(yData[i],screenDistance,resolution.x()/screenWidth);
    }
    m_CustomPlot->addGraph();
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setData(xData,yData);
    //TODOPLOTLINE
    QPen pen;
    pen.setColor(color);
    pen.setWidth(width);
    switch (style) {
    case 0:
        pen.setStyle(Qt::SolidLine);
        break;
    case 1:
        pen.setStyle(Qt::DotLine);
        break;
    }
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setPen(QPen(color,width));
    m_CustomPlot->graph(m_CustomPlot->graphCount()-1)->setName(name);
    //Ejes
    m_CustomPlot->xAxis->setLabel("Time (ms)");
    m_CustomPlot->yAxis->setLabel("Position "+index);
    //Recuadro de margenes de pantalla
    margins=new QCPItemRect(m_CustomPlot);
    margins->setPen(QPen(Qt::transparent,0,Qt::SolidLine));
    if(m_graphType == GT.PLOTX){
        margins->topLeft->setCoords(time[0]-1,testDim.x()/2);
        margins->bottomRight->setCoords(time[time.size()-1]+1,-testDim.x()/2);
        m_CustomPlot->rescaleAxes();
        m_CustomPlot->yAxis->setRange(-0.55*testDim.x(),0.55*testDim.x());

    }
    else if(m_graphType == GT.PLOTY){
        margins->topLeft->setCoords(time[0]-1,testDim.y()/2);
        margins->bottomRight->setCoords(time[time.size()-1]+1,-testDim.y()/2);
        m_CustomPlot->rescaleAxes();
        m_CustomPlot->yAxis->setRange(-0.55*testDim.y(),0.55*testDim.y());
    }
    else if(m_graphType == GT.PUPILAREA)
        m_CustomPlot->rescaleAxes();


}

void OscannPlot::plotBlinks(int funcType){
    bool nFirst=false;
    QVector<double> blinksTmp,timeTmp;
    for(int i=0;i<blinks.size();i++){
        if(blinks[i]==1 && i!=blinks.size()-1){
            if(funcType==GT.PLOTX)
                blinksTmp.push_back(x[i]);
            else if(funcType==GT.PLOTY)
                blinksTmp.push_back(y[i]);
            timeTmp.push_back(time[i]);
        }
        else if((blinks[i]==0 || i==blinks.size()-1) && !blinksTmp.isEmpty()){
            plot(timeTmp,blinksTmp, 0,"Blinks",QColor(250,150,0));
            blinksTmp.clear();
            timeTmp.clear();
            if(nFirst)
                m_CustomPlot->legend->removeItem(m_CustomPlot->legend->itemCount()-1);
            nFirst=true;
        }
    }
    //SANTI APAÑO????? TEMPORAL PARPADEOS 2
    nFirst=false;
    QCPItemTracer *fail;
    for(int i=0;i<blinks.size();i++){
        if(blinks[i]==2 && i!=blinks.size()-1){ //Se hacen los de tipo 2, solo cambiando la condición y el color de salida
            if(funcType==GT.PLOTX)
                blinksTmp.push_back(x[i]);
            else if(funcType==GT.PLOTY)
                blinksTmp.push_back(y[i]);
            timeTmp.push_back(time[i]);
            fail = new QCPItemTracer(m_CustomPlot);
            if(funcType==GT.PLOTX)
                fail->position->setCoords(time[i],x[i]);
            else if(funcType==GT.PLOTY)
               fail->position->setCoords(time[i],y[i]);
            fail->setStyle(QCPItemTracer::tsCircle);
            fail->setPen(QPen(QColor(250,0,0),2));

        }
        else if((blinks[i]==0 || i==blinks.size()-1) && !blinksTmp.isEmpty()){
            plot(timeTmp,blinksTmp, 0,"Failure",QColor(250,0,0),3);
            blinksTmp.clear();
            timeTmp.clear();
            if(nFirst)
                m_CustomPlot->legend->removeItem(m_CustomPlot->legend->itemCount()-1);
            nFirst=true;
        }
    }
}

void OscannPlot::addPicture(QString dir){
    if(dir == ""){
        if(QFile(QString(testDir+"/image.png")).exists()){
            picture=QPixmap(testDir+"/image.png");
            picDir=QString(testDir+"/image.png");
            emit autoPic(true);
        }
    }
    else if(dir != "" && (dir.split(".").last() == "png" || dir.split(".").last() == "jpg")){
        picture=QPixmap(dir);
        picDir=dir;
        emit autoPic(false);
    }
    else{
        picture=QPixmap(static_cast<int>(testDim.x()),static_cast<int>(testDim.y()));
        picture.fill(Qt::white);
    }

    pic=new QCPItemPixmap(m_CustomPlot);
    pic->setLayer("background");
    pic->setPixmap(picture);
    pic->setScaled(true,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pic->topLeft->setCoords(-utilsProcess::px2deg(pic->pixmap().width()/2),utilsProcess::px2deg(pic->pixmap().height()/2));
    pic->bottomRight->setCoords(utilsProcess::px2deg(pic->pixmap().width()/2),-utilsProcess::px2deg(pic->pixmap().height()/2));
}

void OscannPlot::pupilLightVar(){
    QVector<double> varCoord;
    for(int i=1;i<xS.size();i++){
        if(xS[i-1]!=xS[i] || yS[i-1]!=yS[i])
            varCoord.push_back(time[i]);
    }

    if(varCoord.size()<50){
        for(int i=0;i<varCoord.size();i++){
            QCPItemLine *varLine = new QCPItemLine(m_CustomPlot);
            varLine->start->setCoords(varCoord[i],m_CustomPlot->yAxis->range().upper);
            varLine->end->setCoords(varCoord[i],m_CustomPlot->yAxis->range().lower);
            varLine->setPen(QPen(QColor(0,204,255),2,Qt::DashLine));
        }
    }
}

void OscannPlot::heatMap(){
    QCPColorMap *colorMap = new QCPColorMap(m_CustomPlot->xAxis,m_CustomPlot->yAxis);
    colorMap->data()->setSize(160,90); //Se ponen las dimensiones del test para el heatmap (10px de resolucion)
    colorMap->data()->setRange(QCPRange(-testDim.x()/2,testDim.x()/2),QCPRange(-testDim.y()/2,testDim.y()/2)); //Se colocan los margenes del heatmap
    //Asignacion de los datos al heatmap
    for(int i=0;i<testDim.x();i+=10){
        for(int j=0;j<testDim.y();j+=10){
            colorMap->data()->setData(i,j,0);
        }
    }
    int xMap,yMap;
    for(int i=0;i<x.length();i++){
        colorMap->data()->coordToCell(utilsProcess::deg2px(x[i]),utilsProcess::deg2px(y[i]),&xMap,&yMap);
        colorMap->data()->setCell(xMap,yMap,colorMap->data()->cell(xMap,yMap)+1);
    }
    //TODO (David): Implementar filtro de mediana para eliminar posibles sacadas
    colorMap->data()->fillAlpha(100);                   //Se pone el heatmap semi-transparente
    colorMap->setGradient(QCPColorGradient::gpJet);     //Seleccionar el gradiente de colores para el heatmap
    colorMap->setInterpolate(true);                     //Se hace que el heatmap este interpolado
    colorMap->rescaleDataRange();                       //Reescalar el heatmap a las dimensiones del plot
    onCustomReplot();
}

//__________________CONFIGURACIONES__________________//

QPoint OscannPlot::setScreen(QString path){
    if(QFile(path+QString("/camera.ini")).exists()){
        qDebug()<<Q_FUNC_INFO<<" path: "<<path;
        QSettings *settings = new QSettings(path + QString("/camera.ini"), QSettings::IniFormat);
        resolution.setX(settings->value("screenWidth","1920").toInt());
        resolution.setY(settings->value("screenHeight","1080").toInt());
        screenWidth=settings->value("monitorWidth","53").toDouble();
        screenDistance=settings->value("monitorDistance","60").toDouble();
        ratioPxDeg=settings->value("screenWidth","1920").toDouble()/((360/M_PI)*qAtan(settings->value("monitorWidth","53").toDouble()/(2*settings->value("monitorDistance","60").toDouble())));
        utilsProcess::resolution=resolution;
        utilsProcess::sDist=screenDistance;
        utilsProcess::sWidth=screenWidth;
        screenSet=true;
    }
    else
        screenSet=false;
    return resolution;
}

double OscannPlot::loadDistance(QString path){
    if(QFile(path+QString("/camera.ini")).exists()){
        QSettings *settings = new QSettings(path + QString("/camera.ini"), QSettings::IniFormat);
        return settings->value("monitorDistance","1").toDouble();
    }
    else
        return 1;
}

double OscannPlot::loadWidth(QString path){
    if(QFile(path+QString("/camera.ini")).exists()){
        QSettings *settings = new QSettings(path + QString("/camera.ini"), QSettings::IniFormat);
        return settings->value("monitorWidth","1").toDouble();
    }
    else
        return 1;
}

//__________________FUNCION DE ENTRADA QML__________________//

QPixmap OscannPlot::getImage(int width,int hight,int fontSize,QColor backgroundcolor){
    m_CustomPlot->setBackground(Qt::white);
    m_CustomPlot->axisRect()->setBackground(backgroundcolor);
    m_CustomPlot->axisRect()->setMargins(QMargins(90,10,10,90));
    m_CustomPlot->yAxis->setRange(-25,25);
    m_CustomPlot->xAxis->setLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->xAxis->setTickLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->xAxis->setLabelColor(Qt::black);
    m_CustomPlot->xAxis->setTickLabelColor(Qt::black);
    m_CustomPlot->yAxis->setLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->yAxis->setTickLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->yAxis->setLabelColor(Qt::black);
    m_CustomPlot->yAxis->setTickLabelColor(Qt::black);
    m_CustomPlot->legend->setFont(QFont("Helvetica",fontSize));
    title->setFont(QFont("Helvetica",fontSize));
    title->setBrush(Qt::white);
    if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY){
        //m_CustomPlot->graph(m_graphIndex-1)->setPen(QPen(Qt::red,2.5));
        m_CustomPlot->graph(m_graphIndex-1)->setPen(QPen(Qt::gray,2.5,Qt::DotLine));
        m_CustomPlot->graph(m_graphIndex)->setPen(QPen(QColor(0,204,255),2.5));
    }
    return m_CustomPlot->toPixmap(width,hight);
}


void OscannPlot::init(bool preview, int mode,bool px2DegTmp,QString testPath,QString imgPath,QColor colorBegin,QColor colorEnd){
    m_preview = preview;
    m_graphIndex=0;
    px2Deg=px2DegTmp;
    if(px2Deg){
        unitIndex="deg";
        testDim.setX(utilsProcess::px2deg(resolution.x()/2)*2); //MUY IMPORTANTE!
        testDim.setY(utilsProcess::px2deg(resolution.y()/2)*2); //Siempre se mide respecto del centro de la pantalla (no quitar el /2 y *2)
    }
    else{
        unitIndex="px";
        testDim.setX(resolution.x());
        testDim.setY(resolution.y());
    }

    if(m_creatingPdf){  //4.0.11: New Statement
        testName=testPath;
        qDebug()<<Q_FUNC_INFO<<" testName: "<<testName;
    }
    else if(testPath!=""){
        testDir=testPath;
        QStringList ele = testDir.split("/");
        testName=QString(ele.last()).split("-").first();
        m_sessionName=QString(ele[ele.length()-2]);
    }
    else{
        testName="";
        m_sessionName = "";
    }
    lastColor=0;
    imgDir=imgPath;


    updateCustomPlotSize();
    xPix=qFabs(m_CustomPlot->axisRect()->right()-m_CustomPlot->axisRect()->left());
    yPix=qFabs(m_CustomPlot->axisRect()->top()-m_CustomPlot->axisRect()->bottom());
    //The items of these vectors, and other added in the future, most be removed from the vector before make a clean to m_CustomPlot.
    //Borrar todos los items y graficas que hay en pantalla
    m_CustomPlot->clearGraphs();
    m_CustomPlot->clearItems();
    //Indicador de zoom (futuro cuadrado)
    zoomInd=new QCPItemRect(m_CustomPlot);
    zoomInd->setLayer("overlay");
    zoomInd->setVisible(false);
    //Titulo
    title=new QCPItemText(m_CustomPlot);
    title->setLayer("legend");
    title->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    title->position->setType(QCPItemPosition::ptAxisRectRatio);
    //Oscann 3.0.3: title->position->setCoords(0.005,0.02);
    //Oscann 4.0.5: title->position->setCoords(0.005,0.04); //This change was for pdf? Check it
    title->position->setCoords(0.005,0.005);
    title->setFont(QFont("Helvetica",14));
    //TEXTCOLOR
    if(m_creatingPdf){
        title->setPen(QPen(Qt::white));
    }else{
        title->setPen(QPen(Qt::transparent));
        title->setColor(QColor(255,255,255));
        m_CustomPlot->legend->setTextColor(QColor(255,255,255));
    }
    //BACKGROUNDCOLOR:title->setBrush(QBrush(QColor(230,230,230)));
    title->setBrush(QBrush(Qt::transparent));
    title->setPadding(QMargins(4,1,4,1));
    title->setVisible(false);
    //Texto coordenadas
    pointerLabel=new QCPItemText(m_CustomPlot);
    pointerLabel->setLayer("overlay");
    pointerLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignRight);
    pointerLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    pointerLabel->position->setCoords(0.995,0.005);
    pointerLabel->setFont(QFont("Helvetica",12));
    //TEXTCOLOR
    if(m_creatingPdf){
        pointerLabel->setPen(QPen(Qt::white));
    }else{
        pointerLabel->setPen(QPen(Qt::transparent));
        pointerLabel->setColor(QColor(255,255,255));
    }
    //BACKGROUNDCOLOR: pointerLabel->setBrush(QColor(230,230,230));
    pointerLabel->setBrush(Qt::transparent);
    pointerLabel->setPadding(QMargins(2,2,2,2));
    pointerLabel->setVisible(false);
    //Punto coordenadas
    pointer=new QCPItemTracer(m_CustomPlot);
    pointer->setLayer("overlay");
    pointer->position->setCoords(0,0);
    pointer->setStyle(QCPItemTracer::tsCircle);
    pointer->setPen(QPen(Qt::black,2));
    pointer->setBrush(Qt::darkGray);
    pointer->setSize(10);
    pointer->setVisible(false);
    pointer->setId(-1);
    pointer->setType(-1);
    //Erik
    pointer->setPlotXAxis(m_CustomPlot->xAxis);
    pointer->setPlotYAxis(m_CustomPlot->yAxis);
    pointer->setXYScaleFactor(6.0, 0.03, false);
    showPointer=false;
    //Rectangulo de seleccion de sacada
    //Extras
    m_CustomPlot->xAxis->grid()->setVisible(true);
    m_CustomPlot->yAxis->grid()->setVisible(true);
    m_CustomPlot->legend->setVisible(true);
    m_graphType=mode;
    //Plot estandar en X
    if(m_graphType == GT.PLOTX){
        plot(time,xS, 1,"Stimulus",CS.graphStimulus()); //timeS
        plot(time,x, 0,"Gaze",CS.graphGaze());
        plotBlinks(m_graphType);
        title->setText(QString("%1 : %2").arg(m_sessionName).arg(m_objData->getTitle(testName)));
    }
    //Plot estandar en Y
    else if(m_graphType == GT.PLOTY){
        plot(time,yS, 1,"Stimulus",CS.graphStimulus()); //timeS
        plot(time,y, 0,"Gaze",CS.graphGaze());
        plotBlinks(m_graphType);
        title->setText(QString("%1 : %2").arg(m_sessionName).arg(m_objData->getTitle(testName)));
    }
    //Scatter de Y frente a X
    else if(m_graphType == GT.SCATTER){
        scatter(x,y,"XY Processed",QColor(0,204,255),QColor(0,102,127));
        //scatter(xS,yS,"XY Stimulus",Qt::black,Qt::black);
        title->setText("XY Gaze");
    }
    //Plot con imagen seleccionada
    else if(m_graphType == GT.PICTURE){
        addPicture(imgPath);
        m_CustomPlot->xAxis->grid()->setVisible(false);
        m_CustomPlot->yAxis->grid()->setVisible(false);
        scatter(x,y,"XY Processed",colorBegin,colorEnd);
//        heatMap();
        title->setText("Picture Gaze");
    }
    //Plot area de la pupila
    else if(m_graphType == GT.PUPILAREA){ //Plot del area de la pupila vista desde la camara
        plot(time,pupilArea, 0,"Pupil area",QColor(0,0,120));
        pupilLightVar();
        m_CustomPlot->yAxis->setLabel("Pupil area seen from camera (px^2)"); //Se modifica la etiqueta del eje Y
        title->setText("Pupil Area");
    }
    if(m_graphType != GT.SCATTER)
        autoScale();
    title->setVisible(true);
    setZoomMode(1);
    emit zoomChanged(false);
    if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY){
        m_graphIndex = 1;
        if(!m_creatingPdf){
            m_videoPreviewer->setPointerFromTo(0, m_CustomPlot->graph(m_graphIndex)->data().data()->size());
            m_tracerSelected = pointer;         //To move tracer when a test is loaded
        }
    }
    else{
        m_graphIndex = 0;
    }
    if(!m_creatingPdf){
        m_plotKeys.clear();
        if(QFile(QString(testDir+"/raw/"+testDir.split("/").last()+"_0.avi")).exists()){
            m_videoAvailable = true;
            for(int i=0;i<m_CustomPlot->graph(m_graphIndex)->data().data()->size();i++){
                m_plotKeys.push_back(m_CustomPlot->graph(m_graphIndex)->data().data()->at(i)->key);
            }
            m_picturePosition = QPointF(0,0);
            calcPic();
        }
        else{
            m_videoAvailable = false;
        }
    }
    pointer->setLastKey((m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key);
    pointer->setPlotSize(m_CustomPlot->graph(m_graphIndex)->data().data()->size());
    m_wheel = 0;
    m_earlyReleased = false;
    m_zooming = false;
    f_playing = false;
    if(m_graphType != GT.PICTURE && !m_creatingPdf)
        m_videoPreviewer->newPointerPosition(m_tracerPosition = 0);
    //NOTE: These lines were added because the first Zoom in the scatter calibration they do not have value...
    maxRange=QPointF(m_CustomPlot->xAxis->range().upper,m_CustomPlot->yAxis->range().upper);
    minRange=QPointF(m_CustomPlot->xAxis->range().lower,m_CustomPlot->yAxis->range().lower);
    onCustomReplot();
}

void OscannPlot::wheelEvent(QWheelEvent *event){
    //TODO (David): Mirar bien para mantener un sistema consistente de zoom que utilice la misma relación de aspecto que antes de hacer zoom
    if(m_CustomPlot->graphCount() > 0 &&    //Zoom Out
            m_CustomPlot->xAxis->pixelToCoord(event->pos().x())<m_CustomPlot->xAxis->range().upper && m_CustomPlot->xAxis->pixelToCoord(event->pos().x())>m_CustomPlot->xAxis->range().lower &&
            m_CustomPlot->yAxis->pixelToCoord(event->pos().y())<m_CustomPlot->yAxis->range().upper && m_CustomPlot->yAxis->pixelToCoord(event->pos().y())>m_CustomPlot->yAxis->range().lower){

        //Calcula el proximo zoom respecto del centro de la pantalla
        QPointF nextMaxRange(m_CustomPlot->xAxis->range().upper-0.05*m_CustomPlot->xAxis->range().size(),
                             m_CustomPlot->yAxis->range().upper-0.05*m_CustomPlot->yAxis->range().size());

        QPointF nextMinRange(m_CustomPlot->xAxis->range().lower+0.05*m_CustomPlot->xAxis->range().size(),
                             m_CustomPlot->yAxis->range().lower+0.05*m_CustomPlot->yAxis->range().size());

        //Calcula el ratio de desplazamiento para mover el zoom al lugar correcto
        //1 seria mover el zoom al extremo de uno de los lados o superior o inferior, 0 seria mantener el zoom en el centro
        QPointF cRatio((2*m_CustomPlot->xAxis->pixelToCoord(event->pos().x())-m_CustomPlot->xAxis->range().upper-m_CustomPlot->xAxis->range().lower)/m_CustomPlot->xAxis->range().size(),
                       (2*m_CustomPlot->yAxis->pixelToCoord(event->pos().y())-m_CustomPlot->yAxis->range().upper-m_CustomPlot->yAxis->range().lower)/m_CustomPlot->yAxis->range().size());

        //Caso en el que se hace +zoom
        if(event->delta() > 0 && (nextMaxRange.x()-nextMinRange.x()>0.0001*(maxRange.x()-minRange.x()) || nextMaxRange.y()-nextMinRange.y()>0.0001*(maxRange.y()-minRange.y()))){

            //Se corrige la colocacion del cuadrado de enfoque con el ratio multiplicando a la distancia hasta el borde
            m_CustomPlot->xAxis->setRange(nextMinRange.x()+cRatio.x()*(m_CustomPlot->xAxis->range().upper-nextMaxRange.x()),
                                          nextMaxRange.x()+cRatio.x()*(m_CustomPlot->xAxis->range().upper-nextMaxRange.x()));

            m_CustomPlot->yAxis->setRange(nextMinRange.y()+cRatio.y()*(m_CustomPlot->yAxis->range().upper-nextMaxRange.y()),
                                          nextMaxRange.y()+cRatio.y()*(m_CustomPlot->yAxis->range().upper-nextMaxRange.y()));
        }
        else if(event->delta() < 0){    //Zoom Out
            //Se calcula el proximo zoom respecto del centro de la pantalla
            nextMaxRange=QPointF(m_CustomPlot->xAxis->range().upper+0.05*m_CustomPlot->xAxis->range().size(),
                                 m_CustomPlot->yAxis->range().upper+0.05*m_CustomPlot->yAxis->range().size());

            nextMinRange=QPointF(m_CustomPlot->xAxis->range().lower-0.05*m_CustomPlot->xAxis->range().size(),
                                 m_CustomPlot->yAxis->range().lower-0.05*m_CustomPlot->yAxis->range().size());

            //Caso en el que el proximo cuadro se sale por el lado derecho, se mueve el cuadrado a la izquierda
            if(nextMaxRange.x()>maxRange.x() && nextMinRange.x()>minRange.x()+nextMaxRange.x()-maxRange.x())
                m_CustomPlot->xAxis->setRange(nextMinRange.x()-nextMaxRange.x()+maxRange.x(),maxRange.x());
            //Caso en el que el proximo zoom se sale por el lado izquierdo, se mueve el cuadrado a la derecha
            else if(nextMaxRange.x()<maxRange.x()+nextMinRange.x()-minRange.x() && nextMinRange.x()<minRange.x())
                m_CustomPlot->xAxis->setRange(minRange.x(),nextMaxRange.x()-nextMinRange.x()+minRange.x());
            //Caso en el que el proximo zoom se sale por los dos lados, se pone el zoom original
            else if(nextMaxRange.x()-nextMinRange.x()>maxRange.x()-minRange.x())
                m_CustomPlot->xAxis->setRange(minRange.x(),maxRange.x());
            //Caso por defecto, se mueve el cuadrado segun el ratio de desplazamiento obtenido
            else
                m_CustomPlot->xAxis->setRange(nextMinRange.x()+cRatio.x()*(m_CustomPlot->xAxis->range().upper-nextMaxRange.x()),
                                              nextMaxRange.x()+cRatio.x()*(m_CustomPlot->xAxis->range().upper-nextMaxRange.x()));
            //Caso en el que el proximo cuadro se sale por el extremo superior, se mueve el cuadrado hacia abajo
            if(nextMaxRange.y()>maxRange.y() && nextMinRange.y()>minRange.y()+nextMaxRange.y()-maxRange.y())
                m_CustomPlot->yAxis->setRange(nextMinRange.y()-nextMaxRange.y()+maxRange.y(),maxRange.y());
            //Caso en el que el proximo cuadro se sale por el extremo inferior, se mueve el cuadrado hacia arriba
            else if(nextMaxRange.y()<maxRange.y()+nextMinRange.y()-minRange.y() && nextMinRange.y()<minRange.y())
                m_CustomPlot->yAxis->setRange(minRange.y(),nextMaxRange.y()-nextMinRange.y()+minRange.y());
            //Caso en el que el proximo cuadrado se sale por ambos extremos, se pone el zoom original
            else if(nextMaxRange.y()-nextMinRange.y()>maxRange.y()-minRange.y())
                m_CustomPlot->yAxis->setRange(minRange.y(),maxRange.y());
            //Caso por defecto, se mueve el cuadrado segun el ratio de desplazamiento obtenido
            else
                m_CustomPlot->yAxis->setRange(nextMinRange.y()+cRatio.y()*(m_CustomPlot->yAxis->range().upper-nextMaxRange.y()),
                                              nextMaxRange.y()+cRatio.y()*(m_CustomPlot->yAxis->range().upper-nextMaxRange.y()));
        }
        m_videoPreviewer->setPointerFromTo(qRound(m_CustomPlot->xAxis->range().lower/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(0)->data().data()->size()),
                                           qRound(m_CustomPlot->xAxis->range().upper/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(0)->data().data()->size()));
        setXYScaleFactor(m_CustomPlot->xAxis->range().upper-m_CustomPlot->xAxis->range().lower,
                         m_CustomPlot->yAxis->range().upper-m_CustomPlot->yAxis->range().lower, false);
        onCustomReplot();
    }
}




//__________________INTERACCIONES__________________//

void OscannPlot::setZoomMode(int mode){
    if(m_CustomPlot->graphCount()>0){
        switch(mode){
        case 0:
            setCursor(Qt::OpenHandCursor);
            break;
        case 1:
            setCursor(Qt::CrossCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
        }
        zoomMode=mode;
    }
    else{
        setCursor(Qt::ArrowCursor);
        zoomMode=-1;
    }
}
//v4.0.13
void OscannPlot::openInExplorer(){
    system(QString("nemo %1").arg(testDir).toLatin1().data());
}
void OscannPlot::autoScale(bool autom, unsigned int index){
    if(m_CustomPlot->graphCount()>0){
        if(autom){
            m_CustomPlot->rescaleAxes();
            double xMin = index > 0 ? m_CustomPlot->xAxis->range().lower-0.1*m_CustomPlot->xAxis->range().size() : -45.0;
            double xMax = index > 2 ? m_CustomPlot->xAxis->range().upper+0.1*m_CustomPlot->xAxis->range().size() : 45.0;
            double yMin = index > 6 ? m_CustomPlot->yAxis->range().lower-0.1*m_CustomPlot->yAxis->range().size() : -20.0;
            double yMax = index > 0 ? m_CustomPlot->yAxis->range().upper+0.1*m_CustomPlot->yAxis->range().size() : 40.0;
            m_CustomPlot->xAxis->setRange(xMin,xMax);
            m_CustomPlot->yAxis->setRange(yMin,yMax);
        }
        else{
            if(m_graphType == GT.PLOTX){
                m_CustomPlot->rescaleAxes();
                m_CustomPlot->yAxis->setRange(-0.55*testDim.x(),0.55*testDim.x());
            }
            else if(m_graphType == GT.PLOTY){
                m_CustomPlot->rescaleAxes();
                m_CustomPlot->yAxis->setRange(-0.55*testDim.y(),0.55*testDim.y());
            }
            else if(m_graphType == GT.PUPILAREA){
                m_CustomPlot->rescaleAxes();
            }
            else if(m_graphType == GT.SCATTER){ //TODOZOOM
                m_CustomPlot->xAxis->setRange(m_scatterRangeX.x(), m_scatterRangeX.y());
                m_CustomPlot->yAxis->setRange(m_scatterRangeY.x(), m_scatterRangeY.y());
            }
            else if(m_graphType == GT.PICTURE){
                if(xPix/testDim.x()>=yPix/testDim.y()){
                    m_CustomPlot->xAxis->setRange(-testDim.x()*((testDim.y()/testDim.x())/(yPix/xPix))/2,testDim.x()*((testDim.y()/testDim.x())/(yPix/xPix))/2);
                    m_CustomPlot->yAxis->setRange(-testDim.y()/2,testDim.y()/2);
                }
                else{
                    m_CustomPlot->xAxis->setRange(-testDim.x()/2,testDim.x()/2);
                    m_CustomPlot->yAxis->setRange(-testDim.y()*((testDim.x()/testDim.y())/(xPix/yPix))/2,testDim.y()*((testDim.x()/testDim.y())/(xPix/yPix))/2);
                }
            }
            maxRange=QPointF(m_CustomPlot->xAxis->range().upper,m_CustomPlot->yAxis->range().upper);
            minRange=QPointF(m_CustomPlot->xAxis->range().lower,m_CustomPlot->yAxis->range().lower);
            setXYScaleFactor(m_CustomPlot->xAxis->range().upper-m_CustomPlot->xAxis->range().lower,
                            m_CustomPlot->yAxis->range().upper-m_CustomPlot->yAxis->range().lower, true);
        }
        if(m_graphType != GT.SCATTERCLB && !m_creatingPdf)
            m_videoPreviewer->setPointerFromTo(0, m_CustomPlot->graph(m_graphIndex)->data().data()->size());
        onCustomReplot();
    }
    m_wheel = 0;
}

void OscannPlot::removeEvents(QCPItemTracer* obj){
    removeEventFilter(obj);
    disconnect(obj, SIGNAL(moveMe(int,int, int)), nullptr, nullptr);
    disconnect(obj, SIGNAL(dotCatched(int, int, int)), nullptr, nullptr);
    disconnect(obj, SIGNAL(dotReleased(QPoint, int)), nullptr, nullptr);
    disconnect(obj, SIGNAL(overSomeTracer(bool)), nullptr, nullptr);
}

void OscannPlot::installEvents(QCPItemTracer* obj){
    connect(obj, SIGNAL(moveMe(int,int,int)), this, SLOT(moveMeSlot(int,int,int)));
    connect(obj, SIGNAL(dotCatched(int, int, int)), this, SLOT(dotCatchedSlot(int, int, int)));
    connect(obj, SIGNAL(dotReleased(QPoint, int)), this, SLOT(dotReleasedSlot(QPoint, int)));
    connect(obj, SIGNAL(overSomeTracer(bool)), this, SLOT(overSomeTracerSlot(bool)));
    installEventFilter(obj);
}


void OscannPlot::setXYScaleFactor(double xValue, double yValue, bool init){
    if(xValue != 0.0 && yValue != 0.0){
        m_xFactor = (xValue)*0.00021;
        double yFactor = (yValue)*0.000375;
        pointer->setXYScaleFactor(m_xFactor, yFactor, init);
        if(init)
            m_xFactorInit = m_xFactor;

    }
}

void OscannPlot::changeColor(){
    QCPRange xRange=m_CustomPlot->xAxis->range(),yRange=m_CustomPlot->yAxis->range();
    QPointF p;
    bool continuePointer=false;
    int saveLast;
    //Vuelta a mostrar el punto de coordenadas si estaba visible
    if(showPointer){
        p=pointer->position->coords();
        continuePointer=true;
    }
    saveLast=lastColor+1;
    switch(saveLast){
    case 0:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(0,204,255),QColor(0,102,127));
        break;
    case 1:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(255,0,0),QColor(255,255,0));
        break;
    case 2:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(51,127,51),QColor(0,204,255));
        break;
    case 3:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(255,255,255),QColor(127,127,127));
        break;
    case 4:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(127,127,127),QColor(0,0,0));
        break;
    default:
        init(false, GT.PICTURE,true,testDir,picDir,QColor(0,204,255),QColor(0,102,127));
        saveLast=0;
        break;
    }
    lastColor=saveLast;
    m_CustomPlot->xAxis->setRange(xRange);
    m_CustomPlot->yAxis->setRange(yRange);
    //Ultimo paso para volver a mostrar el punto de coordenadas si estaba visible
    if(continuePointer){
        pointer->position->setCoords(p);
        indexPoint(pointer->position->coords());
    }
    onCustomReplot();
}
//__________________ACCIONES RATON__________________//
void OscannPlot::routeHoverEvents( QHoverEvent* event ){
    if (m_CustomPlot){
        QHoverEvent* newEvent = new QHoverEvent( event->type(), event->pos(), event->oldPos(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
        emit newText(false);
    }
}
void OscannPlot::mousePressEvent( QMouseEvent* event ){
    if(m_CustomPlot->graphCount()>0 && m_graphType!=GT.SCATTERCLB && !m_preview){
        m_earlyReleased = false;
        //Eliminar antialiasing durante el movimiento
        for(int i=0;i<m_CustomPlot->itemCount();i++)
            m_CustomPlot->item(i)->setAntialiased(false);
        for(int i=0;i<m_CustomPlot->graphCount();i++)
            m_CustomPlot->graph(i)->setAntialiased(false);
        //Guardar coordenadas en las que se origino la pulsacion
        m_mouse.setX(m_CustomPlot->xAxis->pixelToCoord(event->pos().x()));
        m_mouse.setY(m_CustomPlot->yAxis->pixelToCoord(event->pos().y()));
        prev=m_mouse;
        if(event->button()==Qt::LeftButton)
            leftPressed=true;
        if(event->button()==Qt::RightButton)
            rightPressed=true;
        if(cursor().shape() == Qt::OpenHandCursor)  //Poner el cursor en ClosedHand si OpenHand
            setCursor(Qt::ClosedHandCursor);
    }
    routeMouseEvents(event);
}
void OscannPlot::mouseMoveEvent( QMouseEvent* event ){
    if((leftPressed || rightPressed) && m_CustomPlot->graphCount()>0 && !moveTimer.isActive() && m_graphType!=GT.SCATTERCLB && !m_movingDot  && !m_preview){
        if(!m_movingDot)
            m_movingOnPlot = true;
        if(ctrlPressed){
            if(m_CustomPlot->xAxis->pixelToCoord(event->pos().x()) >= m_CustomPlot->xAxis->range().lower &&
               m_CustomPlot->xAxis->pixelToCoord(event->pos().x()) <= m_CustomPlot->xAxis->range().upper &&
               m_CustomPlot->yAxis->pixelToCoord(event->pos().y()) >= m_CustomPlot->yAxis->range().lower &&
               m_CustomPlot->yAxis->pixelToCoord(event->pos().y()) <= m_CustomPlot->yAxis->range().upper){
                QPointF move(QPointF(m_CustomPlot->xAxis->pixelToCoord(event->pos().x())-prev.x(),m_CustomPlot->yAxis->pixelToCoord(event->pos().y())-prev.y()));
                if(m_CustomPlot->xAxis->range().lower-move.x()>minRange.x() && m_CustomPlot->xAxis->range().upper-move.x()<maxRange.x())
                    m_CustomPlot->xAxis->setRange(m_CustomPlot->xAxis->range().lower-move.x(),m_CustomPlot->xAxis->range().upper-move.x());
                if(m_CustomPlot->yAxis->range().lower-move.y()>minRange.y() && m_CustomPlot->yAxis->range().upper-move.y()<maxRange.y())
                    m_CustomPlot->yAxis->setRange(m_CustomPlot->yAxis->range().lower-move.y(),m_CustomPlot->yAxis->range().upper-move.y());
                prev=QPointF(m_CustomPlot->xAxis->pixelToCoord(event->pos().x()),m_CustomPlot->yAxis->pixelToCoord(event->pos().y()));
                if(cursor().shape() == Qt::ArrowCursor)
                    setCursor(Qt::ClosedHandCursor);
            }
            else{
                if(cursor().shape() == Qt::ClosedHandCursor)
                    setCursor(Qt::ArrowCursor);
            }
            if(zoomInd->visible())
                zoomInd->setVisible(false);
        }
        else if(zoomMode==1 && leftPressed){                                                //Habilitado modo zoom
            qDebug()<<" leftPressed: "<<leftPressed
                   <<" rightPressed: "<<rightPressed
                   <<" m_CustomPlot->graphCount(): "<<m_CustomPlot->graphCount()
                   <<" !moveTimer.isActive(): "<<!moveTimer.isActive()
                   <<" !m_preview: "<<!m_preview
                   <<" m_movingDot: "<<m_movingDot
                   <<" minRange: "<<minRange
                   <<" maxRange: "<<maxRange  ;
            zoomInd->topLeft->setCoords(m_mouse.x(),m_mouse.y());
            QPointF zoomDest;                                                               //Esta variable se utiliza para cambiar el valor objetivo en caso de que el indice se salga de los margenes de la pantalla
            if(m_CustomPlot->xAxis->pixelToCoord(event->pos().x())<minRange.x())
                zoomDest.setX(minRange.x());
            else if(m_CustomPlot->xAxis->pixelToCoord(event->pos().x())>maxRange.x())
                zoomDest.setX(maxRange.x());
            else
                zoomDest.setX(m_CustomPlot->xAxis->pixelToCoord(event->pos().x()));
            if(m_CustomPlot->yAxis->pixelToCoord(event->pos().y())<minRange.y())
                zoomDest.setY(minRange.y());
            else if(m_CustomPlot->yAxis->pixelToCoord(event->pos().y())>maxRange.y())
                zoomDest.setY(maxRange.y());
            else
                zoomDest.setY(m_CustomPlot->yAxis->pixelToCoord(event->pos().y()));

            zoomInd->bottomRight->setCoords(zoomDest);
            if(zoomInd->visible()==false)
                zoomInd->setVisible(true);
            m_videoPreviewer->setPointerFromTo(qRound(zoomInd->topLeft->coords().x()/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(m_graphIndex)->data().data()->size()),
                                               qRound(zoomInd->bottomRight->coords().x()/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(m_graphIndex)->data().data()->size()));
        }
        onCustomReplot();
        moveTimer.start(20);
    }
}
void OscannPlot::mouseReleaseEvent( QMouseEvent* event ){
    if(m_CustomPlot->graphCount()>0 && m_graphType!=GT.SCATTERCLB && !m_preview){
        double xScaleFactor = 0.0, yScaleFactor = 0.0;
        bool setFlag = false;
        //Modo zoom habilitado
        if(zoomMode==1){
            //Hacer zoom hacia el cuadrante seleccionado
            if(leftPressed && !m_zooming){
                QPointF nextZoom(qFabs(zoomInd->topLeft->coords().x()-zoomInd->bottomRight->coords().x()),qFabs(zoomInd->topLeft->coords().y()-zoomInd->bottomRight->coords().y()));
                if(nextZoom.x()>0.02*m_CustomPlot->xAxis->range().size() && nextZoom.y()>0.02*m_CustomPlot->yAxis->range().size() &&
                   nextZoom.x()>0.0001*(maxRange.x()-minRange.x()) && nextZoom.y()>0.0001*(maxRange.y()-minRange.y())){
                    m_zooming = true;
                    m_CustomPlot->xAxis->setRange(zoomInd->topLeft->coords().x(),zoomInd->bottomRight->coords().x());
                    m_CustomPlot->yAxis->setRange(zoomInd->bottomRight->coords().y(),zoomInd->topLeft->coords().y());
                    if(zoomInd->bottomRight->coords().x() - zoomInd->topLeft->coords().x() > 0)
                        xScaleFactor = zoomInd->bottomRight->coords().x() - zoomInd->topLeft->coords().x();
                    else
                        xScaleFactor = zoomInd->topLeft->coords().x() - zoomInd->bottomRight->coords().x();
                    if(zoomInd->topLeft->coords().y() - zoomInd->bottomRight->coords().y() > 0)
                        yScaleFactor = zoomInd->topLeft->coords().y() - zoomInd->bottomRight->coords().y();
                    else
                        yScaleFactor = zoomInd->bottomRight->coords().y() - zoomInd->topLeft->coords().y();
                    setFlag = true;
                    m_zooming = false;
                }
                if(zoomInd->visible() == true){
                    zoomInd->setVisible(false);
                    zoomInd->topLeft->setCoords(0,0);
                    zoomInd->bottomRight->setCoords(0,0);
                    m_videoPreviewer->setPointerFromTo(qRound(m_CustomPlot->xAxis->range().lower/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(0)->data().data()->size()),
                                                       qRound(m_CustomPlot->xAxis->range().upper/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(0)->data().data()->size()));
                }
            }
            else if(rightPressed){
                emit showMenu(0, false, false, false);                          //Quitar zoom con el boton derecho
            }
            if(setFlag)
                setXYScaleFactor(xScaleFactor, yScaleFactor, false);
        }
        if(leftPressed && !m_movingOnPlot){                                     //Actualizar indicador de coordenadas
            m_tracerSelected = pointer;
            calcCoord();
            m_tracerSelected->setVisible(true);
            installEvents(m_tracerSelected);
            showPointer=true;
            indexPoint(m_tracerSelected->position->coords());
            if(m_graphType != GT.SCATTER && m_graphType != GT.PICTURE)
                calcPic();

        }
        //Resetear indicadores de pulsacion de raton
        if(event->button()==Qt::LeftButton)
            leftPressed=false;
        if(event->button()==Qt::RightButton)
            rightPressed=false;
        //Poner cursor en modo openHand si closeHand
        if(cursor().shape()==Qt::ClosedHandCursor)
            setCursor(Qt::OpenHandCursor);

        //Habilitar antialiasing
        for(int i=0;i<m_CustomPlot->itemCount();i++)
            m_CustomPlot->item(i)->setAntialiased(true);
        for(int i=0;i<m_CustomPlot->graphCount();i++)
            m_CustomPlot->graph(i)->setAntialiased(true);


        onCustomReplot();
        m_movingOnPlot = false;
    }
}

void OscannPlot::trackerPosCorrection(int *pos, int mouseX){
    int diff;
    int graph=1;
    if(m_graphType == GT.PUPILAREA)
        graph=0;
    diff = qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x()) - mouseX;
    if(diff != 0){
        if(qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x()) > mouseX){
            diff = qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x()) - mouseX;
            while(diff >= 0){
                (*pos)--;
                diff = qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x()) - mouseX;
            }
        }
        else{
            diff = mouseX - qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x());
            while(diff >= 0){
                (*pos)++;
                diff = mouseX -  qRound(m_CustomPlot->graph(graph)->coordsToPixels(m_CustomPlot->graph(graph)->data().data()->at(*pos)->key,m_CustomPlot->graph(graph)->data().data()->at(*pos)->value).x());
            }
        }
    }

}

void OscannPlot::moveMeSlot(int id, int pos, int mouseX){
    if(id >= -1 && m_tracerSelected != nullptr){
        int graph=1;
        if(m_graphType == GT.PUPILAREA)
            graph=0;
        trackerPosCorrection(&pos, mouseX);
        m_videoPreviewer->newPointerPosition(m_tracerPosition = pos);
        m_tracerSelected->position->setCoords(m_CustomPlot->graph(graph)->data().data()->at(pos)->key,m_CustomPlot->graph(graph)->data().data()->at(pos)->value);
        indexPoint(m_tracerSelected->position->coords());
        calcPic();
        onCustomReplot();
    }
}

void OscannPlot::dotCatchedSlot(int pos, int id, int mouseX){
    m_movingDot = true;
    m_movingDotId = id;
    m_earlyReleased = false;
    m_videoPreviewer->newPointerPosition(m_tracerPosition = pos);
    if(id == -1){
        trackerPosCorrection(&pos, mouseX);
        pointer->position->setCoords(m_CustomPlot->graph(m_graphIndex)->data().data()->at(pos)->key,m_CustomPlot->graph(m_graphIndex)->data().data()->at(pos)->value);
        indexPoint(pointer->position->coords());
        m_tracerSelected = pointer;
    }else{
        switch(id%3){
            case 1: //Latency
            trackerPosCorrection(&pos, mouseX);
            break;
        case 2://
            trackerPosCorrection(&pos, mouseX);
        break;
        case 0:
            trackerPosCorrection(&pos, mouseX);
            break;
        }
    }
    calcPic();
    onCustomReplot();
}

void OscannPlot::dotReleasedSlot(QPoint pos, int id){
    if(m_movingDotId != -2){
        if(leftPressed && !m_movingOnPlot && id == -1){
            m_mouse.setX(m_CustomPlot->xAxis->pixelToCoord(pos.x()));
            m_mouse.setY(m_CustomPlot->yAxis->pixelToCoord(pos.y()));
            m_tracerSelected = pointer;
            calcCoord();
            indexPoint(m_tracerSelected->position->coords());
            if(m_graphType != GT.SCATTER && m_graphType != GT.PICTURE)
                calcPic();
            m_movingDot = false;
            m_tracerSelected = nullptr;
            m_earlyReleased = true;
        }
    }else{
        m_movingDotId = -99;
    }
    if(m_movingDot && m_movingDotId == id){
        m_movingDot = false;
        m_movingDotId = -2;
        m_tracerSelected = nullptr;
        m_earlyReleased = true;
    }
}

void OscannPlot::overSomeTracerSlot(bool overSomeTracer){
    if(overSomeTracer){
        QApplication::restoreOverrideCursor();
        QApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    }
    else{
        QApplication::restoreOverrideCursor();
    }
}



void OscannPlot::mouseDoubleClickEvent(QMouseEvent *event){Q_UNUSED(event);}
void OscannPlot::mouseWheelEvent(QWheelEvent *event){Q_UNUSED(event);}
void OscannPlot::routeMouseEvents( QMouseEvent* event ){
    if (m_CustomPlot){
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }
}

void OscannPlot::setCreatingPdf(const bool value){
    m_creatingPdf = value;
}

void OscannPlot::setVideoPreviewer(videoPreview *vp){
    connect( vp, SIGNAL(newPos(int)), this, SLOT(updatePointerPosition(int)) );
    m_videoPreviewer = vp;
}
//TODOPLAY
void OscannPlot::updatePointerPosition(int pos){
    if (m_CustomPlot->graphCount()>0){
        m_tracerPosition = pos;
        showPointer = true;
        pointer->setVisible(true);
        //pointer->position->setCoords(m_CustomPlot->graph(0)->data().data()->at(m_tracerPosition)->key,m_CustomPlot->graph(0)->data().data()->at(m_tracerPosition)->value);
        if(m_graphType == GT.SCATTER)
            pointer->position->setCoords(x[m_tracerPosition],y[m_tracerPosition]);
        else if(m_graphType == GT.PLOTX)
            pointer->position->setCoords(time[m_tracerPosition],x[m_tracerPosition]);
        else if(m_graphType == GT.PLOTY)
            pointer->position->setCoords(time[m_tracerPosition],y[m_tracerPosition]);
        //qDebug()<<Q_FUNC_INFO<<" pointer->position->coords(): "<<pointer->position->coords();
        indexPoint(pointer->position->coords());
        onCustomReplot();
    }

}
/*TODODEBUG:
void OscannPlot::quit(){
    qDebug()<<Q_FUNC_INFO<<m_frames;
    QApplication::quit();
}*/

//__________________ACCIONES TECLADO__________________//

void OscannPlot::keyPress(int key){
    if(!keyTimer.isActive() && m_CustomPlot->graphCount()>0){
        if((m_graphType == GT.PLOTX || m_graphType == GT.PLOTY || m_graphType == GT.PUPILAREA || m_graphType == GT.SCATTER) && pointer->visible()){
            if(Qt::Key(key)==Qt::Key_Left || (Qt::Key(key)==Qt::Key_Right && !f_playing)){
                if(Qt::Key(key)==Qt::Key_Left && m_tracerPosition-1>=0)
                    m_tracerPosition--;
                else if(Qt::Key(key)==Qt::Key_Right && m_tracerPosition+1<m_CustomPlot->graph(m_graphIndex)->data().data()->size())
                    m_tracerPosition++;
                //Segmentation Fault: H12O -> 4987130 -> TASVH-06022017-121114 (3384ms)
                                    //H12O -> 4987130 -> TSVH-06092017-123850 (2305ms)
                                    //H12O -> 10035875 -> TSMH-06022017-105809 (2013ms), (437ms), (117ms)
                //Oscann 3.0.6: This lines was commented in version 3.0.4
                m_videoPreviewer->newPointerPosition(m_tracerPosition);
                if(m_tracerSelected != nullptr){
                    m_tracerSelected->position->setCoords(m_CustomPlot->graph(m_graphIndex)->data().data()->at(m_tracerPosition)->key,m_CustomPlot->graph(m_graphIndex)->data().data()->at(m_tracerPosition)->value);
                    indexPoint(m_tracerSelected->position->coords());
                    calcPic();
                    onCustomReplot();
                }
            }
        }
        //Erik: 20 millisecons is too much
        //keyTimer.start(20);
        keyTimer.start(10);
    }
    if(Qt::Key(key)==Qt::Key_Control){
        ctrlPressed=true;
        setZoomMode(0);
    }
}

void OscannPlot::keyRelease(int key){
    if(Qt::Key(key)==Qt::Key_Control){
        ctrlPressed=false;
        setZoomMode(1);
    }
}


//__________________PUNTO INDICADOR__________________//

void OscannPlot::indexPoint(QPointF point){
    if(point!=QPointF(0,0)){
        m_picturePosition = point;
        //Text
        pointerLabel->setVisible(true);
        if(m_graphType == GT.SCATTER || m_graphType == GT.PICTURE){
            pointerLabel->setText(QString::number(point.x(),'f',2) + unitIndex + " , " + QString::number(point.y(),'f',2) + unitIndex + QString("(%1)").arg(m_tracerPosition));
        }
        else if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY){
            pointerLabel->setText(QString::number(point.x()) + "ms , " + QString::number(point.y(),'f',2) + unitIndex + QString("(%1)").arg(m_tracerPosition));
        }
        else{
            pointerLabel->setText(QString::number(point.x()) + "ms , " + QString::number(point.y(),'f',2) + "px2" + QString("(%1)").arg(m_tracerPosition));
        }
    }
    else{
        pointerLabel->setVisible(false);
    }
}

void OscannPlot::calcCoord(){
    if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY || m_graphType == GT.PUPILAREA){
        //Colocar la marca en el punto deonde ha caido el pulso de raton (solo para plot continuos en el tiempo)
        m_tracerPosition=qRound(m_mouse.x()/(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key*m_CustomPlot->graph(m_graphIndex)->data().data()->size());
        m_videoPreviewer->newPointerPosition(m_tracerPosition);
        if(m_tracerPosition<0)
            pointer->position->setCoords(0,m_CustomPlot->graph(m_graphIndex)->data().data()->at(0)->value);
        else if(m_tracerPosition>m_CustomPlot->graph(m_graphIndex)->data().data()->size())
            pointer->position->setCoords((m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->key,(m_CustomPlot->graph(m_graphIndex)->data().data()->constEnd()-1)->value);
        else{
            pointer->position->setCoords(m_CustomPlot->graph(m_graphIndex)->data().data()->at(m_tracerPosition)->key,
                                         m_CustomPlot->graph(m_graphIndex)->data().data()->at(m_tracerPosition)->value);
        }
    }
    else
        pointer->position->setCoords(m_mouse);
}

//__________________WIDGET__________________//

void OscannPlot::savePlot(int saveWidth,int saveHeight,int fontSize,QColor backColor){
    QDir pupilTmp(testDir+"/plot");
    if(!pupilTmp.exists())
        pupilTmp.mkpath(".");

    QString filePath;

    if(m_graphType == GT.PLOTX){
        filePath = QString(testDir+"/plot/"+testDir.split("/").last()+"-X.png");
    }
    else if(m_graphType == GT.PLOTY){
        filePath = QString(testDir+"/plot/"+testDir.split("/").last()+"-Y.png");
    }
    else if(m_graphType == GT.SCATTER){
        filePath = QString(testDir+"/plot/"+testDir.split("/").last()+"-S.png");
    }
    else{
        filePath = QString(testDir+"/plot/"+testDir.split("/").last()+".png");
    }

    m_CustomPlot->setBackground(Qt::white);
    m_CustomPlot->axisRect()->setBackground(backColor);
    m_CustomPlot->axisRect()->setMargins(QMargins(90,10,10,90));

    m_CustomPlot->xAxis->setLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->xAxis->setTickLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->xAxis->setLabelColor(Qt::black);
    m_CustomPlot->xAxis->setTickLabelColor(Qt::black);
    m_CustomPlot->yAxis->setLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->yAxis->setTickLabelFont(QFont("Helvetica",fontSize));
    m_CustomPlot->yAxis->setLabelColor(Qt::black);
    m_CustomPlot->yAxis->setTickLabelColor(Qt::black);

    m_CustomPlot->legend->setFont(QFont("Helvetica",fontSize));
    title->setFont(QFont("Helvetica",fontSize));
    title->setBrush(Qt::white);


    if(showPointer){
        pointerLabel->setFont(QFont("Helvetica",fontSize));
        pointerLabel->position->setCoords(0.92,0.02);
    }

    if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY){
        m_CustomPlot->graph(m_graphIndex-1)->setPen(QPen(Qt::red,2.5));
        m_CustomPlot->graph(m_graphIndex)->setPen(QPen(Qt::blue,2.5));
        onCustomReplot();
        m_CustomPlot->savePng(filePath,saveWidth,saveHeight);
        m_CustomPlot->graph(m_graphIndex-1)->setPen(QPen(QColor(QColor(0,204,255)),2.5));
        m_CustomPlot->graph(m_graphIndex)->setPen(QPen(QColor(0,0,120),2.5));
    }
    else if(m_graphType == GT.PICTURE){
        onCustomReplot();

        QImage toSave(saveWidth,saveHeight,QImage::Format_RGB32),toLoad;
        toSave.fill(Qt::white);

        QPainter tmpPainter(&toSave);

        if(saveWidth/static_cast<double>(saveHeight) >= xPix/static_cast<double>(yPix)){
            m_CustomPlot->savePng(filePath,saveHeight*(xPix/(float)yPix),saveHeight);
            toLoad.load(filePath);
            tmpPainter.drawImage(QRect((saveWidth-saveHeight*(xPix/(float)yPix))/2,0,saveHeight*(xPix/(float)yPix),saveHeight),toLoad);
        }
        else{
            m_CustomPlot->savePng(filePath,saveWidth,saveWidth*(yPix/(float)xPix));
            toLoad.load(filePath);
            tmpPainter.drawImage(QRect(0,(saveHeight-saveWidth*(yPix/(float)xPix))/2,saveWidth,saveWidth*(yPix/(float)xPix)),toLoad);
        }

        toSave.save(filePath);
    }
    else if(m_graphType == GT.SCATTER || m_graphType == GT.PUPILAREA){
        onCustomReplot();
        m_CustomPlot->savePng(filePath,saveWidth,saveHeight);
    }

    m_CustomPlot->setBackground(QColor(53,53,53));
    m_CustomPlot->axisRect()->setBackground(QColor(230,230,230));
    m_CustomPlot->axisRect()->setMargins(QMargins(90,10,40,42));

    m_CustomPlot->xAxis->setLabelFont(QFont("Helvetica",10));
    m_CustomPlot->xAxis->setTickLabelFont(QFont("Helvetica",10));
    m_CustomPlot->xAxis->setLabelColor(Qt::white);
    m_CustomPlot->xAxis->setTickLabelColor(Qt::white);
    m_CustomPlot->yAxis->setLabelFont(QFont("Helvetica",10));
    m_CustomPlot->yAxis->setTickLabelFont(QFont("Helvetica",10));
    m_CustomPlot->yAxis->setLabelColor(Qt::white);
    m_CustomPlot->yAxis->setTickLabelColor(Qt::white);

    m_CustomPlot->legend->setFont(QFont("Helvetica",10));
    title->setFont(QFont("Helvetica",14));
    title->setBrush(QColor(230,230,230));


    if(showPointer){
        pointerLabel->setFont(QFont("Helvetica",12));
        pointerLabel->position->setCoords(0.95,0.02);
    }

    onCustomReplot();
}

void OscannPlot::clearPlot(){
    m_graphType = GT.UND;
    m_CustomPlot->clearGraphs();
    m_CustomPlot->clearItems();
    m_CustomPlot->xAxis->setLabel("X Axis");
    m_CustomPlot->yAxis->setLabel("Y Axis");
    m_CustomPlot->xAxis->setRange(0,5);
    m_CustomPlot->yAxis->setRange(0,5);
    m_CustomPlot->legend->setVisible(false);
    m_CustomPlot->xAxis->grid()->setVisible(true);
    m_CustomPlot->yAxis->grid()->setVisible(true);
    showPointer=false;
    zoomMode=-1;
    onCustomReplot();
}

void OscannPlot::clearAll(){
    clearPlot();
    calcPic();
}

void OscannPlot::removeVectors(){
    x.clear();
    y.clear();
    xR.clear();
    yR.clear();
    time.clear();
    xS.clear();
    yS.clear();
    pupilArea.clear();
}

void OscannPlot::onCustomReplot(){
    if(m_graphType == GT.PICTURE){
        //Actualizar la imagen
        QRectF plotRect(QPointF(utilsProcess::deg2px(m_CustomPlot->xAxis->range().lower),
                                utilsProcess::deg2px(m_CustomPlot->yAxis->range().upper)),
                        QPointF(utilsProcess::deg2px(m_CustomPlot->xAxis->range().upper),
                                utilsProcess::deg2px(m_CustomPlot->yAxis->range().lower)));
        QRectF pictureRect(QPointF(-picture.width()/2,picture.height()/2),QPointF(picture.width()/2,-picture.height()/2));
        QRectF intersection=plotRect.intersected(pictureRect);
        QRect cut(QPoint(intersection.left()+picture.width()/2,-(intersection.bottom()-picture.height()/2)),QPoint(intersection.right()+picture.width()/2,-(intersection.top()-picture.height()/2)));

        pic->setPixmap(picture.copy(cut));
        pic->topLeft->setCoords(utilsProcess::px2deg(intersection.left()),utilsProcess::px2deg(intersection.bottom()));
        pic->bottomRight->setCoords(utilsProcess::px2deg(intersection.right()),utilsProcess::px2deg(intersection.top()));
    }
    update();
}

void OscannPlot::paint( QPainter* painter ){
    if (m_CustomPlot){
        QPixmap picture( boundingRect().size().toSize() );
        picture.fill(Qt::transparent);
        QCPPainter qcpPainter( &picture );
        m_CustomPlot->toPainter( &qcpPainter );
        painter->drawPixmap( QPoint(), picture );
    }
}

void OscannPlot::updateCustomPlotSize(){
    if (m_CustomPlot){
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
}

//__________________DATOS__________________//


void OscannPlot::setData(OData *data){
    m_objData = data;
}
void OscannPlot::updateData(){
    x.clear();
    y.clear();
    xR.clear();
    yR.clear();
    time.clear();
    xS.clear();
    yS.clear();
    pupilArea.clear();
    blinks.clear();
    valid.clear();

    csvLoaded=false;

    OProcessed value;
    QVectorIterator< OProcessed > items(m_objData->m_processedData);

    m_objData->m_processedData.data()->x();
    m_objData->m_processedData.data()->xR();

    while(items.hasNext()){
        value = items.next();
        x.push_back(value.x());
        y.push_back(value.y());
        xR.push_back(value.xR());
        yR.push_back(value.yR());
        time.push_back(static_cast<double>(value.time()));
        xS.push_back(value.xS());
        yS.push_back(value.yS());
        pupilArea.push_back(value.area());
        blinks.push_back(value.getParpadeo());
        valid.push_back(value.valid());

    }

    //TODO: Reducir cantidad de puntos necesarios para dibujar el estimulo (necesario cambiar gran parte del codigo)
}

void OscannPlot::pupilAtSlot(double xIn, double yIn, double sxIn, double syIn){
    x.push_back(xIn);
    y.push_back(yIn);
    xS.push_back(sxIn);
    yS.push_back(syIn);
}

void OscannPlot::scatterSlot(unsigned int index){
    calibScatter();
    autoScale(true, index); //No comentar!!!
}

QString OscannPlot::loadFromDB(QString patient, QString test, QString mongoUrl, unsigned int mongoPort){
    time.clear();
    x.clear();
    y.clear();
    xS.clear();
    yS.clear();
    //pupilArea.clear();
    blinks.clear();
    valid.clear();
    //char date_time_format[] = "%d/%m/%Y %H:%M:%S";
    //char date_time_format[] = "%d/%m/%Y";
    //char time_str[] = "yyyy.mm.dd.HH-MM.SS.fff";
    QString date;

    //mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(mongoUrl).arg(mongoPort).toLatin1().data()));
    mongocxx::client client(mongocxx::uri("mongodb://localhost:27017"));

    mongocxx::database m_db = client["tests"];
    try{
        //mongocxx::collection coll = m_db["TSVH"];
        mongocxx::collection coll = m_db[test.toLatin1().data()];
        mongocxx::options::find opts{};
        //opts.projection(bsoncxx::builder::stream::document{} << "_id" << 0 << "date" << 1 <<"time"<<1<<"gaze"<<1<<"stimulus"<<1<<"blinks"<<1<< bsoncxx::builder::stream::finalize);
        if(test[test.length()-1]  == 'H'){//TSVH, TASVH, TSMV, TASVH
            opts.projection(bsoncxx::builder::stream::document{} << "_id" << 0 << "date" << 1 <<"time"<<1<<"gazeX"<<1<<"stimulusX"<<1<<"blinks"<<1<< bsoncxx::builder::stream::finalize);
        }else if(test[test.length()-1]  == 'V'){
            opts.projection(bsoncxx::builder::stream::document{} << "_id" << 0 << "date" << 1 <<"time"<<1<<"gazeY"<<1<<"stimulusY"<<1<<"blinks"<<1<< bsoncxx::builder::stream::finalize);
        }
        bsoncxx::stdx::optional<bsoncxx::document::value> doc = coll.find_one(bsoncxx::builder::stream::document{} << "patient" << patient.toLatin1().data() << bsoncxx::builder::stream::finalize, opts);
        if(doc) {
            bsoncxx::document::element tmp;
            auto v = (*doc).view();
            //uint64_t Epoch_time = v["date"].get_date().value.count();
            //time_t t_unix = Epoch_time/1000;
            //struct tm tm = *localtime(&t_unix);
            //strftime(time_str, strlen(time_str), date_time_format, &tm);

            QDate d = QDate::currentDate();
            date.append(QString::number(d.day()));
            date.append("/");
            date.append(QString::number(d.month()));
            date.append("/");
            date.append(QString::number(d.year()));

            tmp = v["time"];
            for (bsoncxx::array::element l : tmp.get_array().value) {
                time.push_back(l.get_double().value);
            }
            //tmp = v["gaze"];
            if(test[test.length()-1]  == 'H')
                tmp = v["gazeX"];
            else
                tmp = v["gazeY"];
            for (bsoncxx::array::element l : tmp.get_array().value) {
                x.push_back(l.get_double().value);
            }
            //tmp = v["stimulus"];
            if(test[test.length()-1]  == 'H')
                tmp = v["stimulusX"];
            else
                tmp = v["stimulusY"];
            for (bsoncxx::array::element l : tmp.get_array().value) {
                xS.push_back(l.get_double().value);
            }
            tmp = v["blinks"];
            for (bsoncxx::array::element l : tmp.get_array().value) {
                blinks.push_back(l.get_int32().value);
            }
        }
        else{
            return date;
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }
    //pupilArea.push_back(lineString.at(9).toDouble());
    //blinks.push_back(lineString.at(12).toInt());
    return date;
}


bool OscannPlot::loadCsv(QString csvPath){
    qDebug()<<Q_FUNC_INFO<<" ::::: ::::: ::::: ::::: ::::: ::::: ::::: ::::: ::::: csvPath: "<<csvPath;
    QStringList lineString;
    QVector<int> checkLength;

    QFile file(csvPath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    lineString=QString(file.readLine()).split(",");
    for(int i=0;i<lineString.size();i++){
        if(lineString.at(i) == ""){
            qDebug() << "CSV formar not valid!";
            return false;
        }
    }
    if(lineString.at(0) != "Resolution" || lineString.at(3) != "Distance" || lineString.at(5) != "Width" ||
       lineString.at(7) != "Subject" || lineString.at(9) != "Test" || lineString.at(11) != "Calibration"){
        qDebug() << "CSV formar not valid! THIS";
        return false;
    }

    checkLength.push_back(lineString.length());
    resolution.setX(lineString.at(1).toInt());
    resolution.setY(lineString.at(2).toInt());
    screenDistance=(lineString.at(4).toDouble());
    screenWidth=(lineString.at(6).toDouble());
    for(int i=0;i<lineString.size();i++){
        if(lineString.at(i) == ""){
            qDebug() << "CSV formar not valid!";
            return false;
        }
    }

    if(checkLength[0]!=19){
        return false;
    }
    utilsProcess::resolution=resolution;
    utilsProcess::sDist=screenDistance;
    utilsProcess::sWidth=screenWidth;
    x.clear();
    y.clear();
    xR.clear();
    yR.clear();
    time.clear();
    xS.clear();
    yS.clear();
    pupilArea.clear();
    blinks.clear();
    valid.clear();
    int j=0;
    while(!file.atEnd()){
        lineString=QString(file.readLine()).split(",");
        if(j++<10)
        for(int i=0;i<lineString.size();i++){
            if(lineString.at(i) == ""){
                csvLoaded=false;
                qDebug() << "CSV formar not valid!";
                return false;
            }
        }
        x.push_back(lineString.at(1).toDouble());
        y.push_back(lineString.at(2).toDouble());
        xR.push_back(lineString.at(10).toDouble());
        yR.push_back(lineString.at(11).toDouble());
        time.push_back(lineString.at(0).toDouble());
        xS.push_back(lineString.at(3).toDouble());
        yS.push_back(lineString.at(4).toDouble());
        pupilArea.push_back(lineString.at(9).toDouble());
        blinks.push_back(lineString.at(12).toInt());
        valid.push_back(lineString.at(13).toInt());
    }

    testDir.clear();
    QStringList csvPathList(csvPath.split("/"));
    for(int i = 1; i < csvPathList.length()-1; i++)
        testDir = QString(testDir+"/"+csvPathList.at(i));

    testName=QString(testDir.split("/").last()).split("-").first();

    QDirIterator mainFolder(testDir,QDirIterator::Subdirectories);
    QStringList directories;

    QFileInfo checkFile;
    while(mainFolder.hasNext()){
        checkFile.setFile(mainFolder.next());
        if(checkFile.fileName().split("/").back()!="." && checkFile.fileName().split("/").back()!="..")
            directories.push_back(checkFile.absolutePath());
    }
    directories.removeDuplicates();

    QFileInfoList aviCheck,datCheck=QDir(testDir).entryInfoList(QStringList("*.dat"),QDir::Files);

    //Funcion para que Windows elimine el d1.dat
    QString checkD1;
    QStringList checkD1List;
    for(int i=0;i<datCheck.length();i++){
        checkD1List=datCheck.at(i).absoluteFilePath().split(".");
        checkD1=checkD1List.at(checkD1List.length()-2);
        if(checkD1.at(checkD1.length()-2)=='d' && checkD1.at(checkD1.length()-1)=='1')
            datCheck.removeAt(i);
    }
    csvLoaded=true;
    return true;
}

void OscannPlot::calibScatter(){
    if(!m_clbScatterAble)
        return;

    QPointF med(median(x),median(y));
    int i=0;

    while(i<x.size()){
        if(sqrt(qPow(x[i]-med.x(),2)+qPow(y[i]-med.y(),2))>100){
            x.remove(i);
            y.remove(i);
            xS.remove(i);
            yS.remove(i);
        }
        else
            i++;
    }
    px2Deg=false;
    unitIndex="px";
    m_graphType = GT.SCATTERCLB;

    updateCustomPlotSize(); //=186

    m_CustomPlot->clearGraphs();
    m_CustomPlot->clearItems();
    m_CustomPlot->xAxis->grid()->setVisible(true);
    m_CustomPlot->yAxis->grid()->setVisible(true);
    m_CustomPlot->legend->setVisible(true);


    //Titulo
    title=new QCPItemText(m_CustomPlot);
    title->setLayer("legend");
    title->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    title->position->setType(QCPItemPosition::ptAxisRectRatio);
    title->position->setCoords(0.005,0.02);
    title->setFont(QFont("Helvetica",14));
    title->setPen(QPen(Qt::black));
    title->setBrush(Qt::white);
    title->setPadding(QMargins(4,1,4,1));
    title->setVisible(false);

    int aux=0;
    QColor sequenceColor(Qt::red);
    QVector<double> xTmp,yTmp;
    for(int i=1;i<x.size();i++){
        if(xS[i]!=xS[i-1] || yS[i]!=yS[i-1] || i==x.size()-1){
            scatter(xTmp,yTmp,"Calibration XY",sequenceColor,sequenceColor);
            QCPItemText *calibIndex = new QCPItemText(m_CustomPlot);
            QCPItemTracer *calibMean = new QCPItemTracer(m_CustomPlot);

            calibIndex->setText(QString::number(aux));
            calibIndex->setPositionAlignment(Qt::AlignBottom|Qt::AlignLeft);
            calibIndex->position->setType(QCPItemPosition::ptPlotCoords);
            calibIndex->position->setCoords(median(xTmp),median(yTmp));
            calibIndex->setFont(QFont("Helvetica",16));
            calibIndex->setPadding(QMargins(2,2,2,2));
            calibIndex->setBrush(Qt::NoBrush);
            calibIndex->setPen(Qt::NoPen);

            calibMean->position->setCoords(median(xTmp),median(yTmp));
            calibMean->setStyle(QCPItemTracer::tsPlus);
            calibMean->setPen(QPen(Qt::black,4));

            xTmp.clear();
            yTmp.clear();

            if(sequenceColor==Qt::red)
                sequenceColor=Qt::blue;
            else if(sequenceColor==Qt::blue)
                sequenceColor=Qt::yellow;
            else if(sequenceColor==Qt::yellow)
                sequenceColor=Qt::green;
            else
                sequenceColor=Qt::red;

            aux++;
        }
        else{
            xTmp.push_back(x[i-1]);
            yTmp.push_back(-y[i-1]);
        }
    }

    m_CustomPlot->legend->setVisible(false);
    title->setText("Calibration XY");
    title->setVisible(true);



    onCustomReplot();
}

template<class T>
double median(QVector<T> vIn){
    std::sort(vIn.begin(),vIn.end());
    if(vIn.size()%2==0){
        return (vIn[vIn.size()/2]+vIn[vIn.size()/2-1])/2.0;
    }else{
        return vIn[vIn.size()/2];
    }
}

void OscannPlot::changeRaw(bool change){
    showRaw=change;

    bool notCont=false;
    if(showRaw){
        for(int i=0;i<m_CustomPlot->graphCount();i++){
            if(m_CustomPlot->graph(i)->name().contains("Raw"))
                notCont=true;
        }
        if(!notCont){
            QRectF prv(QPointF(m_CustomPlot->xAxis->range().lower,m_CustomPlot->yAxis->range().upper),QPointF(m_CustomPlot->xAxis->range().upper,m_CustomPlot->yAxis->range().lower));
            if(m_graphType == GT.PLOTX)
                plot(time,xR, 0,"X Raw",QColor(255,0,0),1.0);
            else if(m_graphType == GT.PLOTY)
                plot(time,yR, 0,"Y Raw",QColor(255,0,0),1.0);
            else if(m_graphType == GT.SCATTER){
                init(false, GT.SCATTER,px2Deg,testDir);
                scatter(xR,yR,"XY Raw",QColor(255,150,150),QColor(150,0,0),0.5);
            }
            else if(m_graphType == GT.PICTURE){
                init(false, GT.PICTURE,px2Deg,testDir,imgDir,QColor(0,204,255),QColor(0,51,127));
                scatter(xR,yR,"XY Raw",QColor(255,150,150),QColor(150,0,0),0.5);
            }
            m_CustomPlot->xAxis->setRange(prv.left(),prv.right());
            m_CustomPlot->yAxis->setRange(prv.bottom(),prv.top());
        }
    }
    else{
        notCont=true;
        int toRemove=0;
        for(int i=0;i<m_CustomPlot->graphCount();i++){
            if(m_CustomPlot->graph(i)->name().contains("Raw")){
                notCont=false;
                toRemove=i;
                break;
            }
        }
        if(!notCont){
            if(m_graphType == GT.PLOTX || m_graphType == GT.PLOTY)
                m_CustomPlot->removeGraph(toRemove);
            else if(m_graphType == GT.SCATTER)
                init(false, GT.SCATTER,px2Deg,testDir);
            else if(m_graphType == GT.PICTURE)
                init(false, GT.PICTURE,px2Deg,testDir,imgDir,QColor(0,204,255),QColor(0,51,127));
        }
    }
    onCustomReplot();
}

//__________________VIDEO__________________//

void OscannPlot::makeVideo(QString videoDir){
    QPixmap pix;
    if(m_graphType == GT.PICTURE)
        pix=pic->pixmap();
    else{
        if(px2Deg)
            pix=QPixmap(utilsProcess::deg2px(testDim.x()/2)*2,utilsProcess::deg2px(testDim.y()/2)*2);  //La division y multiplicacion separadas son muy importantes, no quitar (David)
        else
            pix=QPixmap(testDim.x(),testDim.y());
    }

    outputVideo = new cv::VideoWriter(videoDir.toLatin1().data(),cv::VideoWriter::fourcc('F','M','P','4'),100,cv::Point(pix.width(),pix.height()));

    cv::Mat frame_ori;
    if(m_graphType == GT.PICTURE){
        QFile myPic(picDir);
        myPic.open(QIODevice::ReadOnly);
        std::vector<uchar> buff(myPic.size());
        myPic.read((char*)buff.data(),myPic.size());
        frame_ori=cv::imdecode(buff,cv::IMREAD_COLOR);
        qDebug() << "Mat type:" << frame_ori.type();
    }
    else
        frame_ori=cv::Mat(cv::Size(pix.width(),pix.height()),16,cv::Scalar(40,40,40));

    qDebug() << "Begining gaze video processing...";
    emit beginProcess();

    int k=0;
    for(int i=0;i<x.size();i++){
        cv::Mat frame=frame_ori.clone();
        if(px2Deg){
            cv::circle(frame,cv::Point(utilsProcess::deg2px(xS[i])+pix.width()/2,-utilsProcess::deg2px(yS[i])+pix.height()/2),18,cv::Scalar(0,160,0),-9);
            cv::rectangle(frame,cv::Rect(utilsProcess::deg2px(xS[i])+pix.width()/2-4,-utilsProcess::deg2px(yS[i])+pix.height()/2-2,8,4),cv::Scalar(255,255,255),cv::FILLED);
            cv::rectangle(frame,cv::Rect(utilsProcess::deg2px(xS[i])+pix.width()/2-2,-utilsProcess::deg2px(yS[i])+pix.height()/2-4,4,8),cv::Scalar(255,255,255),cv::FILLED);
        }
        else{
            cv::circle(frame,cv::Point(xS[i]+pix.width()/2,-yS[i]+pix.height()/2),18,cv::Scalar(0,160,0),-9);
            cv::rectangle(frame,cv::Rect(xS[i]+pix.width()/2-4,-yS[i]+pix.height()/2-2,8,4),cv::Scalar(255,255,255),cv::FILLED);
            cv::rectangle(frame,cv::Rect(xS[i]+pix.width()/2-2,-yS[i]+pix.height()/2-4,4,8),cv::Scalar(255,255,255),cv::FILLED);
        }
        for(int j=k;j>=1;j--)
            cv::circle(frame,cv::Point(utilsProcess::deg2px(x[i-j])+pix.width()/2,-utilsProcess::deg2px(y[i-j])+pix.height()/2),8,cv::Scalar(150*j/k,150*j/k,255),-4);
        if(k<20)
            k++;
        cv::circle(frame,cv::Point(utilsProcess::deg2px(x[i])+pix.width()/2,-utilsProcess::deg2px(y[i])+pix.height()/2),14,cv::Scalar(0,0,255),-7);
        QString showTime(QString::number(time[i]).toLatin1().data()+QString("ms"));
        cv::putText(frame,showTime.toLatin1().data(),cv::Point(50,50),cv::FONT_HERSHEY_PLAIN,2,cv::Scalar(0,255,255),2);
        outputVideo->operator <<(frame);

        emit processed((i+1)/double(x.size()));
        QCoreApplication::processEvents();
    }

    qDebug() << "Gaze video processed!";
}

void OscannPlot::calcPic(){
    //if(m_videoAvailable && m_graphType != GT.PICTURE && m_graphType != GT.SCATTER && m_graphType != GT.SCATTERCLB && m_CustomPlot->graphCount()>0){
    if(m_videoAvailable && m_graphType != GT.PICTURE && m_graphType != GT.SCATTERCLB && m_CustomPlot->graphCount()>0){
        m_videoPreviewer->newPointerPosition(m_plotKeys.indexOf(m_picturePosition.x()));

    }
}

void OscannPlot::capturePupil(){
    if(m_CustomPlot->graphCount()>0){
        int pos=m_plotKeys.indexOf(pointer->position->coords().x());
        QDir pupilTmp(testDir+"/capture");
        if(!pupilTmp.exists())
            pupilTmp.mkpath(".");
        cv::imwrite(QString(testDir+"/capture/"+testDir.split("/").last()+QString("-%1.png").arg(pos, 6, 10, QChar('0'))).toLatin1().data(),m_pupilFrame);
    }
}

//__________________DATA EXPORT/IMPORT__________________//

//#################################FUNCTION fastCalib######################################
//AUTOR: ERIK HERNANDEZ SERRATO
//IN: QSTRING: RUTA DE LA CARPETA DE UNA PRUEBA
//OUT: QSTRING: RUTA DE LA CARPETA DE LA CALIBRACIÓN MAS CERCANA A LA PRUEBA
//DESCRIPCIÓN: Se busca dentro de la carpeta de la prueba que se ha pasado como argumento,
//la calibración más cercana por tiempos que le corresponde, se da prioridad a las calibraciónes
//que se han hecho antes de la prueba, pero en el caso que no haya se le asigna la más cercana que
//se haya hecho despues de la prueba.

QString OscannPlot::fastCalib(QString tstPath){
    QString prevPath="";
    QStringList auxList=tstPath.split("/");
    for(int i=1;i<auxList.size()-1;i++)
        prevPath+="/"+auxList[i];

    //lISTA QUE CONTIENE TODOS LOS TEST DE LA CARPETA
    auxList=QDir(prevPath).entryList();

    QVector<int> timeDist;
    QString clbTime("");
    //Tiempo en el que se realiza la prueba que se esta pasando como argumento.
    QString tstTime=tstPath.split("/").last().split("-").last();
    std::string firstChar;

    int i=0;
    while(i<auxList.size()){
        firstChar=QString(auxList[i]).toStdString().at(0);
        if(firstChar=="C" && QFile(prevPath+"/"+auxList[i]+"/camera.ini").exists()){
            //Hora de la calibración: clbTime.
            clbTime=QString(auxList[i]).split("-").last();
            //timeDist. Distancia en tiempo(int) desde la prueba que se pasa como argumento hasta la calibración que se esta evaluando.
            timeDist.push_back(tstTime.toInt()-clbTime.toInt());
            i++;
        }
        else
            auxList.removeAt(i);
    }

    int minPos=-1,minNeg=-1;

    if(timeDist.size()==0)//No hay calibraciones o si hay pero no tienen camera.ini
        return nullptr;
    else{
        for(int i=0;i<timeDist.size();i++){
            //Se busca la menor distancia entre calibración y la prueba
            if(timeDist[i]>=0){
                if(minPos==-1)
                    minPos=i;
                else if(timeDist[i]<timeDist[minPos])
                    minPos=i;
            }
            //Se busca la menor distancia entre calibración y la prueba
            else{
                if(minNeg==-1)
                    minNeg=i;
                else if(timeDist[i]>timeDist[minNeg])
                    minNeg=i;
            }
        }
    }

    if(minPos!=-1){
        return QString(prevPath+"/"+auxList.at(minPos));
    }
    else if(minNeg!=-1){
        return QString(prevPath+"/"+auxList.at(minNeg));
    }
    else
        return nullptr;
}

/*
Ordena las pruebas que se encuentren en la ruta folderPath. Se ordenanan las pruebas por sessión, fecha y hora.
Devuelve una lista con las direcciones de las pruebas
Las pruebas se han de procesar en el orden que tiene dentro de esta lista

*/

void OscannPlot::sortDirectories(){
    qDebug()<<"START FUNCTION..............................."<<Q_FUNC_INFO;
    QFileInfo checkFile;
    QStringList directories;
    QList<QPair<QString, int> > pairs;
    QStringList timeSorted;
    QStringList dateSorted;
    int i=0;
    m_sessionSorted.clear();

    while(m_mainFolder->hasNext()){
        checkFile.setFile(m_mainFolder->next());
        directories.push_back( checkFile.absolutePath().split("/")[checkFile.absolutePath().split("/").length()-2] + "|" + checkFile.absolutePath());
    }
    if(directories.length() > 1){
        for(i=0;i<directories.length();i++){
            pairs.append(qMakePair(directories[i].split(m_folderPath)[1].split("-").back(), i));
        }
        qSort(pairs.begin(), pairs.end());
        for(i=0;i<pairs.length();i++){
            timeSorted.push_back(directories.at(pairs.at(i).second));
        }
        pairs.clear();
        for(i=0;i<timeSorted.length();i++){
            pairs.append(qMakePair(timeSorted[i].split(m_folderPath)[1].split("-")[1], i));
        }
        qSort(pairs.begin(), pairs.end());
        for(i=0;i<pairs.length();i++){
            dateSorted.push_back(timeSorted.at(pairs.at(i).second));
        }
        pairs.clear();
        for(i=0;i<dateSorted.length();i++){
            pairs.append(qMakePair(dateSorted[i].split("|")[0], i));
        }
        qSort(pairs.begin(), pairs.end());
        for(i=0;i<pairs.length();i++){
            m_sessionSorted.push_back(dateSorted.at(pairs.at(i).second));
        }
    }
    else{
        m_sessionSorted = directories;
    }
}

QStringList OscannPlot::searchTests(QString folderPath){
    qDebug()<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++SEARCHTESTS";
    m_folderPath = folderPath;
    m_mainFolder = new QDirIterator(m_folderPath, QStringList() << "*.ini", QDir::Files, QDirIterator::Subdirectories);
    sortDirectories();
    return m_sessionSorted;
}


QStringList OscannPlot::processFolder(QString folderPath){
    qDebug()<<"**********************START THE FUNCION:"<<Q_FUNC_INFO;
    m_folderPath = folderPath;
    cv::VideoCapture vc;
    int dirCount=0;
    QFileInfoList aviCheck,datCheck;
    bool isAviUseful;
    QString lcl_clb;
    int frameCount;
    m_mainFolder = new QDirIterator(m_folderPath, QStringList() << "camera.ini", QDir::Files, QDirIterator::Subdirectories);
    sortDirectories();
    //Recorre todas las pruebas dispuestas en la carpeta.
    while(dirCount<m_sessionSorted.size()){
        isAviUseful = true;
        aviCheck    =   QDir(QString(m_sessionSorted[dirCount].split("|")[1]  +"/raw")).entryInfoList(QStringList("*.avi"),QDir::Files);
        datCheck    =   QDir(m_sessionSorted[dirCount].split("|")[1]).entryInfoList(QStringList("*d1.dat"),QDir::Files|QDir::Hidden);
        frameCount = 0;
        if(aviCheck.count()>=1 && datCheck.count()>=1){
            lcl_clb = fastCalib(m_sessionSorted[dirCount].split("|")[1]).isNull() ? "@0" : "@1";
            for(int i=0;i<aviCheck.count();i++){
//Oscann 4.0.10 isAviUseful &= vc.open(aviCheck.at(i).absoluteFilePath().toLatin1().data());
                //¿Existe un archivo .avi dentro de la carpeta de la prueba con más de 16 frames?
                isAviUseful &= vc.open(aviCheck.at(i).absoluteFilePath().toLatin1().data()) && vc.get(cv::CAP_PROP_FRAME_COUNT) > 16;
                frameCount += vc.get(cv::CAP_PROP_FRAME_COUNT);
            }
            if(isAviUseful){
                if(QDir(m_sessionSorted[dirCount].split("|")[1]).entryInfoList(QStringList("*.dat"),QDir::Files).size()>0){
                    m_sessionSorted[dirCount] = m_sessionSorted[dirCount].split("|")[0] + "|0@" + m_sessionSorted[dirCount].split("|")[1]  + "@" +  QString::number(frameCount) + lcl_clb;
                }else{
                    m_sessionSorted[dirCount] = m_sessionSorted[dirCount].split("|")[0] + "|1@" + m_sessionSorted[dirCount].split("|")[1]  + "@" + QString::number(frameCount) + lcl_clb;
                }
            }
            else{
                m_sessionSorted[dirCount] = m_sessionSorted[dirCount].split("|")[0] + "|-1@" + m_sessionSorted[dirCount].split("|")[1]  + "@" + QString::number(frameCount) + lcl_clb;
            }
            dirCount++;
        }
        else{
            m_sessionSorted.removeAt(dirCount);
        }
        aviCheck.clear();
    }
    qDebug()<<Q_FUNC_INFO<<" /********//********//********//********//********//********//********//********//********/ m_sessionSorted: "<<m_sessionSorted;
    return m_sessionSorted;
}

QStringList OscannPlot::processCsv(QString folderPath){
    QDirIterator mainFolder(folderPath,QDirIterator::Subdirectories);
    QStringList directories;

    QFileInfo checkFile;
    while(mainFolder.hasNext()){
        checkFile.setFile(mainFolder.next());
        if(checkFile.isDir() && checkFile.fileName().split("/").back()!="." && checkFile.fileName().split("/").back()!="..")
            directories.push_back(checkFile.absolutePath());
    }

    directories.removeDuplicates();

    int dirCount=0,noCalib=0; //0 - Procesa calibraciones, 1 - No procesa calibraciones (dejar en 1 para hospitales)
    std::string firstChar;
    QFileInfoList datCheck;
    while(dirCount<directories.size()){
        datCheck=QDir(directories[dirCount]).entryInfoList(QStringList("*.dat"),QDir::Files);
        if(datCheck.size()<=0)
            directories.removeAt(dirCount);
        else{
            firstChar=directories.at(dirCount).split("/").last().toStdString().at(0);
            if(firstChar=="C" && noCalib)
                    directories.removeAt(dirCount);
            else
                dirCount++;
        }
    }

    return directories;
}
