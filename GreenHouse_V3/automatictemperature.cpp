#include "automatictemperature.h"

#define HEATER_PORT 24
#define FANING_PORT 27

automaticTemperature::automaticTemperature()
{
    // Create GPIOs
    // Setup GPIOS
    this->Heater = new GPIO();
    this->Faning = new GPIO();

    this->Heater->setPort(HEATER_PORT) ;
    this->Faning->setPort(FANING_PORT) ;

    this->currentTemperature = new QString("20");
}

automaticTemperature::automaticTemperature(int optimalTemperature)
{
    this->optimalTemperature = optimalTemperature ;
    // Create GPIOs
    // Setup GPIOS
    this->Heater = new GPIO();
    this->Faning = new GPIO();

    this->Heater->setPort(HEATER_PORT) ;
    this->Faning->setPort(FANING_PORT) ;

    this->currentTemperature = new QString("20");
}

automaticTemperature::~automaticTemperature()
{

}

void automaticTemperature::checkTemperature()
{
    qDebug("checkingTemperature");
    int minimumTemperature, maximumTemperature ;
    float currentIntTemperature ;
    minimumTemperature = this->optimalTemperature - 1 ;
    maximumTemperature = this->optimalTemperature + 1 ;
    currentIntTemperature = this->currentTemperature->toFloat() ;

    qDebug("minimumTemperature : %d",minimumTemperature);
    qDebug("maximumTemperature : %d",maximumTemperature);
    qDebug("current temperature : %f",currentIntTemperature);

    if(currentIntTemperature>maximumTemperature)
    {
        qDebug("Faning");
        this->Faning->enablePort();
        this->Heater->disablePort();
    }
    else if(currentIntTemperature<minimumTemperature)
    {
        qDebug("Heating");
        this->Faning->disablePort();
        this->Heater->enablePort();
    }
    else
    {
        qDebug("Automatic temperature resting");
        this->Faning->disablePort();
        this->Heater->disablePort();
    }
}

void automaticTemperature::doWork()
{
    while(this->flag)
    {
        // Waiting 1h
        qDebug("automaticTemperature at %d°C", this->optimalTemperature );
        QThread::sleep(10);
        checkTemperature();
    }
}
