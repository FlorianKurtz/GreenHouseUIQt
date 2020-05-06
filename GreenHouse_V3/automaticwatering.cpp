#include "automaticwatering.h"

#define authorizedStartTime 8
#define authorizedBandTime 12
#define wateringLongTime 10

#define WATERING_PORT 23

automaticWatering::automaticWatering()
{
    this->currentHumidity = new QString("50");
    this->Watering = new GPIO();
    this->Watering->setPort(WATERING_PORT) ;
}

automaticWatering::automaticWatering(int wateringPerDay)
{
    this->currentHumidity = new QString("50");
    this->wateringPerDay = wateringPerDay ;
    this->optimalHumidity =  wateringPerDay ;
    this->Watering = new GPIO();
    this->Watering->setPort(WATERING_PORT) ;
}

automaticWatering::~automaticWatering()
{

}

void automaticWatering::doWork()
{
    QDate firstDate = QDate::currentDate();
    while(this->flag)
    {
        qDebug("automaticWatering launched");
        // Waiting 1h
        QThread::sleep(10);
        // Humidity control
        checkWateringByHum();
        // Time control
        checkWateringByTime(firstDate);
    }
}

void automaticWatering::checkWateringByTime(QDate firstDate)
{
    qDebug("checkingWateringByTime");
    qDebug("automaticWatering : %d per day",this->wateringPerDay);
    // TIME CONTROLLING
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();
    if((firstDate.dayOfWeek() != currentDate.dayOfWeek()))
    {
        qDebug("New watering day");
        firstDate = currentDate ;
        this->wateringCounter = 0 ;
    }
    else
    {
        int intervalTime =    authorizedBandTime/this->wateringPerDay ;
        int wateringTime = authorizedStartTime + intervalTime*(this->wateringCounter + 1);

        if(currentTime.hour() == wateringTime)
        {
            qDebug("Watering");
            this->wateringCounter++;
            this->Watering->enablePort();
            QThread::sleep(wateringLongTime);
            this->Watering->disablePort();
        }
    }

}

void automaticWatering::checkWateringByHum()
{
    qDebug("checkingWateringByHum");

    // Humidity percentage control
    float currentIntHumidity = this->currentHumidity->toFloat() ;
    if((currentIntHumidity < 100) && (currentIntHumidity > 0))
    {
        qDebug("automaticWatering launched : %d",this->optimalHumidity);

        int minimumHumidity ;
        minimumHumidity = this->optimalHumidity - 5 ;


        qDebug("minimumHumidity : %d",minimumHumidity);
        qDebug("current humidity : %f",currentIntHumidity);

        if(currentIntHumidity<minimumHumidity)
        {
            qDebug("Watering");
            this->wateringCounter++;
            this->Watering->enablePort();
            QThread::sleep(wateringLongTime);
            this->Watering->disablePort();
        }
    }
}
