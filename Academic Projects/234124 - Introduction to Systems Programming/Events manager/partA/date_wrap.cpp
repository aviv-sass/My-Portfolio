#include "date_wrap.h"
#include "exceptions.h"
using namespace std;


namespace mtm {

    class DateWrap;

    DateWrap::DateWrap(int day, int month, int year):date(dateCreate(day,month,year)){
        if(date == NULL){
            throw InvalidDate(); 
        }
    }

    DateWrap::DateWrap(const DateWrap& wrraped_date):date(dateCopy(wrraped_date.date)){}

    const int DateWrap::day() const{
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return day;
    }

    const int DateWrap::month() const{
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return month;
    }

    const int DateWrap::year() const{
        int day, month, year;
        dateGet(date, &day, &month, &year);
        return year;
    }

    bool DateWrap::operator<(const DateWrap& wrraped_date){
        return dateCompare(date, wrraped_date.date) < 0;
    }

    bool DateWrap::operator>(const DateWrap& wrraped_date){
        return dateCompare(date, wrraped_date.date) > 0;
    }

    bool DateWrap::operator==(const DateWrap& wrraped_date){
        return !(this->operator<(wrraped_date)) && !(this->operator>(wrraped_date));
    }

    bool DateWrap::operator<=(const DateWrap& wrraped_date){
        return this->operator<(wrraped_date) || this->operator==(wrraped_date);
    }

    bool DateWrap::operator>=(const DateWrap& wrraped_date){
        return this->operator>(wrraped_date) || this->operator==(wrraped_date);
    }

    bool DateWrap::operator!=(const DateWrap& wrraped_date){
        return !this->operator==(wrraped_date);
    }

    DateWrap DateWrap::operator++(int){
        DateWrap temp = *this;
        dateTick(date);
        return temp;
    }

    DateWrap& DateWrap::operator+=(int days){ 
        if(days < 0){
            throw NegativeDays();
        }
        int i = 0;
        while(i < days){
            this->operator++(0);
            i++;
        }
        return *this;
    }

    ostream& operator<<(ostream& os, const DateWrap& wrraped_date){
        int day, month, year;
        dateGet(wrraped_date.dwGetDate(), &day, &month, &year);
        return os << day << "/" << month << "/" << year;
    }

    DateWrap operator+(DateWrap& wrraped_date, int days){ 
        if(days < 0){
            throw NegativeDays();
        }
        DateWrap new_date = DateWrap(wrraped_date); 
        return new_date+=(days);
    }

    DateWrap operator+(int days, DateWrap& wrraped_date){
        DateWrap new_date = DateWrap(wrraped_date); 
        return new_date+(days);
    }

    DateWrap& DateWrap::operator=(const DateWrap& wrraped_date){ 
        if(this == &wrraped_date){
            return *this;
        }
        dateDestroy(date);
        Date temp = dateCreate(wrraped_date.day(), wrraped_date.month(), wrraped_date.year());
        date = temp;
        return *this;
    }

    DateWrap::~DateWrap() {
        dateDestroy(date);
    }

}


