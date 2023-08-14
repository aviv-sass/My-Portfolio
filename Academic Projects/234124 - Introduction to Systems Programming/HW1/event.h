#ifndef EVENT_H_
#define EVENT_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "priority_queue.h"
#include "date.h"
#include "member.h"

//---------------------------------------------------------------------------------------------

//---------------------------------------func for event----------------------------------------

//---------------------------------------------------------------------------------------------

/** Type for defining the event */
typedef struct event_t *Event;

/**
* eventCreate: Allocates a new empty event.
*
* @param name - The name of the new event
* @param id - A unique serial number for the new event
* @param date - The date of the new event
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new Map in case of success.
*/
Event eventCreate(char* name, int id, Date date);

/**
* eventFree: Releases all the information within the event
*
* @param event - Target event to be deallocated. If event is NULL nothing will be
* 		done
*/
void eventFree(Event event);

/**
* eventCopy: Creates a copy of target event.
*
* @param event - Target event.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A event containing the same elements as event otherwise.
*/
Event eventCopy(Event event);

/**
* eventEqual:
* Type of function used by the priority queue to identify equal events.
* @param event1 - One of the events
* @param event2 - One of the events
* @return :
* 		true if they're equal by the date and by the name;
*		false otherwise;
*/
bool eventEqual(Event event1, Event event2);

//---------------------------------------------------------------------------------------------

//----------------------------------------help func--------------------------------------------

//---------------------------------------------------------------------------------------------

/** eventGetDate: Returns the date of the event.
* @param event - Target event.
* @return the date, If event is NULL nothing will be done
*/
Date eventGetDate(Event event);

/** eventGetName: Returns the name of the event
* @param event - Target event.
* @return the name, If event is NULL nothing will be done
*/
char* eventGetName(Event event);

/** eventGetId: Returns the id number of the event
* @param event - Target event.
* @return the id, If event is NULL nothing will be done
*/
int eventGetId(Event event);

/** eventGetFirstIdMember: Returns the first id number on the members list are responsible of the event.
* @param event - Target event.
* @return the first id, If event or the members list (are responsible) are NULL nothing will be done.
*/
int eventGetFirstIdMember(Event event);

/** eventCheckIfIdMemberExist: Checking if the member is responsible of the event.
* @param event - Target event.
* @param id - target id of the member.
* @return
* 		true if the member is responsible;
*		false otherwise;
*/
bool eventCheckIfIdMemberExist(Event event, int id);

/** eventAddMember: Add a member to the list of the members are responsible of the event.
* @param event - Target event.
* @param member - Target member.
* @param id - Target id of the member.
* @return
*   PQ_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	PQ_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	PQ_SUCCESS the paired elements had been inserted successfully
*/
PriorityQueueResult eventAddMember(Event event,Member member, int id);

/** eventRemoveMember: Remove a member from the list of the members are responsible of the event.
* @param event - Target event.
* @param member - Target member.
* @return :
* 		true If the removal was completed;
*		false otherwise;
*/
bool eventRemoveMember(Event event,Member member);

/** eventGetNamesResponse: Returns the names of the members are responsible of the event. 
* @param event - Target event.
* @return a priority queue of the members.
*/
PriorityQueue eventGetNamesResponse(Event event);

/** The function Updating for the date of the event.
* @param event - Target event.
* @param member - Target date.
* @return :
* 		true If the update was completed;
*		false otherwise;
*/
bool eventUpdateDate(Event event, Date date);

#endif //EVENT_H_

//---------------------------------------------------------------------------------------------

//-------------------------------------------end-----------------------------------------------

//--------------------------------------------------------------------------------------------
