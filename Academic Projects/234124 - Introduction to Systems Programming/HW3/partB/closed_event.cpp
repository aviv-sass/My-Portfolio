#include "closed_event.h"
using namespace std;

namespace mtm {

    class ClosedEvent;

    ClosedEvent::ClosedEvent(const DateWrap date,string name): BaseEvent(date, name){}

    ClosedEvent::ClosedEvent(const ClosedEvent& event): BaseEvent(event),invited_list(event.invited_list){}

    void ClosedEvent::addInvitee(int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        Student *new_student = new Student(id);        
        if(invited_list.pqContains(new_student)){
            new_student->~Student();
            throw AlreadyInvited();
        }
        invited_list.pqAddNode(new_student);  
    }
    
    void ClosedEvent::registerParticipant(int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        Student new_student(id);
        if(!invited_list.pqContains(&new_student)){
            throw RegistrationBlocked();
        }
        BaseEvent::registerParticipant(id);
    }

    BaseEvent* ClosedEvent::clone() const{
        return new ClosedEvent(*this);
    }
}