#include "gpio.h"

// Constructors
GPIO::GPIO()
{
    qDebug("GPIO succesfully created");
}
GPIO::GPIO(int port)
{
    qDebug("GPIO succesfully created with arguments");
    this->setPort(port);
}
// Methods
void GPIO::setPort(int port)
{
    // Attributes initialization
    this->portNumber = port ;
    this->pathValueString.append("/sys/class/gpio/gpio");
    this->pathValueString.append(QString::number(port));
    QString pathDirectionString = this->pathValueString ;
    pathDirectionString.append("/direction");
    this->pathValueString.append("/value");

    // GPIO initialization
    FILE *sysInitHandle = NULL;
    if (!QFile::exists(this->pathValueString))
    {
        if ((sysInitHandle = fopen("/sys/class/gpio/export","w")) != NULL )
        {
            fwrite(QString::number(port).toStdString().c_str(),sizeof(char),2,sysInitHandle);
            fclose(sysInitHandle);
            qDebug("GPIO %d added to export",this->portNumber);
        }
    }
    QFile f(pathDirectionString);
    if (f.open(QIODevice::ReadOnly))
    {
        QTextStream in(&f);
        QString line = in.readLine();
        if(line == "in")
        {
            qDebug("GPIO %d direction  : %s",this->portNumber,line.toStdString().c_str());
            f.close();

            if ((sysInitHandle = fopen(pathDirectionString.toStdString().c_str(),"w")) != NULL )
            {
                fwrite("out",sizeof(char),4,sysInitHandle);
                fclose(sysInitHandle);
                qDebug("GPIO %d direction put to out",this->portNumber);
            }
        }
    }

}
void GPIO::enablePort()
{
    FILE *sysGPIOHandle = NULL;
    if ((sysGPIOHandle = fopen(this->pathValueString.toStdString().c_str(),"w")) != NULL )
    {
        fwrite("1",sizeof(char),2,sysGPIOHandle);
        fclose(sysGPIOHandle);
        qDebug("GPIO %d succesfully enabled",this->portNumber);
    }
}

void GPIO::disablePort()
{
    FILE *sysGPIOHandle = NULL;
    if ((sysGPIOHandle = fopen(this->pathValueString.toStdString().c_str(),"w")) != NULL )
    {
        fwrite("0",sizeof(char),2,sysGPIOHandle);
        fclose(sysGPIOHandle);
        qDebug("GPIO %d succesfully disabled",this->portNumber);
    }
}

int GPIO::getPortState()
{
    QFile f(this->pathValueString);
    int outputValue ;
    if (f.open(QIODevice::ReadOnly))
    {
      outputValue = f.readAll().at(0) - 48;
      f.close();
      //qDebug("GPIO %d value = %d",this->portNumber,outputValue);
    }
    return outputValue ;
}
