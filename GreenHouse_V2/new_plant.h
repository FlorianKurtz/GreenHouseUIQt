#ifndef NEW_PLANT_H
#define NEW_PLANT_H

#include <QDialog>

#include "plant.h"

namespace Ui {
class new_plant;
}

class new_plant : public QDialog
{
    Q_OBJECT

public:
    explicit new_plant(QWidget *parent = 0);
    ~new_plant();

public slots :
    void create_new(void);

private:
    Ui::new_plant *ui;

signals:
    void new_plant_created(plant *new_p);
};

#endif // NEW_PLANT_H 
