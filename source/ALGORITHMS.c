#include "ALGORITHMS.h"



SET* algo_3(spmat *A){
	int n,c,index, ones,mones, i, *indicesz;
	SET *setP,*setO;
	GROUP  *g, *g1, *g2, *gz;
	double norm;

	c=0;
	setP = allocateSET();
	setO = allocateSET();
	n = A->n;
	gz = allocateGROUP(n);
	indicesz = gz->indices;
	for(i=0; i<n; i++){
		indicesz[i] = i;
	}

	addToSET(setP,  gz); /* setP = {{1,...,n}}.*/

	/* initial allocations used in all algortihms */
	sums = calloc(sizeof(double), A->n);
	if(sums ==NULL){exit(1);}
	leadPair = allocateEgPair(n);
	s = calloc(sizeof(double), n);
	if(s ==NULL){exit(1);}
	unmoved = calloc(sizeof(int), n);
	if(unmoved ==NULL){exit(1);}
	improve = calloc(sizeof(double), n);
	if(improve ==NULL){exit(1);}
	mult_1 = calloc(sizeof(double),n);
	if(mult_1 ==NULL){exit(1);}
	indices = calloc(sizeof(int), n);
	if(indices ==NULL){exit(1);}
	b0 = calloc(sizeof(double), n);
	if(b0 ==NULL){exit(1);}
	my_tmp = calloc(sizeof(double),A->n);
	if(my_tmp ==NULL){exit(1);}
	score = calloc(sizeof(double),A->n);
	if(score ==NULL){exit(1);}
	x = calloc(sizeof(double), A->n);
	if(x ==NULL){exit(1);}
	Bg_row = calloc(sizeof(double),A->n);
	if(Bg_row ==NULL){exit(1);}


	while(setP->numOfGroups!=0){ /*repeat until P is empty*/
		g1 =g2 = NULL;
		ones = mones = index = 0;
		g = popGROUP(setP);
		if(c==0){
			c++;
			sum_of_rows(A, g);
			norm = norm_1(A);
		}else{
			sum_of_rows(A, g);
		}
		algo_2(A, g, norm);

		for( i=0 ; i < g->size ; i++){
			index = g->indices[i];
			if(s[index]==1){
				ones += 1;
			}else{
				mones +=1;
			}
		}

		if(ones == 0 || mones == 0){
			addToSET(setO , g);
			g= NULL;
			continue;
		}

		g1 = allocateGROUP(ones);
		g2 = allocateGROUP(mones);
		compute_g1_g2(g, &g1, &g2);
		freeGROUP(g);
		if(g1->size==1){
			addToSET( setO, g1);
		}else{
			addToSET( setP, g1);
		}
		if(g2->size==1){
			addToSET( setO, g2);
		}else{
			addToSET( setP, g2);
		}
	}

	freeSET(setP);
	free(sums);
	free(b0);
	free(s);
	free(mult_1);
	freeEgPair(leadPair);
	free(my_tmp);
	free(indices);
	free(improve);
	free(unmoved);
	free(x);
	free(Bg_row);
	free(score);
	return setO;
}


void algo_2(spmat *A, GROUP *g, double norm){
	computeLead(A, g, norm);
	compute_S(A, g);
}


void computeLead(spmat *A, GROUP *g, double norm){
	computeDominVec(A, g, norm); /* computes dominating vector of shifted B^[g] */
	computeLeadVal(A, g, norm); /* computes leading Value of B^[g] - using formula form class */
}


double norm_1(spmat *A){
	list **Mat;
	int i,j, n ;
	double  tmp, currSum, finalSum,*k, M;
	node *p;
	n = A->n;
	Mat = A->Mat;
	k = A->k;
	M = A->M;
	finalSum =0;
	for(i=0;i<n;i++){ /* for each row i */
		currSum = 0;
		p = Mat[i]->head; /* p points to head of row i */
		j=0;
		while(j<n){
			if(p!= NULL && p->colInd ==j && i==j){
				tmp = p->val - (1/M * k[i]*k[j]);
				currSum += fabs( tmp - sums[j]);
				p=p->next;
				j++;
				continue;
			}else if(p!=NULL && p->colInd == j){
				tmp = p->val - (1/M * k[i]*k[j]);
				currSum += fabs(tmp);
				p= p -> next;
				j++;
				continue;
			}else if( p == NULL && i == j){
				tmp = - (1/M * k[i]*k[j]);
				currSum += fabs( tmp - sums[j]);
				j++;
				continue;
			}else if(p == NULL){
				tmp = - (1/M * k[i]*k[j]);
				currSum += fabs( tmp);
				j++;
				continue;
			}else if(p!= NULL && p->colInd != j){
				tmp = - (1/M * k[i]*k[j]);
				currSum += fabs( tmp);
				j++;
				continue;
			}
		}
		if(currSum > finalSum){
			finalSum = currSum;
		}
	 }

	return finalSum;
}


void computeDominVec(spmat* A, GROUP *g, double norm){ /* uses power iteration*/
	double  *b1, magnit;
	int ng, i, index,c;
	ng = g->size;

	for(i = 0 ; i<ng; i++){
		index = g->indices[i];
		b0[index] = rand() ;
	}

	c=0;
	do{
		if(c> ( A->n * 5000 + 300000) ){
			exit(1);
		}
		c++;
			b1 = (leadPair)->eigenVec;
			(leadPair)->eigenVec = b0;
			mult_B_g(A,g, b0, b1,1);
			for(i=0;i<ng;i++){
				index = g->indices[i];
				b1[index] += norm * b0[index]; /* adds the norm multiplication to each entry - because shift */
			}
			magnit = vectorMagnitude(g,b1);
			if(magnit == 0){
				printf("magnitudeof vector bk is zero");
				exit(1);
			}
			for(i=0; i<ng; i++){
				index = g->indices[i];
				b1[index] = (b1[index]) / magnit;
			}
			b0 = b1;
		}while(!differenceIsZero(g, (leadPair)->eigenVec, b1));
}

void computeLeadVal(spmat *A, GROUP *g, double norm){
		int i, index;
		double B1; /* = dominVec * (shifted_B^[g] * dominVec) */
		double B2;/* = dominVec * dominVec */
		double *dominVec;

		int ng = g->size;
		B1 = B2 = 0;
		dominVec = leadPair->eigenVec;

		mult_B_g(A, g, dominVec, my_tmp,1);
		for(i=0;i<ng;i++){
			index = g->indices[i];
			my_tmp[index] += norm * dominVec[index]; /* adds the norm multiplication to each entry - because shift */
		}

		for(i=0; i<ng;i++ ){
			index = g->indices[i];
	 		B1 += dominVec[index] * my_tmp[index];
		}

		for(i=0; i<ng;i++ ){
			index = g->indices[i];
			B2 += dominVec[index] * dominVec[index];
		}

		leadPair->eigenVal = B1/B2 - norm;
}

void compute_S(spmat *A, GROUP *g){
	int i, index;
	double delta_Q;
	if(!IS_POSITIVE(leadPair->eigenVal)){
		for(i=0; i<g->size;i++){
			index = g->indices[i];
			s[index] = 1;
		}
		improve_S(A, g);
		return;
	}
	for(i=0; i<g->size;i++){
		index = g->indices[i];
		if(IS_POSITIVE(leadPair->eigenVec[index])){
			s[index] = 1;
		}else{
			s[index] =-1;
		}
	}
	delta_Q = computeModularity(A, g);
	if(!IS_POSITIVE(delta_Q)){
		for(i=0; i<g->size;i++){
			index = g->indices[i];
			s[index] = 1;
		}
	}
	improve_S(A, g);
}


double computeModularity(spmat *A, GROUP *g){
	double  res;
	int ng, i,index;
	res =0;
	ng = g->size;
	mult_B_g(A, g, s, mult_1, 1); /* here we computed B^[g] * s */
	for(i=0;i<ng;i++){ /* here we compute s^T * mult_1 = s^T * B^[g] * s*/
		index = g->indices[i];
		res+= s[index] * mult_1[index];
	}
	return res;
}

void mult_B_g(spmat *A, GROUP *g, double *s, double *res,int kova){ /* here is the B^[g] * s */
	double resD1, *k;
	double M;
	int i, ng, index1;
	ng = g->size;
	M = A->M;
	k = A->k;
	mult_list(A, g, s, res);

	/* Ds: */
	resD1 = 0;
	index1 =0;
	for(i=0; i<ng;i++ ){
		index1 = g->indices[i];
		resD1+= s[index1] * k[index1];
	}

	for(i=0; i<ng;i++ ){/*As - Ds */
		index1 = g->indices[i];
		res[index1] -= 1/M * k[index1] * resD1;
	}
	if(kova == 1){
		for(i=0; i<ng;i++ ){/*As - Ds - sums*s */
			index1 = g->indices[i];
			res[index1] -= sums[index1] * s[index1];
		}
	}
}

void sum_of_rows(spmat *A, GROUP *g){
	int i,j,index1,index2, ng;
	double count ,M;
	list **Mat;
	node *p;

	Mat = A->Mat;
	ng = g->size;
	M = A->M;

	for(i=0;i<ng;i++){ /* for each row */
		index1 = g->indices[i];
		p = Mat[index1]->head;
		j=0;
		count = 0;
		while(j<ng){
			index2 = g->indices[j];
			if( p != NULL && p->colInd < index2){
				p = p->next;
				continue;
			}else if(p!= NULL && p->colInd == index2){
				count += ( p->val);
				p = p->next;
			}
			count -= (A->k[index1] * A->k[index2]) / M ;
			j++;
		}

		sums[index1] = count;
	}
}

void compute_g1_g2(GROUP *g, GROUP **g1, GROUP **g2){
	int i,ng, ones, mones, index1, index2,  index;
	index1= index2 = ones = mones = 0;
	ng = g->size;

	for(i=0;i<ng;i++){
		index = g->indices[i];
		if(s[index]==1){
			(*g1)->indices[index1] = index;
			index1++;
		}else{
			(*g2)->indices[index2] = index;
			index2++;
		}
	}
}

double vectorMagnitude (GROUP *g, double *vec){
	int i, index;
	double sum=0;
	for(i=0;i<g->size;i++){
		index = g->indices[i];
		sum+= vec[index]  *  vec[index];
	}
	return sqrt(sum);
}

int differenceIsZero(GROUP *g,double *vec1, double *vec2){
	int i,index;
	for(i=0;i<g->size;i++){
		index = g->indices[i];
		if(IS_POSITIVE(fabs(vec1[index]-vec2[index]))){
			return 0;
		}
	}
	return 1;
}

void improve_S(spmat *A, GROUP *g){
	double delta_Q;
	int ng,i,j, j_tag, i_tag, index, m;
	double curr_max_improve, max_improve;

	ng = g->size;
	j_tag = 0;

	mult_B_g(A,g,s,x,0);
	for(i=0;i<ng;i++){
		index = g->indices[i];
		score[index] = -2*(s[index] * x[index] + (A->k[index]*A->k[index]) / (A->M));
	}
	do {
		memset(unmoved, 0, sizeof(int) * (A->n));

		for(i=0;i<ng;i++){
			j_tag = find_max_arr(score,g, unmoved);
			s[j_tag] = -s[j_tag];
			get_row_B_g(A,g,j_tag,Bg_row);

			indices[i] = j_tag;
			if(i==0){
				improve[i] = score[j_tag];
			}else{
				improve[i] = improve[i-1] + score[j_tag];
			}
			for(j=0;j<ng;j++){
				index= g->indices[j];
				if(index==j_tag){
					score[index] = -score[index];
				}else{
					score[index] = score[index] - 4*s[index]*s[j_tag]*Bg_row[index];
				}
			}
			unmoved[j_tag] = 1;
		}

		i_tag = 0;
		curr_max_improve = max_improve = -DBL_MAX;
		for(j=0; j<ng; j++){
			curr_max_improve = improve[j];
			if(curr_max_improve > max_improve){
				max_improve = curr_max_improve;
				i_tag = j;
			}
		}

		for(i=ng-1 ; i > i_tag ; i--){
			j = indices[i];
			(s)[j] = -((s)[j]);
			get_row_B_g(A,g,j,Bg_row);
			for(m=0;m<ng;m++){
				index= g->indices[m];
				if(index==j){
					score[index] = -score[index];
					}else{
						score[index] = score[index] - 4*s[index]*s[j] * Bg_row[index];
					}
			}
		}
		if(i_tag == ng-1){
			delta_Q = 0;
		}else{
			delta_Q = improve[i_tag];
		}

	}while(IS_POSITIVE(delta_Q));
}

int find_max_arr(double *arr, GROUP *g, int *unmoved){
	int i, j,index;
	double curr_max,max;
	i = 0;
	curr_max = max = -DBL_MAX;
	for(j=0; j<g->size; j++){
		index = g->indices[j];
		curr_max = arr[index];
		if(unmoved[index] == 0){
			if(curr_max > max){
				max = curr_max;
				i = index;
			}
		}
	}
	return i;
}

void get_row_B_g(spmat *A,GROUP *g, int j_tag, double *res){
	node *tmp;
	int ng,j,index,i;
	tmp = A->Mat[j_tag]->head;
	ng = g->size;
	j=0;
	while(j<ng){
		index = g->indices[j];
		if( tmp != NULL && tmp->colInd < index){
			tmp = tmp->next;
			continue;
		}else if(tmp!= NULL && tmp->colInd == index){
			res[index] =  ( tmp->val) - (A->k[j_tag] * A->k[index]) / A->M ;
			tmp = tmp->next;
			j++;
			continue;
		}
		res[index] = (-1/A->M) * (A->k[j_tag] * A->k[index]) ;
		j++;
	}
	for(i=0;i<ng;i++){
		index = g->indices[i];
	}
}



