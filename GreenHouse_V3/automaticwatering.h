#ifndef AUTOMATICWATERING_H
#define AUTOMATICWATERING_H


#include <QtCore>
#include <QDate>
#include <QThread>
#include "gpio.h"

class automaticWatering : public QObject
{
    Q_OBJECT
public:
    explicit automaticWatering();
    automaticWatering(int);
    ~automaticWatering();

    GPIO *Watering;
    QString *currentHumidity ;
    int wateringPerDay ;
    int wateringCounter ;
    int optimalHumidity ;
    void doWork();
    void checkWateringByTime(QDate) ;
    void checkWateringByHum() ;
    bool flag = false ;

signals:

public slots:

};

#endif // AUTOMATICWATERING_H
