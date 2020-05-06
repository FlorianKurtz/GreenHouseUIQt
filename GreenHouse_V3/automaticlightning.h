#ifndef AUTOMATICLIGHTNING_H
#define AUTOMATICLIGHTNING_H

#include <QtCore>
#include <QThread>
#include "gpio.h"


class automaticLightning : public QObject
{
    Q_OBJECT
public:
    explicit automaticLightning();
    automaticLightning(int,int);
    ~automaticLightning();

     GPIO *Lightning ;
    int aubeTime, crepusculeTime ;
    void checkLightning() ;
    void doWork();
    bool flag = false ;

signals:

public slots:
};

#endif // AUTOMATICLIGHTNING_H
