#include "plant.h"

plant::plant()
{

}

plant::plant(int ident_id, QString name, QString description, int growing_days, int flowering_days, double day_temp, double night_temp, double hum, int growing_suntime, int flowering_suntime )
{
    this->id = ident_id ;
    this->name = name ;
    this->description = description ;
    this->growing_days = growing_days ;
    this->flowering_days = flowering_days ;
    this->day_temp = day_temp ;
    this->night_temp = night_temp ;
    this->hum = hum ;
    this->growing_suntime = growing_suntime ;
    this->flowering_suntime = flowering_suntime ;
    this->growing_days_left = growing_days ;
    this->flowering_days_left = flowering_days ;
    this->project_days_left = growing_days + flowering_days ;

}

int plant::compare_id(int id)
{
    if (this->id == id)
    {
        return 1 ;
    }
    return 0 ;
}
