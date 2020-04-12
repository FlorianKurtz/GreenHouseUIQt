#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>
#include <QVector>
#include <iostream>

#include "getdatewindow.h"
#include "new_plant.h"
#include "plant.h"

namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = 0);
    ~choose();
    QVector<plant> list_plant ;
    plant *actualPlant ;
    plant *tomato;
    plant *carot;
    plant *apple;
    plant *rose;

public slots :
    void open_new_plant(void);
    void save_new_plant(plant*);
    void display_plant(int);
    void validate(void);

signals :
    void send_actual_plant(plant*);


private:
    Ui::choose *ui;
    int ident = 0;
};

#endif // CHOOSE_H
