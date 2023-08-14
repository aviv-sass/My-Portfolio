#include "event.h"

#define ERROR -1

//---------------------------------------------------------------------------------------------

//---------------------------------genric func for member id-----------------------------------

//---------------------------------------------------------------------------------------------

PQElement eventCopyMemberIdGeneric(PQElement element){
    return memberCopy((Member)element);
}

void eventFreeMemberIdGeneric(PQElement element){
    memberFree((Member)element);
}

bool eventEqualMembersIdGeneric(PQElement element1, PQElement element2){
    return memberEqual((Member)element1, (Member)element2);
}

PQElementPriority eventCopyMemberIdPriorityGeneric(PQElementPriority n) {
    if (!n) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

void eventFreeMemberIdPriorityGeneric(PQElementPriority n) {
    free(n);
}

int eventCompareMemberIdsPriorityGeneric(PQElementPriority n1, PQElementPriority n2) {
    return (*(int *) n2 - *(int *) n1);
}

//---------------------------------------------------------------------------------------------

//---------------------------------------func for event----------------------------------------

//---------------------------------------------------------------------------------------------

struct event_t{
    Date eventDate;
    char* eventName;
    int eventId;
    PriorityQueue membersListById;
};

void eventFree(Event event){
    if(!event){
        return;
    }
    pqDestroy(event->membersListById);
    free(event->eventName);
    dateDestroy(event->eventDate);
    free(event);
    return;
}

Event eventCreate(char* name, int id, Date date){
    if(!name || !date){
        return NULL;
    }
    Event event = malloc(sizeof(*event));
    if(!event){
        return NULL;
    }
    Date my_date = dateCopy(date);
    if(!my_date){
        eventFree(event);
        return NULL;
    }
    char* my_name = stringDuplicate(name);
    if(!my_name){
        eventFree(event);
        dateDestroy(my_date);
        return NULL;
    }
    event->eventName = my_name;
    event->eventId = id;
    event->eventDate = my_date;
    event->membersListById = NULL;
    return event;  
}

Event eventCopy(Event event){
    if (!event) {
        return NULL;
    }
    Event event_copy = eventCreate(event->eventName,event->eventId,event->eventDate);
    if(!event_copy){
        return NULL;
    }
    if(event->membersListById != NULL){
        PriorityQueue members_id_copy = pqCopy(event->membersListById);
        if(!members_id_copy){
            eventFree(event_copy);
            return NULL;
        }
        event_copy->membersListById = members_id_copy;
    }
    return event_copy; 
}

bool eventEqual(Event event1, Event event2){
    if(!event1 || !event2){
        return false;
    }
    return event1->eventId == event2->eventId;
}

//---------------------------------------------------------------------------------------------

//----------------------------------------help func--------------------------------------------

//---------------------------------------------------------------------------------------------

Date eventGetDate(Event event){
    return !event ? NULL : event->eventDate;
}

char* eventGetName(Event event){
    return !event ? NULL : event->eventName;
}

int eventGetId(Event event){
    return !event ? ERROR: event->eventId;
}

int eventGetFirstIdMember(Event event){
    if(!event || !event->membersListById){
        return ERROR;
    }
    PriorityQueue member_id = event->membersListById;
    Member member = (Member)pqGetFirst(member_id);
    if(!member){
        pqDestroy(member_id);
        event->membersListById = NULL;
        return ERROR;
    }
    int id = memberGetId(member);
    if(id == ERROR){
        return ERROR;
    }
    if(pqRemove(member_id) != PQ_SUCCESS){
        return ERROR;
    }
    member = (Member)pqGetFirst(member_id);
    if(member == NULL){
        pqDestroy(member_id);
        event->membersListById = NULL;
    }
    return id;
}

bool eventCheckIfIdMemberExist(Event event, int id){
    if(!event || !event->membersListById){
        return false;
    }
    PriorityQueue pqMembersId = event->membersListById;
    PQElement member = pqGetFirst(pqMembersId);
    if(!member){
        pqDestroy(event->membersListById);
        event->membersListById = NULL;
        return false;
    }
    while(member){
        Member current_member = (Member)member;
        int member_id = memberGetId(current_member);
        if(member_id == ERROR){
            return false;
        }
        if(member_id == id){
            return true;
        }
        member = pqGetNext(pqMembersId);
    }
    return false;
}

PriorityQueueResult eventAddMember(Event event, Member member, int id){
    if(!event || !member){
        return PQ_NULL_ARGUMENT;
    }
    bool flag = false; // if Create A New Members List
    if(event->membersListById == NULL){
        PriorityQueue members_id = pqCreate(eventCopyMemberIdGeneric,eventFreeMemberIdGeneric,
                            eventEqualMembersIdGeneric,eventCopyMemberIdPriorityGeneric,
                            eventFreeMemberIdPriorityGeneric,eventCompareMemberIdsPriorityGeneric);
        if(!members_id){
            return PQ_OUT_OF_MEMORY;
        }
        event->membersListById = members_id;
        flag = true;
    }
    PriorityQueue pq_members_id = event->membersListById;
    Member member_to_add = memberCopy(member);
    if(!member){
        if(flag){
            pqDestroy(pq_members_id);
            event->membersListById = NULL;
            return PQ_OUT_OF_MEMORY;
        }
        return PQ_OUT_OF_MEMORY;
    }
    PriorityQueueResult result = pqInsert(pq_members_id,member_to_add,&id);
    if(result != PQ_SUCCESS){
        if(flag){
            pqDestroy(pq_members_id);
            event->membersListById = NULL;
            memberFree(member_to_add);
            return result;
        }
    }
    memberFree(member_to_add);
    return result;
}

bool eventRemoveMember(Event event,Member member){
    if(!event || !member){
        return false;
    }
    PriorityQueue pq_member_id = event->membersListById;
    if(pqRemoveElement(pq_member_id,member) != PQ_SUCCESS){
        return false;
    } 
    Member check_empty_list = (Member)pqGetFirst(pq_member_id);
    if(!check_empty_list){
        pqDestroy(pq_member_id);
        event->membersListById = NULL;
    }
    return true;
}

PriorityQueue eventGetNamesResponse(Event event){
    if(!event){
        return NULL;
    }
    if(!event->membersListById){
        return NULL;
    }
    return event->membersListById;
}

bool eventUpdateDate(Event event, Date date){
    if(!event){
        return false;
    }
    event->eventDate = date;
    return true;
}
//---------------------------------------------------------------------------------------------

//-------------------------------------------end-----------------------------------------------

//---------------------------------------------------------------------------------------------