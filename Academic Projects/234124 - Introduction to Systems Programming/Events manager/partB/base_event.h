#ifndef BASE_EVENT_H_
#define BASE_EVENT_H_
#include "PriorityQueue.h"
#include "student.h"
#include "../partA/exceptions.h"
#include "../partA/date_wrap.h"
#include "../partA/exceptions.h"
#include <iostream>
#include <sstream>
#include <string>
#define MAX_NAMBER_DIGITS 1234567890
#define MIN_NAMBER_DIGITS 1
using namespace std;

namespace mtm {
    class BaseEvent{
        private:
            DateWrap date_event;
            string name_event; 
            PriorityQueue<Student*> member_list;

            BaseEvent(const DateWrap& date, const string name);
            BaseEvent(const BaseEvent& event);
            virtual void registerParticipant(int id);
            virtual void unregisterParticipant(int id);
            virtual ostream& printShort(ostream& os);
            virtual ostream& printLong(ostream& os);
            
            /**
            * bePrintMemberList: Organize the text for printing a list of participants.
            * @return :
            * 	a string with the information about the participants.
            */
            string bePrintMemberList();
            virtual BaseEvent* clone() const;
            
            /**
            * beDateGet: get the date of the event.
            * @return :
            *   DateWrap of the date.
            */
            DateWrap beDateGet();
            
            /**
            * getName(): get the name of the event.
            * @return :
            * 	string with the name.
            */
            string getName() const;
            virtual ~BaseEvent() = default;

            bool operator<(const BaseEvent& base_event);
            bool operator>(const BaseEvent& base_event);
            bool operator==(const BaseEvent& base_event);
            bool operator!=(const BaseEvent& base_event);
    };
}
#endif //BASE_EVENT_H_