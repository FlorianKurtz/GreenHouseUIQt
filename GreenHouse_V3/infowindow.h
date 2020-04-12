#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWindow(QWidget *parent = 0);
    ~InfoWindow();
    //TempHum *DHT22 ;
    QString *Temperature ;
    QString *Humidity ;

private slots:
    void openMainWindow();
    void refreshInfo(QString*,QString*);
    void refreshGIF(void);

private:
    Ui::InfoWindow *ui;
};

#endif // INFOWINDOW_H
