#ifndef MEMBER_H_
#define MEMBER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * stringDuplicate : help to copy a string
 * @param str - String to copy
 * @return :
 *    The copt string will return
 *    if somthing goes wrong return NULL  
 */
char* stringDuplicate(const char* str);

//---------------------------------------------------------------------------------------------

//---------------------------------------func for member----------------------------------------

//---------------------------------------------------------------------------------------------

/** Type for defining the member */
typedef struct member_t *Member;

/**
* memberFree: Releases all the information within the member
*
* @param member - Target member to be deallocated. If member is NULL nothing will be
* 		done
*/
void memberFree(Member member);

/**
* memberCreate: Allocates a new empty member.
*
* @param name - The name of the new member
* @param id - A unique serial number for the new member
* @param num_of_events - The number of events that the new member in charge.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new Map in case of success.
*/
Member memberCreate(char* name, int id, int num_of_events);

/**
* memberCopy: Creates a copy of target member.
*
* @param member - Target member.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A member containing the same elements as member otherwise.
*/
Member memberCopy(Member member);

/**
* memberEqual:
* Type of function used by the priority queue to identify equal members.
* @param member1 - One of the members
* @param member2 - One of the members
* @return :
* 		true if they're equal by id;
*		false otherwise;
*/
bool memberEqual(Member member1, Member member2);

//---------------------------------------------------------------------------------------------

//----------------------------------------help func--------------------------------------------

//---------------------------------------------------------------------------------------------

/**
* memberGetNumOfEvents: Returns the number of events that the member is responsible.
* @param member - Target member.
* @return number of events.
*/
int memberGetNumOfEvents(Member member);

/**
* memberGetId: Returns the the ID number of the member.
* @param member - Target member.
* @return id number.
*/
int memberGetId(Member member);

/**
 * memberGetName: Returns the the name of the member.
* @param member - Target member.
* @return name of the member.
*/
char* memberGetName(Member member);

/**
 * memberUpdateNumOfEvents: 
 * The function update the number of events that the member is responsible.
 * @param member - The member
 * @param num - +1 or -1
 * @return :
 *      true If the update was completed;
 *      false otherwise;
*/
bool memberUpdateNumOfEvents(Member member,int num);

#endif //MEMBER_H_

//---------------------------------------------------------------------------------------------

//-------------------------------------------end-----------------------------------------------

//---------------------------------------------------------------------------------------------