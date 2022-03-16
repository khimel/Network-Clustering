#include "eigenPAIR.h"


eigenPAIR* allocateEgPair(int size){
	eigenPAIR *pair;
	pair = calloc(sizeof(eigenPAIR),1);
	pair->eigenVec = calloc(sizeof(double),size);
	pair->eigenVal = 0;
	return pair;
}

void freeEgPair(eigenPAIR *pair){
	free(pair->eigenVec);
	free(pair);
}
