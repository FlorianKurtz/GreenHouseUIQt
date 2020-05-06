#include "tsl2591.h"

// Constructors
TSL2591::TSL2591()
{
    this->Lux  = new QString() ;
    this->integrationTime  = new QString() ;
    this->full  = new QString() ;
    this->infrarouge  = new QString() ;
    this->gain  = new QString() ;
    qDebug("TSL2591 succesfully created");
}
TSL2591::~TSL2591()
{

}
// Methods
void TSL2591::getInfos()
{
    QString command("python");
    // i2c adresse = 0x29 | MODEL TSL2591 Adafruit
    QStringList params  {"/home/pi/Documents/Adafruit_Python_TSL2591/getLux.py"};

    QProcess *process = new QProcess();
    process->start(command,params);
    process->waitForFinished(1000);
    QString output(process->readAllStandardOutput());
    process->close();
    if(!output.isEmpty())
    {
        // Layout infos
        output.remove("{");
        output.remove("'lux': ");
        output.remove("'integration_time': ");
        output.remove("'full': ");
        output.remove("'ir': ");
        output.remove("'gain': ");
        output.remove("\n");
        QStringList TSL2591Values = output.split(",");

        // Assignment
        *Lux = TSL2591Values.at(0) ;
        *integrationTime = TSL2591Values.at(1) ;
        *full = TSL2591Values.at(2) ;
        *infrarouge = TSL2591Values.at(3) ;
        *gain = TSL2591Values.at(4) ;

        // Debug
        qDebug("Lux = %s",this->Lux->toStdString().c_str());
        emit updateLux(this->Lux);
    }
}

void TSL2591::doWork()
{
    while(1)
    {
        this->getInfos();
        // Waiting 3seconds
        sleep(10);
    }
}
