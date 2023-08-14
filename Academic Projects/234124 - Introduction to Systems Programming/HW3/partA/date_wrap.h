#ifndef DATE_WRAP_H_
#define DATE_WRAP_H_
#include<iostream>
#include "exceptions.h"
extern "C" {
    #include "date.h"
}
using std::cout;
using std::endl;
using namespace std;

namespace mtm {

    class DateWrap{
        private:
            Date date = NULL;
        
        public:
            DateWrap(int day, int month, int year);
            DateWrap(const DateWrap& wrraped_date);
            const int day() const;
            const int month() const;
            const int year() const;
            
            /**
            * dwGetDate: get the date.
            * @return :
            * 	a date.
            */ 
            const Date dwGetDate() const{
                Date copy_date = this->date;
                return copy_date;
            }
            bool operator<(const DateWrap& wrraped_date);
            bool operator>(const DateWrap& wrraped_date);
            bool operator==(const DateWrap& wrraped_date);
            bool operator<=(const DateWrap& wrraped_date);
            bool operator>=(const DateWrap& wrraped_date);
            bool operator!=(const DateWrap& wrraped_date);
            DateWrap operator++(int);
            DateWrap& operator+=(int days);
            friend ostream& operator<<(ostream& os, const DateWrap& wrraped_date);
            DateWrap& operator=(const DateWrap& wrraped_date);
            ~DateWrap();
    };

    DateWrap operator+(DateWrap& wrraped_date, int days);

    DateWrap operator+(int days, DateWrap& wrraped_date);

}

#endif //DATE_WRAP_H_
