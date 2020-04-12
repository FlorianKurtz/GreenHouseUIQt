#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GreenHouse");
    //setWindowIcon();

    // SETUP THE STATUS BAR
    date = new QDate();
    time = new QTime();
    date_lab = new QLabel(date->currentDate().toString());
    time_lab = new QLabel(time->currentTime().toString());
    statusProgressBar = new QProgressBar(this);

    ui->statusbar->addWidget(date_lab);
    ui->statusbar->addPermanentWidget(time_lab);
    ui->statusbar->addPermanentWidget(statusProgressBar);

    // HIDE THE AUTO COMPONENTS
    ui->main_tabWidget->setTabEnabled(2,false);

    ui->to_lab->hide();
    ui->til_lab->hide();
    ui->beg_light_hour_doubleSpinBox->hide();
    ui->end_light_hour_doubleSpinBox->hide();

    ui->min_humidity_lab->hide();
    ui->min_hum_doubleSpinBox->hide();

    ui->day_temp_lab->hide();
    ui->night_temp_lab->hide();
    ui->day_temp_doubleSpinBox->hide();
    ui->night_temp_doubleSpinBox->hide();

    connect(ui->new_project_button,SIGNAL(clicked()),this,SLOT(new_project()));
    connect(ui->exit_button,SIGNAL(clicked()),qApp, SLOT(quit()));

    // Control connections
    connect(ui->min_hum_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(refresh_hum_threshold(double)));
    connect(ui->growing_days_spinBox,SIGNAL(valueChanged(int)),this,SLOT(refresh_growing_days(int)));
    connect(ui->flowering_days_spinBox,SIGNAL(valueChanged(int)),this,SLOT(refresh_flowering_days(int)));
    connect(ui->beg_light_hour_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(refresh_beg_light_hour(double)));
    connect(ui->end_light_hour_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(refresh_end_light_hour(double)));
    connect(ui->day_temp_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(refresh_day_temp(double)));
    connect(ui->night_temp_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(refresh_night_temp(double)));

    // START project connection
    connect(ui->start_project_button,SIGNAL(clicked()),this,SLOT(start_project()));

    // AUTO Modes
    connect(ui->light_auto_button,SIGNAL(clicked()),this,SLOT(light_auto()));
    connect(ui->heat_auto_button,SIGNAL(clicked()),this,SLOT(heat_auto()));
    connect(ui->fan_auto_button,SIGNAL(clicked()),this,SLOT(fan_auto()));
    connect(ui->watering_auto_button,SIGNAL(clicked()),this,SLOT(watering_auto()));

    // MANU Modes
    connect(ui->light_on_button,SIGNAL(clicked()),this,SLOT(light_on()));
    connect(ui->light_off_button,SIGNAL(clicked()),this,SLOT(light_off()));

    connect(ui->heat_on_button,SIGNAL(clicked()),this,SLOT(heat_on()));
    connect(ui->heat_off_button,SIGNAL(clicked()),this,SLOT(heat_off()));

    connect(ui->fan_on_button,SIGNAL(clicked()),this,SLOT(fan_on()));
    connect(ui->fan_off_button,SIGNAL(clicked()),this,SLOT(fan_off()));

    connect(ui->watering_on_button,SIGNAL(clicked()),this,SLOT(watering_on()));
    connect(ui->watering_off_button,SIGNAL(clicked()),this,SLOT(watering_off()));

    // THREAD Creation and Connection
    culture = new culture_task();
    connect(this,SIGNAL(send_mode_fan(int)),culture,SLOT(get_mode_fan(int)));
    connect(this,SIGNAL(send_mode_watering(int)),culture,SLOT(get_mode_watering(int)));
    connect(this,SIGNAL(send_mode_heat(int)),culture,SLOT(get_mode_heating(int)));
    connect(this,SIGNAL(send_mode_light(int)),culture,SLOT(get_mode_lightning(int)));
    connect(this,SIGNAL(send_plant(plant*)),culture,SLOT(get_plant(plant*)));
    connect(culture,SIGNAL(send_refresh()),this,SLOT(refresh()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_project()
{
    emit send_plant(actualPlant);
    ui->main_tabWidget->setTabEnabled(2,true) ;
    culture->start();
}

void MainWindow::refresh(void)
{
    refresh_info();
}

void MainWindow::light_auto(void)
{
    ui->to_lab->show();
    ui->til_lab->show();
    ui->beg_light_hour_doubleSpinBox->show();
    ui->end_light_hour_doubleSpinBox->show();
    // Change colors
    ui->light_auto_button->setStyleSheet("background-color: brown;");
    ui->light_on_button->setStyleSheet("background-color: green;");
    ui->light_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_light(2);
}

void MainWindow::light_on(void)
{
    ui->to_lab->hide();
    ui->til_lab->hide();
    ui->beg_light_hour_doubleSpinBox->hide();
    ui->end_light_hour_doubleSpinBox->hide();
    // Change colors
    ui->light_auto_button->setStyleSheet("background-color: green;");
    ui->light_on_button->setStyleSheet("background-color: brown;");
    ui->light_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_light(1);
}

void MainWindow::light_off(void)
{
    ui->to_lab->hide();
    ui->til_lab->hide();
    ui->beg_light_hour_doubleSpinBox->hide();
    ui->end_light_hour_doubleSpinBox->hide();
    // Change colors
    ui->light_auto_button->setStyleSheet("background-color: green;");
    ui->light_on_button->setStyleSheet("background-color: green;");
    ui->light_off_button->setStyleSheet("background-color: brown;");
    // Emit signal
    emit send_mode_light(0);
}

void MainWindow::heat_auto(void)
{
    ui->day_temp_lab->show();
    ui->night_temp_lab->show();
    ui->day_temp_doubleSpinBox->show();
    ui->night_temp_doubleSpinBox->show();
    // Change colors
    ui->heat_auto_button->setStyleSheet("background-color: brown;");
    ui->heat_on_button->setStyleSheet("background-color: green;");
    ui->heat_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_heat(2);
}

void MainWindow::heat_on(void)
{
    ui->day_temp_lab->hide();
    ui->night_temp_lab->hide();
    ui->day_temp_doubleSpinBox->hide();
    ui->night_temp_doubleSpinBox->hide();
    // Change colors
    ui->heat_auto_button->setStyleSheet("background-color: green;");
    ui->heat_on_button->setStyleSheet("background-color: brown;");
    ui->heat_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_heat(1);
}

void MainWindow::heat_off(void)
{
    ui->day_temp_lab->hide();
    ui->night_temp_lab->hide();
    ui->day_temp_doubleSpinBox->hide();
    ui->night_temp_doubleSpinBox->hide();
    // Change colors
    ui->heat_auto_button->setStyleSheet("background-color: green;");
    ui->heat_on_button->setStyleSheet("background-color: green;");
    ui->heat_off_button->setStyleSheet("background-color: brown;");
    // Emit signal
    emit send_mode_heat(0);
}

void MainWindow::fan_auto(void)
{
    // Change colors
    ui->fan_auto_button->setStyleSheet("background-color: brown;");
    ui->fan_on_button->setStyleSheet("background-color: green;");
    ui->fan_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_fan(2);
}

void MainWindow::fan_on(void)
{
    // Change colors
    ui->fan_auto_button->setStyleSheet("background-color: green;");
    ui->fan_on_button->setStyleSheet("background-color: brown;");
    ui->fan_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_fan(1);
}

void MainWindow::fan_off(void)
{
    // Change colors
    ui->fan_auto_button->setStyleSheet("background-color: green;");
    ui->fan_on_button->setStyleSheet("background-color: green;");
    ui->fan_off_button->setStyleSheet("background-color: brown;");
    // Emit signal
    emit send_mode_fan(0);
}

void MainWindow::watering_auto(void)
{
    ui->min_humidity_lab->show();
    ui->min_hum_doubleSpinBox->show();
    // Change colors
    ui->watering_auto_button->setStyleSheet("background-color: brown;");
    ui->watering_on_button->setStyleSheet("background-color: green;");
    ui->watering_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_watering(2);
}

void MainWindow::watering_on(void)
{
    ui->min_humidity_lab->hide();
    ui->min_hum_doubleSpinBox->hide();
    // Change colors
    ui->watering_auto_button->setStyleSheet("background-color: green;");
    ui->watering_on_button->setStyleSheet("background-color: brown;");
    ui->watering_off_button->setStyleSheet("background-color: green;");
    // Emit signal
    emit send_mode_watering(1);
}

void MainWindow::watering_off(void)
{
    ui->min_humidity_lab->hide();
    ui->min_hum_doubleSpinBox->hide();
    // Change colors
    ui->watering_auto_button->setStyleSheet("background-color: green;");
    ui->watering_on_button->setStyleSheet("background-color: green;");
    ui->watering_off_button->setStyleSheet("background-color: brown;");
    // Emit signal
    emit send_mode_watering(0);
}

void MainWindow::get_info(plant *tmp, QDate *date, QTime *time)
{
    actualPlant = tmp ;
    this->date = date ;
    this->time = time ;
    ui->plant_name_lineEdit->setText(actualPlant->name);
    ui->plant_desc_textEdit->setText(actualPlant->description);
    ui->growing_days_spinBox->setValue(actualPlant->growing_days);
    ui->flowering_days_spinBox->setValue(actualPlant->flowering_days);
    ui->min_hum_doubleSpinBox->setValue(actualPlant->hum);
    ui->day_temp_doubleSpinBox->setValue(actualPlant->day_temp);
    ui->night_temp_doubleSpinBox->setValue(actualPlant->night_temp);
    refresh_info();

}

void MainWindow::get_info(plant *tmp)
{
    actualPlant = tmp ;
    ui->plant_name_lineEdit->setText(actualPlant->name);
    ui->plant_desc_textEdit->setText(actualPlant->description);
    ui->growing_days_spinBox->setValue(actualPlant->growing_days);
    ui->flowering_days_spinBox->setValue(actualPlant->flowering_days);
    ui->min_hum_doubleSpinBox->setValue(actualPlant->hum);
    ui->day_temp_doubleSpinBox->setValue(actualPlant->day_temp);
    ui->night_temp_doubleSpinBox->setValue(actualPlant->night_temp);
    refresh_info();

}

void MainWindow::new_project()
{
    choose *choose_window = new choose();
    choose_window->showFullScreen();
    QWidget::close();

}

void MainWindow::refresh_hum_threshold(double hum)
{
    actualPlant->hum = hum ;
    refresh_info();
}

void MainWindow::refresh_growing_days(int growing_days)
{
    actualPlant->growing_days = growing_days ;
    refresh_info();
}

void MainWindow::refresh_flowering_days(int flowering_days)
{
    actualPlant->flowering_days = flowering_days ;
    refresh_info();
}

void MainWindow::refresh_beg_light_hour(double beg_hour)
{
    actualPlant->beg_hour = beg_hour ;
    refresh_info();
}

void MainWindow::refresh_end_light_hour(double end_hour)
{
    actualPlant->end_hour = end_hour ;
    refresh_info();
}


void MainWindow::refresh_day_temp(double day_temp)
{
    actualPlant->day_temp = day_temp ;
    refresh_info();
}

void MainWindow::refresh_night_temp(double night_temp)
{
    actualPlant->night_temp = night_temp ;
    refresh_info();
}

void MainWindow::refresh_info(void)
{
    if(actualPlant->mode)
        ui->mode_lineEdit->setText("Flowering");
    else
        ui->mode_lineEdit->setText("Growing");


    if(actualPlant->day_or_night)
    {
        ui->temp_lcdNumber->display(actualPlant->day_temp);
        ui->moon_lab->setText("");
        ui->sun_lab->setText("Sun");
    }
    else
    {
        ui->temp_lcdNumber->display(actualPlant->night_temp);
        ui->moon_lab->setText("Moon");
        ui->sun_lab->setText("");
    }

    date_lab->setText(date->currentDate().toString());
    time_lab->setText(time->currentTime().toString());

    ui->watering_lcdNumber->display(actualPlant->hum);
    ui->growing_days_lcdNumber->display(actualPlant->growing_days);
    ui->growing_lightning_lcdNumber->display(actualPlant->growing_suntime);
    ui->flowering_days_lcdNumber->display(actualPlant->flowering_days);
    ui->flowering_lightning_lcdNumber->display(actualPlant->flowering_suntime);

    ui->growing_days_left_lcdNumber->display(actualPlant->growing_days_left);
    ui->flowering_days_left_lcdNumber->display(actualPlant->flowering_days_left);
    ui->project_days_left_lcdNumber->display(actualPlant->project_days_left);

    ui->growing_day_left_progressBar->setValue((1-(actualPlant->growing_days_left/actualPlant->growing_days)));
    ui->flowering_day_left_progressBar->setValue((1-(actualPlant->flowering_days_left/actualPlant->flowering_days)));
    ui->project_day_left_progressBar->setValue((1-(actualPlant->project_days_left/(actualPlant->growing_days+actualPlant->flowering_days))));

    statusProgressBar->setValue((1-(actualPlant->project_days_left/(actualPlant->growing_days+actualPlant->flowering_days))));
}
