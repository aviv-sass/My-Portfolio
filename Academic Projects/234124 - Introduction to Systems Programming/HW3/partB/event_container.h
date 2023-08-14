#ifndef EVENT_CONTAINER_H_
#define EVENT_CONTAINER_H_
#include "PriorityQueue.h"
#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include "base_event.h"
#include "open_event.h"
#include "closed_event.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


namespace mtm {
    class EventContainer{
        protected:
            PriorityQueue<BaseEvent*> events_list;
        public:
            class EventIterator{
                protected:
                    Node<BaseEvent*>* node_iter;
                public:
                    friend class EventContainer;
                    explicit EventIterator(Node<BaseEvent*>* it = nullptr);
                    EventIterator(const EventIterator& it);
                    EventIterator operator++();
                    EventIterator& operator=(const EventIterator& it);
                    BaseEvent& operator*();
                    bool operator==(const EventIterator& it);
                    bool operator!=(const EventIterator& it);
            };
            friend class EventIterator;
            EventContainer();
            EventContainer(const EventContainer& events);
            virtual void add(const BaseEvent& event);
            EventIterator begin();
            EventIterator end();
            virtual ~EventContainer() = default;

    };
}
#endif //EVENT_CONTAINER_H_