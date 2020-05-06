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
    bool Mode = false; // false = Manual | true = Automatic

private slots:
    void openMainWindow();
    void faningButtonSlot();
    void wateringButtonSlot();
    void heatingButtonSlot();
    void lightningButtonSlot();
    void receiveMode(bool);

private:
    Ui::ControlWindow *ui;

signals :
    void sendMode(bool);
};

#endif // CONTROLWINDOW_H
