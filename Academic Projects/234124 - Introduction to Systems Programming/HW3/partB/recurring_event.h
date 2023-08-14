#ifndef RECURRING_EVENT_H_
#define RECURRING_EVENT_H_

#include "event_container.h"

namespace mtm{
    template <class EventType>
    class RecurringEvent: public EventContainer{
        public:
            RecurringEvent(const DateWrap& date,const string name, const int num, const int days);
            RecurringEvent(const RecurringEvent& event);
            void add(const BaseEvent& event) override;
            ~RecurringEvent() = default;
    };

    template<class EventType>
    RecurringEvent<EventType>::RecurringEvent(const DateWrap& date,const string name, const int num, const int days){
        if(num < 1){
            throw InvalidNumber();
        }
        if(days < 1){
            throw InvalidInterval();
        }
        DateWrap date_change = date;
        for(int i=1;i<=num;i++){
            DateWrap date_to_add(date_change);
            EventType new_event(date_to_add,name);
            EventContainer::add(new_event);
            date_change += days;
        }   
    }

    template<class EventType>
    void RecurringEvent<EventType>::add(const BaseEvent& event){
        throw NotSupported();
    }
}

#endif // RECURRING_EVENT_H_