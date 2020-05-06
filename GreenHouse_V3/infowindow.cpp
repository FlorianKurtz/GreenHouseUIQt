#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/info-page-text.jpg");
    ui->backgroundLabel->setPixmap(backgroundImage);

    ui->customPlot->setVisible(false);
    ui->customPlot->addGraph(); // Humidity graph
    ui->customPlot->addGraph(); // Temperature graph
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis2); // Light graph
    for (int gi=0; gi<3; gi++)
    {
        if(gi == 0)
        {
            QColor color("darkBlue");
            ui->customPlot->graph(gi)->setName("Humidity");
            ui->customPlot->graph(gi)->setPen(QPen(color.lighter(200)));

        }else if(gi==1)
        {
            QColor color("darkRed");
            ui->customPlot->graph(gi)->setName("Temperature");
            ui->customPlot->graph(gi)->setPen(QPen(color.lighter(200)));

        }else
        {
            QColor color("darkYellow");
            ui->customPlot->graph(gi)->setName("Light");
            ui->customPlot->graph(gi)->setPen(QPen(color.lighter(200)));
        }
    }

    connect(ui->gotoMainPageButton,SIGNAL(clicked()),this, SLOT(openMainWindow()));
    connect(ui->resetGifButton,SIGNAL(clicked()),this, SLOT(resetGif()));
    connect(ui->displayModeButton,SIGNAL(clicked()),this, SLOT(changeDisplayMode()));
    connect(ui->takePictureButton,SIGNAL(clicked()),this,SLOT(takeNewPicture()));

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
    connect(this, SIGNAL (sendMode(bool)), mainWindow, SLOT(receiveMode(bool)));
    mainWindow->showFullScreen();
    emit sendMode(this->Mode);
    QWidget::close();
}

void InfoWindow::receiveInfo(QString* Temperature,QString* Humidity)
{
    qDebug("Temperature and Humidity received by InfoWindow");
    this->Temperature = Temperature ;
    this->Humidity = Humidity ;
    // Plotting part
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();

    QCPGraphData currentHumidity, currentTemperature ;
    currentHumidity.key = now ;
    currentHumidity.value = this->Humidity->toDouble() ;
    currentTemperature.key = now ;
    currentTemperature.value = this->Temperature->toDouble() ;
    if(currentHumidity.value<100)
    {
        this->humidityData.append(currentHumidity);
    }
    this->temperatureData.append(currentTemperature);

    if(this->displayMode == 1)
    {
        refreshPlot() ;
    }else{
        refreshInfo() ;
    }
}

void InfoWindow::receiveLux(QString* Lux)
{
    qDebug("Lux received by InfoWindow");
    this->Lux = Lux ;
    // Plotting part
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();

    QCPGraphData currentLux ;
    currentLux.key = now ;
    currentLux.value = this->Lux->toDouble() ;
    this->luxData.append(currentLux);

    if(this->displayMode == 1)
    {
        refreshPlot() ;
    }else{
        refreshLux() ;
    }
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

void InfoWindow::receiveMode(bool Mode)
{
    qDebug("Mode received by InfoWindow");
    this->Mode = Mode ;
}

void InfoWindow::resetGif()
{
    // ResetGif
    QMessageBox msgBox;
    msgBox.setText("All the pictures taken will be deleted");
    msgBox.setInformativeText("Are you sure to remove them ?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Reset);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec() ;
    switch (ret) {
        case QMessageBox::Reset:
            // Don't Save was clicked
            qDebug("GIF resetted");
            QProcess::execute("python /home/pi/Pictures/resetGIF.py");
            refreshGIF();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            break;
        default:
            // should never be reached
            break;
    }
}

void InfoWindow::changeDisplayMode()
{
    if(this->displayMode)
    {
        qDebug("Display mode to textual");
        this->displayMode = false;
        // Switch background to textual
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/info-page-text.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
        // Switch display mode to writing
        ui->dateLabel->setVisible(true);
        ui->humLabel->setVisible(true);
        ui->tempLabel->setVisible(true);
        ui->lightLabel->setVisible(true);
        ui->customPlot->setVisible(false);
        refreshInfo();
    }else
    {
        qDebug("Display mode to graphical");
        this->displayMode = true;
        // Switch background to graphical
        QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/info-page-graph.jpg");
        ui->backgroundLabel->setPixmap(backgroundImage);
        // Switch display mode to plotting
        ui->dateLabel->setVisible(false);
        ui->humLabel->setVisible(false);
        ui->tempLabel->setVisible(false);
        ui->lightLabel->setVisible(false);
        ui->customPlot->setVisible(true);
        refreshPlot();
    }
}

void InfoWindow::refreshPlot()
{
    qDebug("Refreshing plot");
    // set locale to english, so we get english month names:
    ui->customPlot->setLocale(QLocale(QLocale::French, QLocale::France));
    for (int gi=0; gi<3; gi++)
    {
      if(gi == 0)
      {
          ui->customPlot->graph(gi)->data()->set(this->humidityData);
      }
      else if(gi == 1)
      {
          ui->customPlot->graph(gi)->data()->set(this->temperatureData);
      }
      else
      {
          ui->customPlot->graph(gi)->data()->set(this->luxData);
      }
    }
    // set a more compact font size for bottom and left axis tick labels:
    ui->customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 6));
    ui->customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 6));
    ui->customPlot->yAxis2->setTickLabelFont(QFont(QFont().family(), 6));
    ui->customPlot->xAxis->setLabelFont(QFont(QFont().family(), 8));
    ui->customPlot->yAxis->setLabelFont(QFont(QFont().family(), 8));
    ui->customPlot->yAxis2->setLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    ui->customPlot->xAxis->setLabel("Date and Clock");
    ui->customPlot->yAxis->setLabel("Temperature (°C) / Humidity (%)");
    ui->customPlot->yAxis2->setLabel("Light (Lux)");
    // make top and right axes visible but without ticks and labels:
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->xAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    if(temperatureData.length()>1)
    {
        // configure bottom axis to show date instead of number:
        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
        dateTicker->setDateTimeFormat("d/MM/yy\nHH:mm");
        ui->customPlot->xAxis->setTicker(dateTicker);
        ui->customPlot->xAxis->setRange(temperatureData[0].key, temperatureData[temperatureData.length()-1].key);
    }
    ui->customPlot->yAxis->setRange(0, 100);
    ui->customPlot->yAxis2->setRange(0, 1000);
    // show legend with slightly transparent background brush:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    ui->customPlot->replot();
}

void InfoWindow::refreshInfo()
{
    ui->humLabel->setText(this->Humidity->append("%"));
    ui->tempLabel->setText(this->Temperature->append("°C"));
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("ddd MMMM d yyyy HH:mm"));
}

void InfoWindow::refreshLux()
{
    double doubleLux = this->Lux->toDouble() ;
    QString *doubleLuxSetup = new QString(QString::number(doubleLux,'f',2));
    this->Lux = doubleLuxSetup ;
    ui->lightLabel->setText(this->Lux->append("Lux"));
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("ddd MMMM d yyyy HH:mm"));
}

void InfoWindow::takeNewPicture()
{
    this->myCamera->takePicture();
    this->myCamera->makeGIF();
    refreshGIF();
}
