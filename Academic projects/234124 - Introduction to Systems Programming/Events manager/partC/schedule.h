#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include "../partB/event_container.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <list> 
#include <iterator>
using std::cout;
using std::endl;
using namespace std;

namespace mtm {
    class Schedule{
        private:
            list<BaseEvent*> my_schedule;
        public:
            Schedule(){}
            Schedule(const Schedule& copy_schedule);
            /**
            * myFunctionSort: inserts the event in the right place in list.
            * @param event - Target event.
            */
            void myFunctionSort(BaseEvent* event);
            void addEvents(const EventContainer& container);
            void registerToEvent(const DateWrap& date, string name, int id);
            void unregisterFromEvent(const DateWrap& date, string name, int id);
            void printAllEvents() const;
            void printMonthEvents(int month, int year) const;
            template <typename Predicate>
            void printSomeEvents(Predicate predicate, bool verbose = false) const;
            void printEventDetails(const DateWrap& date, string name) const;
            ~Schedule() = default;
    };

    template <typename Predicate>
    void Schedule::printSomeEvents(Predicate predicate, bool verbose) const{
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            if(predicate(event_check)){
                if(verbose){
                    event_check.printLong(std::cout) << endl;
                }
                else{
                    event_check.printShort(std::cout) << endl;
                }
            }
        }
    }
}

#endif //SCHEDULE_H_