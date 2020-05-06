#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QVector>
#include "mainwindow.h"
#include "qcustomplot.h"

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();
    void refreshPlot();
    void refreshInfo();
    void refreshLux();
    //TempHum *DHT22 ;
    QString *Temperature ;
    QString *Humidity ;
    QString *Lux ;
    Camera *myCamera ;
    bool Mode = false; // false = Manual | true = Automatic
    bool displayMode = false ; // false = Writing | true = Plotting
    QVector<QCPGraphData> luxData ;
    QVector<QCPGraphData> humidityData ;
    QVector<QCPGraphData> temperatureData ;

private slots:
    void openMainWindow();
    void receiveInfo(QString*,QString*);
    void receiveMode(bool);
    void receiveLux(QString*);
    void refreshGIF();
    void resetGif();
    void changeDisplayMode();
    void takeNewPicture();

private:
    Ui::InfoWindow *ui;

signals :
    void sendMode(bool);
};

#endif // INFOWINDOW_H
