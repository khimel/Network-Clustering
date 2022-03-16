#include "spmat.h"
#include "ALGORITHMS.h"

spmat* spmat_allocate_list(int n){
	int i;
	spmat *A;
	list **Mat;
	A= malloc(sizeof(spmat) * 1);
	if(A == NULL){
		exit(1);
	}
	Mat = malloc(sizeof(list*) * n);
	if(Mat == NULL){
		exit(1);
	}
	for(i=0;i<n;i++){
		Mat[i] = calloc(sizeof(list),1);
		if(Mat[i] == NULL){
			exit(1);
		}
	}
	A->Mat = Mat;
	A->n = n;
	return A;
}

void add_row_list(struct _spmat *A, const double *row, int i){
	list **Mat;
	list *list_i;
	int j;
	Mat = A->Mat;
	list_i = Mat[i];
	list_i->len=0;
	list_i->head = NULL;
	list_i->tail = NULL;
	for(j=0; j < (A->n) ; j++){
		if(row[j]==0){
			continue;
		}
		else{
			insertLast(list_i, row[j],j);
		}
	}
	Mat[i] = list_i;
}

void insertLast(list *listy, double value, int colIndex){
	node *last = malloc(sizeof(node) * 1); /*init a new node*/
	if(last == NULL){
		exit(1);
	}
	listy->len +=1;
	last->val = value;
	last->next = NULL;
	last->colInd = colIndex;
	if(listy->len==1){
		listy->tail=last;
		listy->head =last;
	}
	else{
	listy->tail->next= last;
	listy->tail = last;
	}
}


void mult_list(const struct _spmat *A, GROUP *g, const double *v, double *result){
	int i,*index1,*index2, ng,j, tmp;
	list **Mat;
	node *p;
	double c;
	ng = g->size;
	Mat = A->Mat;
	index1 =g->indices;

	for(i=0 ; i<ng ; i++){ /* for each row that it's index is in g */
		p = Mat[*index1]->head; /* p points to the first node in row */
		c=0;
		j=0;
		index2 = g->indices;
		if(p==NULL){
			result[*index1] = 0;
			index1++;
			continue;
		}
		while(p!=NULL){
			if(p->colInd == *index2){ /* if the p points to a node in column from g */
				c +=((p->val) * (v[*index2]));
				p = p->next;
				index2++;
				j++;
				continue;
			}else if(p->colInd < *index2){
				p = p->next;
				continue;
			}else if(p->colInd > *index2){
				tmp = binarySearch(g, j, ng-1, p->colInd);
				if(tmp == -1){
					p=p->next;
					continue;
				}
				index2 = g->indices + tmp;
				j = tmp;
				continue;
			}
		}
		result[*index1] = c;
		index1++;
	}
}

void free_list(struct _spmat *A){
	list **Mat;
	node *p,*tmp;
	int i;
	Mat = A->Mat;

	for(i=0 ; i<(A->n); i++){ /* for every list(row) */
		p = Mat[i]->head;   /* p points to head of i'th list */
		while(p!=NULL){
			tmp = p;
			p = p->next;
			free(tmp);
		}
		free(Mat[i]);
	}
	free(Mat);
	free(A->k);
	free(A);
}


int binarySearch(GROUP *g, int l, int r, int x)
{
	int mid;
    if (r >= l) {
        mid = l + (r - l) / 2;

        /* If the element is present at the middle
         itself*/
        /*printf("g->mid %d \n", g->indices[mid]);*/
        if (g->indices[mid] == x)
            return mid;

        /* If element is smaller than mid, then
         it can only be present in left subarray*/
        if (g->indices[mid] > x)
            return binarySearch(g, l, mid - 1, x);

         /*Else the element can only be present
        in right subarray*/
        return binarySearch(g, mid + 1, r, x);
    }

    /* We reach here when element is not
     present in array*/
    return -1;
}







