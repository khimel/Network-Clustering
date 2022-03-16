/**
 * main Summary:
 *
 *  Module main runs our main function algo_3, and writes the result to output file!
 *
 *
 * main - writes the result on output file, where The first value represents the number of groups
 * in the division.
 * The second value represents the number of nodes in the first group, followed by the indices
 * of the nodes in the group, in increasing order.
 * The next value is the number of nodes in the second group, followed by the indices of the
 * nodes in group, then the number of nodes and indices of nodes in the third group, and so
 * on until the last group.
 *
 */
#include "readNwrite.h"
#include "ALGORITHMS.h"
#include <time.h>



/*
	 *The function main writes the result on output file, where The first value represents the number of groups
	 * in the division.
	 * The second value represents the number of nodes in the first group, followed by the indices
	 * of the nodes in the group, in increasing order.
	 * The next value is the number of nodes in the second group, followed by the indices of the
	 * nodes in group, then the number of nodes and indices of nodes in the third group, and so
	 * on until the last group.
	 *
	 *@param argc - length of the arguments.
	 *@param argv - argv[1] = input filename , argv[2] = output filename.
	 *@return 0
*/
int main(int argc, char *argv[]){
	spmat *A;
	SET *result;
	/*double start,end;*/
	srand(time(NULL));
	/*start = clock();*/
	if(argc != 3){
		printf("invalid input\n");
		exit(1);
	}
	
	A = inputToSpmat(argv[1]); /* spmat A allocated and filled here */
	result = algo_3(A);
	free_list(A); /* spmat A is freed :) */

	groupsToOutput(argv[2], result);
	freeSET(result);

	/*end = clock();*/
	/*printf("my MAIN took: %f seconds \n", (double)(end - start)/CLOCKS_PER_SEC);*/

	return 0;

}
