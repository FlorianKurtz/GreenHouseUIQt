#include "culture_task.h"

culture_task::culture_task()
{
    actualDate = new QDate();
    endGrowingDate = new QDate();
    endFloweringDate = new QDate();
    actualTime = new QTime();
}

void culture_task::run()
{
    *actualDate = QDate::currentDate();
    *endGrowingDate = actualDate->addDays(actualPlant->growing_days);
    *endFloweringDate = actualDate->addDays(actualPlant->flowering_days);

    while(1)
    {
        *actualDate = QDate::currentDate();
        actualPlant->growing_days_left = actualDate->daysTo(*endGrowingDate);
        actualPlant->flowering_days_left = actualDate->daysTo(*endFloweringDate);
        actualPlant->project_days_left = actualPlant->growing_days_left + actualPlant->flowering_days_left ;

        *actualTime = QTime::currentTime();

        actualTemp = getTemp();
        actualHum = getHum();

        if(actualPlant->growing_days_left>0)    // GROWING MODE
        {
            actualPlant->mode = false ;
        }
        else                                    // FLOWERING MODE
        {
            actualPlant->mode = false ;
        }

        if((actualTime->hour() < actualPlant->beg_hour) && (actualTime->hour() > actualPlant->end_hour))
        {
            actualPlant->day_or_night = false ;
        }
        else
        {
            actualPlant->day_or_night = true ;
        }

        // CONTROL FUNCTION
        control();
        // REFRESH INFO ON MAIN PAGE
        emit send_refresh();

        sleep(1);
    }
}

void culture_task::control(void)
{
    heating();
    watering();
    fan();
    lightning();
}

void culture_task::heating(void)
{
    switch(mode_heating)
    {
    case 0 :    // OFF
        break;
    case 1 :    // ON
        break;
    case 2 :    // AUTO
        // REGULATION
        if(actualPlant->day_or_night)
        {
            if(actualTemp < actualPlant->day_temp)
            {
                // ON
            }
            else
            {
                // OFF
            }
        }
        else
        {
            if(actualTemp < actualPlant->night_temp)
            {
                // ON
            }
            else
            {
                // OFF
            }
        }
        break ;
    default :
        break ;
    }
}

void culture_task::watering(void)
{
    switch(mode_watering)
    {
    case 0 :    // OFF
        break;
    case 1 :    // ON
        break;
    case 2 :    // AUTO
        // REGULATION
        if(actualHum < actualPlant->hum)
        {
            // ON
        }
        else
        {
            // OFF
        }
        break ;
    default :
        break ;
    }
}

void culture_task::fan(void)
{
    switch(mode_fan)
    {
    case 0 :    // OFF
        break;
    case 1 :    // ON
        break;
    case 2 :    // AUTO
        // REGULATION
        if(actualPlant->day_or_night)
        {
            if(actualTemp > actualPlant->day_temp)
            {
                // ON
            }
            else
            {
                // OFF
            }
        }
        else
        {
            if(actualTemp > actualPlant->night_temp)
            {
                // ON
            }
            else
            {
                // OFF
            }
        }
        break ;
    default :
        break ;
    }
}

void culture_task::lightning(void)
{
    switch(mode_lightning)
    {
    case 0 :    // OFF
        break;
    case 1 :    // ON
        break;
    case 2 :    // AUTO
        // REGULATION
        if(actualPlant->day_or_night)
        {
            // ON
        }
        else
        {
            // OFF
        }
        break ;
    default :
        break ;
    }
}

double culture_task::getTemp(void)
{
    double temp = 0 ;
    // GET SENSOR VALUE
    return temp ;
}

double culture_task::getHum(void)
{
    double hum = 0 ;
    // GET SENSOR VALUE
    return hum ;
}

void culture_task::get_mode_watering(int mode) // 0 = OFF // 1 = ON // 2 = AUTO
{
    mode_watering = mode;
}

void culture_task::get_mode_heating(int mode) // 0 = OFF // 1 = ON // 2 = AUTO
{
    mode_heating = mode;
}

void culture_task::get_mode_fan(int mode) // 0 = OFF // 1 = ON // 2 = AUTO
{
    mode_fan = mode;
}
void culture_task::get_mode_lightning(int mode) // 0 = OFF // 1 = ON // 2 = AUTO
{
    mode_lightning = mode;
}
void culture_task::get_plant(plant *plant)
{
    actualPlant = plant ;
}
