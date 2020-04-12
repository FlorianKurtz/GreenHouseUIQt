#ifndef TEMPHUM_H
#define TEMPHUM_H

#include <QtCore>
#include <QString>
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
#include <unistd.h>

class TempHum :public QThread
{
    Q_OBJECT
public:
    // Methods
    explicit TempHum();
    ~TempHum();

    // Attributes
    QString *Temperature ;
    QString *Humidity ;

    void getInfos();
    int exec();
    void run();

signals :
    void updateInfo(QString*,QString*);
};

#endif // TEMPHUM_H
