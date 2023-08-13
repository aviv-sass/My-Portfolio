#ifndef ONE_TIME_EVENT_H_
#define ONE_TIME_EVENT_H_

#include "event_container.h"

namespace mtm{
    template <class EventType>
    class OneTimeEvent: public EventContainer{
        public:
            OneTimeEvent(const DateWrap& date,const string name);
            OneTimeEvent(const OneTimeEvent& event);
            void add(const BaseEvent& event) override;
            ~OneTimeEvent() = default;
    };

    template<class EventType>
    OneTimeEvent<EventType>::OneTimeEvent(const DateWrap& date,const string name){
        EventType event(date,name);
        EventContainer::add(event);
    }

    template<class EventType>
    OneTimeEvent<EventType>::OneTimeEvent(const OneTimeEvent& event): EventContainer(event){}

    template<class EventType>
    void OneTimeEvent<EventType>::add(const BaseEvent& event){
        throw NotSupported();
    }
}

#endif // ONE_TIME_EVENT_H_