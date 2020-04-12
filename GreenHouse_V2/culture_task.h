#ifndef CULTURE_TASK_H
#define CULTURE_TASK_H

#include <QDate>
#include <QThread>
#include <QTime>

#include <iostream>

#include "plant.h"

class culture_task : public QThread
{
    Q_OBJECT
public:
    explicit culture_task(void);
    // overriding the QThread's run() method
    void run();
    double getTemp(void);
    double getHum(void);
    void control(void);
    plant *actualPlant ;

    QDate *actualDate ;
    QDate *endGrowingDate ;
    QDate *endFloweringDate ;

    QTime *actualTime ;

    void watering(void);
    void heating(void);
    void fan(void);
    void lightning(void);

    int mode_watering = 0;
    int mode_heating = 0;
    int mode_fan = 0;
    int mode_lightning = 0;

    double actualTemp ;
    double actualHum ;

private :


public slots :
    void get_plant(plant*);
    void get_mode_watering(int); // 0 = OFF // 1 = ON // 2 = AUTO
    void get_mode_heating(int); // 0 = OFF // 1 = ON // 2 = AUTO
    void get_mode_fan(int); // 0 = OFF // 1 = ON // 2 = AUTO
    void get_mode_lightning(int); // 0 = OFF // 1 = ON // 2 = AUTO

signals :
    void send_refresh(void);

};

#endif // CULTURE_TASK_H
