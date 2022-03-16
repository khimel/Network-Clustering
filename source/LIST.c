
#include "LIST.h"


LIST* allocateLIST(){
	LIST* listy;
	listy = calloc(sizeof(LIST),1);
	if(listy == NULL){exit(1);}
	listy->head = NULL;
	listy->tail = NULL;
	listy->len = 0;
	return listy;
}

void insertLastLIST(LIST *listy, GROUP *g){
	NODE *last;
	listy->len +=1;
	last = allocateNODE();
	last->g = g;
	last->next = NULL;
	if(listy ->len == 1){
		listy->tail = last;
		listy->head = last;
	}else{
		listy->tail->next= last;
		listy->tail = last;
	}
}


GROUP* removeFirstLIST(LIST *listy){/* frees the node struct but not the group! */
	GROUP *g;
	NODE *tmp;
	tmp = listy->head;
	g = tmp->g;

	listy->len -=1;
	listy->head = tmp->next;
	if(listy->len ==0){
		listy->tail = NULL;
	}
	free(tmp);

	return g;
	/* did not free the group g! */
}


void freeLIST(LIST *listy){/* frees the LIST -- should use freeNODE in it */
	NODE *tmp, *p;
	p= listy->head;
	while(p != NULL){
		tmp = p;
		p = p->next;
		freeNODE(tmp);
	}
	free(listy);
}

NODE* allocateNODE(){
	NODE *new;
	new = malloc(sizeof(NODE) * 1);
	return new;
}

void freeNODE(NODE* node){ /* frees the node and what's inside it */
	freeGROUP(node->g);
	free(node);
}
