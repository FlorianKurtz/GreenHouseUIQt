#ifndef AUTOMATICTEMPERATURE_H
#define AUTOMATICTEMPERATURE_H

#include <QtCore>
#include <QThread>
#include "gpio.h"

class automaticTemperature : public QObject
{
    Q_OBJECT
public:
    explicit automaticTemperature();
    automaticTemperature(int);
    ~automaticTemperature();

    GPIO *Heater, *Faning ;
    QString *currentTemperature ;
    bool flag = false ;
    int optimalTemperature ;
    void doWork();
    void checkTemperature() ;

signals:

public slots:

};

#endif // AUTOMATICTEMPERATURE_H
