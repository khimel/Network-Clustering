/* Implementation of readNwrite */
#include "readNwrite.h"
#include "spmat.h"

spmat* inputToSpmat(char fileName[]){

	FILE *inputFile;
	spmat *A;
	double M, *k,*row;
	int i, n,tmp_k, j, *tmp_v, *tmp, ch;


	inputFile = fopen(fileName, "r");
	if(inputFile == NULL){exit(1);}

	fread(&n, sizeof(int), 1,inputFile);

	A = spmat_allocate_list(n);
	M=0;
	k = calloc(sizeof(double),n);
	if(k == NULL){exit(1);}
	row = calloc(sizeof(double),n);
	if(row == NULL){exit(1);}
	tmp_v = calloc(sizeof(int) ,n);
	if(tmp_v == NULL){exit(1);}
	tmp_k =0;
	for(i=0; i<n; i++){ /* for each node */
		ch = fread(&tmp_k, sizeof(int), 1, inputFile);
		if(ch !=1){exit(1);}
		k[i] = tmp_k;
		M += tmp_k;
		if(tmp_k >0){
			tmp = tmp_v;
			ch = fread(tmp_v, sizeof(int), tmp_k,inputFile);
			if(ch != tmp_k){exit(1);}
			for(j=0 ; j<n ; j++){
				if(j == *tmp){
					row[j] =1;
					tmp++;
				}
			}

			add_row_list(A, row, i);
		}
		memset(row,0,sizeof(double) * n); /* set row to zeros */
		memset(tmp_v,0,sizeof(int)*n);
	}

	if(M == 0){
		printf("M is zero - no edges in the graph");
		exit(1);
	}
	A->M = M;
	A->k = k;


	free(tmp_v);
	free(row);
	fclose(inputFile);
	return A;

}

void groupsToOutput(char fileName[], SET *O){
	FILE *outFile;
	int numOfGroups, n;
	LIST *listOfGroups;
	NODE *p;
	numOfGroups= O->numOfGroups;
	outFile = fopen(fileName, "w");
	if(outFile == NULL){
	    exit(1);
	}

	if (fwrite(&numOfGroups, sizeof(int),1, outFile) != 1){
		exit(1);
	}

	 listOfGroups = O->groups;
	 p = listOfGroups->head;
	 while(p != NULL){
		if ( fwrite(&p->g->size, sizeof(int), 1, outFile) != 1){
			exit(1);

		}
		n =  p->g->size;
		 if ((int)fwrite(p->g->indices, sizeof(int), n, outFile)!= n){
			 exit(1);
		 }
		 p= p->next;
	 }

	 fclose(outFile);
}
