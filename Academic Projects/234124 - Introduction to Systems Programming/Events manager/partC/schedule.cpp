#include "schedule.h"
 std::list<BaseEvent*>::iterator it;

namespace mtm {
    
    class Schedule;

    Schedule::Schedule(const Schedule& copy_schedule):my_schedule(copy_schedule.my_schedule){}

    typedef EventContainer::EventIterator container_iterator;

    void Schedule::myFunctionSort(BaseEvent* event_to_add){
        for(it = my_schedule.begin(); it != my_schedule.end(); ++it){
            BaseEvent& event_check = **it;
            if(*event_to_add > event_check){
                continue;
            }
            my_schedule.insert(it,event_to_add);
            return;
        }
        my_schedule.push_back(event_to_add);
    }

    void Schedule::addEvents(const EventContainer& events){
        EventContainer help_cont(events); 
        for(container_iterator i = help_cont.begin(); i != help_cont.end(); ++i){
            BaseEvent& event = *i;
            for(it = my_schedule.begin(); it != my_schedule.end(); ++it){
                BaseEvent& event_check = **it;
                if(event_check == event){
                    throw EventAlreadyExists();
                }
            }
        }
        for(container_iterator i = help_cont.begin(); i != help_cont.end(); ++i){
            BaseEvent& event = *i;
            myFunctionSort(&event);
        }
    }

    void Schedule::registerToEvent(const DateWrap& date, string name, int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        BaseEvent help_event(date,name);
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            if(event_check > help_event){
                throw EventDoesNotExist();
            }
            if(event_check == help_event){
                event_check.registerParticipant(id);
                return;
            }
        }
        throw EventDoesNotExist();
    }

    void Schedule::unregisterFromEvent(const DateWrap& date, string name, int id){
        BaseEvent help_event(date,name);
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            if(event_check == help_event){
                event_check.unregisterParticipant(id);
                return;
            }
        }
        throw EventDoesNotExist();
    }

    void Schedule::printAllEvents() const{
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            event_check.printShort(cout);
            cout << endl;
        }
    }

    void Schedule::printMonthEvents(int month, int year) const{
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            DateWrap current_date = event_check.beDateGet();
            int current_year = current_date.year();
            if(current_year > year){
                return;
            }
            if(current_year < year){
                continue;
            }
            int current_month = current_date.month();
            if(current_month > month){
                return;
            }
            if(current_month < month){
                continue;
            }
            event_check.printShort(cout);
            cout << endl;
        }
    }
    
    void Schedule::printEventDetails(const DateWrap& date, string name) const{
        BaseEvent help_event(date,name);
        for(BaseEvent* event : my_schedule){
            BaseEvent& event_check = *event;
            if(event_check == help_event){
                event_check.printLong(cout);
                cout << endl;
                return;
            }
        }
        throw EventDoesNotExist();
    }
}