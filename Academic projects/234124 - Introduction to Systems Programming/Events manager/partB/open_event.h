#ifndef OPEN_EVENT_H_
#define OPEN_EVENT_H_

#include "base_event.h"
using namespace std;
using namespace mtm;

namespace mtm {

    class OpenEvent: public BaseEvent
    {
        public:
            OpenEvent(const DateWrap& date, const string name);
            OpenEvent(const OpenEvent& event);
            BaseEvent* clone() const override;
            ~OpenEvent() = default;
    };
}

#endif //OPEN_EVENT_H_