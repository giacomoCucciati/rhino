#include <QApplication>
#include <TApplication.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    TApplication theApp("App", &argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
