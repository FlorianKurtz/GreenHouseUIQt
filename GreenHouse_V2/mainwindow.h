#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QColor>
#include <QLabel>
#include <QProgressBar>

#include <plant.h>
#include "choose.h"
#include "culture_task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    plant *actualPlant ;
    QDate *date ;
    QLabel *date_lab ;
    QTime *time ;
    QLabel *time_lab ;
    QProgressBar *statusProgressBar ;

    void refresh_info(void);
    culture_task *culture ;

public slots :
    void get_info(plant*);
    void get_info(plant*,QDate*,QTime*);
    void new_project(void);

    void refresh_hum_threshold(double);
    void refresh_growing_days(int);
    void refresh_flowering_days(int);
    void refresh_beg_light_hour(double);
    void refresh_end_light_hour(double);
    void refresh_day_temp(double);
    void refresh_night_temp(double);
    void refresh(void);

    void start_project(void);

    void light_auto(void);
    void light_on(void);
    void light_off(void);

    void heat_auto(void);
    void heat_on(void);
    void heat_off(void);

    void fan_auto(void);
    void fan_on(void);
    void fan_off(void);

    void watering_auto(void);
    void watering_on(void);
    void watering_off(void);

signals :
    void send_mode_watering(int);
    void send_mode_fan(int);
    void send_mode_heat(int);
    void send_mode_light(int);
    void send_plant(plant*);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
