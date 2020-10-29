#include "spectrum.h"

using namespace std;

Spectrum::Spectrum(){}

Spectrum::Spectrum(QString histoFileNameNew,string type, int spectrumNumber){

    histoFileName=histoFileNameNew;
    loadHistoVector(type,spectrumNumber);
    binStep = histoVector.at(0).interval.width();
    minValue = histoVector.at(0).interval.minValue();

}

Spectrum::~Spectrum(){}
float Spectrum::calibrateBin(float value){

    return value*caliSlope+caliIntercept;

}

void Spectrum::loadHistoVector(string type, int spectrumNumber){
    if (type=="chn"){
        ifstream file (histoFileName.toUtf8().constData(), ios::in|ios::binary);
        if(file.is_open()){
                        //1 char = 1 byte... devo leggere 32 byte di header
                        char stuff[8];
                        file.read (stuff, sizeof(stuff));

                        int tempReal;								//legge il tempo reale
                        file.read (reinterpret_cast<char*>(&tempReal), sizeof(tempReal));
                        realTime=tempReal/50;
                        cout<<"Real time: "<<realTime<<endl;

                        int tempLive;
                        file.read (reinterpret_cast<char*>(&tempLive), sizeof(tempLive));
                        liveTime=tempLive/50;
                        cout<<"Live time: "<<liveTime<<endl;

                        char day[2];
                        file.read (day, sizeof(day));
                        dateAndTimeMeasure.append(day[0]);
                        dateAndTimeMeasure.append(day[1]);
                        dateAndTimeMeasure.append("-");
                        char month[3];
                        file.read (month, sizeof(month));
                        dateAndTimeMeasure.append(month[0]);
                        dateAndTimeMeasure.append(month[1]);
                        dateAndTimeMeasure.append(month[2]);
                        dateAndTimeMeasure.append("-");
                        char year[2];
                        file.read (year, sizeof(year));
                        dateAndTimeMeasure.append(year[0]);
                        dateAndTimeMeasure.append(year[1]);
                        dateAndTimeMeasure.append("  @  ");

                        char otherStuff[1];                             //dopo la data c'è "1", che indica misura presa dopo l'anno 2000
                        file.read (otherStuff, sizeof(otherStuff));

                        char hour[2];
                        file.read (hour, sizeof(hour));
                        dateAndTimeMeasure.append(hour[0]);
                        dateAndTimeMeasure.append(hour[1]);
                        dateAndTimeMeasure.append(":");
                        char minute[2];
                        file.read (minute, sizeof(minute));
                        dateAndTimeMeasure.append(minute[0]);
                        dateAndTimeMeasure.append(minute[1]);

                        char otherStuff_2[2];                       //channel offset
                        file.read (otherStuff_2, sizeof(otherStuff_2));

                        unsigned short channelsNumber;
                        file.read (reinterpret_cast<char*>(&channelsNumber), sizeof(channelsNumber));
                        cout<<"Number of channels: "<<channelsNumber<<endl;
                        chNum = (int)channelsNumber;
                        char channels[chNum*4];
                        file.read (channels, sizeof(channels));
                        char otherStuff_1[4];
                        file.read(otherStuff_1, sizeof(otherStuff_1));
                        file.read(reinterpret_cast<char*>(&caliIntercept), sizeof(caliIntercept));
                        file.read(reinterpret_cast<char*>(&caliSlope), sizeof(caliSlope));
                        cout<<"Calibration: "<<caliSlope<<" x Bin + "<<caliIntercept<<endl;
                        file.close();
        }
        ifstream fileAgain (histoFileName.toUtf8().constData(), ios::in|ios::binary);
        if(fileAgain.is_open()){
            char stuff[32];
            fileAgain.read (stuff, sizeof(stuff));
            for(int i = 0; i <chNum; i++){
                int temp;
                float floatTemp; 
                fileAgain.read(reinterpret_cast<char*>(&temp), sizeof(int));

                vettoreValori.push_back(temp);          //AGGIUNTA MAFFE
                origHistoVector.append(QwtIntervalSample( temp, calibrateBin(i), calibrateBin(i+1)));
                histoVector.append(QwtIntervalSample( temp, calibrateBin(i), calibrateBin(i+1)));
                if (temp == 0) {
                    floatTemp = 0.1;
                } else {
                    floatTemp = (float)temp;
                }
                logHistoVector.append(QwtIntervalSample( floatTemp, calibrateBin(i), calibrateBin(i+1)));
            }
            fileAgain.close();

        }
    } else if (type=="tas"){
        int counter=0;
        ifstream file (histoFileName.toUtf8().constData(), ios::in|ios::binary);
        if(file.is_open()){
            while(!file.eof()) {
                //4 char = 1 float
                char stuff[4];
                file.read (stuff, sizeof(stuff));
                float chNumberTemp;
                file.read (reinterpret_cast<char*>(&chNumberTemp), sizeof(chNumberTemp));
                chNum = chNumberTemp;
                char otherStuff_1[16*4];
                file.read(otherStuff_1, sizeof(otherStuff_1));
                float liveTimeTemp;
                file.read (reinterpret_cast<char*>(&liveTimeTemp), sizeof(liveTimeTemp));
                liveTime = (int)liveTimeTemp;
                char otherStuff[5*4];
                file.read(otherStuff, sizeof(otherStuff));
                file.read(reinterpret_cast<char*>(&caliIntercept), sizeof(caliIntercept));
                file.read(reinterpret_cast<char*>(&caliSlope), sizeof(caliSlope));
                cout<<"Number of channels: "<<chNum<<endl;
                cout<<"Live time: "<<liveTime<<endl;
                cout<<"Calibration: "<<caliSlope<<" x Bin + "<<caliIntercept<<endl;
                char otherStuff_2[104*4];
                file.read(otherStuff_2, sizeof(otherStuff_2));
                for(int i = 0; i <chNum; i++){
                    float temp;
                    float floatTemp; 
                    file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                    origHistoVector.append(QwtIntervalSample( temp, calibrateBin(i), calibrateBin(i+1)));
                    histoVector.append(QwtIntervalSample( temp, calibrateBin(i), calibrateBin(i+1)));
                    if (temp == 0) {
                        floatTemp = 0.1;
                    } else {
                        floatTemp = (float)temp;
                    }
                    logHistoVector.append(QwtIntervalSample( floatTemp, calibrateBin(i), calibrateBin(i+1)));
                }
                file.close();
                if(counter==spectrumNumber) break;
                else counter++;
            }
        }
    }
}

void Spectrum::rebinning(int newBinFactor){

    histoVector.clear();
    binFactor=newBinFactor;

    for(int i=0; i<origHistoVector.size();){
        double minVal = origHistoVector.at(i).interval.minValue();
        double maxVal = origHistoVector.at(i).interval.maxValue();
        double tempVal= origHistoVector.at(i).value;
        for(int k=1; k<binFactor; k++){
            if((i+k)<=origHistoVector.size()-1){
                maxVal = origHistoVector.at(i+k).interval.maxValue();
                tempVal += origHistoVector.at(i+k).value;
            }
        }
        histoVector.append(QwtIntervalSample( tempVal, minVal, maxVal));
        i+=binFactor;
    }
    binStep = histoVector.at(0).interval.width();
    minValue = histoVector.at(0).interval.minValue();
    chNum = histoVector.size();
}

void Spectrum::recalibrate(){

    int n = calibrationVect.size();
    Double_t x[n], y[n];
    for (int i=0; i<n; i++) {
        x[i] = calibrationVect.at(i).first;
        y[i] = calibrationVect.at(i).second;
    }
    TGraph *calGraph = new TGraph(n, x, y);
    TF1 *fit = new TF1("fit","[0]*x + [1]");
    calGraph->Fit("fit");
    cout<<fit->GetParameter(0)<<" "<<fit->GetParameter(1)<<endl;
    caliSlope = fit->GetParameter(0);
    caliIntercept = fit->GetParameter(1);
    histoVector.clear();
    for (int j=0; j<chNum; j++) {
        int tempValue = origHistoVector.at(j).value;
        histoVector.append(QwtIntervalSample( tempValue, calibrateBin(j), calibrateBin(j+1)));
    }
    binStep = histoVector.at(0).interval.width();
    minValue = histoVector.at(0).interval.minValue();
}

// void Spectrum::peakId(QString destinazione) {
//     cout<<"INIZIO peakID() !!!"<<endl;
//     cout<<vettoreValori.size()<<" lunghezza del vettore che contiene l'istogramma"<<endl;

//     int Z=5;
//     int W=5;
//     int gamma=8;
//     double epsilon=1.22;
//     int weights[23] = {1, 3, 6, 10, 15, 16, 13, 6, -5, -20, -29, -32, -29, -20, -5, 6, 13, 16, 15, 10, 6, 3, 1};
//     vector<double> s;
//     vector<double> f;
//     int n1, n2, n3, n1_max, n1_min, n2_max, n2_min, n3_max, n3_min;
//     vector<double> peakVector;
//     int t;
//     //QString destinazione;
//     //QString destinazione_file;


//     //t = Spectrum::histoFileName.lastIndexOf("/");
//     //destinazione = histoFileName.left(t+1);
//     //cout<<destinazione.toStdString() <<endl;
//     //cout<<fileName.toStdString() <<endl;
//     //destinazione_file = destinazione + fileName;
//     //cout<<destinazione_file.toStdString()<<endl;



//    for (int i=0; i<vettoreValori.size(); i++)  {                    //VETTORE DELLE DERIVTATE SECONDE INIZIALE
//         if (i==0) {                         //Bin iniziale, riempito con 0
//             s.push_back(0);
//             continue;
//         }
//         if (i==vettoreValori.size()-1) {    //Bin finale, riempito con i conteggi del bin finale
//             s.push_back(0);
//             continue;
//         }
//         s.push_back(vettoreValori.at(i+1)-2*vettoreValori.at(i)+vettoreValori.at(i-1) );

//    }

//    for (int k=0; k<Z; k++)  {                                       //Z VOLTE SMUSSAMENTO DERIVATA SECONDA S
//         for (int i=0; i<s.size(); i++)   {
//             if (i>=6 && i<=s.size()-6)   s.at(i)=(s.at(i-2)+s.at(i-1)+s.at(i)+s.at(i+1)+s.at(i+2))/W;
//         }
//    }


//    for (int i=0; i<11; i++) f.push_back(0);                         //VETTORE DEVIAZIONI STANDARD F
//    for (int i=11; i<vettoreValori.size()-11; i++)   {
//         int sommatoria = 0;
//         int indice_weights = 0;

//         for (int j=i-11; j<=i+11; j++) {

//                 sommatoria = sommatoria + pow((weights[indice_weights]), 2)*vettoreValori.at(j);
//                 //cout<<"j: "<<j<<" peso: "<<weights[indice_weights]<<" conteggi: "<<vettoreValori.at(j)<<" sommatoria: "<<sommatoria<<endl;
//                 indice_weights++;
//         }

//         f.push_back(sqrt(sommatoria/(5220.)));
//         indice_weights = 0;
//         //cout<<sommatoria<<endl;
//         //cout<<"bin: "<<i<<" sommatoria: "<<sommatoria<<endl;
//     }
//     for (int i=vettoreValori.size()-11; i<vettoreValori.size(); i++)    f.push_back(0);

//     n1 = int(1.22*gamma+0.5);
//     cout<<"n1: "<<n1<<endl;

//     n1_min = n1-epsilon;
//     n1_max = n1+epsilon;

//     n2_min = int(0.5*(n1-epsilon)+0.5);
//     n2_max = int(0.5*(n1+epsilon)+0.5);
//     cout<<"n2_min: "<<n2_min<<endl;
//     cout<<"n2_max: "<<n2_max<<endl;

//     n3_min = int(fabs((n1-epsilon)*(1-2)+0.5));
//     n3_max = int(fabs((n1+epsilon)*(1-2)+0.5));
//     cout<<"n3_min: "<<n3_min<<endl;
//     cout<<"n3_max: "<<n3_max<<endl;

//     /*for (int i=0; i<f.size(); i++)  {
//         cout<<f.at(i)<<endl;
//     }*/

//     /*for (int i=0; i<s.size(); i++)  {           //PRIMISSIMA APPROSSIMZIONE
//         if  (fabs(s.at(i))>0.1*f.at(i)) {
//             cout<<"picco! "<<"canale: "<<i<<" energia: "<<caliSlope*i+caliIntercept<<endl;
//         }
//     }*/

//     /*TH1F *h1;                       //FIT DI PROVA-------------------
//     h1= new TH1F("prova","prova", vettoreValori.size(), 0, vettoreValori.size()+1);
//     for (int j=0; j<vettoreValori.size(); j++)	{
//         h1->SetBinContent(j+1, vettoreValori.at(j));
//     }

//     TF1 * fit = new TF1 ("gaussianaFondo", "gaus(0) + pol1(3)");
//     //fit->SetParameter(0, 100);
//     fit->SetParameter(1, 3600);
//     fit->SetParameter(2, 2);
//     fit->SetParLimits(0,0, 1000);
//     fit->SetParLimits(2,0, 100);
//     h1->Fit(fit, "", "", 3500, 3700);       //---------------------------------
//     cout<<"PICCO FITTATO "<<fit->GetParameter(1)*caliSlope+caliIntercept<<endl;*/

//     /*int trova (int x, int y)  {
//         int min;
//         min = x;
//         for (int i=x; i<y; i++) {
//             if (s.at(i)<min)    min=i;
//         }
//         return min;
//     }*/



//     int M;                                    //CICLO CONDIZIONI PER TROVARE I PICCHI
//     int i1, i2, i3, i4, i5;
//     double i0;
//     for (int i=120; i<16000; i++)  {

//         if (s.at(i) > f.at(i))  M=1;
//         else {
//                 if (s.at(i)>0)  M=2;
//                 else M=3;
//         }

//         if (s.at(i-1) > f.at(i-1))    {
//             if (M==1)    continue;
//             if (M==2)   {
//                 i2=i-1;
//                 //cout<<"i2: "<<i2<<endl;
//             }
//             if (M==3)    {
//                 i3=i;
//                 //cout<<"i3: "<<i3<<endl;
//                 i2=i-1;
//                 //cout<<"i2: "<<i2<<endl;
//                 continue;
//             }
//         }
//         else    {
//             if (s.at(i-1)>0)    {
//                 if (M==1)   {
//                     i1=i;
//                     //cout<<"i1: "<<i1<<endl;
//                 }
//                 if (M==2)    continue;
//                 if (M==3)   {
//                     i3=i;
//                     //cout<<"i3: "<<i3<<endl;
//                 }
//             }
//             else    {
//                 if (M==3)   continue;
//                 if (M==1 || M==2)   {
//                     i5=i-1;
//                     //cout<<"i5: "<<i5<<endl;

//                     int min=i3;
//                     for (int j=i3; j<i5; j++)   {
//                         if (s.at(j)<s.at(min))   min=j;
//                     }
//                     i4=min;
//                     //cout<<"i4: "<<i4<<endl;

//                     double sommatoria = 0;
//                     double produttoria = 0;
//                     for (int k=i3; k<i5; k++)   {
//                         produttoria = produttoria + k*s.at(k);
//                         sommatoria = sommatoria + s.at(k);
//                     }
//                     i0 = produttoria/sommatoria;
//                     //cout<<"i0: "<<i0<<endl;

//                     if (fabs(s.at(i4)) > 0.05*f.at(i4) )    {       //&& fabs(i5-i3+1-n1)<epsilon
//                         peakVector.push_back(i0);
//                         cout<<"i0!!!: "<<i0*caliSlope+caliIntercept<<endl;
//                     }
//                 }
//             }
//         }


//     }

//     ofstream punt(destinazione.toStdString().c_str());
//     punt << "Mean" <<"	"<<"Mean Err"<<"	"<<"FWHM"<<"    "<<"FWHM Err"<<"    "<<"NET Area"<<"    "<<"NET Area Err"<<"    "<<"Counts/s"<<"    "<<"Counts/s Err"<<endl;
//     double ampiezzaBin = (chNum*caliSlope+caliIntercept)/chNum;
//     for (int i=0; i<peakVector.size(); i++) {

//         TH1F *histoPicco;
//         histoPicco= new TH1F("prova","prova", vettoreValori.size(), 0, vettoreValori.size()+1);
//         for (int j=0; j<vettoreValori.size(); j++)	{
//             histoPicco->SetBinContent(j+1, vettoreValori.at(j));
//         }     

//         if (i==peakVector.size()-1 || peakVector.at(i+1)-peakVector.at(i) > 3*gamma)  {                                                   // GAUSSIANA SINGOLA
//             //punt<<"picco"<<"    "<<peakVector.at(i)*caliSlope+caliIntercept<<endl;
//             TF1 * singleGaus = new TF1 ("gaussianaFondo", "gaus(0) + pol1(3)");
//             //singleGaus->SetParameter(0, vettoreValori.at(i0));
//             singleGaus->SetParameter(1, peakVector.at(i));
//             singleGaus->SetParameter(2, gamma);
//             //singleGaus->SetParameter(0, vettoreValori.at(peakVector.at(i)) - vettoreValori.at(peakVector.at(i)-3*gamma));
//             //singleGaus->SetParLimits(0,0, vettoreValori.at(peakVector.at(i)));
//             //singleGaus->SetParLimits(1, peakVector.at(i)-30, peakVector.at(i)+30);
//             singleGaus->SetParLimits(2,0, 50);
//             histoPicco->Fit(singleGaus, "", "", peakVector.at(i)-3*gamma, peakVector.at(i)+3*gamma);
//             //cout<<"3gamma: "<<3*gamma*caliSlope<<endl;

//             double amp = singleGaus->GetParameter(0);
//             double ampErr = singleGaus->GetParError(0);
//             double mean = singleGaus->GetParameter(1)*caliSlope+caliIntercept;
//             double meanErr = singleGaus->GetParError(1)*caliSlope;
//             double sigma = singleGaus->GetParameter(2)*caliSlope;
//             double sigmaErr = singleGaus->GetParError(2)*caliSlope;
//             double FWHM = 2.355*sigma;
//             double FWHMErr = 2.355*sigmaErr;
//             double netArea = (int)(amp*sigma*sqrt(2*3.1416)/ampiezzaBin);
//             double netAreaErr = (int)((sqrt(2*3.1416)*sqrt(sigma*sigma*ampErr*ampErr+amp*amp*sigmaErr*sigmaErr))/ampiezzaBin);
//             double activity = netArea/liveTime;
//             double activityErr = netAreaErr/liveTime;

//             if (FWHM>FWHMErr && netArea>netAreaErr && netArea>0)    {
//                 punt<<mean<<"    "<<meanErr<<"    "<<FWHM<<"    "<<FWHMErr<<"  "<<netArea<<"    "<<netAreaErr<<"    "<<activity<<"  "<<activityErr<<endl;
//             }
//         }

//         else    {                                                                               //GAUSSIANA DOPPIA
//             //punt<<peakVector.at(i)*caliSlope+caliIntercept<<"   "<<peakVector.at(i+1)*caliSlope+caliIntercept<<endl;
//             TF1 * doubleGaus = new TF1 ("doppiaGaussiana", "gaus(0) + gaus(3) + pol1(6)");
//             doubleGaus->SetParameter(1, peakVector.at(i));
//             doubleGaus->SetParameter(4, peakVector.at(i+1));
//             doubleGaus->SetParameter(2, gamma);
//             doubleGaus->SetParameter(5, gamma);
//             //doubleGaus->SetParameter(0, vettoreValori.at(peakVector.at(i)) - vettoreValori.at(peakVector.at(i)-1.6*gamma));
//             //doubleGaus->SetParameter(3, vettoreValori.at(peakVector.at(i+1)) - vettoreValori.at(peakVector.at(i+1)+1.6*gamma));
//             //doubleGaus->SetParLimits(2,0, 50);
//             //doubleGaus->SetParLimits(5,0, 50);
//             histoPicco->Fit(doubleGaus, "", "", peakVector.at(i)-1.6*gamma, peakVector.at(i+1)+1.6*gamma);

//             double amp1 = doubleGaus->GetParameter(0);
//             double ampErr1 = doubleGaus->GetParError(0);
//             double mean1 = doubleGaus->GetParameter(1)*caliSlope+caliIntercept;
//             double meanErr1 = doubleGaus->GetParError(1)*caliSlope;
//             double sigma1 = doubleGaus->GetParameter(2)*caliSlope;
//             double sigmaErr1 = doubleGaus->GetParError(2)*caliSlope;
//             double FWHM1 = 2.355*sigma1;
//             double FWHMErr1 = 2.355*sigmaErr1;
//             double netArea1 = (int)(amp1*sigma1*sqrt(2*3.1416)/ampiezzaBin);
//             double netAreaErr1 = (int)((sqrt(2*3.1416)*sqrt(sigma1*sigma1*ampErr1*ampErr1+amp1*amp1*sigmaErr1*sigmaErr1))/ampiezzaBin);
//             double activity1 = netArea1/liveTime;
//             double activityErr1 = netAreaErr1/liveTime;

//             double amp2 = doubleGaus->GetParameter(3);
//             double ampErr2 = doubleGaus->GetParError(3);
//             double mean2 = doubleGaus->GetParameter(4)*caliSlope+caliIntercept;
//             double meanErr2 = doubleGaus->GetParError(4)*caliSlope;
//             double sigma2 = doubleGaus->GetParameter(5)*caliSlope;
//             double sigmaErr2 = doubleGaus->GetParError(5)*caliSlope;
//             double FWHM2 = 2.355*sigma2;
//             double FWHMErr2 = 2.355*sigmaErr2;
//             double netArea2 = (int)(amp2*sigma2*sqrt(2*3.1416)/ampiezzaBin);
//             double netAreaErr2 = (int)((sqrt(2*3.1416)*sqrt(sigma2*sigma2*ampErr2*ampErr2+amp2*amp2*sigmaErr2*sigmaErr2))/ampiezzaBin);
//             double activity2 = netArea2/liveTime;
//             double activityErr2 = netAreaErr2/liveTime;

//             if (FWHM1 > FWHMErr1 && netArea1 > netAreaErr1 && netArea1 > 0)    {
//                 punt<<mean1<<"    "<<meanErr1<<"    "<<FWHM1<<"    "<<FWHMErr1<<"  "<<netArea1<<"    "<<netAreaErr1<<"    "<<activity1<<"  "<<activityErr1<<"  DOPPIA!"<<endl;
//             }
//             if (FWHM2 > FWHMErr2 && netArea2 > netAreaErr2 && netArea2 > 0)    {
//                 punt<<mean2<<"    "<<meanErr2<<"    "<<FWHM2<<"    "<<FWHMErr2<<"  "<<netArea2<<"    "<<netAreaErr2<<"    "<<activity2<<"  "<<activityErr2<<"  DOPPIA!"<<endl;
//             }
//             ++i;
//         }


//     }
//     punt.close();




//     cout<<"FINE peakID() !!!"<<endl;
// }

//CLASS PEAK
void Peak::calculateNetArea(){

    netArea = (int)(amp*sigma*sqrt(2*3.1416))/binWidth;
    netAreaErr = (int)(sqrt(2*3.1416)*sqrt(sigma*sigma*ampErr*ampErr+amp*amp*sigmaErr*sigmaErr))/binWidth;
}

void Peak::calculateFWHM(){

    FWHM = 2.355*sigma;
    FWHMErr = 2.355*sigmaErr;
}

void Peak::isItBad(){

    if(FWHMErr>FWHM) badPeak=true;
    if(netAreaErr>netArea) badPeak=true;

}


//CLASS MARKERSANDFIT
void MarkersAndFits::setFitInterval(QVector<QwtIntervalSample> histoVector){

    Double_t leftValue = tempMarkersVector.at(0)->xValue();
    Double_t rightValue = tempMarkersVector.at(1)->xValue();
    if (leftValue>rightValue) {
        Double_t tempValue = leftValue;
        leftValue = rightValue;
        rightValue = tempValue;
    }

    int leftCell = (int)((leftValue-histoVector.at(0).interval.minValue())/histoVector.at(0).interval.width());
    int rightCell = (int)((rightValue-histoVector.at(0).interval.minValue())/histoVector.at(0).interval.width());
    fitIntervalHisto.clear();
    for(int i = leftCell; i<=rightCell; i++){
        fitIntervalHisto.push_back(histoVector.at(i));
    }

}

void MarkersAndFits::fit(bool chiSquare, int whichBg){

    int numberOfBins = fitIntervalHisto.size();
    Double_t leftValue = fitIntervalHisto.at(0).interval.minValue();
    Double_t rightValue = fitIntervalHisto.at(numberOfBins-1).interval.maxValue();
    double binStep = fitIntervalHisto.at(0).interval.width();
    TH1F *h1 = new TH1F("h1","h1 title",numberOfBins,fitIntervalHisto.at(0).interval.minValue(),fitIntervalHisto.at(fitIntervalHisto.size()-1).interval.maxValue());
    for(int i=0; i< numberOfBins; i++){
        h1->Fill(fitIntervalHisto.at(i).interval.minValue()+binStep/2,fitIntervalHisto.at(i).value);

    }
    double numberOfParams = 0;
    numberOfGaussians = tempMarkersVector.size()-2;
    if(whichBg==0) numberOfParams =2+3*numberOfGaussians+1;
    if(whichBg==1) numberOfParams =3+3*numberOfGaussians+1;
    if(whichBg==2) numberOfParams =4+3*numberOfGaussians+1;

    MyFitFunction *myFit = new MyFitFunction(whichBg,numberOfGaussians);

    func = new TF1("fit",myFit,&MyFitFunction::totalFitFunc ,leftValue,rightValue,numberOfParams);

    if(whichBg==0){
        func->SetParameter(3*numberOfGaussians,(fitIntervalHisto.at(0).value-fitIntervalHisto.at(numberOfBins-1).value)/(leftValue-rightValue));
        func->SetParameter(3*numberOfGaussians+1,fitIntervalHisto.at(0).value-func->GetParameter(3*numberOfGaussians)*leftValue);
    } else if(whichBg==1){
        func->SetParameter(3*numberOfGaussians,0);
        func->SetParameter(3*numberOfGaussians+1,(fitIntervalHisto.at(0).value-fitIntervalHisto.at(numberOfBins-1).value)/(leftValue-rightValue));
        func->SetParameter(3*numberOfGaussians+2,fitIntervalHisto.at(0).value-func->GetParameter(3*numberOfGaussians+1)*leftValue);
    } else if(whichBg==2){
        func->SetParameter(3*numberOfGaussians,-(fitIntervalHisto.at(0).value-fitIntervalHisto.at(numberOfBins-1).value)/2);
        func->SetParameter(3*numberOfGaussians+1,(fitIntervalHisto.at(0).value-fitIntervalHisto.at(numberOfBins-1).value)/(leftValue-rightValue));
        func->SetParameter(3*numberOfGaussians+2,(leftValue+rightValue)/2);
        func->SetParameter(3*numberOfGaussians+3,(fitIntervalHisto.at(0).value+fitIntervalHisto.at(numberOfBins-1).value)/2);
    } else if(whichBg==3){
        cout<<"Not implemented yet"<<endl;
    }

    double maxVal = 0;
    for(int k=0; k< numberOfBins; k++){
        double cellVal = fitIntervalHisto.at(k).value;

        if (cellVal > maxVal) {
            maxVal = cellVal;
        }
    }


    for(int j = 0; j<numberOfGaussians;j++){
        double maxPeak = tempMarkersVector.at(j+2)->yValue()-(fitIntervalHisto.at(0).value+fitIntervalHisto.at(numberOfBins-1).value)/2;
        func->SetParameter(3*j,maxPeak);
        func->SetParameter(3*j+1,tempMarkersVector.at(j+2)->xValue());
        func->SetParameter(3*j+2,1);
        func->SetParLimits(3*j,0,maxVal*1.1);
        func->SetParLimits(3*j+1,tempMarkersVector.at(j+2)->xValue()*0.95,tempMarkersVector.at(j+2)->xValue()*1.05);
        func->SetParLimits(3*j+2,0,100);

    }

    if(chiSquare) h1->Fit("fit");
    else h1->Fit("fit","L");
    double a = func->GetParameter(numberOfGaussians*3);
    double b = func->GetParameter(numberOfGaussians*3+1);
    double c = func->GetParameter(numberOfGaussians*3+2);
    double d = func->GetParameter(numberOfGaussians*3+3);

    QVector<double> xFitSingleGaussTemp;
    singleGaussVector.push_back(xFitSingleGaussTemp);

    for( int i = 0; i < numberOfBins; i++ ){

        xFitVal.push_back((fitIntervalHisto.at(i).interval.minValue()+fitIntervalHisto.at(i).interval.maxValue())/2);
        singleGaussVector.at(0).push_back(xFitVal.at(i));

        if(whichBg==0) yFitValBack.push_back(a*xFitVal.at(i)+b);
        if(whichBg==1) yFitValBack.push_back(a*xFitVal.at(i)*xFitVal.at(i)+b*xFitVal.at(i)+c);
        if(whichBg==2) yFitValBack.push_back(a*atan(xFitVal.at(i)*b+c)+d);
        if(whichBg==3) cout<<"Not implemented yet"<<endl;


        yFitValGauss.push_back(yFitValBack.at(i));
        for(int j = 0; j<numberOfGaussians;j++){
            double con = func->GetParameter(3*j);
            double mean = func->GetParameter(3*j+1);
            double sigma = func->GetParameter(3*j+2);
            double yGauss = (con* TMath::Exp( -(xFitVal.at(i)-mean)*(xFitVal.at(i)-mean)/(2*sigma*sigma)));
            yFitValGauss.replace(i,yFitValGauss.at(i)+yGauss);
            if(i==0) {
                QVector<double> yFitSingleGaussTemp;
                singleGaussVector.push_back(yFitSingleGaussTemp);
            }
            singleGaussVector.at(j+1).push_back(yFitValBack.at(i) + yGauss);
        }

        //calculate difference
        double offset=maxVal*1.05;
        yFitDifference.push_back(fitIntervalHisto.at(i).value-yFitValGauss.at(i)+offset);
        yFitMean.push_back(offset);

    }



    for(int j = 0; j<numberOfGaussians;j++){
        double con = func->GetParameter(3*j);
        double mean = func->GetParameter(3*j+1);
        double sigma = func->GetParameter(3*j+2);
        Peak* peak = new Peak(con, mean, sigma, func->GetParError(3*j), func->GetParError(3*j+1), func->GetParError(3*j+2),binStep);
        peaksVectorTemp.push_back(peak);
    }

    int degreeOfFreedom = numberOfBins-numberOfGaussians*3-3-1;
    redChiSquare = func->GetChisquare()/degreeOfFreedom;

}



void MarkersAndFits::calculateIntegral(){

    int numberOfBins = fitIntervalHisto.size();
    integral=0;
    numberOfGaussians=1;
    for(int i=0; i< numberOfBins; i++){
        integral +=fitIntervalHisto.at(i).value;
        integralHisto.append(fitIntervalHisto.at(i));

        QwtIntervalSample tempInterval = fitIntervalHisto.at(i);
        if (tempInterval.value == 0) tempInterval.value = 0.1;
        logIntegralHisto.append(tempInterval);
    }
}

void MarkersAndFits::clearVectors(){
    /*for(int k = 0; k<tempMarkersVector.size(); k++){
        //prevMarkersVector.append(tempMarkersVector.at(k));
        tempMarkersVector.at(k)->detach();
    }

    tempMarkersVector.clear();*/
    xFitVal.clear();
    yFitValBack.clear();
    yFitValGauss.clear();
    yFitDifference.clear();
    yFitMean.clear();
    integralHisto.clear();
    peaksVectorTemp.clear();
    singleGaussVector.clear();
}



MyDialog::MyDialog(QWidget *parent, int number) : QDialog(parent){
    setModal(true);
    buttonsNumber= number;
    QHBoxLayout *dialogLayout = new QHBoxLayout(this);
    setLayout(dialogLayout);
    for (int i = 0; i < buttonsNumber; i++){
        QPushButton *button = new QPushButton(QString::number ( i,'g',6 ), this);
        button->setCheckable(true);
        dialogLayout->addWidget(button);
        buttonVector.push_back(button);
        connect(button, SIGNAL(clicked()), this, SLOT(accept()));

    }

}

void MyDialog::accept() {

    for(int i = 0; i<buttonVector.size(); i++){
        if(buttonVector.at(i)->isChecked()) selected=i;
    }
    QDialog::accept();
}

