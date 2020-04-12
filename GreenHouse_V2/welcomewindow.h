#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include "choose.h"
namespace Ui {
class welcomewindow;
}

class welcomewindow : public QWidget
{
    Q_OBJECT

public:
    explicit welcomewindow(QWidget *parent = 0);
    ~welcomewindow();

public slots :
    void open_choose_page(void);

private:
    Ui::welcomewindow *ui;
};

#endif // WELCOME_H
