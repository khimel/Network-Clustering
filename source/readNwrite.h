/**
 * readNwrite Summary:
 *
 *  Module readNwrite reads the input from input file and writes output to output file
 *
 */


#include "spmat.h"
#include "SET.h"

#ifndef READNWRITE_H_
#define READNWRITE_H_


/*
	 *The function inputToSpmat takes allocated empty spmat *A and fills it, fills vector k and M according to input file.
	 *@param fileName - input file
	 *@return spmat - spare matrix A updated according to the input
*/
spmat* inputToSpmat(char fileName[]); /* read A and vector k and M */


/*
	 *The function groupsToOutput writes the output groups in set to output file fileName.
	 *@param fileName - output file
	 *@param O - set of output groups
	 *@return
*/
void groupsToOutput(char fileName[], SET *O);






#endif
