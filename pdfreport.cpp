#include "pdfreport.h"
#include <QDebug>
#include <QResource>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressDialog>
#include <QVector>

/**
  *   @brief  Constructor por defecto
  *
  *   @param  parent es el objeto padre, necesario ya que se hereda de QObject
  *   @return void
  */
pdfreport::pdfreport(QObject *parent) : QObject(parent){}

void pdfreport::setMongoInfo(const QString url, const unsigned int port){
    m_mongoUrl = url;
    m_mongoPort = port;
}

QStringList pdfreport::dbPatients(QString pathology){
    QStringList list;
    m_pathology.clear();
    m_pathology = pathology;
    m_patient.clear();
    //mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
    mongocxx::database db = client["datos"];
    mongocxx::collection coll;
    mongocxx::options::find opts{};
    opts.projection(bsoncxx::builder::stream::document{} << "_id" << 0 <<"ID"<<1<< bsoncxx::builder::stream::finalize);
    try{
        coll = db[m_pathology.toLatin1().data()];
        mongocxx::cursor cursor = coll.find({},opts);
        for(auto doc : cursor) {
            list.push_back(doc["ID"].get_utf8().value.to_string().c_str());
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }


    return list;
}


QStringList pdfreport::availableTests(QString patient){
    QStringList tests;
    QVector<QPair<unsigned int, QString>> unsorted;
    m_patient.clear();
    m_patient = patient;
    //mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);
    mongocxx::database db = client["tests"];
    mongocxx::collection coll;
    bsoncxx::stdx::optional<bsoncxx::document::value> query;
    try{
        auto cursor1 = db.list_collections();
        for (const bsoncxx::document::view& doc : cursor1){
            coll = db[doc["name"].get_utf8().value.to_string().c_str()];
            query = coll.find_one(bsoncxx::builder::stream::document{} << "patient" << m_patient.toLatin1().data() << bsoncxx::builder::stream::finalize);
            if(query) {
                tests.append(doc["name"].get_utf8().value.to_string().c_str());
            }
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }
    foreach(const QString t, tests){
        qDebug()<<Q_FUNC_INFO<<" -----=====----- -----=====----- -----=====----- -----=====----- t: "<<t;
        if(t.compare("TSVH") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(0,t));
        }else if(t.compare("TSVV") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(1,t));
        }else if(t.compare("TASH") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(2,t));
        }else if(t.compare("TASV") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(3,t));
        }else if(t.compare("TSMH") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(4,t));
        }else if(t.compare("TSMV") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(5,t));
        }else if(t.compare("TFIX") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(6,t));
        }else if(t.compare("TSLSH") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(7,t));
        }else if(t.compare("TSLSV") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(8,t));
        }else if(t.compare("TIF1") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(9,t));
        }else if(t.compare("TIF2") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(10,t));
        }else if(t.compare("TOPTVD") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(11,t));
        }else if(t.compare("TOPTHR") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(12,t));
        }else if(t.compare("TOPTVU") == 0){
            unsorted.push_back(QPair<unsigned int, QString >(13,t));
        }
    }
    qSort(unsorted.begin(), unsorted.end());
    tests.clear();
    for(int i=0;i<unsorted.size();i++){
        tests.push_back(unsorted.at(i).second);
    }
    qDebug()<<Q_FUNC_INFO<<" -----=====----- -----=====----- -----=====----- -----=====----- tests: "<<tests;
    return tests;
}


void pdfreport::allParams(){
    //mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);
    mongocxx::database db = client["datos"];
    QString key;
    m_allParams.clear();
    try{
        mongocxx::collection coll = db[m_pathology.toLatin1().data()];
        bsoncxx::stdx::optional<bsoncxx::document::value> doc = coll.find_one(bsoncxx::builder::stream::document{} << "ID" << m_patient.toLatin1().data() << bsoncxx::builder::stream::finalize);
        if(doc) {
            auto v = (*doc).view();
            foreach(auto mEK, v){
                //TEMP_
                key = mEK.key().to_string().c_str();
                if(key.mid(0,5).compare("TEMP_") == 0)
                    //qDebug()<<" key: "<<mEK.key().to_string().c_str();
                    m_allParams.push_back(mEK.key().to_string().c_str());
            }
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }
}


void pdfreport::paramsToShow(QString test){
    //Debe regresra una lista con: Latencia, Ganancia, etc basado en _lat_, _gain_, etc
    qDebug()<<Q_FUNC_INFO<<" test: "<<test;
    for(int i=0;i<m_testsParams.length();i++){
        if(m_testsParams[i].first.compare(test.toLower()) == 0){
            qDebug()<<Q_FUNC_INFO<<" test: "<<m_testsParams[i].first;
            qDebug()<<Q_FUNC_INFO<<" params: "<<m_testsParams[i].second;
        }
    }

}

//TODO: NOTE: This is show a Popup Dialog to select which parameters to include...
int pdfreport::testParams(QStringList tests){
    tests.removeAll(QString(""));
    m_tests.clear();
    m_tests =tests;
    qDebug()<<Q_FUNC_INFO<<" -----=====----- -----=====----- -----=====----- -----=====----- tests: "<<tests<<" length: "<<tests.length();


    QStringList test, hv;

    QVector<QStringList> vars;
    int i=0;


    //QVector<QPair<QString, QStringList>> tp;

    m_testsParams.clear();


    foreach(const QString &l, m_tests){
        if(     l.mid(0,4).toLower().compare("tsls") == 0 ||
                l.mid(0,4).toLower().compare("tsll") == 0 ||
                l.mid(0,4).toLower().compare("tfix") == 0){
            test.push_back(l.mid(0,4).toLower());
        }else{
            test.push_back(l.mid(0,3).toLower());
        }
        hv.push_back(l[l.length()-1].toLower());                                                                                                       //TEMP_tsv_lat_h
    }
    for(i=0;i<test.length();i++){
        m_testsParams.push_back(QPair<QString, QStringList>(test[i]+hv[i], QStringList()));;
    }

    int from;
    foreach(const QString p, m_allParams){
        for(i=0;i<test.length();i++){
            if(p.contains(test[i]) && p[p.length()-1] == hv[i]){
                from = 5+test[i].length();
                m_testsParams[i].second.append(p.mid(from, p.length()-1-from));
            }
        }
    }
    for(i=0;i<m_testsParams.length();i++){
        qDebug()<<Q_FUNC_INFO<<" test: "<<m_testsParams[i].first;
        qDebug()<<Q_FUNC_INFO<<" params: "<<m_testsParams[i].second;
    }
    qDebug()<<Q_FUNC_INFO<<" m_tests.length(): "<<m_tests.length();
    return m_tests.length();
}

QVector<int> pdfreport::selectConclusion(QVector<int> patologias, QVector<bool> diferenciales, QVector<int> resultadosDemencias, QVector<int> resultadosParkinson){
    QVector<int> seleccion;
    for (int i = 0; i<patologias.length(); i++){
        if(patologias[i] == 2)
            seleccion.append(2);
        if(patologias[i] == 5)
            seleccion.append(5);
        if(patologias[i] == 9)
            seleccion.append(9);
        if(patologias[i] == 3)
            seleccion.append(3);
        if(patologias[i] == 10)
            seleccion.append(10);
        if(patologias[i] == 8)
            seleccion.append(8);
    }
    if(diferenciales[0]){
        if(patologias.contains(2) & patologias.contains(5)){
            if(resultadosDemencias[0] == 2 & resultadosDemencias[1] == 5){
                seleccion.append(25);
                seleccion.remove(seleccion.indexOf(2));
                seleccion.remove(seleccion.indexOf(5));
            }
        }
    }
    if(diferenciales[1]){
        if(patologias.contains(2) & patologias.contains(9)){
            if(resultadosDemencias[0] == 2 & resultadosDemencias[2] == 9){
                seleccion.append(29);
                if(!seleccion.contains(25))
                    seleccion.remove(seleccion.indexOf(2));
                seleccion.remove(seleccion.indexOf(9));
            }
        }
    }
    if(diferenciales[2]){
        if(patologias.contains(5) & patologias.contains(9)){
            if(resultadosDemencias[1] == 5 & resultadosDemencias[2] == 9){
                seleccion.append(59);
                if(!seleccion.contains(25))
                    seleccion.remove(seleccion.indexOf(5));
                if(!seleccion.contains(29))
                    seleccion.remove(seleccion.indexOf(9));
            }
        }
    }
    if(diferenciales[3]){
        if(patologias.contains(3) & patologias.contains(10)){
            if(resultadosParkinson[0] == 3 & resultadosParkinson[1] == 10){
                seleccion.append(310);
                seleccion.remove(seleccion.indexOf(3));
                seleccion.remove(seleccion.indexOf(10));
            }
        }
    }
    return seleccion;
}

QString pdfreport::ImprimeInformeControl(int patologia_estudiada, int resultado) {

    QString mensaje;
    QString texto;

    double accuracy[] = { 0.9753, 0.9654, 0.8368, 0.9866, 0.9192, 0.8753 };
    double IC_max[] = { 0.9985,0.9912,0.9916,0.9923,0.937,0.9265 };
    double IC_min[] = { 0.95, 0.9147, 0.6919, 0.9783, 0.8829, 0.8004 };
    double sensibilidad[] = { 1,1,0.85,1,0.94,1 };
    double especificidad[] = { 0.95,0.9,0.78,0.95,1,0.95 };
    if (resultado != 1) {
        if (patologia_estudiada == 2 && resultado == 2) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Alzheimer's disease.";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].(*)").arg(accuracy[0]).arg(IC_min[0]).arg(IC_max[0]).arg(sensibilidad[0]).arg(especificidad[0]);
            mensaje += texto;
        }
        else if (patologia_estudiada == 3 && resultado == 3) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Parkinson's disease.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].(*)").arg(accuracy[3]).arg(IC_min[3]).arg(IC_max[3]).arg(sensibilidad[3]).arg(especificidad[3]);
            mensaje += texto;
        }
        else if (patologia_estudiada == 5 && resultado == 5) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Frontotemporal dementia.\n";
            texto = QString(" [Accuracy: %1,  CI: [%2, %3],  Sensitivity: %4,  Specificity: %5].(*)").arg(accuracy[1]).arg(IC_min[1]).arg(IC_max[1]).arg(sensibilidad[1]).arg(especificidad[1]);
            mensaje += texto;
        }
        else if (patologia_estudiada == 8 && resultado == 8) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Minimal Hepatic Encephalopathy.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].(*)").arg(accuracy[5]).arg(IC_min[5]).arg(IC_max[5]).arg(sensibilidad[5]).arg(especificidad[5]);
            mensaje += texto;
        }
        else if (patologia_estudiada == 9 && resultado == 9) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Mild Cognitive Impairment.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].(*)").arg(accuracy[2]).arg(IC_min[2]).arg(IC_max[2]).arg(sensibilidad[2]).arg(especificidad[2]);
            mensaje += texto;
        }
        else if (patologia_estudiada == 10 && resultado == 10) {
            mensaje += "Findings in the performed eye movement tests are not those expected for aged-matched controls.";
            mensaje += " In patients with cognitive complaints, the pattern found in eye movement performance is compatible with ";
            mensaje += "Parkinsonisms.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].(*)").arg(accuracy[4]).arg(IC_min[4]).arg(IC_max[4]).arg(sensibilidad[4]).arg(especificidad[4]);
            mensaje += texto;
        }
        else
            mensaje = "Error: OM Battery ID does not match with AI result.(*)\n";
    }
    else
        mensaje += "Findings in the performed eye movement tests don't reveal disorders and are those expected for aged-matched controls.(*)\n";

    return mensaje;
}

QString pdfreport::ImprimeInformeDiferencial(int patologia_estudiada1, int patologia_estudiada2, int resultado) {

    QString mensaje;
    QString texto;

    double accuracy[] = { 0.889, 0.814, 0.86, 0.867 };
    double IC_max[] = { 0.89,0.89,0.93,0.93 };
    double IC_min[] = { 0.83, 0.86, 0.88, 0.80 };
    double sensibilidad[] = { 0.89,0.85,0.82,1 };
    double especificidad[] = { 0.89,0.78,0.88,0.7 };

    mensaje += "In this differential analysis, the pattern found in eye movement performance is compatible with ";
    if ((patologia_estudiada1 == 2 && patologia_estudiada2 == 5) || (patologia_estudiada1 == 5 && patologia_estudiada2 == 2)) {
        if (resultado == 2 || resultado == 5) {
            if (resultado == 2)
                mensaje += "Alzheimer's Disease.\n";
            else if (resultado == 5)
                mensaje += "Frontotempral Dementia.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].\n NOT FOR DIAGNOSTIC USE.(*)").arg(accuracy[0]).arg(IC_min[0]).arg(IC_max[0]).arg(sensibilidad[0]).arg(especificidad[0]);
            mensaje += texto;
        }
        else
            mensaje = "Error: OM Battery ID does not match with AI result.\n";
    }
    else if ((patologia_estudiada1 == 2 && patologia_estudiada2 == 9) || (patologia_estudiada1 == 9 && patologia_estudiada2 == 2)) {
        if (resultado == 2 || resultado == 9) {
            if (resultado == 2)
                mensaje += "Alzheimer's Disease.\n";
            else if (resultado == 9)
                mensaje += "Mild Cognitive Impairment.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].\n NOT FOR DIAGNOSTIC USE.(*)").arg(accuracy[1]).arg(IC_min[1]).arg(IC_max[1]).arg(sensibilidad[1]).arg(especificidad[1]);
            mensaje += texto;
        }
        else
            mensaje = "Error: OM Battery ID does not match with AI result.\n";
    }
    else if ((patologia_estudiada1 == 5 && patologia_estudiada2 == 9) || (patologia_estudiada1 == 9 && patologia_estudiada2 == 5)) {
        if (resultado == 5 || resultado == 9) {
            if (resultado == 5)
                mensaje += "Frontotempral Dementia.\n";
            else if (resultado == 9)
                mensaje += "Mild Cognitive Impairment.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].\n NOT FOR DIAGNOSTIC USE.(*)").arg(accuracy[2]).arg(IC_min[2]).arg(IC_max[2]).arg(sensibilidad[2]).arg(especificidad[2]);
            mensaje += texto;
        }
        else
            mensaje = "Error: OM Battery ID does not match with AI result.\n";
    }
    else if ((patologia_estudiada1 == 3 && patologia_estudiada2 == 10) || (patologia_estudiada1 == 10 && patologia_estudiada2 == 3)) {
        if (resultado == 3 || resultado == 10) {
            if (resultado == 3)
                mensaje += "Parkinson's Disease.\n";
            else if (resultado == 10)
                mensaje += "Parkinsionisms.\n";
            texto = QString(" [Accuracy: %1;  CI: [%2, %3];  Sensitivity: %4; Specificity: %5].\n NOT FOR DIAGNOSTIC USE.(*)").arg(accuracy[3]).arg(IC_min[3]).arg(IC_max[3]).arg(sensibilidad[3]).arg(especificidad[3]);
            mensaje += texto;
        }
        else
            mensaje = "Error: OM Battery ID does not match with AI result.\n";
    }
    return mensaje;
}

/**
  *   @brief  Genera un reporte PDF
  *
  *   @details
  *   Es la función principal, llamando a esta se genera un pdf con la información de todas las pruebas
  *   dentro de inputPath.
  *
  *   Antes de empezar a generarlo se muestra un cuadro de diálogo para configurar algunos parámetros del reporte.
  *
  *   Para crear el pdf se usan funciones de la clase auxiliar "pdfreporthelper".
  *
  *   @param  inputPath ruta a partir de la cual se buscan pruebas para el reporte. También se guarda el pdf aquí
  *   @return void
  */
void pdfreport::newReport(QString filePathJson){

     qDebug()<<Q_FUNC_INFO<<" -----------------------------------------------------NEW REPORT------------------------------------------------------------------------------------------------------: "<<m_date;

    QStringList simpleList;
    QString reference;
    QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>> tableGraphs;
    //QVector<QPair<QString, QStringList>> items;
    //TODO: traer de la DB: _lat_ -> Latencia; _gain_ -> Ganancia

    //tests.removeAll(QString(""));

    qDebug()<<Q_FUNC_INFO<<" tests: "<<m_tests<<" length: "<<m_tests.length();

    //items.push_back(QPair< QString , QStringList >("TSVH" , {"Latencia", "Ganancia", "VelocidadPico", "Hipometria", "Hipermetria", "Parpadeos"}));
    //items.push_back(QPair< QString , QStringList >("TASH" , {"LatenciA", "Hipometria", "Hipermetria", "Parpadeos"}));
    //items.push_back(QPair< QString , QStringList >("TSMH" , {"Latencia", "Hipometria", "Hipermetria", "Parpadeos"}));
    //items.push_back(QPair< QString , QStringList >("TSLSH" , {"Latencia", "Ganancia", "Seguimiento", "swj"}));

    //NOTE: m_testsParams == items

    /////////////////////////////////////////////
    //INICIALIZAR EL PDF Y ABRIRLO PARA ESCRITURA
    /////////////////////////////////////////////
    /// \brief pdfWr
    //TODO: Open a FileDialog to select destination
    QPdfWriter pdfWr(QString(filePathJson + "/%1.pdf").arg(m_patient));
    pdfWr.setCreator("Aura Innovative Robotics S.L.");
    pdfWr.setTitle(m_patient);
    pdfReportHelper pdfObj(pdfWr);
    //HEADER
    int hHead=30;
    int paddingHead=3;
    QImage headLogoIzq("/home/oscann/Pictures/hm.jpg"); //Probar aqui a cargar .png si el .jpg no devuelve resultado
    if(headLogoIzq.isNull()){
        headLogoIzq.load("/home/oscann/Pictures/hm.jpg");
    }
    QImage headLogoAura;
    headLogoAura.load(":/qml/qtcam/videocapturefilter_QML/images/auralogo_16_9.png"); //Logo de aura en 16:9 en el qrc
    //FOOTER
    int hFoot=15;
    int paddingFoot=paddingHead;

    AuraJson *json = new AuraJson();
    json->readJson(QString(filePathJson+"/%1.json").arg(m_patient));

    if (json->getAge() <= 40)
        reference = 'A';
    else if (json->getAge() <= 50)
        reference = 'B';
    else if (json->getAge() <= 60)
        reference = 'C';
    else
        reference = 'D';

    pdfObj.configHeader(hHead,paddingHead,headLogoIzq,headLogoAura);
    pdfObj.configFooter(hFoot,paddingFoot);

    tableGraphs = getGraphsAndTables(m_pathology, m_patient, reference);
    simpleList.clear();
    //Asignar los parámetros de la lista de la pag.1 y del pie de pagina
    simpleList.append("ID|"+m_patient);
    simpleList.append("Date|" + m_date);
    simpleList.append("Age Group|"+reference);

    qDebug() << "Step 1:";
    //QVector<int> patologias_estudiadas = {5,3,10};
    qDebug() << "resultados IA DEMENCIAS: " << json->getResultados_IA_demencias();
    //json->createJson();
    //json->writeJson();
    QVector<int> patologias_estudiadas = json->getPathologies();//{2,5,3,10}; //HAY QUE AGREGAR LA LECTURA DEL JSON!! (se puede hacer desde fuera y considerar el vector un parámetro de la clase)
    qDebug() << "patologias_estudiadas: " << patologias_estudiadas;
    qDebug() << "Step 2:";
    //QVector<bool> diferenciales = {1,1,0,0};
    QVector<bool> diferenciales = json->getIA_analysis();//{1,1,0,0};
    qDebug() << "Step 3:";
    QVector<int> resultadosDemencias = json->getResultados_IA_demencias(); //{2,5,9,2,2,9};
    QVector<int> resultadosParkinson = json->getResultados_IA_parkinson(); //{3,1,3};
    int resultadoEHM = json->getResultados_IA_EHM(); //8;

    QStringList patologias;
    for (int i = 0; i < patologias_estudiadas.length(); i++) {
        if (patologias_estudiadas[i] == 2)
            patologias << "   Alzheimer Disease tasks\n";
        else if (patologias_estudiadas[i] == 3)
            patologias << "   Parkinson Disease tasks\n";
        else if (patologias_estudiadas[i] == 5)
            patologias << "   Frontotemporal Dementia tasks\n";
        else if (patologias_estudiadas[i] == 8)
            patologias << "   Minimal Hepatic Encephalopathy tasks\n";
        else if (patologias_estudiadas[i] == 9)
            patologias << "   Mild Cognitive Impairment tasks\n";
        else if (patologias_estudiadas[i] == 10)
            patologias << "   Parkinsionisms tasks\n";
    }

    if (diferenciales[0])
        patologias << "   Differential AD vs FTD tasks";
    if (diferenciales[1])
        patologias << "   Differential AD vs MCI tasks";
    if (diferenciales[2])
        patologias << "   Differential FTD vs MCI tasks";
    if (diferenciales[3])
        patologias << "   Differential PD vs PKS tasks";
    qDebug() << "Step 4:";
    qDebug() << "patologias: " << patologias;
    simpleList.append("OM Battery ID|"+patologias[0]);
    if(patologias.length()>1){
        for(int i = 1; i<patologias.length(); i++)
            simpleList.append(patologias[i]);
    }

    //int n_demencias = 0;
    //for (int i = 0; i < patologias_estudiadas.length(); i++){
    //    if (patologias_estudiadas[i] == 2 | patologias_estudiadas[i] == 5 | patologias_estudiadas[i] == 9)
    //        n_demencias++;
    //}
    qDebug() << "Step 5:";
    QVector<bool> json_result_types = json->getResults_types();
    bool differential = false;
    if (json_result_types[2])
    {
        QVector<int> seleccion = selectConclusion(patologias_estudiadas,diferenciales,resultadosDemencias,resultadosParkinson);
        for (int i = 0; i < seleccion.length(); i++) {
            if (seleccion[i] == 2)
                simpleList.append("AD conclusion|"+ImprimeInformeControl(2,resultadosDemencias[0]));
            else if (seleccion[i] == 5)
                simpleList.append("DFT conclusion|"+ImprimeInformeControl(5,resultadosDemencias[1]));
            else if (seleccion[i] == 9)
                simpleList.append("DCL conclusion|"+ImprimeInformeControl(9,resultadosDemencias[2]));
            else if (seleccion[i] == 25)
            {
                simpleList.append("Differential analysis: AD vs FTD|"+ImprimeInformeDiferencial(2,5,resultadosDemencias[3]));
                differential = true;
            }
            else if (seleccion[i] == 29)
            {
                simpleList.append("Differential analysis: AD vs MCI|"+ImprimeInformeDiferencial(2,9,resultadosDemencias[4]));
                differential = true;
            }
            else if (seleccion[i] == 59)
            {
                simpleList.append("Differential analysis: FTD vs MCI|"+ImprimeInformeDiferencial(5,9,resultadosDemencias[5]));
                differential = true;
            }
            else if (seleccion[i] == 8)
                simpleList.append("MHE conclusion|"+ImprimeInformeControl(8,resultadoEHM));
            else if (seleccion[i] == 3)
                simpleList.append("PD conclusion|"+ImprimeInformeControl(3,resultadosParkinson[0]));
            else if (seleccion[i] == 10)
                simpleList.append("PKS conclusion|"+ImprimeInformeControl(10,resultadosParkinson[1]));
            else if (seleccion[i] == 310)
            {
                simpleList.append("Differential analysis: EP vs PKS|"+ImprimeInformeDiferencial(3,10,resultadosParkinson[2]));
                differential = true;
            }
        }
    }
    else
    {
        simpleList.append("Conclusion|Aid to diagnosis can not be applied due to missing tests.");
    }
    //TODO: Pablo's Number
    //simpleList.append("Asistencia Diferencial|0,8 EA");
    //simpleList.append("&nbsp;|0,5 EP");
    //simpleList.append("&nbsp;|0,7 UN");
    //Configurar titulo y pie de pagina antes de imprimir las hojas
    pdfObj.setHeaderTitle("ANÁLISIS DE MOVIMIENTO OCULAR");
    pdfObj.setFooterText(m_patient);
    pdfObj.newPDF(pdfWr,tableGraphs,simpleList, false, differential);
}

QString pdfreport::validateDBElement(bsoncxx::document::element l){
    if(l.type() == bsoncxx::type::k_double){
        //qDebug()<<Q_FUNC_INFO<< "dato = "<<QString("%1").arg(l.get_double().value, 0, 'f', 2)<<"tipo double";
        return QString("%1").arg(l.get_double().value, 0, 'f', 2);
    }
    else if(l.type() == bsoncxx::type::k_int32){
        //qDebug()<<Q_FUNC_INFO<< "dato = "<<QString("%1").arg(l.get_int32().value)<<"tipo int32";
        return QString("%1").arg(l.get_int32().value);
    }
    else if(l.type() == bsoncxx::type::k_int64){
        //qDebug()<<Q_FUNC_INFO<< "dato = "<<QString("%1").arg(l.get_int64().value)<<"tipo int64";
        return QString("%1").arg(l.get_int64().value);
    }
    else if(l.type() == bsoncxx::type::k_utf8){
        //qDebug()<<Q_FUNC_INFO<< "dato = "<<QString("%1").arg(l.get_utf8().value.to_string().c_str())<<"tipo utf8";
        return QString("%1").arg(l.get_utf8().value.to_string().c_str());
    }
    return "-";
}

QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>> pdfreport::getGraphsAndTables(QString pathology, QString patient, QString reference){
    QPair<QVector<QPixmap>, QPair<QVector<QStringList>, QVector<QStringList>>> result;
    QStringList qslSta;
    QStringList qslCns;
    QVector<QStringList> qvSta;
    QVector<QStringList> qvCns;
    QVector<QPixmap> graphs;
    QString test, hv, dbVar;

    QVector<QPair<QString,QString>> staValues;
    QVector<QPair<QString,QString>> cnsValues;

    QVector<QString> staLabels;
    QVector<QString> cnsLabels;

    QPair<QString, QStringList> pair;

    //mongocxx::client client(mongocxx::uri(QString("mongodb://oscann:CuevaErikSilviaPablo@%1:%2/?authSource=admin&authMechanism=SCRAM-SHA-1").arg(m_mongoUrl).arg(m_mongoPort).toLatin1().data()));
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);
    mongocxx::database db = client["datos"];

    std::ostringstream ssKey;

    std::string key;
    mongocxx::pipeline p{};
    bsoncxx::builder::basic::document group_doc;
    group_doc.append(bsoncxx::builder::basic::kvp("_id", "null"));

    //NOTE: Order matters
    m_testsParams.clear();

    qDebug()<<Q_FUNC_INFO<<" )()()()()()()()()()()()()()()()()()()()()()()( m_tests: "<<m_tests;

    foreach(const QString &t, m_tests){
        qDebug()<<Q_FUNC_INFO<<" )()()()()()()()()()()()()()()()()()()()()()()( t.toLower(): "<<t.toLower();
              if(t.toLower().compare("tsvh") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tsvh" , {"_lat_", "_gain_", "_vpeak_", "_err_pos_", "_err_neg_", "_blinks_", "_fast_"}));
        }else if(t.toLower().compare("tsvv") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tsvv" , {"_lat_", "_gain_", "_vpeak_", "_err_pos_", "_err_neg_", "_blinks_", "_fast_"}));
        }else if(t.toLower().compare("tsmh") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tsmh" , {"_lat_","_gain_","_vpeak_","_err_pos_","_err_neg_","_blinks_","_fast_","_corr_"}));
        }else if(t.toLower().compare("tsmv") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tsmv" , {"_lat_","_gain_","_vpeak_","_err_pos_","_err_neg_","_blinks_","_fast_","_corr_"}));
        }else if(t.toLower().compare("tash") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tash" , {"_blins_","_corr_","_ref_","_err_","_sor_","_adel_","_lat_","_lat_ref_","_Tref_","_err_pos_","_err_neg_"}));
        }else if(t.toLower().compare("tasv") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tasv" , {"_blins_","_corr_","_ref_","_err_","_sor_","_adel_","_lat_","_lat_ref_","_err_pos_","_err_neg_"}));
        }else if(t.toLower().compare("tslsh") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tslsh" , {"_lat_","_gain_","_pursuitTime_","_errorPursuitOnly_","_blinks_","_catchup_","_backup_","_swj_"}));
        }else if(t.toLower().compare("tslsv") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tslsv" , {"_lat_","_gain_","_pursuitTime_","_errorPursuitOnly_","_blinks_","_catchup_","_backup_","_swj_"}));
        }else if(t.toLower().compare("tfix") == 0){
            m_testsParams.push_back(QPair< QString , QStringList >("tfix" , {"_bcea","_microsacadas","_sacadas","_drift","_swjmono","_swjbi"}));
        }
    }
    qDebug()<<Q_FUNC_INFO<<" )()()()()()()()()()()()()()()()()()()()()()()( m_testsParams: "<<m_testsParams;

    //m_testsParams.push_back(QPair< QString , QStringList >("tsvh" , {"_lat_", "_gain_", "_vpeak_", "_err_pos_", "_err_neg_", "_blinks_", "_fast_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tsvv" , {"_lat_", "_gain_", "_vpeak_", "_err_pos_", "_err_neg_", "_blinks_", "_fast_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tsmh" , {"_lat_","_gain_","_vpeak_","_err_pos_","_err_neg_","_blinks_","_fast_","_corr_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tsmv" , {"_lat_","_gain_","_vpeak_","_err_pos_","_err_neg_","_blinks_","_fast_","_corr_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tash" , {"_blins_","_corr_","_ref_","_err_","_sor_","_adel_","_lat_","_lat_ref_","_Tref_","_err_pos_","_err_neg_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tasv" , {"_blins_","_corr_","_ref_","_err_","_sor_","_adel_","_lat_","_lat_ref_","_err_pos_","_err_neg_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tslsh" , {"_lat_","_gain_","_pursuitTime_","_errorPursuitOnly_","_blinks_","_catchup_","_backup_","_swj_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tslsv" , {"_lat_","_gain_","_pursuitTime_","_errorPursuitOnly_","_blinks_","_catchup_","_backup_","_swj_"}));
    //m_testsParams.push_back(QPair< QString , QStringList >("tfix" , {"_bcea","_microsacadas","_sacadas","_drift","_swjmono","_swjbi"}));




    foreach (pair, m_testsParams) {
        if(pair.first.mid(0,4).compare("tsls") == 0 || pair.first.mid(0,4).compare("tfix") == 0){
            test = pair.first.mid(0,4);
        }else{
            test = pair.first.mid(0,3);
        }
        if(pair.first.mid(0,4).compare("tfix") == 0)
            hv = "";
        else
            hv = pair.first[pair.first.length()-1];                                                                                                       //TEMP_tsv_lat_h
        foreach(const QString &str, pair.second){
            ssKey.str(std::string());
            ssKey<<"avg_" << test.toLatin1().data() << str.toLatin1().data() << hv.toLatin1().data();
            key = ssKey.str();
            qDebug()<<Q_FUNC_INFO<<" key: "<<key.c_str();
            group_doc.append(
                        bsoncxx::builder::basic::kvp(key,
                        bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$avg", QString("$TEMP_%1%3%2").arg(test).arg(hv).arg(str).toLatin1().data()))));

            ssKey.str(std::string());
            ssKey<<"std_" << test.toLatin1().data() << str.toLatin1().data() << hv.toLatin1().data();
            key = ssKey.str();
            qDebug()<<Q_FUNC_INFO<<" key: "<<key.c_str();
            group_doc.append(bsoncxx::builder::basic::kvp(key,
                             bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("$stdDevSamp", QString("$TEMP_%1%3%2").arg(test).arg(hv).arg(str).toLatin1().data()))));
        }
    }
    p.group(group_doc.extract());
    qDebug()<<" ========== ========== ========== ========== ========== ========== ========== ========== pathology: "<<pathology;
    qDebug()<<" ========== ========== ========== ========== ========== ========== ========== ========== patient: "<<patient;

    try{
        mongocxx::collection coll = db[pathology.toLatin1().data()];
        bsoncxx::stdx::optional<bsoncxx::document::value> doc = coll.find_one(bsoncxx::builder::stream::document{} << "ID" << patient.toLatin1().data() << bsoncxx::builder::stream::finalize);
        if(doc) {
            auto v = (*doc).view();
            std::cout <<"DOVUMENTO V =" << bsoncxx::to_json(v) << std::endl;
            //mongocxx::cursor cursorRef = db[pathology.toLatin1().data()].aggregate(p, mongocxx::options::aggregate{});
            mongocxx::cursor cursorRef = db[QString("ControlesGrupo%1").arg(reference).toLatin1().data()].aggregate(p, mongocxx::options::aggregate{});
            mongocxx::cursor::iterator iRef = cursorRef.begin();
            bsoncxx::document::view vRef = *iRef;
            std::cout <<"DOVUMENTO V =" << bsoncxx::to_json(vRef) << std::endl;
            foreach (pair, m_testsParams) {
                qDebug() << "pair = " << pair;
                if(pair.first.mid(0,4).compare("tsls") == 0 || pair.first.mid(0,4).compare("tfix") == 0){
                    test = pair.first.mid(0,4);
                }else{
                    test = pair.first.mid(0,3);
                }
                if(pair.first.mid(0,4).compare("tfix") == 0)
                    hv = "";
                else
                    hv = pair.first[pair.first.length()-1];                                                                                                       //TEMP_tsv_lat_h
                qslSta.clear();
                qslCns.clear();
                qslSta.append("?|Valor|Desviación|Valor|Desviación");
                staValues.clear();
                cnsValues.clear();
                staLabels.clear();
                cnsLabels.clear();
                QString strsd;
                foreach(const QString &str, pair.second){
                    qDebug()<<Q_FUNC_INFO<<" test_variable: "<<str;
                    strsd = str + "sd_";
                    if(str.compare("_lat_") == 0){                                                  //TSV, TSM, TAS, TS
                        if(test.compare("tsls") == 0)
                            strsd = "";
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Latencia");
                    }else if(str.compare("_err_pos_") == 0){                                        //TSV, TAS, TSM
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        //staLabels.push_back("Hipermetria");
                        staLabels.push_back("Hipometria");
                    }else if(str.compare("_err_neg_") == 0){                                        //TSV, TAS, TSM
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        //staLabels.push_back("Hipometria");
                        staLabels.push_back("Hipermetria");
                    }else if(str.compare("_gain_") == 0){                                           //TSV, TSM
                        if(test.compare("tsls") == 0)
                            strsd = "";
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Ganancia");
                    }else if(str.compare("_vpeak_") == 0){                                          //TSV, TSM
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Velocidad Pico");
                    }else if(str.compare("_blinks_") == 0){                                         //TSV, TAS, TSM
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Parpadeos");
                    }else if(str.compare("_fast_") == 0){                                           //TSV, TAS, TSM
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Adelantos");
                    }else if(str.compare("_swj_") == 0){
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Square Wave Jerks");
                    }else if(str.compare("_lat_ref_") == 0){                                        //TAS
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Latencia Reflexiva");
                    }else if(str.compare("_Tref_") == 0){                                           //TAS
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Tiempo Reflexiva");
                    }else if(str.compare("_err_") == 0){                                            //TAS
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Erroneas");
                    }else if(str.compare("_corr_") == 0){                                           //TAS, TSM
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Correctas");
                    }else if(str.compare("_ref_") == 0){                                            //TAS
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Reflexivas");
                    }else if(str.compare("_sor_") == 0){                                            //TAS
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("SORa");
                    }else if(str.compare("_catchup_") == 0){                                        //TSL
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Alcances");
                    }else if(str.compare("_backup_") == 0){                                         //TSL
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Regresos");
                    }else if(str.compare("_pursuitTime_") == 0){                                    //TSL
                        if(test.compare("tsls") == 0)
                            strsd = "";
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Tiempo");
                    }else if(str.compare("_errorPursuitOnly_") == 0){                               //TSL
                        if(test.compare("tsls") == 0)
                            strsd = "";
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("Error");
                    }else if(str.compare("_microsacadas") == 0){                                    //TFIX
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("MicroSacadas");
                    }else if(str.compare("_bcea") == 0){                                            //TFIX
                        if(test.compare("tfix") == 0)
                            strsd = "";
                        staValues.push_back(QPair<QString,QString>(str, strsd));
                        staLabels.push_back("BCEA");
                    }else if(str.compare("_sacadas") == 0){                                         //TFIX
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Sacadas");
                    }else if(str.compare("_drift") == 0){                                           //TFIX
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("Drifts");
                    }else if(str.compare("_swjmono") == 0){                                           //TFIX
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("SWJmono");
                    }else if(str.compare("_swjbi") == 0){                                           //TFIX
                        cnsValues.push_back(QPair<QString,QString>(str, strsd));
                        cnsLabels.push_back("SWJbi");
                    }
                }
                for(int i=0;i<staValues.length();i++){
                    qDebug()<<Q_FUNC_INFO<<" staValues Label: "<<staLabels.at(i);
                    qDebug()<<Q_FUNC_INFO<<" staValues element Avg: "<<QString("TEMP_%1%2%3").arg(test).arg(staValues.at(i).first).arg(hv).toLatin1().data();
                    qDebug()<<Q_FUNC_INFO<<" staValues element Sd: "<<QString("TEMP_%1%2%3").arg(test).arg(staValues.at(i).second).arg(hv).toLatin1().data();
                    qslSta.append(QString("%1|%2|%3|%4|%5")
                                  .arg(staLabels.at(i).toLatin1().data())
                                  .arg(validateDBElement(v[QString("TEMP_%1%2%3").arg(test).arg(staValues.at(i).first).arg(hv).toLatin1().data()]))
                                  .arg(staValues.at(i).second == "" ? "-" : validateDBElement(v[QString("TEMP_%1%2%3").arg(test).arg(staValues.at(i).second).arg(hv).toLatin1().data()]))
                                  .arg(validateDBElement(vRef[QString("avg_%1%2%3").arg(test).arg(staValues.at(i).first).arg(hv).toLatin1().data()]))
                                  .arg(validateDBElement(vRef[QString("std_%1%2%3").arg(test).arg(staValues.at(i).first).arg(hv).toLatin1().data()]))
                            );
                }
                for(int i=0;i<cnsValues.length();i++){
                    qDebug()<<Q_FUNC_INFO<<" cnsValues Label: "<<cnsLabels.at(i);
                    qDebug()<<Q_FUNC_INFO<<" cnsValues element Name: "<<QString("TEMP_%1%2%3").arg(test).arg(cnsValues.at(i).first).arg(hv).toLatin1().data();
                    qslCns.append(QString("%4|%1|%2|%3")
                                  .arg(validateDBElement(v[QString("TEMP_%1%2%3").arg(test).arg(cnsValues.at(i).first).arg(hv).toLatin1().data()]))
                                  .arg(validateDBElement(vRef[QString("avg_%1%2%3").arg(test).arg(cnsValues.at(i).first).arg(hv).toLatin1().data()]))
                                  .arg(validateDBElement(vRef[QString("std_%1%2%3").arg(test).arg(cnsValues.at(i).first).arg(hv).toLatin1().data()]))
                                  .arg(cnsLabels.at(i).toLatin1().data())
                            );
                }

                qvSta.append(qslSta);
                qvCns.append(qslCns);
                graphs.append(getImage(0, pair.first.toUpper()));
            }
            result.second.first = qvSta;
            result.second.second = qvCns;
            result.first = graphs;
        }
        else{
            return result;
        }
    }catch (mongocxx::exception &e) {
        std::cerr << "MONGO ERROR: "<<e.what()<<"\n";
    }
    return result;
}


QPixmap pdfreport::getImage(unsigned int mode, QString testName){
    //Mode={0-Plot;1-Imagen;2-Pupila luz}
    OscannPlot plot;
    //NOTE: plot.init(graphType -> UND = -1,PLOTX = 0,PLOTY = 1,SCATTER = 2,SCATTERCLB = 3,PICTURE = 4,PUPILAREA  = 5,
    m_date = plot.loadFromDB(m_patient, testName, m_mongoUrl, m_mongoPort);
    qDebug()<<Q_FUNC_INFO<<" -----------------------------------------------------------------------------------------------------------------------------------------------------------m_date: "<<m_date;
    qDebug()<<Q_FUNC_INFO<<" mode: "<<mode;
    if(m_date.compare("yyyy.mm.dd.HH-MM.SS.fff") == 0)
        m_date = "No disponible";
    plot.setCreatingPdf(true);
    if(mode==0){
        //4.0.11: plot.init(false, 0,true, testName + "-");
        plot.init(false, 0,true, testName);
    }
    return plot.getImage(1930,800);
}





//Dialogo para cambiar el logo
//Aviso: Probably the worst gui code in the history of gui codes

/**
  *   @brief  Gestiona el funcionamiento del diálogo de configuración del logo
  *
  *   @details
  *   Funciona lanzando una instancia de oscann oculta y con un modo especial con el que
  *   simplemente se carga la prueba y se guardan las capturas en sus carpetas correspondientes
  *
  *   @param  *button puntero con la información del boton que se ha pulsado (la función es el callback de pulsar el boton)
  *   @return void
  */
void pdfreport::configLogoDialog(QAbstractButton *button){
    if(button->text()!= "OK"){ //Si se pulso un boton que no ponía OK (es decir, el de configure, change o delete)

        dialogLogo = new QDialog(); //Hacer un dialogo nuevo en la variable de la clase
        QVBoxLayout * vbox = new QVBoxLayout();
        QLabel * labelA= new QLabel("Logo Actual:");
        QLabel * labelImg = new QLabel; //La imagen se mostrará en esta etiqueda

        QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok); //Poner 2 botones y el de OK
        buttonBox->addButton("Change",QDialogButtonBox::ActionRole);
        buttonBox->addButton("Remove",QDialogButtonBox::ActionRole);

        QObject::connect(buttonBox, SIGNAL(accepted()), dialogLogo, SLOT(accept()));
        connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), SLOT(changeLogo(QAbstractButton*))); //Cualquier pulsación de boton llama a esta funcion

        QPixmap imagen("./logoIzq.jpg"); //Intentar cargar la imagen de bin en formato jpg
        if(imagen.isNull()){
            imagen.load("./logoIzq.png"); //Y si no se puede con jpg probar con png
        }
        QSize szImg=imagen.size();
        if(!imagen.isNull()){
            imagen = imagen.scaled(QSize(400,225)); //Si la imagen existe, reescalar a un 16:9 pequeño y mostrar
            labelImg->setPixmap(imagen);
        }

        vbox->addWidget(labelA);
        vbox->addWidget(labelImg);
        if(!imagen.isNull()){
            if(qAbs(szImg.width()/static_cast<double>(szImg.height())-(16.0/9.0))>0.01){
                //Comprobar si la imagen cargada es 16:9 y si no, mostrar aviso de que va a salir deforme en el report
                QLabel * labelAviso= new QLabel("AVISO: La imagen no tiene formato 16:9 y aparecerá deformada en el reporte");
                vbox->addWidget(labelAviso);
            }
        }
        vbox->addWidget(buttonBox);

        dialogLogo->setLayout(vbox); //Poner el layout y lanzar el dialogo
        dialogLogo->exec();
    }
}

/**
  *   @brief  Gestiona el cambio de la imagen en el diálogo
  *
  *   @details
  *   Se abre un dialogo para que el usuario elija una imágen. Esta se copia en una ruta conocida en la carpeta de ejecución
  *   Por último se cierra el diálogo y se crea uno nuevo con la imagen actualizada
  *
  *   @param  *button puntero con la información del boton que se ha pulsado (la función es el callback de pulsar el boton)
  *   @return void
  */
void pdfreport::changeLogo(QAbstractButton *button){
    //Funcion para cambiar el logo en la carpeta bin
    dialogLogo->close(); //Cerrar el dialogo anterior (Manera cutre de actualizarlo)
    if(button->text()=="Change"){ //Si se pulsó change
        QString fileName = QFileDialog::getOpenFileName(nullptr,
            tr("Open Image"), "/home/", tr("Image Files (*.jpg *.png)"));
        QFile file(fileName);
        if(file.exists()){ //Pedir una imagen por filedialog y ver si existe
            //Borrar la imagen anterior en jpg o png
            QFile imgJPG("./logoIzq.jpg");
            if(imgJPG.exists()){
                imgJPG.remove();
            }
            QFile imgPNG("./logoIzq.png");
            if(imgPNG.exists()){
                imgPNG.remove();
            }
            //Y copiar la nueva a la carpeta (Con el tipo de archivo en minusculas)
            QFileInfo fileInf(file);
            file.copy("./logoIzq."+fileInf.suffix().toLower());
        }
    }else if(button->text()=="Remove"){
        //Si se pulsó remove, eliminar la imagen. Como no se sabe su tipo se intenta eliminar tanto el jpg, como png.
        QFile imgJPG("./logoIzq.jpg");
        if(imgJPG.exists()){
            imgJPG.remove();
        }
        QFile imgPNG("./logoIzq.png");
        if(imgPNG.exists()){
            imgPNG.remove();
        }
    }
    configLogoDialog(button); //Y lanzar de nuevo el dialogo del logo, que mostrará los cambios hechos aquí
}
