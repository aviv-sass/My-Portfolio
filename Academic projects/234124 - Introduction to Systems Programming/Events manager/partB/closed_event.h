#ifndef CLOSED_EVENT_H_
#define CLOSED_EVENT_H_


#include "base_event.h"

namespace mtm {

    class ClosedEvent: public BaseEvent
    {
        private:
            PriorityQueue<Student*> invited_list;
        public:
            ClosedEvent(const DateWrap date, const string name);
            ClosedEvent(const ClosedEvent& event);
            void registerParticipant(int id) override; 
            BaseEvent* clone() const override;
            void addInvitee(int id);
            ~ClosedEvent() = default;
    };
}

#endif //CLOSED_EVENT_H_