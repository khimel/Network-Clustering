/**
 * LIST Summary:
 *
 *  Module LIST represents linked list , with nodes build from struct GROUP.
 *  Module LIST is needed for implementation of SET
 *
 *  allocateGROUP - allocates memory and initializes indices and size of GROUP struct
 *  freeGROUP - releases memory allocated for indices and size of GROUP struct
 *
 * allocateLIST - allocates and initialize linked list, and its len, head, tail
 * insertLastLIST- inserts new node to the end of linked list
 * removeFirstLIST - removes and returns head of the list
 * freeLIST - releases memory allocated for the list and its nodes
 * allocateNODE - allocates memory for node
 * freeNODE - releases memory allocated for the node
 *
 */


#include "spmat.h"
#ifndef LIST_H_
#define LIST_H_

typedef struct _NODE{
	GROUP *g;
	struct _NODE *next;
}NODE;

typedef struct _LIST{
	NODE *head;
	NODE *tail;
	int len;
}LIST;


/*
	 *The function allocateLIST allocates memory and initializes linked list, and its len, head, tail.
	 *@param
	 *@return LIST - the initialized list
*/
LIST* allocateLIST();


/*
	 *The function insertLastLIST inserts new node with GROUP g to the end of linked list listy.
	 *@param listy - modified linked list
	 *@param g - data of the inserted node
	 *@return
*/
void insertLastLIST(LIST *listy, GROUP *g);


/*
	 *The function removeFirstLIST removes and returns head of the list listy, and releases memory allocated for the head.
	 *@param listy - modified linked list
	 *@return GROUP - data of the deleted node
*/
GROUP* removeFirstLIST(LIST *listy);


/*
	 *The function freeLIST releases memory allocated for the list and its nodes.
	 *@param listy - modified linked list
	 *@return
*/
void freeLIST(LIST *listy);


/*
	 *The function allocateNODE allocates memory for node.
	 *@param
	 *@return NODE - allocated node
*/
NODE* allocateNODE();


/*
	 *The function freeNODE releases memory allocated for the node.
	 *@param node - node to be released
	 *@return
*/
void freeNODE(NODE* node); /* frees the NODE */



#endif /* LIST_H_ */
