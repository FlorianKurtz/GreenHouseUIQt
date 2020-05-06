#ifndef PLANTWINDOW_H
#define PLANTWINDOW_H

#include <QWidget>
#include "mainwindow.h"
#include "automaticlightning.h"
#include "automatictemperature.h"
#include "automaticwatering.h"

namespace Ui {
class PlantWindow;
}


class PlantWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PlantWindow(QWidget *parent = 0);
    ~PlantWindow();
    void switchToManualMode() ;

    bool Mode = false ; // 0 = Manual | 1 = Automatic
    // Threads
    QThread automaticLightningWorkerThread, automaticWateringWorkerThread, automaticTemperatureWorkerThread ;
    //TempHum *DHT22 ;
    int aubeTime = 8 ;
    int crepusculeTime = 18 ;
    int wateringPerDay= 70 ;
    int optimalTemperature = 24 ;

    QString *Temperature ;
    QString *Humidity ;
    automaticLightning *automaticLightningWorker ;
    automaticWatering *automaticWateringWorker ;
    automaticTemperature *automaticTemperatureWorker ;

private slots:
    void openMainWindow();
    void updateMode();
    void refreshInfo(QString*,QString*);

    void plusAubeTime();
    void minusAubeTime();
    void plusCrepusculeTime();
    void minusCrepusculeTime();
    void plusTemperature();
    void minusTemperature();
    void plusHumidity();
    void minusHumidity();

    void receiveMode(bool);


private:
    Ui::PlantWindow *ui;

signals:
    void sendMode(bool);
    void startLightning();
    void startWatering();
    void startTemperature();

};

#endif // PLANTWINDOW_H
