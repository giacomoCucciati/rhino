#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spectrum.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtCore>
#include <QFont>
#include <QWheelEvent>
#include <QInputDialog>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QRectF>
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TFile.h>
#include <TBranch.h>
#include <TObjArray.h>
#include <TMath.h>
#include <QCheckBox>
#include <qwt_scale_engine.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qwt_plot_renderer.h>
// #include <spectrum.h>
#include <mylabel.h>
#include <QTextEdit>

#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeAll(){
    this->setWindowTitle("Rhino");

    myLabel* rhinoLabel = new myLabel(ui->centralWidget);
    rhinoLabel->setObjectName(QString::fromUtf8("rhinoLabel"));
    ui->verticalLayout->addWidget(rhinoLabel);
    QImage image(":/Rhino.png");
    rhinoLabel->setPixmap(QPixmap::fromImage(image));

    QwtPlotCanvas *canvas = qobject_cast<QwtPlotCanvas*>(ui->histoPlot->canvas());
    if(canvas) {
      zoomer = new MyZoomer(canvas);
      zoomer->setMousePattern( QwtEventPattern::MouseSelect1,Qt::MidButton);
      zoomer->setMousePattern( QwtEventPattern::MouseSelect3,Qt::MidButton,Qt::ControlModifier );
    }

    m_picker = new QwtPickerClickPointMachine();
    m_picker->setState(QwtPickerMachine::PointSelection);

    d_picker = new MyPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::VLineRubberBand, QwtPicker::AlwaysOff, ui->histoPlot->canvas());
    //d_picker->setTrackerMode(QwtPicker::AlwaysOn);
    d_picker->setStateMachine(m_picker);


    QObject::connect(d_picker, SIGNAL(selected( const QPointF)),this, SLOT(catchPointSelected( const QPointF)));
    QObject::connect(zoomer,SIGNAL(zoomed(QRectF)),this,SLOT(modifyScrollOnZoom(QRectF)));
    QObject::connect(ui->histoScrollBar,SIGNAL(valueChanged(int)),this,SLOT(modifyHistoOnScroll(int)));

    zoomer->setRubberBandPen(QPen(Qt::red, 1));
    zoomer->setTrackerPen(QPen(Qt::red, 1));
    histoScrollBarMaxLength = 100000;
    ui->histoPlot->setCanvasBackground( Qt::black );
    histogramFirst = new QwtPlotHistogram;
    histogramFirst->setStyle(QwtPlotHistogram::Outline);
    histogramFirst->setPen(QPen(Qt::yellow, 1));
    histogramFirst->attach(ui->histoPlot);
    histogramSecond = new QwtPlotHistogram;
    histogramSecond->setStyle(QwtPlotHistogram::Outline);
    histogramSecond->setPen(QPen(Qt::magenta, 1,Qt::DashDotLine));
    histogramSecond->attach(ui->histoPlot);
    gaussianFit = new QwtPlotCurve;
    gaussianFit->setPen( QColor( Qt::red ) );
    gaussianFit->attach(ui->histoPlot);
    backgroundFit = new QwtPlotCurve;
    backgroundFit->setPen( QColor( Qt::cyan ) );
    backgroundFit->attach(ui->histoPlot);
    differenceFit = new QwtPlotCurve;
    differenceFit->setPen( QColor( Qt::green ) );
    differenceFit->attach(ui->histoPlot);
    differenceLine = new QwtPlotCurve;
    differenceLine->setPen( QColor( Qt::green ) );
    differenceLine->attach(ui->histoPlot);
    integralFit = new QwtPlotHistogram;
    integralFit->setStyle(QwtPlotHistogram::Outline);
    integralFit->setPen(QPen(Qt::yellow, 1.5));
    integralFit->setBrush(Qt::cyan);
    integralFit->attach(ui->histoPlot);
    ui->histoScrollBar->setMinimum(0);
    ui->histoScrollBar->setPageStep(histoScrollBarMaxLength);
    ui->histoScrollBar->setMaximum(histoScrollBarMaxLength-ui->histoScrollBar->pageStep());
    myMarkersAndFits = new MarkersAndFits();
    setEnabledConsole(false);
    ui->chiSquareRadio->setChecked(true);
    ui->quadraticBgFitRadio->setChecked(true);
    ui->bestBgFitRadio->setDisabled(true);
    ui->firstSpecButton->setDisabled(true);
    ui->secondSpecButton->setDisabled(true);
    ui->menuFile->actions().at(1)->setDisabled(true);
    pathName="~/";
    showMaximized();
    isLogScaleActive = false;
    baseValueLinLogScale = 0.0;
    useLastSigma = false;
    ui->splitter->setStretchFactor(0,3);
    ui->splitter_2->setStretchFactor(0,10);


}

void MainWindow::setEnabledConsole(bool enable){

    zoomer->setEnabled(enable);
    ui->fitButton->setEnabled(enable);
    ui->binFactorBox->setEnabled(enable);
    ui->leftButton->setEnabled(enable);
    ui->rightButton->setEnabled(enable);
    ui->rebinButton->setEnabled(enable);
    ui->saveFitButton->setEnabled(enable);
    ui->gaussiansToolButton->setEnabled(enable);


}

//------------------------------------------------//
//                  MENU BAR                      //
//------------------------------------------------//


void MainWindow::on_actionQuit_triggered()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Rhino"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)    qApp->quit();
}

void MainWindow::on_actionLoad_File_triggered()
{

    QString histoFileName = QFileDialog::getOpenFileName (this, tr("Load file"), pathName);
    if (histoFileName.compare("")){
        ui->histoPlot->setAxisAutoScale(QwtPlot::xBottom,true);
        ui->histoPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        if ( histoFileName.endsWith(".chn") || histoFileName.endsWith(".Chn") || histoFileName.endsWith(".CHN")){
            firstSpectrum = new Spectrum(histoFileName,"chn",0);

            int t;          //AGGIUNTA MAFFE
            cout<<firstSpectrum->histoFileName.toStdString()<<endl;
            t=histoFileName.lastIndexOf("/");
            firstSpectrum->fileName=histoFileName.right(histoFileName.size()-t-1);
            firstSpectrum->fileName.chop(4);

        } if (histoFileName.endsWith(".root") || histoFileName.endsWith(".Root") || histoFileName.endsWith(".ROOT")) {
            
            TFile *f = new TFile(histoFileName.toUtf8().constData());
            if (f->IsZombie()) {
                cout << "Error opening file" << endl;
                exit(-1);
            } else {
                TTree *myTree = (TTree*)f->Get("outTree");
                TObjArray *myArray = myTree->GetListOfBranches();
                vector<string> listOfBranches;
                vector<string>::iterator listOfBranchesIt;
                for (int j = 0; j < myArray->GetEntries(); j++) {
                    TBranch *myBranch = (TBranch*)myArray->At(j);
                    listOfBranches.push_back(myBranch->GetFullName().Data());
                }

                QStringList items;
                
                for (listOfBranchesIt = listOfBranches.begin(); listOfBranchesIt != listOfBranches.end(); listOfBranchesIt++) {
                    items<<QString::fromStdString(*listOfBranchesIt);
                }

                bool ok1;
                bool ok2;
                string energiesString = "";

                // Choosing energy channel in the TTree
                QString item1 = QInputDialog::getItem(this, tr("From TTree to histo"), tr("Branch to plot:"), items, 0, false, &ok1);                      
                if (ok1 && !item1.isEmpty())
                    energiesString = item1.toStdString();
                
                // Choosing number of channels in the histogram
                bool ok;
                int chNum = QInputDialog::getInt(this, tr("From TTree to histo"), tr("Number of channels:"), 3600, 0, 16000, 1, &ok);
                if (ok)
                    cout<<chNum<<endl;

                // Choosing max enregy of the histogram
                Double_t maxEnergy = QInputDialog::getDouble(this, tr("From TTree to histo"), tr("Max energy (kEv):"), 10000, -2147483647 ,2147483647, 1, &ok);
                if (ok)
                    cout<<maxEnergy<<endl;

                firstSpectrum = new Spectrum(histoFileName,"root",0, chNum, energiesString, maxEnergy);
            }
        } else {

            firstSpectrum = new Spectrum(histoFileName,"tas",readTasFile(histoFileName));

            int t;      //AGGIUNTA MAFFE
            cout<<firstSpectrum->histoFileName.toStdString()<<endl;
            t=histoFileName.lastIndexOf("/");
            firstSpectrum->fileName=histoFileName.right(histoFileName.size()-t-1);

        }
        selectedSpectrum = firstSpectrum;

        int j;
        j=histoFileName.lastIndexOf("/");
        pathName = histoFileName.left(j+1);
        //cout<<pathName.toStdString()<<endl;



        QwtText title(firstSpectrum->histoFileName);
        title.setFont(QFont("Times",12,QFont::Bold));
        ui->histoPlot->setTitle(title);
        if (isLogScaleActive) {
            histogramFirst->setSamples(selectedSpectrum->logHistoVector);
        } else {
            histogramFirst->setSamples(selectedSpectrum->histoVector);
        }
        histogramFirst->setBaseline(baseValueLinLogScale);

        showSpectrumInHistoPlot();
        zoomer->setZoomBase();
        setEnabledConsole(true);

        printSpectrumData();

        ui->firstSpecButton->setChecked(true);
        ui->firstSpecButton->setEnabled(true);
        ui->menuFile->actions().at(1)->setDisabled(false);
        /*QPalette* palette1 = new QPalette();
        palette1->setColor(QPalette::Button ,Qt::red);
        ui->firstSpecButton->setPalette(*palette1);*/

    } else {
        cout<<"No file selected"<<endl;
    }

    //firstSpectrum->peakId();
}

void MainWindow::on_actionSup_Spectrum_triggered()
{

    QString histoFileName = QFileDialog::getOpenFileName (this, tr("Load file"), "~/");
    if (histoFileName.compare("")){
        if( histoFileName.endsWith(".chn") || histoFileName.endsWith(".Chn") || histoFileName.endsWith(".CHN")){
            secondSpectrum = new Spectrum(histoFileName,"chn",0);
        } else {

            secondSpectrum = new Spectrum(histoFileName,"tas",readTasFile(histoFileName));
        }
        QwtText title(selectedSpectrum->histoFileName+"\n"+secondSpectrum->histoFileName);
        title.setFont(QFont("Times",12,QFont::Bold));
        ui->histoPlot->setTitle(title);
        
        if (isLogScaleActive) {
            histogramSecond->setSamples(secondSpectrum->logHistoVector);
        } else {
            histogramSecond->setSamples(secondSpectrum->histoVector);
        }
        histogramSecond->setBaseline(baseValueLinLogScale);
        showSpectrumInHistoPlot();
        ui->secondSpecButton->setEnabled(true);


    } else {
        cout<<"No file selected"<<endl;
    }


}


void MainWindow::on_actionSave_File_triggered()
{


    QString filename = QFileDialog::getSaveFileName(this,tr("Save file"), firstSpectrum->fileName);
    if (filename.compare("")){
        QFile * testFile = new QFile(filename);
        if( ! testFile->open(QIODevice::WriteOnly) ) {
          QMessageBox::warning(NULL, "Test", "Unable to open: " + filename , "OK");
        } else {
            int rowNumber = ui->tableWidget->rowCount();
            int columnNumber = ui->tableWidget->columnCount();
            vector<pair<int,float> > sortingVector;
            for (int r = 0; r<rowNumber; r++){
                if(ui->tableWidget->item(r,8)->checkState()){
                    pair<int,float> p(r,ui->tableWidget->item(r,0)->text().toFloat());
                    sortingVector.push_back(p);
                }
            }


          QTextStream stream(testFile);
          stream<< qSetFieldWidth(13) <<left<<"Energy"<<"Erergy err"<<"FWHM"<<"FWHM err"<<"Net Area"<<"Net Area err"<<"Count/s"<<"Count/s err"<<"Red Chi-Sq"<<"Bg Fit"<<"Spectr. Num";
          stream<<qSetFieldWidth(0)<<endl;
          while(sortingVector.size()!=0){
              int minRowTemp=sortingVector.at(0).first;
              int minEnTemp=sortingVector.at(0).second;
              int vectPosTemp=0;
              for (int r = 0; r<(int)sortingVector.size(); r++) {

                  if (sortingVector.at(r).second<minEnTemp){

                      minRowTemp=sortingVector.at(r).first;
                      minEnTemp=sortingVector.at(r).second;
                      vectPosTemp=r;
                  }

              }
              for (int c = 0; c<columnNumber; c++){

                  if(c!=8){

                    QString value = ui->tableWidget->item(minRowTemp,c)->text();

                    stream<< qSetFieldWidth(13) << left<<value;

                  }

              }

              stream<<qSetFieldWidth(0)<<endl;
              sortingVector.erase(sortingVector.begin() + vectPosTemp);
          }
        }
    }

}

void MainWindow::on_actionContents_triggered()
{
    QDialog *aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle("Rhino");
    QGridLayout *gridLayout;
    QTextEdit *myTextEdit;
    aboutDialog->setMinimumSize(QSize(500, 300));
    aboutDialog->setMaximumSize(QSize(500, 300));
    gridLayout = new QGridLayout(aboutDialog);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    myTextEdit = new QTextEdit(aboutDialog);
    myTextEdit->setObjectName(QString::fromUtf8("myTextEdit"));

    ifstream infoFile;
    infoFile.open("info.txt",  ios::in);
    string allText,tempText;
    if (infoFile.is_open()){
        while(!infoFile.eof())
        {
            getline(infoFile,tempText);
            allText += "\n" + tempText;
        }
    }
    infoFile.close();
    //myTextEdit->setHtml(QString::fromStdString(allText));
    myTextEdit->setText(QString::fromStdString(allText));
    myTextEdit->setReadOnly(true);
    gridLayout->addWidget(myTextEdit, 0, 0, 1, 1);
    aboutDialog->exec();
}
void MainWindow::on_actionManual_triggered()
{
    QDialog *aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle("Rhino");
    QGridLayout *gridLayout;
    QTextEdit *myTextEdit;
    aboutDialog->setMinimumSize(QSize(500, 300));
    aboutDialog->setMaximumSize(QSize(500, 300));
    gridLayout = new QGridLayout(aboutDialog);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    myTextEdit = new QTextEdit(aboutDialog);
    myTextEdit->setObjectName(QString::fromUtf8("myTextEdit"));

    ifstream infoFile;
    infoFile.open("MANUAL",  ios::in);
    string allText,tempText;
    if (infoFile.is_open()){
        while(!infoFile.eof())
        {
            getline(infoFile,tempText);
            allText += "\n" + tempText;
        }
    }
    infoFile.close();
    //myTextEdit->setHtml(QString::fromStdString(allText));
    myTextEdit->setText(QString::fromStdString(allText));
    myTextEdit->setReadOnly(true);
    gridLayout->addWidget(myTextEdit, 0, 0, 1, 1);
    aboutDialog->exec();
}

//------------------------------------------------//
//                 OTHER FUNCTION                 //
//------------------------------------------------//


void MainWindow::showSpectrumInHistoPlot()
{
    ui->histoPlot->setAxisScale(QwtPlot::xBottom,0,selectedSpectrum->histoVector.at(selectedSpectrum->chNum-1).interval.maxValue());
    ui->histoPlot->replot();
}

void MainWindow::modifyScrollOnZoom(QRectF rectangle){

    ui->histoScrollBar->setPageStep(rectangle.width()/zoomer->zoomBase().width()*histoScrollBarMaxLength);
    ui->histoScrollBar->setMaximum(histoScrollBarMaxLength-ui->histoScrollBar->pageStep());
    ui->histoScrollBar->setValue(rectangle.left()*histoScrollBarMaxLength/zoomer->zoomBase().width());
}

void MainWindow::modifyHistoOnScroll(int value){

        qreal leftNew = zoomer->zoomBase().width()*value/histoScrollBarMaxLength;
        qreal widthNew = zoomer->zoomRect().width();
        qreal heightNew = selectedSpectrum->histoVector.at(findMaxInWindow()).value*1.1;
        zoomer->zoom(leftNew, baseValueLinLogScale, widthNew, heightNew);
}

int MainWindow::findMaxInWindow(){

    double leftValue = zoomer->zoomRect().left();
    double rightValue = zoomer->zoomRect().right();
    int leftCell = (int)((leftValue-selectedSpectrum->minValue)/selectedSpectrum->binStep);
    int rightCell = (int)((rightValue-selectedSpectrum->minValue)/selectedSpectrum->binStep);
    if(rightCell>=selectedSpectrum->histoVector.size())rightCell = selectedSpectrum->histoVector.size()-1;

    double maxVal = 0;
    int cellWithMax =0;
    if(leftCell<0)leftCell=0;
    for(int i=leftCell; i< rightCell; i++){
        double cellVal = selectedSpectrum->histoVector.at(i).value;

        if (cellVal > maxVal) {
            maxVal = cellVal;
            cellWithMax=i;
        }
    }
    return cellWithMax;

}

int MainWindow::findMinInWindow(){

    double leftValue = zoomer->zoomRect().left();
    double rightValue = zoomer->zoomRect().right();
    int leftCell = (int)((leftValue-selectedSpectrum->minValue)/selectedSpectrum->binStep);
    int rightCell = (int)((rightValue-selectedSpectrum->minValue)/selectedSpectrum->binStep);
    double minVal = findMaxInWindow();
    int cellWithMin =0;
    for(int i=leftCell; i< rightCell; i++){
        double cellVal = selectedSpectrum->histoVector.at(i).value;

        if (cellVal < minVal) {
            minVal = cellVal;
            cellWithMin=i;
        }
    }
    return cellWithMin;

}


void MainWindow::on_fitButton_clicked()
{
    if(myMarkersAndFits->tempMarkersVector.size()>2){

        // Deleting everything since we need to redraw allt he plots
        // But I save the old sigma first if requested. Not an elegant method.
        Double_t oldSigma;
        if (useLastSigma) oldSigma = myMarkersAndFits->func->GetParameter(myMarkersAndFits->numberOfGaussians*2);
        myMarkersAndFits->clearVectors();

        integralFit->detach();
        for(int g=0; g<(int)singleGaussCurveVector.size(); g++){

            singleGaussCurveVector.at(g)->detach();
        }
        //aggiungo le curve da disegnare
        gaussianFit->attach(ui->histoPlot);
        backgroundFit->attach(ui->histoPlot);
        differenceFit->attach(ui->histoPlot);
        differenceLine->attach(ui->histoPlot);
        myMarkersAndFits->setFitInterval(selectedSpectrum->histoVector);
        if (useLastSigma) myMarkersAndFits->fit(ui->chiSquareRadio->isChecked(), getBgChosen(), oldSigma);
        else myMarkersAndFits->fit(ui->chiSquareRadio->isChecked(), getBgChosen());
        gaussianFit->setSamples( myMarkersAndFits->xFitVal, myMarkersAndFits->yFitValGauss);
        backgroundFit->setSamples( myMarkersAndFits->xFitVal, myMarkersAndFits->yFitValBack);
        differenceFit->setSamples(myMarkersAndFits->xFitVal, myMarkersAndFits->yFitDifference);
        differenceLine->setSamples(myMarkersAndFits->xFitVal, myMarkersAndFits->yFitMean);

        fillTable("peak");
        myMarkersAndFits->prevMarkersVector.clear();
        for(int k = 0; k<myMarkersAndFits->tempMarkersVector.size(); k++){
            myMarkersAndFits->prevMarkersVector.append(myMarkersAndFits->tempMarkersVector.at(k));
        }
        //delete markers when the fit is finished;
        for(int k = 0; k<myMarkersAndFits->tempMarkersVector.size(); k++){
                myMarkersAndFits->tempMarkersVector.at(k)->detach();
        }
        myMarkersAndFits->tempMarkersVector.clear();
        ui->histoPlot->replot();
        useLastSigma = false;

    } else if(myMarkersAndFits->tempMarkersVector.size()==2){ // Integral
        // Removing lines we don't need
        myMarkersAndFits->clearVectors();
        gaussianFit->detach();
        backgroundFit->detach();
        differenceFit->detach();
        differenceLine->detach();
        for(int g=0; g<(int)singleGaussCurveVector.size(); g++){
            singleGaussCurveVector.at(g)->detach();
        }
        // Adding Integral Area
        integralFit->attach(ui->histoPlot);
        myMarkersAndFits->setFitInterval(selectedSpectrum->histoVector);
        myMarkersAndFits->calculateIntegral();
        if (isLogScaleActive) {
            integralFit->setSamples(myMarkersAndFits->logIntegralHisto);
        } else {
            integralFit->setSamples(myMarkersAndFits->integralHisto);
        }
        integralFit->setBaseline( baseValueLinLogScale );


        fillTable("integral");
        //delete markers when the fit is finished;
        for(int k = 0; k<myMarkersAndFits->tempMarkersVector.size(); k++){
                myMarkersAndFits->tempMarkersVector.at(k)->detach();
        }
        myMarkersAndFits->tempMarkersVector.clear();
        ui->histoPlot->replot();

    } else if(myMarkersAndFits->tempMarkersVector.size()==1){
        if (myMarkersAndFits->prevMarkersVector.size()>2){
            myMarker* soloMarker = myMarkersAndFits->tempMarkersVector.at(0);
            Double_t leftValue = myMarkersAndFits->prevMarkersVector.at(0)->xValue();
            Double_t rightValue = myMarkersAndFits->prevMarkersVector.at(1)->xValue();
            if (leftValue>rightValue) {
                Double_t tempValue = leftValue;
                leftValue = rightValue;
                rightValue = tempValue;
            }
            double newValue = myMarkersAndFits->tempMarkersVector.at(0)->xValue();
            if(newValue > leftValue && newValue < rightValue){
                myMarkersAndFits->tempMarkersVector.clear();
                for(int j = 0; j<myMarkersAndFits->prevMarkersVector.size(); j++){
                    myMarkersAndFits->tempMarkersVector.push_back(myMarkersAndFits->prevMarkersVector.at(j));
                }
                myMarkersAndFits->tempMarkersVector.push_back(soloMarker);
                useLastSigma = true;
                on_fitButton_clicked();
            }
        }
    }
}

void MainWindow::catchPointSelected(const QPointF &pos ){
    if (firstSpectrum != NULL) {
        myMarker *newMarker = new myMarker(ui->histoPlot);
        int markerCell = (int)((pos.x()-selectedSpectrum->minValue)/selectedSpectrum->binStep);
        newMarker->setValue(pos.x(),selectedSpectrum->histoVector.at(markerCell).value);
        ui->histoPlot->replot();
        myMarkersAndFits->tempMarkersVector.push_back(newMarker);
        ui->calLineEdit->setText(QString::number ( markerCell,'g',6 ));
    }
}

void MainWindow::wheelEvent(QWheelEvent *event){
    if(d_picker->trackerPosition().x()!=-1){
        if(zoomer->isEnabled()){
            QPointF coordinates = d_picker->getCoordinatesFromPixels(d_picker->trackerPosition());
            qreal widthNew = 0;
            if(event->delta()>0) widthNew = zoomer->zoomRect().width()*0.9;
            else if(event->delta()<0) widthNew = zoomer->zoomRect().width()*1.1;
            if (widthNew>zoomer->zoomBase().width()) widthNew = zoomer->zoomBase().width();
            qreal leftNew = zoomer->zoomRect().left()+(zoomer->zoomRect().width()-widthNew)/2;
            //qreal relVal = coordinates.x() - (zoomer->zoomRect().left() + zoomer->zoomRect().width()/2);
            //relVal = relVal / (zoomer->zoomRect().width()/2) / 5;
            //leftNew = leftNew + relVal * leftNew;
            
            // Correction to the left side position of the window to have a gmap-like zoom:
            // the bin pointed by the cursor stays in the same relative position in the windows,
            // i.e. stays under the cursor while the rest zooms in or out
            qreal relVal = (coordinates.x() - zoomer->zoomRect().left()) / zoomer->zoomRect().width();
            leftNew = -(relVal * widthNew - coordinates.x());
            if (leftNew<zoomer->zoomBase().left()) leftNew =zoomer->zoomBase().left();
            qreal heightNew = zoomer->zoomRect().height();
            zoomer->zoom(leftNew, baseValueLinLogScale, widthNew, heightNew);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    //cout<<event->key()<<endl;
    if(event->key()==70 || event->key()==87){   //pressed 'f' or 'w'
        ui->fitButton->click();
    } else if(event->key()==65){   //pressed 'a'
        ui->leftButton->click();
    } else if(event->key()==68){   //pressed 'd'
        ui->rightButton->click();
    } else if(event->key()==83){   //pressed 's'
        ui->saveFitButton->click();
    } else if(event->key()==69){   //pressed 'e'
        ui->gaussiansToolButton->click();
    } else if(event->key()==81){   //pressed 'q'
        ui->cancelToolButton->click();
    }

}

void MainWindow::on_leftButton_pressed(){
    if (firstSpectrum != NULL) {
        int newValue = ui->histoScrollBar->value();
        if(zoomer->zoomRect().width()*0.5<20) newValue -=20;
        else newValue -=zoomer->zoomRect().width()*0.5;
        if(newValue < ui->histoScrollBar->minimum()) newValue = ui->histoScrollBar->minimum();
        ui->histoScrollBar->setValue(newValue);
    }
}

void MainWindow::on_rightButton_pressed(){
    int newValue = ui->histoScrollBar->value();
    if(zoomer->zoomRect().width()*0.5<20) newValue +=20;
    else newValue +=zoomer->zoomRect().width()*0.5;
    if(newValue > ui->histoScrollBar->maximum()) newValue = ui->histoScrollBar->maximum();
    ui->histoScrollBar->setValue(newValue);
}

void MainWindow::on_saveFitButton_clicked(){
        for(int j=0; j<myMarkersAndFits->numberOfGaussians; j++){
            if(ui->tableWidget->item(j,8)->checkState()==Qt::Unchecked)ui->tableWidget->item(j,8)->setCheckState(Qt::Checked);
            else ui->tableWidget->item(j,8)->setCheckState(Qt::Unchecked);
        }
}

void MainWindow::fillTable(string entryType){

    int rowNumber = ui->tableWidget->rowCount();
    for (int i = 0; i<rowNumber; i++){
        ui->tableWidget->item(i,8)->setBackgroundColor(QColor(255, 255, 255));
    }
    if (entryType=="peak"){
        for(int j=0; j<myMarkersAndFits->numberOfGaussians; j++){

            ui->tableWidget->insertRow(0);
            QColor bgcolor;
            bgcolor.setRgb(255,255,255);
            if(myMarkersAndFits->peaksVectorTemp.at(j)->badPeak) bgcolor.setRgbF(1,0,0,0.1);
            //mean
            QTableWidgetItem *meanItem = new QTableWidgetItem;
            meanItem->setBackgroundColor(bgcolor);
            meanItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->mean,'g',6 ));
            meanItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 0, meanItem);
            //sigma
            QTableWidgetItem *sigmaItem = new QTableWidgetItem;
            sigmaItem->setBackgroundColor(bgcolor);
            sigmaItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->FWHM,'g',6 ));
            sigmaItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 2, sigmaItem);
            //netArea
            QTableWidgetItem *areaItem = new QTableWidgetItem;
            areaItem->setBackgroundColor(bgcolor);
            areaItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->netArea,'g',6 ));
            areaItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 4, areaItem);
            //netArea/T
            QTableWidgetItem *areaTItem = new QTableWidgetItem;
            areaTItem->setBackgroundColor(bgcolor);
            areaTItem->setText(QString::number ( (double)myMarkersAndFits->peaksVectorTemp.at(j)->netArea/selectedSpectrum->liveTime,'g',6 ));
            areaTItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 6, areaTItem);
            //meanErr
            QTableWidgetItem *meanErrItem = new QTableWidgetItem;
            meanErrItem->setBackgroundColor(bgcolor);
            meanErrItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->meanErr,'g',6 ));
            meanErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 1, meanErrItem);
            //sigmaErr
            QTableWidgetItem *sigmaErrItem = new QTableWidgetItem;
            sigmaErrItem->setBackgroundColor(bgcolor);
            sigmaErrItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->FWHMErr,'g',6 ));
            sigmaErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 3, sigmaErrItem);
            //netAreaErr
            QTableWidgetItem *areaErrItem = new QTableWidgetItem;
            areaErrItem->setBackgroundColor(bgcolor);
            areaErrItem->setText(QString::number ( myMarkersAndFits->peaksVectorTemp.at(j)->netAreaErr,'g',6 ));
            areaErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 5, areaErrItem);
            //netArea/TErr
            QTableWidgetItem *areaTErrItem = new QTableWidgetItem;
            areaTErrItem->setBackgroundColor(bgcolor);
            areaTErrItem->setText(QString::number ( (double)myMarkersAndFits->peaksVectorTemp.at(j)->netAreaErr/selectedSpectrum->liveTime,'g',6 ));
            areaTErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 7, areaTErrItem);
            //save option
            QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
            checkBoxItem->setBackgroundColor(QColor(0, 0,255,100));
            checkBoxItem->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(0, 8, checkBoxItem);

            //Spectrum 1 or 2?                      //AGGIUNTA MAFFE
            QTableWidgetItem *whichSpectrum = new QTableWidgetItem;
            int spectrumNumber;
            if (selectedSpectrum==firstSpectrum) spectrumNumber=1;
            else if (selectedSpectrum==secondSpectrum)   spectrumNumber=2;
            whichSpectrum->setBackgroundColor(bgcolor);
            whichSpectrum->setText(QString::number ( spectrumNumber,'g',6 ));
            whichSpectrum->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 11, whichSpectrum);



            if(j==myMarkersAndFits->numberOfGaussians-1) {
                QTableWidgetItem *chiItem = new QTableWidgetItem;
                chiItem->setBackgroundColor(bgcolor);
                chiItem->setText(QString::number ( myMarkersAndFits->redChiSquare,'g',6 ));
                chiItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                ui->tableWidget->setItem(0, 9, chiItem);

            } else {
                QTableWidgetItem *chiItem = new QTableWidgetItem;
                chiItem->setBackgroundColor(bgcolor);
                chiItem->setText("");
                chiItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                ui->tableWidget->setItem(0, 9, chiItem);

            }

            //bg fit
            QTableWidgetItem *bgFitItem = new QTableWidgetItem;
            bgFitItem->setBackgroundColor(bgcolor);
            bgFitItem->setText(QString::number ( (double)getBgChosen(),'g',6 ));
            bgFitItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(0, 10, bgFitItem);

        }
    } else if (entryType=="integral"){

        ui->tableWidget->insertRow(0);
        QColor bgcolor;
        bgcolor.setRgbF(0,1,0,0.1);

        //mean of the interval
        QTableWidgetItem *meanItem = new QTableWidgetItem;
        meanItem->setBackgroundColor(bgcolor);
        meanItem->setText(QString::number ( ( myMarkersAndFits->integralHisto.at(0).interval.minValue() + myMarkersAndFits->integralHisto.back().interval.maxValue() )/2,'g',6 ));
        meanItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 0, meanItem);

        //interval semiwidth
        QTableWidgetItem *semiWidth = new QTableWidgetItem;
        semiWidth->setBackgroundColor(bgcolor);
        semiWidth->setText(QString::number ( (myMarkersAndFits->integralHisto.back().interval.maxValue()-myMarkersAndFits->integralHisto.at(0).interval.minValue())/2 ));
        semiWidth->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 1, semiWidth);

        //no sigma for an integral
        QTableWidgetItem *sigmaItem = new QTableWidgetItem;
        sigmaItem->setBackgroundColor(bgcolor);
        sigmaItem->setText(QString("0"));
        sigmaItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 2, sigmaItem);

        //no sigmaErr for an integral
        QTableWidgetItem *sigmaErrItem = new QTableWidgetItem;
        sigmaErrItem->setBackgroundColor(bgcolor);
        sigmaErrItem->setText(QString("0"));
        sigmaErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 3, sigmaErrItem);

        //netArea
        QTableWidgetItem *areaItem = new QTableWidgetItem;
        areaItem->setBackgroundColor(bgcolor);
        areaItem->setText(QString::number ( myMarkersAndFits->integral,'g',6 ));
        areaItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 4, areaItem);

        //netAreaErr
        QTableWidgetItem *areaErrItem = new QTableWidgetItem;
        areaErrItem->setBackgroundColor(bgcolor);
        areaErrItem->setText(QString::number ( (int)(sqrt(myMarkersAndFits->integral)),'g',6 ));
        areaErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 5, areaErrItem);

        //netArea/T
        QTableWidgetItem *areaTItem = new QTableWidgetItem;
        areaTItem->setBackgroundColor(bgcolor);
        areaTItem->setText(QString::number ( (double)myMarkersAndFits->integral/selectedSpectrum->liveTime,'g',6 ));
        areaTItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 6, areaTItem);

        //netArea/TErr
        QTableWidgetItem *areaTErrItem = new QTableWidgetItem;
        areaTErrItem->setBackgroundColor(bgcolor);
        areaTErrItem->setText(QString::number ( sqrt((double)myMarkersAndFits->integral)/selectedSpectrum->liveTime,'g',6 ));
        areaTErrItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 7, areaTErrItem);

        //save option
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setBackgroundColor(bgcolor);
        checkBoxItem->setCheckState(Qt::Unchecked);
        checkBoxItem->setBackgroundColor(QColor(0, 0,255,100));
        ui->tableWidget->setItem(0, 8, checkBoxItem);

        //chi 2
        QTableWidgetItem *chiItem = new QTableWidgetItem;
        chiItem->setBackgroundColor(bgcolor);
        chiItem->setText(QString::number ( 0,'g',6 ));
        chiItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 9, chiItem);

        //bg fit
        QTableWidgetItem *bgFitItem = new QTableWidgetItem;
        bgFitItem->setBackgroundColor(bgcolor);
        bgFitItem->setText(QString::number ( 0,'g',6 ));
        bgFitItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 10, bgFitItem);

        //Spectrum 1 or 2?                      //AGGIUNTA MAFFE
        QTableWidgetItem *whichSpectrum = new QTableWidgetItem;
        int spectrumNumber;
        if (selectedSpectrum==firstSpectrum) spectrumNumber=1;
        else if (selectedSpectrum==secondSpectrum)   spectrumNumber=2;
        whichSpectrum->setBackgroundColor(bgcolor);
        whichSpectrum->setText(QString::number ( spectrumNumber,'g',6 ));
        whichSpectrum->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->tableWidget->setItem(0, 11, whichSpectrum);
    }


}

int MainWindow::getBgChosen(){
    int backgroundChosen = 1;
    if (ui->linearBgFitRadio->isChecked()) backgroundChosen = 0;
    else if (ui->sigmoidBgFitRadio->isChecked()) backgroundChosen = 2;
    else if (ui->bestBgFitRadio->isChecked()) backgroundChosen = 3;
    return backgroundChosen;
}


void MainWindow::on_rebinButton_clicked()
{
    QRectF oldRect = zoomer->zoomRect();
    ui->histoPlot->setAxisAutoScale(QwtPlot::xBottom,true);
    ui->histoPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    histogramFirst->detach();
    histogramSecond->detach();
    selectedSpectrum->rebinning(ui->binFactorBox->value());
    histogramFirst->attach(ui->histoPlot);
    histogramSecond->attach(ui->histoPlot);
    if(ui->firstSpecButton->isChecked()) histogramFirst->setSamples(selectedSpectrum->histoVector);
    else histogramSecond->setSamples(selectedSpectrum->histoVector);
    showSpectrumInHistoPlot();
    zoomer->setZoomBase();
    zoomer->zoom(oldRect.left(),0,oldRect.width(),zoomer->zoomBase().height());
    qreal heightNew = selectedSpectrum->histoVector.at(findMaxInWindow()).value*1.1;
    zoomer->zoom(oldRect.left(),0,oldRect.width(),heightNew);

}

int MainWindow::readTasFile(QString histoFileNameNew){

    int counter = 0;
    int selectedSpectrum = 0;
    ifstream file (histoFileNameNew.toUtf8().constData(), ios::in|ios::binary);
    if(file.is_open()){
        while(!file.eof()) {
            //4 char = 1 float
            char stuff[4];
            file.read (stuff, sizeof(stuff));
            float chNumberTemp;
            file.read (reinterpret_cast<char*>(&chNumberTemp), sizeof(chNumberTemp));
            char otherStuff_1[128*4];
            file.read(otherStuff_1, sizeof(otherStuff_1));
            for(int i = 0; i <chNumberTemp; i++){
                float temp;
                file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
            }
            file.close();
            counter++;
        }
    }

    if(counter>1){
        MyDialog optionsDialog(this,counter);
        if(optionsDialog.exec()==QDialog::Accepted) selectedSpectrum = optionsDialog.selected;
    }
    return selectedSpectrum;



}

void MainWindow::on_printHistoButton_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOrientation( QPrinter::Landscape );
    printer.setOutputFileName( "spectrogram.pdf" );
    QPrintDialog dialog( &printer );
    if ( dialog.exec() )
    {
        QwtPlotRenderer renderer;

        renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground, false );
        // TO BE FIXED
	//renderer.setLayoutFlag( QwtPlotRenderer::KeepFrames, true );

        renderer.renderTo( ui->histoPlot, printer );
    }

}

void MainWindow::on_logScaleButton_clicked()
{
    // We do something only if there is at least a spectrum in the plot
    if (firstSpectrum == NULL) {
        return;
    }

    isLogScaleActive = !isLogScaleActive;
    if(isLogScaleActive) {
        baseValueLinLogScale = 0.1;
        histogramFirst->setSamples(firstSpectrum->logHistoVector);
        ui->histoPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine(10));
    } else {
        baseValueLinLogScale = 0.0;
        histogramFirst->setSamples(firstSpectrum->histoVector);
        ui->histoPlot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
    }
    histogramFirst->setBaseline(baseValueLinLogScale);
    
    // Same for second spectrum if present
    if (secondSpectrum != NULL) {
        if(isLogScaleActive) {
            histogramSecond->setSamples(secondSpectrum->logHistoVector);
        } else {
            histogramSecond->setSamples(secondSpectrum->histoVector);
        }
        histogramSecond->setBaseline(baseValueLinLogScale);   
    }

    QRectF oldRect = zoomer->zoomRect();
    zoomer->zoom(oldRect.left(), baseValueLinLogScale, oldRect.width(), oldRect.height());
    myMarkersAndFits->clearVectors();
    ui->histoPlot->replot();
}

void MainWindow::on_toolButton_clicked()
{
        //QRgb m_color(255,0,0);
        QColor color(255,0,0,255);
        QColorDialog dialog(color, 0);
        dialog.setOption(QColorDialog::ShowAlphaChannel, true);

        //dialog.move(280, 120);
        if (dialog.exec() == QDialog::Rejected)
            return;
        QColor newColor = dialog.selectedColor();

        if(ui->comboBoxColor->currentText()=="Background")
            ui->histoPlot->setCanvasBackground(QBrush(newColor));
        if(ui->comboBoxColor->currentText()=="Histogram"){
            histogramFirst->setPen( QPen(newColor, 1) );
            integralFit->setPen(QPen(newColor, 1.5));
        }
        if(ui->comboBoxColor->currentText()=="Peak Fit")
            gaussianFit->setPen(QPen(newColor, 1));
        if(ui->comboBoxColor->currentText()=="Background Fit")
            backgroundFit->setPen( QPen(newColor, 1) );
        if(ui->comboBoxColor->currentText()=="Integral")
            integralFit->setBrush(QBrush(newColor));
        if(ui->comboBoxColor->currentText()=="Cursor"){
            zoomer->setTrackerPen(QPen(newColor, 1));
            zoomer->setRubberBandPen(QPen(newColor, 1));
        }
        ui->histoPlot->replot();

}

void MainWindow::on_clearTableButton_clicked()
{
    int rowsNumber = ui->tableWidget->rowCount();
    for(int i = rowsNumber; i>=0; i--){
        ui->tableWidget->removeRow(i);
    }
}

void MainWindow::on_saveImageButton_clicked()
{
    QPixmap qPix = QPixmap::grabWidget(ui->histoPlot);
    if(qPix.isNull()){
    qDebug("Failed to capture the plot for saving");
    return;
    }
    QString types(	"JPEG file (*.jpeg);;"	// Set up the possible graphics formats
    "Portable Network Graphics file (*.png);;"
    "Bitmap file (*.bmp)");
    QString filter; // Type of filter
    QString jpegExt=".jpeg", pngExt=".png", bmpExt=".bmp"; // Suffix for the files
    QString fn = QFileDialog::getSaveFileName(this,tr("Save Image"),
                                              "histogram",types,&filter);

    if ( !fn.isEmpty() ) {	// If filename is not a null
        if (fn.contains(jpegExt)) {	// Remove file extension is already there
            fn.remove(jpegExt);
        }
        else if (fn.contains(pngExt)) {
            fn.remove(pngExt);
        }
        else if (fn.contains(bmpExt)) {
            fn.remove(bmpExt);
        }
        if (filter.contains(jpegExt)) {	// OR, Test to see if jpeg and save
            fn+=jpegExt;
            qPix.save( fn, "JPEG" );
        }
        else if (filter.contains(pngExt)) {	// OR, Test to see if png and save
            fn+=pngExt;
            qPix.save( fn, "PNG" );
        }
        else if (filter.contains(bmpExt)) {	// OR, Test to see if bmp and save
            fn+=bmpExt;
            qPix.save( fn, "BMP" );
        }
    }
}

void MainWindow::on_addCalButton_clicked()
{
    int myChannel = ui->calLineEdit->text().toInt();
    float myEnergy = ui->energyLineEdit->text().toFloat();
    pair<int,float> p(myChannel,myEnergy);
    selectedSpectrum->calibrationVect.push_back(p);
    ui->listPointComboBox->addItem(ui->calLineEdit->text() + " ch -> " + ui->energyLineEdit->text() + " keV");
}

void MainWindow::on_calibrateButton_clicked()
{
    if(selectedSpectrum->calibrationVect.size()>1){

        ui->histoPlot->setAxisAutoScale(QwtPlot::xBottom,true);
        ui->histoPlot->setAxisAutoScale(QwtPlot::yLeft,true);
        if(ui->firstSpecButton->isChecked()) {
            histogramFirst->detach();
            selectedSpectrum->recalibrate();
            histogramFirst->attach(ui->histoPlot);
            histogramFirst->setSamples(selectedSpectrum->histoVector);
        } else {
            histogramSecond->detach();
            selectedSpectrum->recalibrate();
            histogramSecond->attach(ui->histoPlot);
            histogramSecond->setSamples(selectedSpectrum->histoVector);
        }
        showSpectrumInHistoPlot();
        zoomer->zoom(zoomer->zoomBase().left(),0,zoomer->zoomBase().width(),zoomer->zoomBase().height());
        myMarkersAndFits->clearVectors();
        ui->histoPlot->replot();
    }
}

void MainWindow::on_clearCalButton_clicked()
{
    ui->listPointComboBox->clear();
    selectedSpectrum->calibrationVect.clear();
    myMarkersAndFits->clearVectors();
    ui->histoPlot->replot();
    ui->calLineEdit->setText("");
    ui->energyLineEdit->setText("");

}



void MainWindow::on_gaussiansToolButton_clicked()
{
    if( myMarkersAndFits->singleGaussVector.size()>0){
        for(int g=0; g<myMarkersAndFits->numberOfGaussians; g++){
            QwtPlotCurve *gaussianTemp = new QwtPlotCurve;
            gaussianTemp->setPen( QColor( Qt::cyan ) );
            gaussianTemp->attach(ui->histoPlot);
            gaussianTemp->setSamples(myMarkersAndFits->singleGaussVector.at(0),myMarkersAndFits->singleGaussVector.at(g+1) );
            singleGaussCurveVector.push_back(gaussianTemp);
        }
        ui->histoPlot->replot();
    }
}




void MainWindow::on_cancelToolButton_clicked()
{
    //myMarkersAndFits->clearVectors();
    for(int k = 0; k<myMarkersAndFits->tempMarkersVector.size(); k++){
            myMarkersAndFits->tempMarkersVector.at(k)->detach();
    }
    gaussianFit->detach();
    backgroundFit->detach();
    differenceFit->detach();
    differenceLine->detach();
    integralFit->detach();
    myMarkersAndFits->tempMarkersVector.clear();
    ui->histoPlot->replot();

}


void MainWindow::on_firstSpecButton_clicked(bool checked)
{
    if(checked){

        histogramFirst->setPen(QPen(Qt::yellow, 1));
        histogramSecond->setPen(QPen(Qt::magenta, 1,Qt::DashDotLine));
        selectedSpectrum = firstSpectrum;
        ui->secondSpecButton->setChecked(false);
        QRectF oldRect = zoomer->zoomRect();
        qreal heightNew = selectedSpectrum->histoVector.at(findMaxInWindow()).value*1.1;
        zoomer->zoom(oldRect.left(),baseValueLinLogScale,oldRect.width(),heightNew);
        printSpectrumData();


    } else {
        ui->firstSpecButton->setChecked(true);
    }

}

void MainWindow::on_secondSpecButton_clicked(bool checked)
{
    if(checked){
        histogramFirst->setPen(QPen(Qt::yellow, 1,Qt::DashDotLine));
        histogramSecond->setPen(QPen(Qt::magenta, 1));
        selectedSpectrum = secondSpectrum;
        ui->firstSpecButton->setChecked(false);
        QRectF oldRect = zoomer->zoomRect();
        qreal heightNew = selectedSpectrum->histoVector.at(findMaxInWindow()).value*1.1;
        zoomer->zoom(oldRect.left(),baseValueLinLogScale,oldRect.width(),heightNew);
        printSpectrumData();


    } else {
        ui->secondSpecButton->setChecked(true);
    }
}

void MainWindow::printSpectrumData()    {

        ui->channelsLineEdit->setText(QString::number ( selectedSpectrum->chNum,'g',6 ));
        ui->timeLineEdit->setText(QString::number ( selectedSpectrum->liveTime,'g',6 ));
        ui->realLineEdit->setText(QString::number ( selectedSpectrum->realTime,'g',6 ));
        ui->dateAndTimeLineEdit->setText(QString(selectedSpectrum->dateAndTimeMeasure));

}

// void MainWindow::on_autofitButton_clicked()
// {

//     QString filename = QFileDialog::getSaveFileName(this,tr("Save Autofit File"), selectedSpectrum->fileName + "_AUTOFIT.txt");
//     selectedSpectrum->peakId(filename);

// }

// void MainWindow::on_pushButton_clicked()
// {
//     QString link = "http://nucleardata.nuclear.lu.se/toi/";
//     QDesktopServices::openUrl(QUrl(link));
// }
