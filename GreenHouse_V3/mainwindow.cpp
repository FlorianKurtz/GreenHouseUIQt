#include "mainwindow.h"
#include "ui_mainwindow.h"

#define HEATER_PORT 24
#define WATERING_PORT 23
#define LIGHTNING_PORT 22
#define FANING_PORT 27

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Hiding cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    connect(ui->gotoControlPageButton,SIGNAL(clicked()),this, SLOT(openControlWindow()));
    connect(ui->gotoInfoPageButton,SIGNAL(clicked()),this, SLOT(openInfoWindow()));
    connect(ui->gotoPlantPageButton,SIGNAL(clicked()),this, SLOT(openPlantWindow()));

    // DHT22 worker thread launch
    // Qt example
    this->DHT22Worker = new TempHum();
    DHT22Worker->moveToThread(&DHT22WorkerThread);
    connect(this->DHT22Worker, SIGNAL (updateInfo(QString*,QString*)), this, SLOT(refreshInfo(QString*,QString*)));
    connect(&DHT22WorkerThread, &QThread::finished, DHT22Worker, &QObject::deleteLater);
    connect(this, &MainWindow::startDHT22, DHT22Worker, &TempHum::doWork);
    DHT22WorkerThread.start();
    emit startDHT22() ;

    // TSL2591 worker thread launch
    // Qt example
    this->TSL2591Worker = new TSL2591();
    TSL2591Worker->moveToThread(&TSL2591WorkerThread);
    connect(this->TSL2591Worker, SIGNAL (updateLux(QString*)), this, SLOT(receiveLux(QString*)));
    connect(&TSL2591WorkerThread, &QThread::finished, TSL2591Worker, &QObject::deleteLater);
    connect(this, &MainWindow::startTSL2591, TSL2591Worker, &TSL2591::doWork);
    TSL2591WorkerThread.start();
    emit startTSL2591() ;

    // Creating thread for taking picture and creating gif continuously
    this->myCamera = new Camera();
    this->myCamera->start();

    // Create GPIOs for background control
    // Setup GPIOS
    this->Heater = new GPIO();
    this->Watering = new GPIO();
    this->Lightning = new GPIO();
    this->Faning = new GPIO();

    this->Heater->setPort(HEATER_PORT) ;
    this->Watering->setPort(WATERING_PORT) ;
    this->Lightning->setPort(LIGHTNING_PORT) ;
    this->Faning->setPort(FANING_PORT) ;
    refreshBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openControlWindow()
{
    ControlWindow *controlWindow = new ControlWindow();
    controlWindow->showFullScreen();
    controlWindow->Mode = this->Mode ;
    QWidget::close();
}

void MainWindow::openPlantWindow()
{
    PlantWindow *plantWindow = new PlantWindow();
    connect(this->DHT22Worker, SIGNAL (updateInfo(QString*,QString*)), plantWindow, SLOT(refreshInfo(QString*,QString*)));
    connect(this, SIGNAL (sendMode(bool)), plantWindow, SLOT(receiveMode(bool)));
    plantWindow->Temperature = this->DHT22Worker->Temperature ;
    plantWindow->Humidity = this->DHT22Worker->Humidity ;
    plantWindow->Mode = this->Mode ;
    plantWindow->showFullScreen();
    emit sendMode(this->Mode);
    QWidget::close();
}

void MainWindow::openInfoWindow()
{
    InfoWindow *infoWindow  = new InfoWindow();
    connect(this->DHT22Worker, SIGNAL (updateInfo(QString*,QString*)), infoWindow, SLOT(receiveInfo(QString*,QString*)));
    connect(this->TSL2591Worker, SIGNAL (updateLux(QString*)), infoWindow, SLOT(receiveLux(QString*)));
    connect(this->myCamera, SIGNAL (updateGIF(void)), infoWindow, SLOT(refreshGIF(void)));
    infoWindow->Temperature = this->DHT22Worker->Temperature;
    infoWindow->Humidity = this->DHT22Worker->Humidity;
    infoWindow->Lux = this->TSL2591Worker->Lux ;
    infoWindow->Mode = this->Mode ;
    infoWindow->myCamera = this->myCamera ;
    infoWindow->showFullScreen();
    infoWindow->refreshInfo();
    infoWindow->refreshLux();
    QWidget::close();
}

void MainWindow::refreshInfo(QString* Temperature,QString* Humidity)
{
    qDebug("Temperature and Humidity received by MainWindow");
    this->Temperature = Temperature ;
    this->Humidity = Humidity ;
    refreshBackground();
}

void MainWindow::receiveLux(QString* Lux)
{
    qDebug("Lux received by MainWindow");
    this->Lux = Lux ;
    refreshBackground();
}

void MainWindow::receiveMode(bool Mode)
{
    qDebug("Mode received by MainWindow");
    this->Mode = Mode ;
}

void MainWindow::refreshBackground()
{
    QString newGifFileName ;
    bool switchingBackground = false ;

    if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : ON | Heater : ON | Light : ON");
        // Fan : ON | Watering : ON | Heater : ON | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_humide_chaud_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : ON | Heater : ON | Light : OFF");
        // Fan : ON | Watering : ON | Heater : ON | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_humide_chaud_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : ON | Heater : OFF | Light : ON");
        // Fan : ON | Watering : ON | Heater : OFF | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_humide_froid_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : ON | Heater : OFF | Light : OFF");
        // Fan : ON | Watering : ON | Heater : OFF | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_humide_froid_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : OFF | Heater : ON | Light : ON");
        // Fan : ON | Watering : OFF | Heater : ON | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_sec_chaud_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : OFF | Heater : ON | Light : OFF");
        // Fan : ON | Watering : OFF | Heater : ON | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_sec_chaud_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : OFF | Heater : OFF | Light : ON");
        // Fan : ON | Watering : OFF | Heater : OFF | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_sec_froid_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==1)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : ON | Watering : OFF | Heater : OFF | Light : OFF");
        // Fan : ON | Watering : OFF | Heater : OFF | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_sec_froid_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : ON | Heater : ON | Light : ON");
        // Fan : OFF | Watering : ON | Heater : ON | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_humide_chaud_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : ON | Heater : ON | Light : OFF");
        // Fan : OFF | Watering : ON | Heater : ON | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_humide_chaud_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : ON | Heater : OFF | Light : ON");
        // Fan : OFF | Watering : ON | Heater : OFF | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_humide_froid_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==1)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : ON | Heater : OFF | Light : OFF");
        // Fan : OFF | Watering : ON | Heater : OFF | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_humide_froid_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : OFF | Heater : ON | Light : ON");
        // Fan : OFF | Watering : OFF | Heater : ON | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_sec_chaud_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==1)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : OFF | Heater : ON | Light : OFF");
        // Fan : OFF | Watering : OFF | Heater : ON | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_sec_chaud_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==1))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : OFF | Heater : OFF | Light : ON");
        // Fan : OFF | Watering : OFF | Heater : OFF | Light : ON
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/ensoleille_sec_froid_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }else if((this->Faning->getPortState()==0)&&(this->Watering->getPortState()==0)&&(this->Heater->getPortState()==0)&&(this->Lightning->getPortState()==0))
    {
        qDebug("MainWindow background set to Fan : OFF | Watering : OFF | Heater : OFF | Light : OFF");
        // Fan : OFF | Watering : OFF | Heater : OFF | Light : OFF
        newGifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_sec_froid_pas_de_vent.gif" ;
        if(!(this->gifFileName == newGifFileName))
        {
            this->gifFileName = newGifFileName ;
            switchingBackground = true ;
        }
    }
    else
    {
        qDebug("MainWindow background ERROR");
        gifFileName = "/home/pi/Pictures/GreenHouse_UI_Design/GIFs/nuageux_sec_froid_pas_de_vent.gif" ;
    }

    if(switchingBackground)
    {
        qDebug("MainWindow background set to %s",gifFileName.toStdString().c_str());
        // Start GIF background
        // Load animated GIF
        QMovie* movie = new QMovie(gifFileName);

        // Make sure the GIF was loaded correctly
        if (!movie->isValid())
        {
            // Something went wrong :(
            qDebug("MainWindow background gif invalid");
        }

        // Play GIF
        ui->mainGIF->setMovie(movie);
        movie->start();
    }
}
