#ifndef GETDATEWINDOW_H
#define GETDATEWINDOW_H

#include <QDialog>
#include <QTextStream>
#include <string>
#include <plant.h>
#include "mainwindow.h"

namespace Ui {
class getdatewindow;
}

class getdatewindow : public QDialog
{
    Q_OBJECT

public:
    explicit getdatewindow(QWidget *parent = 0);
    ~getdatewindow();
    QDate *currentDate ;
    QTime *currentTime ;
    plant *actualPlant ;
    int hour = 12 ;
    int min = 30 ;
public slots :
    void get_actual_plant(plant*);
    void validate(void);
    void dateChanged(QDate);
    void hourChanged(int);
    void minChanged(int);
signals :
    void send_info(plant*,QDate*,QTime*);
private:
    Ui::getdatewindow *ui;
};

#endif // GETDATEWINDOW_H
