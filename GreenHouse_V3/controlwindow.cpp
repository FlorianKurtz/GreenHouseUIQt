#include "controlwindow.h"
#include "ui_controlwindow.h"

#define HEATER_PORT 24
#define WATERING_PORT 23
#define LIGHTNING_PORT 22
#define FANING_PORT 27

ControlWindow::ControlWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    QPalette palette ;

    QPixmap backgroundImage("/home/pi/Pictures/GreenHouse_UI_Design/Background/control-page.jpg");
    ui->backgrounLabel->setPixmap(backgroundImage);

    // Create GPIOs
    // Setup GPIOS
    this->Heater = new GPIO();
    this->Watering = new GPIO();
    this->Lightning = new GPIO();
    this->Faning = new GPIO();

    this->Heater->setPort(HEATER_PORT) ;
    this->Watering->setPort(WATERING_PORT) ;
    this->Lightning->setPort(LIGHTNING_PORT) ;
    this->Faning->setPort(FANING_PORT) ;

    if(this->Faning->getPortState()==1)
    {
        ui->faningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/ventilation_on.png);");
    }else
    {
        ui->faningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/ventilation_off.png);");
    }

    if(this->Watering->getPortState()==1)
    {
        ui->wateringButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/arrosage_on.png);");
    }else
    {
        ui->wateringButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/arrosage_off.png);");
    }

    if(this->Heater->getPortState()==1)
    {
        ui->heatingButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/chauffage_on.png);");
    }else
    {
        ui->heatingButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/chauffage_off.png);");
    }

    if(this->Lightning->getPortState()==1)
    {
        ui->lightningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/lumiere_on.png);");
    }else
    {
        ui->lightningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/lumiere_off.png);");
    }

    connect(ui->gotoMainPageButton,SIGNAL(clicked()),this, SLOT(openMainWindow()));
    connect(ui->faningButton,SIGNAL(clicked()),this, SLOT(faningButtonSlot()));
    connect(ui->wateringButton,SIGNAL(clicked()),this, SLOT(wateringButtonSlot()));
    connect(ui->lightningButton,SIGNAL(clicked()),this, SLOT(lightningButtonSlot()));
    connect(ui->heatingButton,SIGNAL(clicked()),this, SLOT(heatingButtonSlot()));

}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::openMainWindow()
{
    MainWindow *mainWindow = new MainWindow();
    connect(this, SIGNAL (sendMode(bool)), mainWindow, SLOT(receiveMode(bool)));
    mainWindow->showFullScreen();
    emit sendMode(this->Mode);
    QWidget::close();
}

void ControlWindow::faningButtonSlot()
{
    if(this->Mode == false)
    {
        if(this->Faning->getPortState()==1)
        {
            ui->faningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/ventilation_off.png);");
            this->Faning->disablePort();
        }else
        {
            ui->faningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/ventilation_on.png);");
            this->Faning->enablePort();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Secret mode enable");
        msgBox.exec();
    }
}

void ControlWindow::wateringButtonSlot()
{
    if(this->Mode == false)
    {
        if(this->Watering->getPortState()==1)
        {
            ui->wateringButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/arrosage_off.png);");
            this->Watering->disablePort();
        }else
        {
            ui->wateringButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/arrosage_on.png);");
            this->Watering->enablePort();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Secret mode enable");
        msgBox.exec();
    }
}

void ControlWindow::heatingButtonSlot()
{
    if(this->Mode == false)
    {
        if(this->Heater->getPortState()==1)
        {
            ui->heatingButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/chauffage_off.png);");
            this->Heater->disablePort();
        }else
        {
            ui->heatingButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/chauffage_on.png);");
            this->Heater->enablePort();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Secret mode enable");
        msgBox.exec();
    }
}

void ControlWindow::lightningButtonSlot()
{
    if(this->Mode == false)
    {
        if(this->Lightning->getPortState()==1)
        {
            ui->lightningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/lumiere_off.png);");
            this->Lightning->disablePort();
        }else
        {
            ui->lightningButton->setStyleSheet("border-image:url(/home/pi/Pictures/GreenHouse_UI_Design/Buttons/lumiere_on.png);");
            this->Lightning->enablePort();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Secret mode enable");
        msgBox.exec();
    }
}

void ControlWindow::receiveMode(bool Mode)
{
    qDebug("Mode received by ControlWindow");
    this->Mode = Mode ;
}

