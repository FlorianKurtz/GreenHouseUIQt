#ifndef PLANT_H
#define PLANT_H

#include <QString>

class plant
{
public:
    plant();
    plant(int ident_id, QString name, QString description, int growing_days, int flowering_days, double day_temp, double night_temp, double hum, int growing_suntime, int flowering_suntime );

    QString name ;
    QString description ;
    int id ;

    int growing_days ;
    int flowering_days ;
    int growing_suntime ;
    int flowering_suntime ;

    int growing_days_left ;
    int flowering_days_left ;
    int project_days_left ;

    double beg_hour ;
    double end_hour ;
    double day_temp ;
    double night_temp ;
    double hum ;
    bool mode = false ; // FALSE -> GROWING | TRUE -> FLOWERING
    bool day_or_night = true ; // FALSE -> NIGHT | TRUE -> DAY

    // FUNCTIONS
    bool watering(void);
    int compare_id(int id);


private :

};

#endif // PLANT_H
