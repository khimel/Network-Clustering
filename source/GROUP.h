/**
 * GROUP Summary:
 *
 *  Module GROUP represents group , containing an array of indices and its size
 *
 *  allocateGROUP - allocates memory and initializes indices and size of GROUP struct
 *  freeGROUP - releases memory allocated for indices and size of GROUP struct
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* GROUP of node of graph indices */
#ifndef GROUP_H_
#define GROUP_H_

typedef struct _GROUP{
	int size;
	int *indices;
}GROUP;

/*
	 *The function allocateGROUP allocates memory and initializes indices and size of GROUP struct.
	 *@param size - size of GROUP
	 *@return GROUP - the initialized struct according to size of GROUP
*/
GROUP* allocateGROUP(int size);


/*
	 *The function freeGROUP releases memory allocated for indices and the struct GROUP.
	 *@param g - GROUP to be released
	 *@return
*/
void freeGROUP(GROUP* g);
#endif /* GROUP_H_ */
