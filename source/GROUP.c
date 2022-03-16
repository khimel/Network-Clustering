#include "GROUP.h"

GROUP* allocateGROUP(int size){
	GROUP *g;
	g = calloc(sizeof(GROUP),1);
	g->size = size;
	g->indices = calloc(sizeof(int),size);
	return g;
}


void freeGROUP(GROUP* g){
	free(g->indices);
	free(g);
}
