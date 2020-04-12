#include "welcomewindow.h"
#include "ui_welcomewindow.h"

welcomewindow::welcomewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomewindow)
{
    ui->setupUi(this);
    setWindowTitle("Welcome");
    connect(ui->enter_button,SIGNAL(clicked()),this, SLOT(open_choose_page()));

}

welcomewindow::~welcomewindow()
{
    delete ui;
}

void welcomewindow::open_choose_page()
{
    choose *choosewindow = new choose();
    choosewindow->showFullScreen();
    QWidget::close();
}
