/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionContents;
    QAction *actionLoad_File;
    QAction *actionSave_File;
    QAction *actionQuit;
    QAction *actionManual;
    QAction *actionSup_Spectrum;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLabel *label_11;
    QToolButton *rightButton;
    QToolButton *leftButton;
    QToolButton *fitButton;
    QToolButton *saveFitButton;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_10;
    QToolButton *gaussiansToolButton;
    QToolButton *cancelToolButton;
    QLabel *label_12;
    QTabWidget *tabWidget;
    QWidget *fitOptionsTab;
    QGroupBox *groupBox;
    QRadioButton *chiSquareRadio;
    QRadioButton *maxLikehoodRadio;
    QGroupBox *groupBox_2;
    QRadioButton *linearBgFitRadio;
    QRadioButton *quadraticBgFitRadio;
    QRadioButton *sigmoidBgFitRadio;
    QRadioButton *bestBgFitRadio;
    QWidget *tab_3;
    QLineEdit *calLineEdit;
    QLineEdit *energyLineEdit;
    QPushButton *addCalButton;
    QPushButton *clearCalButton;
    QPushButton *calibrateButton;
    QComboBox *listPointComboBox;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *binFactorBox;
    QToolButton *rebinButton;
    QLabel *label_6;
    QWidget *tab_2;
    QPushButton *clearTableButton;
    QPushButton *printHistoButton;
    QPushButton *saveImageButton;
    QComboBox *comboBoxColor;
    QToolButton *toolButton;
    QLabel *label_5;
    QWidget *tab;
    QLabel *label_23;
    QPushButton *autofitButton;
    QPushButton *pushButton;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QPushButton *firstSpecButton;
    QPushButton *secondSpecButton;
    QLineEdit *timeLineEdit;
    QLabel *label_2;
    QLineEdit *channelsLineEdit;
    QLabel *label_13;
    QLineEdit *realLineEdit;
    QLabel *label_14;
    QLineEdit *dateAndTimeLineEdit;
    QGridLayout *gridLayout_3;
    QwtPlot *histoPlot;
    QTableWidget *tableWidget;
    QScrollBar *histoScrollBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuInfo;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(990, 639);
        actionContents = new QAction(MainWindow);
        actionContents->setObjectName(QStringLiteral("actionContents"));
        actionLoad_File = new QAction(MainWindow);
        actionLoad_File->setObjectName(QStringLiteral("actionLoad_File"));
        actionSave_File = new QAction(MainWindow);
        actionSave_File->setObjectName(QStringLiteral("actionSave_File"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName(QStringLiteral("actionManual"));
        actionSup_Spectrum = new QAction(MainWindow);
        actionSup_Spectrum->setObjectName(QStringLiteral("actionSup_Spectrum"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font;
        font.setPointSize(8);
        label_8->setFont(font);

        gridLayout_2->addWidget(label_8, 2, 2, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 0, 2, 1, 1);

        rightButton = new QToolButton(centralWidget);
        rightButton->setObjectName(QStringLiteral("rightButton"));

        gridLayout_2->addWidget(rightButton, 3, 2, 1, 1);

        leftButton = new QToolButton(centralWidget);
        leftButton->setObjectName(QStringLiteral("leftButton"));

        gridLayout_2->addWidget(leftButton, 3, 0, 1, 1);

        fitButton = new QToolButton(centralWidget);
        fitButton->setObjectName(QStringLiteral("fitButton"));
        fitButton->setCheckable(false);

        gridLayout_2->addWidget(fitButton, 1, 1, 1, 1);

        saveFitButton = new QToolButton(centralWidget);
        saveFitButton->setObjectName(QStringLiteral("saveFitButton"));

        gridLayout_2->addWidget(saveFitButton, 3, 1, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout_2->addWidget(label_7, 2, 1, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setWordWrap(false);
        label_10->setOpenExternalLinks(false);

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        gaussiansToolButton = new QToolButton(centralWidget);
        gaussiansToolButton->setObjectName(QStringLiteral("gaussiansToolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gaussiansToolButton->sizePolicy().hasHeightForWidth());
        gaussiansToolButton->setSizePolicy(sizePolicy);
        gaussiansToolButton->setCheckable(false);

        gridLayout_2->addWidget(gaussiansToolButton, 1, 2, 1, 1);

        cancelToolButton = new QToolButton(centralWidget);
        cancelToolButton->setObjectName(QStringLiteral("cancelToolButton"));

        gridLayout_2->addWidget(cancelToolButton, 1, 0, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font);

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(9);
        tabWidget->setFont(font1);
        fitOptionsTab = new QWidget();
        fitOptionsTab->setObjectName(QStringLiteral("fitOptionsTab"));
        groupBox = new QGroupBox(fitOptionsTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 111, 61));
        chiSquareRadio = new QRadioButton(groupBox);
        chiSquareRadio->setObjectName(QStringLiteral("chiSquareRadio"));
        chiSquareRadio->setGeometry(QRect(0, 20, 97, 21));
        maxLikehoodRadio = new QRadioButton(groupBox);
        maxLikehoodRadio->setObjectName(QStringLiteral("maxLikehoodRadio"));
        maxLikehoodRadio->setGeometry(QRect(0, 40, 111, 21));
        groupBox_2 = new QGroupBox(fitOptionsTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 80, 171, 61));
        linearBgFitRadio = new QRadioButton(groupBox_2);
        linearBgFitRadio->setObjectName(QStringLiteral("linearBgFitRadio"));
        linearBgFitRadio->setGeometry(QRect(0, 20, 97, 21));
        quadraticBgFitRadio = new QRadioButton(groupBox_2);
        quadraticBgFitRadio->setObjectName(QStringLiteral("quadraticBgFitRadio"));
        quadraticBgFitRadio->setGeometry(QRect(0, 40, 97, 21));
        sigmoidBgFitRadio = new QRadioButton(groupBox_2);
        sigmoidBgFitRadio->setObjectName(QStringLiteral("sigmoidBgFitRadio"));
        sigmoidBgFitRadio->setGeometry(QRect(96, 20, 81, 21));
        bestBgFitRadio = new QRadioButton(groupBox_2);
        bestBgFitRadio->setObjectName(QStringLiteral("bestBgFitRadio"));
        bestBgFitRadio->setGeometry(QRect(96, 40, 91, 21));
        tabWidget->addTab(fitOptionsTab, QString());
        groupBox_2->raise();
        groupBox->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        calLineEdit = new QLineEdit(tab_3);
        calLineEdit->setObjectName(QStringLiteral("calLineEdit"));
        calLineEdit->setGeometry(QRect(10, 30, 81, 27));
        energyLineEdit = new QLineEdit(tab_3);
        energyLineEdit->setObjectName(QStringLiteral("energyLineEdit"));
        energyLineEdit->setGeometry(QRect(100, 30, 81, 27));
        addCalButton = new QPushButton(tab_3);
        addCalButton->setObjectName(QStringLiteral("addCalButton"));
        addCalButton->setGeometry(QRect(10, 60, 81, 27));
        clearCalButton = new QPushButton(tab_3);
        clearCalButton->setObjectName(QStringLiteral("clearCalButton"));
        clearCalButton->setGeometry(QRect(50, 120, 99, 27));
        calibrateButton = new QPushButton(tab_3);
        calibrateButton->setObjectName(QStringLiteral("calibrateButton"));
        calibrateButton->setGeometry(QRect(100, 60, 81, 27));
        listPointComboBox = new QComboBox(tab_3);
        listPointComboBox->setObjectName(QStringLiteral("listPointComboBox"));
        listPointComboBox->setGeometry(QRect(10, 90, 171, 27));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 67, 17));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(100, 10, 67, 17));
        binFactorBox = new QSpinBox(tab_3);
        binFactorBox->setObjectName(QStringLiteral("binFactorBox"));
        binFactorBox->setGeometry(QRect(10, 170, 61, 27));
        binFactorBox->setMinimum(1);
        rebinButton = new QToolButton(tab_3);
        rebinButton->setObjectName(QStringLiteral("rebinButton"));
        rebinButton->setGeometry(QRect(80, 170, 22, 25));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 150, 81, 17));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        clearTableButton = new QPushButton(tab_2);
        clearTableButton->setObjectName(QStringLiteral("clearTableButton"));
        clearTableButton->setGeometry(QRect(0, 10, 81, 27));
        printHistoButton = new QPushButton(tab_2);
        printHistoButton->setObjectName(QStringLiteral("printHistoButton"));
        printHistoButton->setGeometry(QRect(90, 10, 81, 27));
        saveImageButton = new QPushButton(tab_2);
        saveImageButton->setObjectName(QStringLiteral("saveImageButton"));
        saveImageButton->setGeometry(QRect(90, 40, 81, 27));
        comboBoxColor = new QComboBox(tab_2);
        comboBoxColor->setObjectName(QStringLiteral("comboBoxColor"));
        comboBoxColor->setGeometry(QRect(0, 90, 111, 24));
        toolButton = new QToolButton(tab_2);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(120, 90, 31, 22));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 70, 67, 17));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_23 = new QLabel(tab);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(20, 10, 241, 51));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        font2.setKerning(true);
        label_23->setFont(font2);
        label_23->setLayoutDirection(Qt::LeftToRight);
        autofitButton = new QPushButton(tab);
        autofitButton->setObjectName(QStringLiteral("autofitButton"));
        autofitButton->setGeometry(QRect(90, 210, 99, 27));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 170, 101, 27));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_7->addWidget(label, 4, 0, 1, 1);

        firstSpecButton = new QPushButton(centralWidget);
        firstSpecButton->setObjectName(QStringLiteral("firstSpecButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(firstSpecButton->sizePolicy().hasHeightForWidth());
        firstSpecButton->setSizePolicy(sizePolicy2);
        firstSpecButton->setCheckable(true);

        gridLayout_7->addWidget(firstSpecButton, 0, 0, 1, 1);

        secondSpecButton = new QPushButton(centralWidget);
        secondSpecButton->setObjectName(QStringLiteral("secondSpecButton"));
        sizePolicy2.setHeightForWidth(secondSpecButton->sizePolicy().hasHeightForWidth());
        secondSpecButton->setSizePolicy(sizePolicy2);
        secondSpecButton->setCheckable(true);

        gridLayout_7->addWidget(secondSpecButton, 0, 1, 1, 1);

        timeLineEdit = new QLineEdit(centralWidget);
        timeLineEdit->setObjectName(QStringLiteral("timeLineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(timeLineEdit->sizePolicy().hasHeightForWidth());
        timeLineEdit->setSizePolicy(sizePolicy3);
        timeLineEdit->setReadOnly(true);

        gridLayout_7->addWidget(timeLineEdit, 2, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_7->addWidget(label_2, 2, 0, 1, 1);

        channelsLineEdit = new QLineEdit(centralWidget);
        channelsLineEdit->setObjectName(QStringLiteral("channelsLineEdit"));
        sizePolicy3.setHeightForWidth(channelsLineEdit->sizePolicy().hasHeightForWidth());
        channelsLineEdit->setSizePolicy(sizePolicy3);
        channelsLineEdit->setReadOnly(true);

        gridLayout_7->addWidget(channelsLineEdit, 4, 1, 1, 1);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_7->addWidget(label_13, 3, 0, 1, 1);

        realLineEdit = new QLineEdit(centralWidget);
        realLineEdit->setObjectName(QStringLiteral("realLineEdit"));
        sizePolicy3.setHeightForWidth(realLineEdit->sizePolicy().hasHeightForWidth());
        realLineEdit->setSizePolicy(sizePolicy3);
        realLineEdit->setReadOnly(true);

        gridLayout_7->addWidget(realLineEdit, 3, 1, 1, 1);

        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_7->addWidget(label_14, 1, 0, 1, 1);

        dateAndTimeLineEdit = new QLineEdit(centralWidget);
        dateAndTimeLineEdit->setObjectName(QStringLiteral("dateAndTimeLineEdit"));
        sizePolicy3.setHeightForWidth(dateAndTimeLineEdit->sizePolicy().hasHeightForWidth());
        dateAndTimeLineEdit->setSizePolicy(sizePolicy3);
        dateAndTimeLineEdit->setReadOnly(true);

        gridLayout_7->addWidget(dateAndTimeLineEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_7);


        gridLayout->addLayout(verticalLayout, 0, 1, 2, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        histoPlot = new QwtPlot(centralWidget);
        histoPlot->setObjectName(QStringLiteral("histoPlot"));
        histoPlot->setMouseTracking(false);

        gridLayout_3->addWidget(histoPlot, 0, 0, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 12)
            tableWidget->setColumnCount(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy4);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(90);

        gridLayout_3->addWidget(tableWidget, 2, 0, 1, 1);

        histoScrollBar = new QScrollBar(centralWidget);
        histoScrollBar->setObjectName(QStringLiteral("histoScrollBar"));
        histoScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(histoScrollBar, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 2, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 990, 25));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QStringLiteral("menuInfo"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuInfo->addAction(actionContents);
        menuInfo->addAction(actionManual);
        menuFile->addAction(actionLoad_File);
        menuFile->addAction(actionSup_Spectrum);
        menuFile->addAction(actionSave_File);
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionContents->setText(QApplication::translate("MainWindow", "Contents", Q_NULLPTR));
        actionLoad_File->setText(QApplication::translate("MainWindow", "Load File", Q_NULLPTR));
        actionSave_File->setText(QApplication::translate("MainWindow", "Save File", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionManual->setText(QApplication::translate("MainWindow", "Manual", Q_NULLPTR));
        actionSup_Spectrum->setText(QApplication::translate("MainWindow", "Sup. Spectrum", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Move right", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Show Gauss", Q_NULLPTR));
        rightButton->setText(QApplication::translate("MainWindow", "D", Q_NULLPTR));
        leftButton->setText(QApplication::translate("MainWindow", "A", Q_NULLPTR));
        fitButton->setText(QApplication::translate("MainWindow", "W", Q_NULLPTR));
        saveFitButton->setText(QApplication::translate("MainWindow", "S", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Move left", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Save fit", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Fit", Q_NULLPTR));
        gaussiansToolButton->setText(QApplication::translate("MainWindow", "E", Q_NULLPTR));
        cancelToolButton->setText(QApplication::translate("MainWindow", "Q", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Cancel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Fit Method", Q_NULLPTR));
        chiSquareRadio->setText(QApplication::translate("MainWindow", "ChiSquare", Q_NULLPTR));
        maxLikehoodRadio->setText(QApplication::translate("MainWindow", "MaxLikelihood", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Background Fit", Q_NULLPTR));
        linearBgFitRadio->setText(QApplication::translate("MainWindow", "Linear", Q_NULLPTR));
        quadraticBgFitRadio->setText(QApplication::translate("MainWindow", "Quadratic", Q_NULLPTR));
        sigmoidBgFitRadio->setText(QApplication::translate("MainWindow", "Sigmoid", Q_NULLPTR));
        bestBgFitRadio->setText(QApplication::translate("MainWindow", "Best", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(fitOptionsTab), QApplication::translate("MainWindow", "Fit Options", Q_NULLPTR));
        addCalButton->setText(QApplication::translate("MainWindow", "Add Point", Q_NULLPTR));
        clearCalButton->setText(QApplication::translate("MainWindow", "Clear All", Q_NULLPTR));
        calibrateButton->setText(QApplication::translate("MainWindow", "Calibrate", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Channel", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Energy ", Q_NULLPTR));
        rebinButton->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Rebinning", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Calibrate", Q_NULLPTR));
        clearTableButton->setText(QApplication::translate("MainWindow", "Clear Table", Q_NULLPTR));
        printHistoButton->setText(QApplication::translate("MainWindow", "Print Histo", Q_NULLPTR));
        saveImageButton->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        comboBoxColor->clear();
        comboBoxColor->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Background", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Histogram", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Peak Fit", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Background Fit", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Integral", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Vertical Bars", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Cursor", Q_NULLPTR)
        );
        toolButton->setText(QApplication::translate("MainWindow", "C", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Colors", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "BETA Version by Maffe\n"
"\n"
" (Only for 16000 channel ADCs)", Q_NULLPTR));
        autofitButton->setText(QApplication::translate("MainWindow", "AUTOFIT !", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Online Libraries", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Autofit", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Number of channels", Q_NULLPTR));
        firstSpecButton->setText(QApplication::translate("MainWindow", "First", Q_NULLPTR));
        secondSpecButton->setText(QApplication::translate("MainWindow", "Second", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Live Time (s)", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Real Time (s)", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Date & Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Mean", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Mean Err", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "FWHM", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "FWHM Err", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Net Area", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Net Area Err", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Counts/s", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Count/s Err", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Red Chi Sqr", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "Bg Fit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Spectr Num.", Q_NULLPTR));
        menuInfo->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
