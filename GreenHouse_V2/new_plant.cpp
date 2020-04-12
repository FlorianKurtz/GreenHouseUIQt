#include "new_plant.h"
#include "ui_new_plant.h"

new_plant::new_plant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_plant)
{
    ui->setupUi(this);
    setWindowTitle("Add your plant !");
    connect(ui->command_buttonBox,SIGNAL(accepted()),this,SLOT(create_new()));
    connect(ui->command_buttonBox,SIGNAL(rejected()),this,SLOT(close()));
}

new_plant::~new_plant()
{
    delete ui;
}

void new_plant::create_new()
{
    QString name = ui->name_textEdit->toPlainText();
    QString description = ui->desc_textEdit->toPlainText();
    int growing_days = ui->growing_spinBox->value();
    int flowering_days = ui->flowering_spinBox->value();
    double day_temp = ui->day_temp_doubleSpinBox->value();
    double night_temp = ui->night_temp_doubleSpinBox->value();
    double hum = ui->watering_spinBox->value();
    int growing_suntime = ui->growing_suntime_spinBox->value();
    int flowering_suntime = ui->flowering_suntime_spinBox->value();
    plant *new_p = new plant(0,name,description,growing_days,flowering_days,day_temp,night_temp,hum,growing_suntime,flowering_suntime);
    emit new_plant_created(new_p);
}
