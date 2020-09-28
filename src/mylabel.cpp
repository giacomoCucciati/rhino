#include "mylabel.h"
#include <QMouseEvent>
#include <QDialog>
#include <QGridLayout>

using namespace std;

myLabel::myLabel(QWidget * parent )
:QLabel(parent)
{
}


void myLabel::mouseReleaseEvent( QMouseEvent * event )
{
    if(event->x()>110 && event->x()<130 && event->y()>93 && event->y()<100) {
        QDialog *aboutDialog = new QDialog(this);
        aboutDialog->setWindowTitle("Rhino");
        QGridLayout *gridLayout;
        QLabel *label;
        aboutDialog->setMinimumSize(QSize(400, 70));
        aboutDialog->setMaximumSize(QSize(400, 70));
        gridLayout = new QGridLayout(aboutDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(aboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText("Authors: Giacomo Cucciati & Stefano Pozzi\n\tGreetings to: Lab 4035");
        gridLayout->addWidget(label, 0, 0, 1, 1);
        aboutDialog->exec();


    }
}
