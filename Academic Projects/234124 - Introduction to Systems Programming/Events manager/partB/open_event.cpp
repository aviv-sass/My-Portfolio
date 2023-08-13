#include "open_event.h"
using namespace std;

namespace mtm {

    class OpenEvent;

    OpenEvent::OpenEvent(const DateWrap& date, string name): BaseEvent(date, name){}

    OpenEvent::OpenEvent(const OpenEvent& event): BaseEvent(event){}

    BaseEvent* OpenEvent::clone() const{
        return new OpenEvent(*this);
    } 

}