#include "member.h"

#define ERROR -1

char* stringDuplicate(const char* str) {
	char *copy = malloc(strlen(str) + 1);
	return copy ? strcpy(copy, str) : NULL;
}

//---------------------------------------------------------------------------------------------

//---------------------------------------func for member----------------------------------------

//---------------------------------------------------------------------------------------------

struct member_t{
    char* memberName;
    int memberId;
    int numofEvents;    
};

void memberFree(Member member){
    if(!member){
        return;
    }
    free(member->memberName);
    free(member);
}

Member memberCreate(char* name, int id, int num_of_events){
    if(!name){
        return NULL;
    }
    Member new_member = malloc(sizeof(*new_member));
    if(!new_member){
        return NULL;
    }
    char* new_name = stringDuplicate(name);
    if(!new_name){
        memberFree(new_member);
        return NULL;
    }
    new_member->memberName = new_name;
    new_member->memberId = id;
    new_member->numofEvents = num_of_events;
    return new_member;
}

Member memberCopy(Member member){
    if(!member){
        return NULL;
    }
    return memberCreate(member->memberName, member->memberId, member->numofEvents);
}

bool memberEqual(Member member1, Member member2){ 
    return member1->memberId == member2->memberId;
}

//---------------------------------------------------------------------------------------------

//----------------------------------------help func--------------------------------------------

//---------------------------------------------------------------------------------------------

int memberGetNumOfEvents(Member member){
    return !member ? ERROR: member->numofEvents;
}

int memberGetId(Member member){
    return !member ? ERROR: member->memberId;
}

char* memberGetName(Member member){
    return member->memberName;
}

bool memberUpdateNumOfEvents(Member member,int num){
    if(!member){
        return false;
    }
    int old_num_Of_Events = member->numofEvents;
    member->numofEvents = old_num_Of_Events + num;
    return true;
}

//---------------------------------------------------------------------------------------------

//-------------------------------------------end-----------------------------------------------

//---------------------------------------------------------------------------------------------