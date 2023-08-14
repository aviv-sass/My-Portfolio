#include "event_container.h"
using namespace std;

namespace mtm {

    class EventContainer;
    
    EventContainer::EventContainer(){}
    
    EventContainer::EventContainer(const EventContainer& events):events_list(events.events_list){}

    void EventContainer::add(const BaseEvent& event){
        BaseEvent* new_event = event.clone();
        if(events_list.pqContains(new_event)){
            new_event->~BaseEvent();
            throw EventAlreadyExists();
        }
        events_list.pqAddNode(new_event);
    }

    EventContainer::EventIterator EventContainer::begin(){
        EventIterator head(events_list.pqGetFirstNode());
        return head;
    }

    EventContainer::EventIterator EventContainer::end(){
        EventIterator tail(0);
        return tail;
    }

    EventContainer::EventIterator::EventIterator(Node<BaseEvent*>* it):node_iter(it){}

    EventContainer::EventIterator::EventIterator(const EventIterator& it):node_iter(it.node_iter){}

    EventContainer::EventIterator EventContainer::EventIterator::operator++(){
        node_iter = node_iter->nodeGetNext();
        return *this;
    }
    
    EventContainer::EventIterator& EventContainer::EventIterator::operator=(const EventIterator& it){
        if(&it == this){
            return *this;
        }
        node_iter = it.node_iter;
        return *this;
    }
    
    BaseEvent& EventContainer::EventIterator::operator*(){
        return *node_iter->nodeGetData();
    }
    
    bool EventContainer::EventIterator::operator==(const EventContainer::EventIterator& it){
        return it.node_iter == node_iter;
    }
    
    bool EventContainer::EventIterator::operator!=(const EventContainer::EventIterator& it){
        return it.node_iter != node_iter;
    }

}
