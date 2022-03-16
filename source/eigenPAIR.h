/**
 * eigenPAIR Summary:
 *
 *  Module eigenPAIR represents eigenpair , containing eigenVec and eigenVal
 *
 *  allocateEgPair - allocates memory and initializes eigenVec and eigenVal
 *  freeEgPair - releases memory allocated for eigenVec and the struct eigenPAIR
 *
 */
#include <stdlib.h>
#include <stdio.h>
#ifndef EIGENPAIR_H_
#define EIGENPAIR_H_


typedef struct _eigenPAIR{
	double *eigenVec, eigenVal;

}eigenPAIR;


/*
	 *The function allocateEgPair allocates memory and initializes eigenVec and eigenVal.
	 *@param size - size of eigenVec
	 *@return eigenPAIR - the initialized struct according to size of eigenVec
*/
eigenPAIR* allocateEgPair(int size);


/*
	 *The function freeEgPair releases memory allocated for eigenVec and the struct eigenPAIR.
	 *@param pair - pair to be released
	 *@return
*/
void freeEgPair(eigenPAIR *pair);

#endif /* EIGENPAIR_H_ */
