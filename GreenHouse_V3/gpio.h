#ifndef GPIO_H
#define GPIO_H

#include <QString>
#include <QDebug>
#include <QFile>

namespace Ui {
class GPIO;
}

class GPIO
{
public:
    // Attributes
    int portNumber ;
    QString pathValueString ;

    // Methods
    GPIO();
    GPIO(int);
    void setPort(int);
    void enablePort();
    void disablePort();
    int getPortState();
};

#endif // GPIO_H
