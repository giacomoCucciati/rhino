#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QString>
#include <QVector>
#include <iostream>
#include <fstream>
#include "qwt_plot_seriesitem.h"
#include <qwt_plot_zoomer.h>
#include <QRectF>
#include <qwt_plot_marker.h>
#include <qwt_plot_canvas.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TF1.h>
#include <TGraph.h>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QLabel>

using namespace std;

class Spectrum {

public:
    Spectrum();
    Spectrum(QString histoFileNameNew,string type, int spectrumNumber);
    Spectrum(QString histoFileNameNew,string type, int spectrumNumber, int channelsNumber, string energyBranchName, Double_t maxEnergy);
    ~Spectrum();
    void loadHistoVector(string type, int spectrumNumber);
    void loadHistoVector(string type, int spectrumNumber, int channelsNumber, string energyBranchName, Double_t maxEnergy);
    float calibrateBin(float value);
    void rebinning(int newBinFactor);
    void recalibrate();
    void peakId(QString destinazione);

    QString histoFileName;
    QVector<QwtIntervalSample> origHistoVector;
    QVector<QwtIntervalSample> histoVector;
    QVector<QwtIntervalSample> logHistoVector; // only for drawing
    
    vector<int> vettoreValori;
    int binFactor;
    float binStep;
    float minValue;
    int chNum;
    int liveTime;
    int realTime;
    QString dateAndTimeMeasure;
    float caliSlope;
    float caliIntercept;
    vector< pair <int,float> > calibrationVect;
    QString fileName;

};

class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer( QwtPlotCanvas *canvas ):
        QwtPlotZoomer( canvas )
    {
        setTrackerMode( AlwaysOn );
    }
    // virtual QwtText trackerTextF( const QPointF &pos ) const
    // {
    //     QColor bg( Qt::white );
    //     bg.setAlpha( 0 );

    //     QwtText text = QwtPlotZoomer::trackerTextF( pos );
    //     text.setBackgroundBrush( QBrush( bg ) );
    //     return text;
    // }

public Q_SLOTS:

    void zoom( const QRectF & rect )
    {
        QRectF newRect;
        const QRectF & baseRect = zoomBase();
        newRect.setCoords( rect.left(), baseRect.top(), rect.right(),baseRect.bottom());
        QwtPlotZoomer::zoom( newRect );
    }

    void zoom( qreal leftNew, qreal topNew, qreal wNew, qreal hNew )
    {
        QRectF newRect(leftNew, topNew, wNew, hNew);
        QwtPlotZoomer::zoom( newRect );
    }


};

class myMarker: public QwtPlotMarker
{
public:

    myMarker(QwtPlot *myplot){

        setLineStyle(QwtPlotMarker::VLine);
        setLabelAlignment(Qt::AlignBottom);
        setLinePen(QPen(Qt::darkGray, 1, Qt::DashLine));
        setValue(1.0, 0.0);
        attach(myplot);

    }

};

class Peak {
public:

    Peak();
    Peak(double newAmp, double newMean, double newSigma, double newAmpErr, double newMeanErr, double newSigmaErr, double newBinWidth){
        amp = newAmp;
        mean = newMean;
        sigma = newSigma;
        ampErr = newAmpErr;
        meanErr = newMeanErr;
        sigmaErr = newSigmaErr;
        binWidth = newBinWidth;
        badPeak = false;
        calculateNetArea();
        calculateFWHM();
        isItBad();
    }
    ~Peak();
    void calculateNetArea();
    void calculateFWHM();
    void isItBad();
    double amp;
    double mean;
    double sigma;
    double ampErr;
    double meanErr;
    double sigmaErr;
    int netArea;
    int netAreaErr;
    double FWHM;
    double FWHMErr;
    double binWidth;
    bool badPeak;

};

class MarkersAndFits {
public:


    MarkersAndFits(){
       numberOfGaussians=0;
    }
    ~MarkersAndFits();
    void setFitInterval(QVector<QwtIntervalSample> histoVector);
    void fit(bool chiSquare, int whichBg, Double_t sigma = 0);
    void calculateIntegral();
    void clearVectors();
    double totalFitFunction(Double_t *x,Double_t *par);
    double sigmoidBackground(Double_t *x,Double_t *par);
    double linearBackground(Double_t *x,Double_t *par);
    double quadraticBackground(Double_t *x,Double_t *par);
    double oneGauss(Double_t *x,Double_t *par);

    //void fitWithGsl();

    QVector<myMarker*> tempMarkersVector;
    QVector<myMarker*> prevMarkersVector;
    QVector<Peak*> peaksVector;
    QVector<Peak*> peaksVectorTemp;
    QVector<QwtIntervalSample> fitIntervalHisto;
    QVector<QwtIntervalSample> integralHisto;
    QVector<QwtIntervalSample> logIntegralHisto;
    TF1 *func;
    QVector<double> xFitVal;
    QVector<double> yFitValGauss;
    QVector<double> yFitValBack;
    QVector<double> yFitDifference;
    QVector<double> yFitMean;
    vector<QVector <double> > singleGaussVector;

    double_t redChiSquare;
    int numberOfGaussians;
    int integral;

};


class MyPicker: public QwtPlotPicker
{
public:
    MyPicker();

    MyPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QWidget *mycanvas):
        QwtPlotPicker(xAxis,yAxis,rubberBand,trackerMode,mycanvas){
    }

    QPointF getCoordinatesFromPixels(QPoint point) {
        return invTransform(point);
    }

};



class MyDialog: public QDialog
{

public:
    MyDialog();
    MyDialog(QWidget *parent=0, int number=0);
    QVector<QPushButton*> buttonVector;
    int buttonsNumber;
    int selected;

public Q_SLOTS:
    void accept();

};

class MyFitFunction {


public:
    MyFitFunction(int whichBgNew, int numberOfGaussiansNew){

        whichBg = whichBgNew;
        numberOfGaussians = numberOfGaussiansNew;

    }

    double oneGauss(double *x, double *par, double commonSigma){
        double fitval = par[0] * TMath::Exp( -(x[0]-par[1])*(x[0]-par[1])/(2*commonSigma*commonSigma) );
        return fitval;
    }
    double linearBackground(double *x, double *par){
        double fitval = par[0]*x[0]+par[1]; //background linear function
        return fitval;
    }
    double quadraticBackground(double *x, double *par){
        double fitval = par[0]*x[0]*x[0]+par[1]*x[0]+par[2]; //background quadratic function
        return fitval;
    }
    double sigmoidBackground(double *x, double *par){
        double fitval = par[0]*atan(par[1]*x[0]+par[2])+par[3]; //background sigmoid function
        return fitval;
    }
    double totalFitFunc(double *x, double *par) {
        double fitval = 0;
        for(int i = 0; i< numberOfGaussians; i++){
            fitval+=oneGauss(x, &par[2*i], par[numberOfGaussians*2]);
        }
        if (whichBg==0)    fitval +=  linearBackground(x,&par[numberOfGaussians*2+1]);
        if (whichBg==1)    fitval +=  quadraticBackground(x,&par[numberOfGaussians*2+1]);
        if (whichBg==2)    fitval +=  sigmoidBackground(x,&par[numberOfGaussians*2+1]);

        return fitval;
    }
    int whichBg;
    int numberOfGaussians;

};


#endif // SPECTRUM_H
