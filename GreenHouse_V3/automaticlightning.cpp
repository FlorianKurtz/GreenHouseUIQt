#include "automaticlightning.h"

#define LIGHTNING_PORT 22

automaticLightning::automaticLightning()
{
    this->Lightning = new GPIO();
    this->Lightning->setPort(LIGHTNING_PORT) ;
}

automaticLightning::automaticLightning(int aubeTime, int crepusculeTime)
{
    this->aubeTime = aubeTime ;
    this->crepusculeTime = crepusculeTime ;
}

automaticLightning::~automaticLightning()
{

}

void automaticLightning::checkLightning()
{
    qDebug("checkingLight");
    QTime currentTime = QTime::currentTime();
    if((currentTime.hour() > this->aubeTime)&&(currentTime.hour() < this->crepusculeTime))
    {
        qDebug("Lightning ON");
        this->Lightning->enablePort();
    }
    else
    {
        qDebug("Lightning OFF");
        this->Lightning->disablePort();
    }
}

void automaticLightning::doWork()
{
    while(this->flag)
    {
        qDebug("automaticLightning launched : %d h for aube, %d h for crepuscule",this->aubeTime,this->crepusculeTime);
        qDebug("flag = %d",this->flag);

        checkLightning();
        // Waiting 1h
        QThread::sleep(10);
    }
}
