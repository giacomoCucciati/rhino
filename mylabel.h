#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <iostream>


class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget * parent = 0 );
    ~myLabel(){}

protected:
    void mouseReleaseEvent( QMouseEvent * event ) ;

};

#endif // MYLABEL_H
