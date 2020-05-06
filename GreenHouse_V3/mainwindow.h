#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QMessageBox>

#include "gpio.h"
#include "temphum.h"
#include "camera.h"
#include "controlwindow.h"
#include "infowindow.h"
#include "plantwindow.h"
#include "tsl2591.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QThread DHT22WorkerThread, TSL2591WorkerThread ;
    GPIO *Heater, *Watering, *Lightning, *Faning ;
    TempHum *DHT22Worker ;
    TSL2591 *TSL2591Worker ;
    Camera *myCamera ;
    QString gifFileName ;
    QString *Temperature ;
    QString *Humidity ;
    QString *Lux ;
    bool Mode = false; // false = Manual | true = Automatic

private slots:
    void openControlWindow();
    void openInfoWindow();
    void openPlantWindow();
    void refreshInfo(QString*,QString*);
    void refreshBackground();
    void receiveMode(bool);
    void receiveLux(QString*);

private:
    Ui::MainWindow *ui;

signals :
    void startDHT22();
    void startTSL2591();
    void sendMode(bool);
};

#endif // MAINWINDOW_H
