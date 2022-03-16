#include "SET.h"

SET* allocateSET(){
	SET *set;
	set = calloc(sizeof(SET),1);
	if(set == NULL){exit(1);}
	set->numOfGroups = 0;
	set->groups = allocateLIST();

	return set;
}

void addToSET(SET* set, GROUP *group){
	insertLastLIST(set->groups, group);
	set->numOfGroups +=1;

}

GROUP* popGROUP(SET *set){
	GROUP *g;
	g= removeFirstLIST(set->groups);
	set->numOfGroups -=1;
	return g;
}

void freeSET(SET *set){
	freeLIST(set->groups);
	free(set);
}
