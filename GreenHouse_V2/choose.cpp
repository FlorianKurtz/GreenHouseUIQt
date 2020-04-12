#include "choose.h"
#include "ui_choose.h"

choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    setWindowTitle("Add or Choose your plant");
    ui->validate_button->hide();

    QString desc_tomato = "The tomato (see pronunciation) is the edible, often red, fruit of the plant Solanum lycopersicum, commonly known as a tomato plant. The plant belongs to the nightshade family, which is called Solanaceae.";
    QString desc_carottes = "The carrot (Daucus carota subsp. sativus) is a root vegetable, usually orange in colour, though purple, black, red, white, and yellow cultivars exist";
    QString desc_apple = "The apple tree (Malus pumila, commonly and erroneously called Malus domestica) is a deciduous tree in the rose family best known for its sweet, pomaceous fruit, the apple.";
    QString desc_rose = "A rose is a woody perennial flowering plant of the genus Rosa, in the family Rosaceae, or the flower it bears. There are over a hundred species and thousands of cultivars";

    tomato = new plant(0,"Tomatoes", desc_tomato,30,30, 22, 18,60 ,14,12);
    carot = new plant(1,"Carots", desc_carottes,45,30, 15, 10, 80,10,10);
    apple = new plant(2,"Apple", desc_apple,90,30, 22,16, 30,14,12);
    rose = new plant(3,"Rose", desc_rose,15,15,18, 18,70,12,12);

    list_plant.resize(100);
    list_plant[ident++] = *tomato ;
    list_plant[ident++] = *carot ;
    list_plant[ident++] = *apple ;
    list_plant[ident++] = *rose ;

    ui->plant_list_comboBox->addItem("Tomatoes");
    ui->plant_list_comboBox->addItem("Carots");
    ui->plant_list_comboBox->addItem("Apple");
    ui->plant_list_comboBox->addItem("Rose");

    connect(ui->plant_list_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(display_plant(int)));
    connect(ui->add_new_button,SIGNAL(clicked()),this,SLOT(open_new_plant()));
    connect(ui->validate_button,SIGNAL(clicked()),this, SLOT(validate()));
}

choose::~choose()
{
    delete ui;
}

void choose::open_new_plant()
{
    new_plant *new_plant_window = new new_plant();
    connect(new_plant_window,SIGNAL(new_plant_created(plant*)),this,SLOT(save_new_plant(plant*)));
    new_plant_window->showFullScreen();
}

void choose::save_new_plant(plant *new_p)
{
    actualPlant = new_p ;
    actualPlant->id = ident ;
    ui->plant_name_lineEdit->setText(actualPlant->name) ;
    ui->plant_desc_textEdit->setText(actualPlant->description) ;
    ui->temp_lcdNumber->display(actualPlant->day_temp);
    ui->watering_lcdNumber->display(actualPlant->hum);
    ui->growing_days_lcdNumber->display(actualPlant->growing_days);
    ui->flowering_days_lcdNumber->display(actualPlant->flowering_days);
    ui->growing_suntime_lcdNumber->display(actualPlant->growing_suntime);
    ui->flowering_suntime_lcdNumber->display(actualPlant->flowering_suntime);

    list_plant[ident++] = *actualPlant ;
    ui->plant_list_comboBox->addItem(actualPlant->name);
}

void choose::display_plant(int id)
{
    std::cout << id << std::endl ;

    for(int i = 0 ; i<list_plant.size() ; i++)
    {
        if(list_plant[i].compare_id(id) == 1)
        {
            std::cout <<"Plante choisie" << std::endl ;
            actualPlant = &list_plant[i] ;
            ui->plant_name_lineEdit->setText(actualPlant->name) ;
            ui->plant_desc_textEdit->setText(actualPlant->description) ;
            ui->temp_lcdNumber->display(actualPlant->day_temp);
            ui->watering_lcdNumber->display(actualPlant->hum);
            ui->growing_days_lcdNumber->display(actualPlant->growing_days);
            ui->flowering_days_lcdNumber->display(actualPlant->flowering_days);
            ui->growing_suntime_lcdNumber->display(actualPlant->growing_suntime);
            ui->flowering_suntime_lcdNumber->display(actualPlant->flowering_suntime);
        }
    }
    ui->validate_button->show();
}

void choose::validate()
{
    MainWindow *main = new MainWindow();
    connect(this,SIGNAL(send_actual_plant(plant*)),main,SLOT(get_info(plant*)));
    emit send_actual_plant(actualPlant);
    main->showFullScreen();
    QWidget::close();
    /*  GET DATE WINDOW
    getdatewindow *getdate = new getdatewindow();
    connect(this,SIGNAL(send_actual_plant(plant*)),getdate,SLOT(get_actual_plant(plant*)));
    emit send_actual_plant(actualPlant);
    getdate->showFullScreen();
    QWidget::close();*/
}
