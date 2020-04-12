#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet();

    connect(ui->gotoControlPageButton,SIGNAL(clicked()),this, SLOT(openControlWindow()));
    connect(ui->gotoInfoPageButton,SIGNAL(clicked()),this, SLOT(openInfoWindow()));

    this->DHT22 = new TempHum();
    connect(this->DHT22, SIGNAL (updateInfo(QString*,QString*)), this, SLOT(refreshInfo(QString*,QString*)));
    this->DHT22->start();

    // Creating thread for taking picture and creating gif continuously
    this->myCamera = new Camera();
    this->myCamera->start();

    // Start GIF background
    // Load animated GIF
    QMovie* movie = new QMovie("/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_humide_froid_vent.gif");

    // Make sure the GIF was loaded correctly
    if (!movie->isValid())
    {
        // Something went wrong :(
    }

    // Play GIF
    ui->mainGIF->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openControlWindow()
{
    ControlWindow *controlWindow = new ControlWindow();
    controlWindow->showFullScreen();
    QWidget::close();
}

void MainWindow::openInfoWindow()
{
    InfoWindow *infoWindow  = new InfoWindow();
    connect(this->DHT22, SIGNAL (updateInfo(QString*,QString*)), infoWindow, SLOT(refreshInfo(QString*,QString*)));
    connect(this, SIGNAL (updateInfo(QString*,QString*)), infoWindow, SLOT(refreshInfo(QString*,QString*)));
    emit updateInfo(this->DHT22->Temperature, this->DHT22->Humidity);
    connect(this->myCamera, SIGNAL (updateGIF(void)), infoWindow, SLOT(refreshGIF(void)));
    infoWindow->showFullScreen();
    QWidget::close();
}

void MainWindow::refreshInfo(QString* Temperature,QString* Humidity)
{
    qDebug("Temperature and Humidity received by MainWindow");
    this->Temperature = Temperature ;
    this->Humidity = Humidity ;
}

