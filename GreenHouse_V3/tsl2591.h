#ifndef TSL2591_H
#define TSL2591_H

#include <QString>
#include <QProcess>
#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include <unistd.h>

class TSL2591 :public QObject
{
    Q_OBJECT
public:
    // Methods
    explicit TSL2591();
    ~TSL2591();

    // Attributes
    QString *Lux ;
    QString *integrationTime ;
    QString *full ;
    QString *infrarouge ;
    QString *gain ;

    void getInfos();
    void doWork();

signals :
    void updateLux(QString*);
};
#endif // TSL2591_H
