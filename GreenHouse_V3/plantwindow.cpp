#include "plantwindow.h"
#include "ui_plantwindow.h"

PlantWindow::PlantWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlantWindow)
{
    ui->setupUi(this);

    this->automaticWateringWorker = new automaticWatering();
    this->automaticLightningWorker = new automaticLightning();
    this->automaticTemperatureWorker = new automaticTemperature();

    ui->aubeLcdNumber->display(this->aubeTime);
    ui->crepusculeLcdNumber->display(this->crepusculeTime);
    ui->temperatureLcdNumber->display(this->optimalTemperature);
    ui->humidityLcdNumber->display(this->wateringPerDay);

    connect(ui->gotoMainPageButton,SIGNAL(clicked()),this, SLOT(openMainWindow()));
    connect(ui->launchAutoButton,SIGNAL(clicked()),this, SLOT(updateMode()));

    connect(ui->minusAubeButton,SIGNAL(clicked()),this,SLOT(minusAubeTime()));
    connect(ui->plusAubeButton,SIGNAL(clicked()),this,SLOT(plusAubeTime()));
    connect(ui->minusCrepusculeButton,SIGNAL(clicked()),this,SLOT(minusCrepusculeTime()));
    connect(ui->plusCrepusculeButton,SIGNAL(clicked()),this,SLOT(plusCrepusculeTime()));
    connect(ui->minusTemperatureButton,SIGNAL(clicked()),this,SLOT(minusTemperature()));
    connect(ui->plusTemperatureButton,SIGNAL(clicked()),this,SLOT(plusTemperature()));
    connect(ui->minusHumidityButton,SIGNAL(clicked()),this,SLOT(minusHumidity()));
    connect(ui->plusHumidityButton,SIGNAL(clicked()),this,SLOT(plusHumidity()));

    if(this->Mode == true)
    {
         // Mode is manual
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-on.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
    }else
    {
        // Mode is automatic
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-off.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
    }


}

PlantWindow::~PlantWindow()
{
    delete ui;
}

void PlantWindow::openMainWindow()
{
    MainWindow *mainWindow = new MainWindow();
    connect(this, SIGNAL (sendMode(bool)), mainWindow, SLOT(receiveMode(bool)));
    emit sendMode(this->Mode);
    mainWindow->showFullScreen();
    QWidget::close();
}

void PlantWindow::updateMode()
{
    if(this->Mode == true)
    {
        switchToManualMode();
    }else
    {
        qDebug("Switching to automatic mode");

        this->Mode = true ; // Mode switch to automatic
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-on.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);

        // automaticLightning worker thread launch
        // Qt example
        this->automaticLightningWorker->aubeTime = this->aubeTime ;
        this->automaticLightningWorker->crepusculeTime = this->crepusculeTime ;
        automaticLightningWorker->moveToThread(&automaticLightningWorkerThread);
        connect(&automaticLightningWorkerThread, &QThread::finished, automaticLightningWorker, &QObject::deleteLater);
        connect(this, &PlantWindow::startLightning, automaticLightningWorker, &automaticLightning::doWork);
        automaticLightningWorkerThread.start();
        emit startLightning() ;

        // automaticWatering worker thread launch
        this->automaticWateringWorker->wateringPerDay = this->wateringPerDay;
        automaticWateringWorker->moveToThread(&automaticWateringWorkerThread);
        connect(&automaticWateringWorkerThread, &QThread::finished, automaticWateringWorker, &QObject::deleteLater);
        connect(this, &PlantWindow::startWatering, automaticWateringWorker, &automaticWatering::doWork);
        automaticWateringWorkerThread.start();
        emit startWatering() ;

        // automaticHeating worker thread launch
        this->automaticTemperatureWorker->optimalTemperature = this->optimalTemperature;
        automaticTemperatureWorker->moveToThread(&automaticTemperatureWorkerThread);
        connect(&automaticTemperatureWorkerThread, &QThread::finished, automaticTemperatureWorker, &QObject::deleteLater);
        connect(this, &PlantWindow::startTemperature, automaticTemperatureWorker, &automaticTemperature::doWork);
        automaticTemperatureWorkerThread.start();
        emit startTemperature() ;

        automaticLightningWorker->flag = true ;
        automaticWateringWorker->flag = true ;
        automaticTemperatureWorker->flag = true ;

    }
}

void PlantWindow::refreshInfo(QString* Temperature,QString* Humidity)
{
    qDebug("Temperature and Humidity received by PlantWindow");
    this->Temperature = Temperature ;
    this->Humidity = Humidity ;
    automaticTemperatureWorker->currentTemperature = this->Temperature ;
    automaticWateringWorker->currentHumidity = this->Humidity ;
}

void PlantWindow::minusAubeTime()
{
    if(this->aubeTime == 0){
        // Hold value
    }
    else
    {
        this->aubeTime-- ;
        ui->aubeLcdNumber->display(this->aubeTime);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::plusAubeTime()
{
    if(this->aubeTime == 23){
        // Hold value
    }
    else
    {
        this->aubeTime++ ;
        ui->aubeLcdNumber->display(this->aubeTime);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::minusCrepusculeTime()
{
    if(this->crepusculeTime == 0){
        // Hold value
    }
    else
    {
        this->crepusculeTime-- ;
        ui->crepusculeLcdNumber->display(this->crepusculeTime);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::plusCrepusculeTime()
{
    if(this->crepusculeTime == 23){
        // Hold value
    }
    else
    {
        this->crepusculeTime++ ;
        ui->crepusculeLcdNumber->display(this->crepusculeTime);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::minusTemperature()
{
    if(this->optimalTemperature == 10){
        // Hold value
    }
    else
    {
        this->optimalTemperature-- ;
        ui->temperatureLcdNumber->display(this->optimalTemperature);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::plusTemperature()
{
    if(this->optimalTemperature == 35){
        // Hold value
    }
    else
    {
        this->optimalTemperature++ ;
        ui->temperatureLcdNumber->display(this->optimalTemperature);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::minusHumidity()
{
    if(this->wateringPerDay == 0){
        // Hold value
    }
    else
    {
        this->wateringPerDay -= 5 ;
        ui->humidityLcdNumber->display(this->wateringPerDay);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::plusHumidity()
{
    if(this->wateringPerDay == 100){
        // Hold value
    }
    else
    {
        this->wateringPerDay += 5 ;
        ui->humidityLcdNumber->display(this->wateringPerDay);
    }
    if(this->Mode == true)
    {
        switchToManualMode();
    }
}

void PlantWindow::switchToManualMode()
{
    qDebug("Switching to manual mode");

    this->Mode = false ; // Mode switch to manual
    QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-off.jpg");
    ui->backgroundLabel->setPixmap(backgroundImage);

    automaticLightningWorker->flag = false ;
    automaticWateringWorker->flag = false ;
    automaticTemperatureWorker->flag = false ;
}

void PlantWindow::receiveMode(bool Mode)
{
    this->Mode = Mode ;
    if(this->Mode == true)
    {
         // Mode is manual
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-on.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
    }else
    {
        // Mode is automatic
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/secret-page-off.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
    }
}
