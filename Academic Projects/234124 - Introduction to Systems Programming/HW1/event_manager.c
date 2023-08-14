#include "event_manager.h"
#include "event.h"
#include "priority_queue.h"
#include "date.h"
#include "member.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


#define MINUS -1
#define PLUS 1
#define MIN_OF_EVENTS 0
#define ERROR -1

//------------------------------------------------------------------------------------------

//-------------------------- func for member prioirity--------------------------------------

//------------------------------------------------------------------------------------------

typedef struct member_priority_t{
    int num_of_events;
    int members_list_by_id;
}*MemberPriority;

// Create a Member Priority to members.
static MemberPriority emCreateMemberPriority(Member member){
    if(!member){
        return NULL;
    }
    int num = memberGetNumOfEvents(member);
    if(num == ERROR){
        return NULL;
    }
    int id = memberGetId(member);
    if(id == ERROR){
        return NULL;
    }
    MemberPriority new_priority = malloc(sizeof(*new_priority));
    if(!new_priority){
        return NULL;
    }
    new_priority->num_of_events = num;
    new_priority->members_list_by_id = id;
    return new_priority;
}

// Create a Copy Member Priority to members.
static MemberPriority emCopyMemberPriority(MemberPriority member_priority){
    if(!member_priority){
        return NULL;
    }
    int copy_id = member_priority->members_list_by_id;
    int copy_num_of_events = member_priority->num_of_events;
    MemberPriority new_priority = malloc(sizeof(*new_priority));
    if(!new_priority){
        return NULL;
    }
    new_priority->num_of_events = copy_num_of_events;
    new_priority->members_list_by_id = copy_id;
    return new_priority;
}

// Releases the information within the member priority.
static void emFreeMemberPriority(MemberPriority member_priority){
    free(member_priority);
}

// Comparing between two Members Priorities.
static int emCompareMemberPriority(MemberPriority p1 ,MemberPriority p2){
    if(p1->num_of_events > p2->num_of_events){
        return 1;
    }
    if(p1->num_of_events < p2->num_of_events){
        return -1;
    }
    assert(p1->num_of_events == p2->num_of_events);
    if(p1->members_list_by_id < p2->members_list_by_id){
        return 1;
    }
    if(p1->members_list_by_id > p2->members_list_by_id){
        return -1;
    }
    assert(p1->members_list_by_id == p2->members_list_by_id);
    return 0;
}

//------------------------------------------------------------------------------------------

//---------------------------------genric func for event------------------------------------

//------------------------------------------------------------------------------------------

// Copy Event Generic (call to eventCopy function).
PQElement emCopyEventGeneric(PQElement element){
    return eventCopy((Event)element);
}

// Releases the information within the event Generic (call to eventFree function).
void emFreeEventGeneric(PQElement element){
    eventFree((Event)element);
}

// Equal two events Generic (call to eventEqual function).
bool emEqualEventsGeneric(PQElement element1, PQElement element2){
    return eventEqual((Event)element1,(Event)element2);
}

// Copy Event Priority Generic (call to dateCopy function).
PQElementPriority emCopyEventPriorityGeneric(PQElementPriority element_priority){
    return dateCopy((Date)element_priority);
}

// Releases the information within the event Priority Generic (call to dateDestroy function).
void emFreeEventPriorityGeneric(PQElementPriority element_priority){
    dateDestroy((Date)element_priority);
}

// Comparing between two events Priorities Generic (call to dateCompare function).
int emCompareEventsPriorityGeneric(PQElementPriority element1, PQElementPriority element2){
    return dateCompare((Date)element1,(Date)element2)*(-1);
}

//------------------------------------------------------------------------------------------

//---------------------------------genric func for member-----------------------------------

//------------------------------------------------------------------------------------------

// Copy Member Generic (call to memberCopy function).
PQElement emCopyMemberGeneric(PQElement element){
    return memberCopy((Member)element);
}

// Releases the information within the member generic (call to memberFree function).
void emFreeMemberGeneric(PQElement element){
    memberFree((Member)element);
}

// Equal two Members Generic (call to memberEqual function).
bool emEqualMembersGeneric(PQElement element1, PQElement element2){
    return memberEqual((Member)element1, (Member)element2);
}

// Copy Member Priority Generic (call to emCopyMemberPriority function).
PQElementPriority emCopyMemberPriorityGeneric(PQElementPriority element_priority){
    return emCopyMemberPriority((MemberPriority) element_priority);
}

// Releases the information within the member priority generic (call to emFreeMemberPriority function).
void emFreeMemberPriorityGeneric(PQElementPriority element_priority){
    emFreeMemberPriority((MemberPriority)element_priority);
}

// Comparing between two members Priorities Generic (call to emCompareMemberPriority function).
int emCompareMembersPriorityGeneric(PQElementPriority element1, PQElementPriority element2){
    return emCompareMemberPriority((MemberPriority)element1, (MemberPriority)element2);
}

//---------------------------------------------------------------------------------------------

//----------------------------------------help func--------------------------------------------

//---------------------------------------------------------------------------------------------

// Equal Date And Name Event between other events of the event maneger.
static bool emEqualDateAndNameEvent(PriorityQueue pqEvents, char* name, Date date){
    if(!pqEvents || !name || !date){
        return false;
    }
    PQElement event = pqGetFirst(pqEvents);
    if(!event){
        return false;
    }
    while(event){
        Event current_event = (Event)event;
        Date current_date = eventGetDate(current_event);
        if(current_date == NULL){
            return false;
        }
        if(dateCompare(date,current_date) == 0){
            char* current_name = eventGetName(current_event);
            if(current_name == NULL){
                return false;
            }
            if(strcmp(name,current_name) == 0){
                return true;
            }
        }
        event = pqGetNext(pqEvents);
    } 
    return false;
}

// Checking if the event in the system by id number or not.
static Event emCheckIdEvent(PriorityQueue pqEvents, int id){
    if(!pqEvents){
        return NULL;
    }
    PQElement event = pqGetFirst(pqEvents);
    if(!event){
        return NULL;
    }
    while(event){
        Event current_event = (Event)event;
        int current_id = eventGetId(current_event);
        if(current_id == ERROR){
            return NULL;
        }
        if(current_id == id){
            return current_event;
        }
        event = pqGetNext(pqEvents);
    }
    return NULL;
}

// Checking if the member in the system by id number or not.
static Member emCheckIdMember(PriorityQueue pqMembers, int id){
    if(!pqMembers){
        return NULL;
    }
    PQElement member = pqGetFirst(pqMembers);
    if(!member){
        return NULL;
    }
    while(member){
        Member current_member = (Member)member;
        int current_id = memberGetId(current_member);
        if(current_id == id){
            return current_member;
        }
        member = pqGetNext(pqMembers);
    }
    return NULL;
}

// subtract  1 from all the members are responsible of the event after removal of an event from the system.
static bool emMinusNumOfEventsFromMembers(PriorityQueue pqMembers, Event event){
    if(!pqMembers || !event){
        return false;
    }
    int current_id_member = eventGetFirstIdMember(event);
    while(current_id_member != ERROR){
        Member member_to_update = emCheckIdMember(pqMembers,current_id_member);
        if(member_to_update == NULL){
            return false;
        }
        MemberPriority old_priority = emCreateMemberPriority(member_to_update);
        if(!old_priority){
            return false;
        }
        if(!memberUpdateNumOfEvents(member_to_update,MINUS)){
            emFreeMemberPriority(old_priority);
            return false;
        }
        MemberPriority new_priority = emCreateMemberPriority(member_to_update);
        if(!new_priority){
            emFreeMemberPriority(old_priority);
            return false;
        }
        if(pqChangePriority(pqMembers,member_to_update,old_priority,new_priority) != PQ_SUCCESS){
            emFreeMemberPriority(old_priority);
            emFreeMemberPriority(new_priority);
            return false;;
        }
        current_id_member = eventGetFirstIdMember(event);
        emFreeMemberPriority(old_priority);
        emFreeMemberPriority(new_priority);
    }
    return true;
}

// add or subtract  1 of the member's events after addition or removal of an event from the system.
static bool emPlusAndMinusOne (PriorityQueue pqMembers, Member member_to_update, int num){
    if(!pqMembers || !member_to_update){
        return false;
    }
    MemberPriority old_priority = emCreateMemberPriority(member_to_update);
    if(!old_priority){
        return false;
    }
    if(!memberUpdateNumOfEvents(member_to_update,num)){
        emFreeMemberPriority(old_priority);
        return false;
    }
    MemberPriority new_priority = emCreateMemberPriority(member_to_update);
    if(!new_priority){
        emFreeMemberPriority(old_priority);
        return false;
    }
    if(pqChangePriority(pqMembers,member_to_update,old_priority,new_priority) != PQ_SUCCESS){
            emFreeMemberPriority(old_priority);
            emFreeMemberPriority(new_priority);
            return false;;
    } 
    emFreeMemberPriority(old_priority);
    emFreeMemberPriority(new_priority);
    return true;
}
//------------------------------------------------------------------------------------------

//--------------------------------------func for EM-----------------------------------------

//------------------------------------------------------------------------------------------

struct EventManager_t {
    PriorityQueue PQEvents;
    PriorityQueue PQMembers;
    Date systemDate;
};

void destroyEventManager(EventManager event_maneger){
    if(!event_maneger){
        return;
    }
    PriorityQueue pq1 = event_maneger->PQEvents;
    PriorityQueue pq2 = event_maneger->PQMembers;
    Date d = event_maneger->systemDate;
    pqDestroy(pq1);
    event_maneger ->PQEvents = NULL;
    pqDestroy(pq2);
    event_maneger ->PQMembers = NULL;
    dateDestroy(d);
    event_maneger ->systemDate =NULL;
    free(event_maneger);
    return;
}

EventManager createEventManager(Date date){
    if(!date){
        return NULL;
    }
    EventManager event_maneger = malloc(sizeof(*event_maneger));
    if(!event_maneger){
        return NULL;
    }
    Date current_date = dateCopy(date);
    if(!current_date){
        free(event_maneger);
        return NULL;
    }
    event_maneger->PQEvents = NULL;
    event_maneger->PQMembers = NULL;
    event_maneger->systemDate = current_date;
    return event_maneger;
}

EventManagerResult emAddEventByDate(EventManager em, char* event_name, Date date, int event_id){
    if(!em || !event_name || !date){
        return EM_NULL_ARGUMENT;
    }
    Date my_date = em->systemDate;
    if(dateCompare(date,my_date) < 0){
        return EM_INVALID_DATE;
    }
    if(event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    PriorityQueue pqEvents = em->PQEvents;
    if(pqEvents != NULL){
        if(emEqualDateAndNameEvent(pqEvents, event_name, date)){
            return EM_EVENT_ALREADY_EXISTS;
        }
        if(emCheckIdEvent(pqEvents, event_id) != NULL){
            return EM_EVENT_ID_ALREADY_EXISTS;
        }
    }
    else{
        PriorityQueue pq_events = pqCreate(emCopyEventGeneric,emFreeEventGeneric,emEqualEventsGeneric,
                                    emCopyEventPriorityGeneric,emFreeEventPriorityGeneric,
                                    emCompareEventsPriorityGeneric); 
        if(!pq_events){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        em->PQEvents = pq_events;
        pqEvents = em->PQEvents;
    }
    Event new_event = eventCreate(event_name, event_id, date);
    if(!new_event){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    if(pqInsert(pqEvents,new_event,date) != PQ_SUCCESS){
        eventFree(new_event);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    eventFree(new_event);
    return EM_SUCCESS;   
}

EventManagerResult emAddEventByDiff(EventManager em, char* event_name, int days, int event_id){
    if(!em || !event_name){
        return EM_NULL_ARGUMENT;
    }
    if(days < 0){
        return EM_INVALID_DATE;
    }
    if(event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    Date date = dateCopy(em->systemDate);
    if(!date){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    for(int j=1; j<=days; j++){
        dateTick(date);
    }
    EventManagerResult result = emAddEventByDate(em, event_name, date, event_id);
    dateDestroy(date);
    return result; 
}

EventManagerResult emRemoveEvent(EventManager em, int event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    PriorityQueue pqEvents = em->PQEvents;
    Event checkExists = emCheckIdEvent(pqEvents,event_id);
    if(checkExists == NULL){
        return EM_EVENT_NOT_EXISTS;
    }
    PriorityQueue pqMembers = em->PQMembers;
    if(pqMembers != NULL){
        if(!emMinusNumOfEventsFromMembers(pqMembers,checkExists)){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }  
    }
    if(pqRemoveElement(pqEvents,checkExists) == PQ_SUCCESS){
        Event current_event = (Event)pqGetFirst(pqEvents);
        if(current_event == NULL){
            em->PQEvents = NULL;
            pqDestroy(pqEvents);
        }
        return EM_SUCCESS;
    }
    destroyEventManager(em);
    return EM_OUT_OF_MEMORY;
}

EventManagerResult emChangeEventDate(EventManager em, int event_id, Date new_date){
    if(!em || !new_date){
        return EM_NULL_ARGUMENT;
    }
    Date new_priority = dateCopy(new_date);
    Date my_date = em->systemDate;
    if(dateCompare(new_priority,my_date) < 0){
        dateDestroy(new_priority);
        return EM_INVALID_DATE;
    }
    if(event_id < 0){
        dateDestroy(new_priority);
        return EM_INVALID_EVENT_ID;
    }
    PriorityQueue pqEvents = em->PQEvents;
    Event my_event = emCheckIdEvent(pqEvents, event_id);
    if(!my_event){
        dateDestroy(new_priority);
        return EM_EVENT_ID_NOT_EXISTS;
    }
    char* current_name = eventGetName(my_event);
    if(emEqualDateAndNameEvent(pqEvents,current_name,new_priority)){
        dateDestroy(new_priority);
        return EM_EVENT_ALREADY_EXISTS;
    }
    Date old_priority = eventGetDate(my_event);
    if(!eventUpdateDate(my_event,new_priority)){
        dateDestroy(new_priority);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    if(pqChangePriority(pqEvents,my_event,old_priority,new_priority) != PQ_SUCCESS){
        dateDestroy(new_priority);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    dateDestroy(old_priority);
    return EM_SUCCESS;
}

EventManagerResult emAddMember(EventManager em, char* member_name, int member_id){
if(!em || !member_name){
        return EM_NULL_ARGUMENT;
    }
    if(member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    PriorityQueue pqMember = em->PQMembers;
    if(pqMember != NULL){
        if(emCheckIdMember(pqMember, member_id) != NULL){
            return EM_MEMBER_ID_ALREADY_EXISTS;
        }
    }
    else{
        PriorityQueue pq_members = pqCreate(emCopyMemberGeneric,emFreeMemberGeneric,emEqualMembersGeneric,
                                  emCopyMemberPriorityGeneric,emFreeMemberPriorityGeneric,
                                  emCompareMembersPriorityGeneric);
        if(!pq_members){
            destroyEventManager(em);
            return EM_OUT_OF_MEMORY;
        }
        em->PQMembers = pq_members;
        pqMember = em->PQMembers;
    }
    Member new_member = memberCreate(member_name, member_id, MIN_OF_EVENTS);
    if(!new_member){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    MemberPriority new_member_priority = emCreateMemberPriority(new_member);
    if(!new_member_priority){
        memberFree(new_member);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;       
    }
    if(pqInsert(pqMember,new_member,new_member_priority) != PQ_SUCCESS){
        emFreeMemberPriority(new_member_priority);
        memberFree(new_member);
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    memberFree(new_member);
    emFreeMemberPriority(new_member_priority);
    return EM_SUCCESS;   
}

EventManagerResult emAddMemberToEvent(EventManager em, int member_id, int event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    PriorityQueue pqEvents = em->PQEvents;
    Event my_event = emCheckIdEvent(pqEvents,event_id);
    if(my_event == NULL){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    PriorityQueue pqMembers = em->PQMembers;
    Member my_member = emCheckIdMember(pqMembers,member_id);
    if(my_member == NULL){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    if(eventCheckIfIdMemberExist(my_event,member_id)){
        return EM_EVENT_AND_MEMBER_ALREADY_LINKED;
    }
    if(eventAddMember(my_event,my_member,member_id) != PQ_SUCCESS){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    if(!emPlusAndMinusOne(pqMembers,my_member,PLUS)){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

EventManagerResult emRemoveMemberFromEvent (EventManager em, int member_id, int event_id){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(event_id < 0){
        return EM_INVALID_EVENT_ID;
    }
    if(member_id < 0){
        return EM_INVALID_MEMBER_ID;
    }
    PriorityQueue pqEvents = em->PQEvents;
    Event my_event = emCheckIdEvent(pqEvents,event_id);
    if(my_event == NULL){
        return EM_EVENT_ID_NOT_EXISTS;
    }
    PriorityQueue pqMembers = em->PQMembers;
    Member my_member = emCheckIdMember(pqMembers,member_id);
    if(my_member == NULL){
        return EM_MEMBER_ID_NOT_EXISTS;
    }
    if(!eventCheckIfIdMemberExist(my_event,member_id)){
        return EM_EVENT_AND_MEMBER_NOT_LINKED;
    }
    if(!eventRemoveMember(my_event,my_member)){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    if(!emPlusAndMinusOne(pqMembers,my_member,MINUS)){
        destroyEventManager(em);
        return EM_OUT_OF_MEMORY;
    }
    return EM_SUCCESS;
}

EventManagerResult emTick(EventManager em, int days){
    if(!em){
        return EM_NULL_ARGUMENT;
    }
    if(days <= 0){
        return EM_INVALID_DATE;
    }
    Date new_curreunt_day = em->systemDate;
    for(int j=1; j<=days; j++){
        dateTick(new_curreunt_day);
    }
    PriorityQueue pqEvents = em->PQEvents;
    if(pqEvents == NULL){
        return EM_SUCCESS;
    }
    PQElement event = pqGetFirst(pqEvents);
    while(event){
        Event current_event = (Event)event;
        Date event_date = eventGetDate(current_event);
        int event_id = eventGetId(current_event);
        if(dateCompare(event_date,new_curreunt_day) < 0){
            if(emRemoveEvent(em,event_id) != EM_SUCCESS){
                destroyEventManager(em);
                return EM_OUT_OF_MEMORY;
            }
            if(em->PQEvents == NULL){
                return EM_SUCCESS;
            }
            event = pqGetFirst(pqEvents);
        }else{
        break;
        } 
    }
    return EM_SUCCESS;
}

int emGetEventsAmount(EventManager em){
    if(!em){
        return MINUS;
    }
    if(!em->PQEvents){
        return 0;
    }
    return pqGetSize(em->PQEvents);
}

char* emGetNextEvent(EventManager em){
    if(!em){
        return NULL;
    }
    PriorityQueue pqEvents = em->PQEvents;
    Event event = (Event)pqGetFirst(pqEvents);
    return eventGetName(event);
}

void emPrintAllEvents(EventManager em, const char* file_name){
    if(!em || !file_name){
        return;
    }
    FILE * file;
    file = fopen(file_name,"w");
    PriorityQueue pqEvents = em->PQEvents;
    Event event = (Event)pqGetFirst(pqEvents);
    while(event){
        int day,month,year;
        Date date = eventGetDate(event);
        if(!dateGet(date,&day,&month,&year)){
            return;
        }
        fprintf(file,"%s,%d.%d.%d", eventGetName(event),day,month,year);
        PriorityQueue pqMembersId = eventGetNamesResponse(event);
        Member member = (Member)pqGetFirst(pqMembersId);
        while(member){
            fprintf(file,",%s", memberGetName(member));
            member = (Member)pqGetNext(pqMembersId);
        }
        fprintf(file,"\n");
        event = (Event)pqGetNext(pqEvents);
    }
    fclose(file);
}

void emPrintAllResponsibleMembers(EventManager em, const char* file_name){
    if(!em || !file_name){
        return;
    } 
    FILE * file;
    file = fopen (file_name, "w");
    Member member = (Member)pqGetFirst(em->PQMembers);
    while(member){
        int num_of_events = memberGetNumOfEvents(member);
        if(num_of_events == 0){
            break;
        }
        fprintf(file,"%s,%d\n" , memberGetName(member),num_of_events);
        member = (Member)pqGetNext(em->PQMembers);
    }
    fclose(file);
}
//---------------------------------------------------------------------------------------------

//-------------------------------------------end-----------------------------------------------

//---------------------------------------------------------------------------------------------


