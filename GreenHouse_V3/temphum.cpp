#include "temphum.h"

// Constructors
TempHum::TempHum()
{
    this->Temperature = new QString() ;
    this->Humidity = new QString() ;
    qDebug("TempHum succesfully created");
}
TempHum::~TempHum()
{

}
// Methods
void TempHum::getInfos()
{
    QString command("python");
    // PORT NUMBER = 4 | MODEL DHT22
    QStringList params  {"/home/pi/Documents/Adafruit_Python_DHT/examples/AdafruitDHT.py","22","4"};

    QProcess *process = new QProcess();
    process->start(command,params);
    process->waitForFinished(3000);
    QString output(process->readAllStandardOutput());
    process->close();
    if(!output.isEmpty())
    {
        // Layout infos
        output.remove("Temp=");
        output.remove("Humidity=");
        output.remove("%");
        output.remove(" ");
        output.remove("\n");
        QStringList DHT22Values = output.split("*");

        // Assignment
        *Temperature = DHT22Values.at(0) ;
        *Humidity = DHT22Values.at(1) ;

        // Debug
        qDebug("Temperature = %s°C",this->Temperature->toStdString().c_str());
        qDebug("Humidity = %s",this->Humidity->toStdString().c_str());
        emit updateInfo(this->Temperature, this->Humidity);
    }
}

void TempHum::doWork()
{
    while(1)
    {
        this->getInfos();
        // Waiting 3seconds
        sleep(10);
    }
}
