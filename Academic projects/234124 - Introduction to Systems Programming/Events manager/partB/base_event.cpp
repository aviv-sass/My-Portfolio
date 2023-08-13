#include "base_event.h"

namespace mtm {

    class BaseEvent;

    BaseEvent::BaseEvent(const DateWrap& date, const string name): date_event(date), name_event(name){}

    BaseEvent::BaseEvent(const BaseEvent& event): date_event(event.date_event), 
        name_event(event.name_event),member_list(event.member_list){}

    void BaseEvent::registerParticipant(int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        Student *new_student = new Student(id);
        if(member_list.pqContains(new_student)){
            new_student->~Student();
            throw AlreadyRegistered();
        } 
        member_list.pqAddNode(new_student);  
    }

    void BaseEvent::unregisterParticipant(int id){
        if(id < MIN_NAMBER_DIGITS || id > MAX_NAMBER_DIGITS){
            throw InvalidStudent();
        }
        Student new_student(id);
        member_list.pqRemoveNode(&new_student);  
    }

    ostream& BaseEvent::printShort(ostream& os){
        os << name_event << " " << date_event << endl;
        return os;
    }

    ostream& BaseEvent::printLong(ostream& os){
        stringstream current_print_short;
        current_print_short << printShort(os).rdbuf();
        string final_string = current_print_short.str() += bePrintMemberList();
        return os << final_string;
    }

    string BaseEvent::bePrintMemberList(){
        string my_text = "";
        Student *current = member_list.pqGetFirst();
        while(current){
            my_text += to_string((*current).studentIdGet()) + "\n";
            current = member_list.pqGetNext();
        }
        return my_text;
    }

    BaseEvent* BaseEvent::clone() const{ 
        return new BaseEvent(*this);
    }

    DateWrap BaseEvent::beDateGet(){
        return date_event;
    }

    string BaseEvent::getName() const{
        return name_event;
    }

    bool BaseEvent::operator<(const BaseEvent& base_event){
        if(this->date_event == base_event.date_event){
            return this->name_event < base_event.name_event;
        }
        return this->date_event < base_event.date_event;
    }

    bool BaseEvent::operator>(const BaseEvent& base_event){
        if(this->date_event == base_event.date_event){
            return this->name_event > base_event.name_event;
        }
        return this->date_event > base_event.date_event;
    }

    bool BaseEvent::operator==(const BaseEvent& base_event){
        return this->date_event == base_event.date_event && this->name_event == base_event.name_event;
    }

    bool BaseEvent::operator!=(const BaseEvent& base_event){
        return !this->operator==(base_event);
    }

}
