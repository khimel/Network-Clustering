/**
 * SET Summary:
 *
 *  Module SET represents set of linked lists, where the nodes data are  of struct GROUP.
 *
 *
 *allocateSET - allocates a SET struct and LIST struct in it
 *addToSET - adds group to the set ,at the end of the list
 *popGROUP - pops the first group in the SET
 *freeSET - releases the memory allocated for the set and list in it
 *
 */

#include "LIST.h"

#ifndef SET_H_
#define SET_H_

typedef struct _SET{
	int numOfGroups;
	LIST *groups;   /* linked list of groups */
}SET;


/*
	 *The function allocateSET allocates a SET struct and LIST struct in it.
	 *@param
	 *@return SET - the allocated set
*/
SET* allocateSET();


/*
	 *The function addToSET adds group to  set ,at the end of the list.
	 *@param set - modified set
	 *@param group - the group to be added
	 *@return
*/
void addToSET(SET* set, GROUP *group);


/*
	 *The function popGROUP pops the first group in the SET.
	 *@param set - modified set
	 *@return GROUP - the removed group
*/
GROUP* popGROUP(SET* set);


/*
	 *The function releases the memory allocated for the set and list in it.
	 *@param set - set to be released
	 *@return
*/
void freeSET(SET *set);


#endif /* SET_H_ */
