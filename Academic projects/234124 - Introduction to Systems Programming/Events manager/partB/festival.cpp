#include "festival.h"

namespace mtm {
    class Festival;

    Festival::Festival(const DateWrap& date):festival_date(date){}
    
    Festival::Festival(const Festival& events):EventContainer(events)
        ,festival_date(DateWrap(events.festival_date)){}
    
    void Festival::add(const BaseEvent& event){
        if(typeid(event) == typeid(BaseEvent)){
           throw NotSupported();
        }
        BaseEvent copy_event(event);
        if(copy_event.beDateGet() != festival_date){
            throw DateMismatch();
        }
        EventContainer::add(event);
    }
}