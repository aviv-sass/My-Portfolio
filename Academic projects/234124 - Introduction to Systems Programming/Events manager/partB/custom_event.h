#ifndef CUSTON_EVENT_H_
#define CUSTON_EVENT_H_
#include "base_event.h"
#include "../partA/exceptions.h"
#include <iostream>
#include <ostream>
using std::cout;
using std::endl;
using namespace std;

namespace mtm{
    template <class CanRegister>
    class CustomEvent: public BaseEvent{
        private:
            CanRegister condition;
        public:
            CustomEvent(const DateWrap& date, const string name,const CanRegister function);
            CustomEvent(const CustomEvent& event);
            void registerParticipant(int id) override; 
            BaseEvent* clone() const override;
            ~CustomEvent() = default;
    };

    template<class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap& date, const string name, CanRegister function):
                                BaseEvent(date, name), condition(function){}

    template<class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const CustomEvent& event): BaseEvent(event),condition(event.condition){}

    template<class CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        if(!condition(id)){
            throw RegistrationBlocked();
        }
        BaseEvent::registerParticipant(id);
    }

    template<class CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const{
        return new CustomEvent(*this);
    }
}

#endif //CUSTON_EVENT_H_