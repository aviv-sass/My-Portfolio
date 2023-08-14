#ifndef FESTIVAL_H_
#define FESTIVAL_H_
#include "event_container.h"
#include "base_event.h"
#include <typeinfo>

using namespace std;


namespace mtm {
    class Festival: public EventContainer{
        private:
            DateWrap festival_date;
        public:
            Festival(const DateWrap& date);
            Festival(const Festival& events);
            void add(const BaseEvent& event) override;
            ~Festival() = default;
    };
}
#endif //FESTIVAL_H_