#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/info-page.jpg");
    ui->backgroundLabel->setPixmap(backgroundImage);

    connect(ui->gotoMainPageButton,SIGNAL(clicked()),this, SLOT(openMainWindow()));
    // Load animated GIF
    QMovie* movie = new QMovie("/home/pi/Pictures/GreenHouse_Pictures/Greenhouse.gif");

    // Make sure the GIF was loaded correctly
    if (!movie->isValid())
    {
        // Something went wrong :(
    }

    // Play GIF
    ui->plantGIFLabel->setMovie(movie);
    movie->start();
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::openMainWindow()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->showFullScreen();
    QWidget::close();
}

void InfoWindow::refreshInfo(QString* Temperature,QString* Humidity)
{
    qDebug("Temperature and Humidity received by InfoWindow");
    this->Temperature = Temperature ;
    this->Humidity = Humidity ;
    this->Temperature->append("°C") ;
    this->Humidity->append("%") ;

    ui->humLabel->setText(*this->Temperature);
    ui->tempLabel->setText(*this->Humidity);
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("ddd MMMM d yyyy HH:mm"));
}

void InfoWindow::refreshGIF()
{
    qDebug("New GIF received by InfoWindow");
    // Load animated GIF
    QMovie* movie = new QMovie("/home/pi/Pictures/GreenHouse_Pictures/Greenhouse.gif");

    // Make sure the GIF was loaded correctly
    if (!movie->isValid())
    {
        // Something went wrong :(
    }

    // Play GIF
    ui->plantGIFLabel->setMovie(movie);
    movie->start();
}

