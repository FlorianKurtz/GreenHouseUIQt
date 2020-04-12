#include "getdatewindow.h"
#include "ui_getdatewindow.h"

getdatewindow::getdatewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getdatewindow)
{
    ui->setupUi(this);
    setWindowTitle("Enter the date");

    currentTime = new QTime() ;
    currentDate = new QDate() ;

    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(dateChanged(QDate)));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(hourChanged(int)));
    connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(minChanged(int)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(validate()));
    connect(ui->buttonBox,SIGNAL(rejected()),qApp,SLOT(quit()));

}

getdatewindow::~getdatewindow()
{
    delete ui;
}

void getdatewindow::validate()
{
    MainWindow *main = new MainWindow();
    int currentDay = currentDate->day();
    int currentMonth = currentDate->month();
    int currentYear = currentDate->year() ;
    QTextStream(stdout) << "date -s "<<hour<<":"<<min<<":00" << endl ;
    QTextStream(stdout) << "date -s "<<currentDay<<"/"<<currentMonth<<"/"<<currentYear<<endl;
    connect(this,SIGNAL(send_info(plant*,QDate*,QTime*)),main,SLOT(get_info(plant*,QDate*,QTime*)));
    emit send_info(actualPlant,currentDate,currentTime);
    main->showFullScreen();
    QWidget::close();
}

void getdatewindow::get_actual_plant(plant* actualPlant)
{
    this->actualPlant = actualPlant;
}

void getdatewindow::dateChanged(QDate currentDate)
{
    this->currentDate = &currentDate ;
}

void getdatewindow::hourChanged(int hour)
{
    this->hour = hour ;
    currentTime->setHMS(hour,min,0);
}
void getdatewindow::minChanged(int min)
{
    this->min = min ;
    currentTime->setHMS(hour,min,0);
}
