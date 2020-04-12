#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>

#include "gpio.h"
#include "temphum.h"
#include "camera.h"
#include "controlwindow.h"
#include "infowindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TempHum *DHT22 ;
    Camera *myCamera ;
    QString *Temperature ;
    QString *Humidity ;

private slots:
    void openControlWindow();
    void openInfoWindow();
    void refreshInfo(QString*,QString*);

private:
    Ui::MainWindow *ui;

signals :
    void updateInfo(QString*,QString*);
};

#endif // MAINWINDOW_H
