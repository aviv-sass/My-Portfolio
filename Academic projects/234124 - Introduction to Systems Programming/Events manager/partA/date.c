#include "date.h"
#include <stdlib.h>
#include <stdio.h>

#define MIN_MONTH 1
#define MIN_DAY 1
#define MAX_DAY 30
#define MAX_MONTH 12
#define DAYS_IN_YEAR 360

struct Date_t {
    int day;
    int month;
    int year; 
};

bool dateIsValid (int day, int month){
    if (day < MIN_DAY || day > MAX_DAY || month < MIN_MONTH || month > MAX_MONTH){
        return false;       
    }
    return true;
}

Date dateCreate(int day, int month, int year){
    if(!dateIsValid(day,month)){
        return NULL;
    }
    Date date = malloc(sizeof(*date));
    if(!date){
        return NULL;
    }
    date->day = day;
    date->month = month;
    date->year = year;
    return date;
}

void dateDestroy(Date date){
    if(!date){
        return;
    }
    free(date);
}

Date dateCopy(Date date){
    if(!date){
        return NULL;
    }
    return dateCreate(date->day,date->month,date->year);
}

bool dateGet(Date date, int* day, int* month, int* year){
    if(!date || !day || !month || !year){
        return false;
    }
    *day = date->day;
    *month = date->month;
    *year = date->year;
    return true;
}

int dateCompare(Date date1, Date date2){
    if(!date1 || !date2){
        return 0;
    }
    if(date1->year == date2->year){
        if(date1->month == date2->month){
            if(date1->day == date2->day){
                return 0;
            }
            return (date1->day > date2->day) ? 1:-1;
        }
        return (date1->month > date2->month) ? 1:-1;
    }
    return (date1->year > date2->year) ? 1:-1;
}

void dateTick(Date date){
    if(!date){
        return;
    }
    if(date->day == MAX_DAY){
        if(date->month == MAX_MONTH){
            date->day = MIN_DAY;
            date->month = MIN_MONTH;
            date->year = (int)(date->year)+1;
            return;
        }
        date->day = MIN_DAY;
        date->month = (int)(date->month)+1;
        return;
    }
    date->day = (int)(date->day)+1;
    return;
}