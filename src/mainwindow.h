#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFont>
#include <QMainWindow>
#include "spectrum.h"
#include <qwt_plot_histogram.h>
#include <TH1F.h>
#include <qwt_plot_curve.h>
#include <QTableWidgetItem>
#include "qwt_plot_zoomer.h"
#include "qwt_picker.h"
#include "qwt_picker_machine.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    //MY VARIABLES
    Spectrum *firstSpectrum;
    Spectrum *secondSpectrum;
    Spectrum *selectedSpectrum;

    QwtPlotHistogram* histogramFirst;
    QwtPlotHistogram* histogramSecond;
    QwtPlotHistogram* integralFit;
    QwtPlotCurve* gaussianFit;
    QwtPlotCurve* backgroundFit;
    QwtPlotCurve* differenceFit;
    QwtPlotCurve* differenceLine;
    vector<QwtPlotCurve*> singleGaussCurveVector;
    MyZoomer *zoomer;
    QwtPickerClickPointMachine *m_picker;
    MyPicker *d_picker;

    MarkersAndFits* myMarkersAndFits;
    int histoScrollBarMaxLength;
    QString pathName;
    bool isLogScaleActive;
    bool useLastSigma;
    float baseValueLinLogScale;
    //MY METHODS
    void showSpectrumInHistoPlot();
    void initializeAll();
    void setEnabledConsole(bool enable);
    int readTasFile(QString histoFileNameNew);
    int getBgChosen();
private slots:

    void modifyScrollOnZoom(QRectF rectangle);

    void modifyHistoOnScroll(int value);
    int findMaxInWindow();
    int findMinInWindow();

    void catchPointSelected(const QPointF &pos );
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void fillTable(string entryType);

    void on_fitButton_clicked();

    void on_leftButton_pressed();

    void on_rightButton_pressed();

    void on_saveFitButton_clicked();


    void on_rebinButton_clicked();

    void on_printHistoButton_clicked();

    void on_toolButton_clicked();

    void on_clearTableButton_clicked();

    void on_logScaleButton_clicked();

    void on_saveImageButton_clicked();

    void on_addCalButton_clicked();

    void on_calibrateButton_clicked();

    void on_clearCalButton_clicked();

    void on_actionContents_triggered();

    void on_gaussiansToolButton_clicked();

    void on_actionLoad_File_triggered();

    void on_actionQuit_triggered();

    void on_actionSave_File_triggered();

    void on_actionManual_triggered();

    void on_cancelToolButton_clicked();

    void on_actionSup_Spectrum_triggered();

    void on_firstSpecButton_clicked(bool checked);

    void on_secondSpecButton_clicked(bool checked);

    void printSpectrumData();
    
    //void on_autofitButton_clicked();

    // void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
