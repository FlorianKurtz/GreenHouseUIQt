#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();
    GPIO *Heater, *Watering, *Lightning, *Faning ;

private slots:
    void openMainWindow();
    void faningButtonSlot();
    void wateringButtonSlot();
    void heatingButtonSlot();
    void lightningButtonSlot();

private:
    Ui::ControlWindow *ui;
};

#endif // CONTROLWINDOW_H
