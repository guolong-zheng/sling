#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int sumDel(TNode *p){
 //pre
 int sum = 0;
 if (p != NULL){
   TNode *pL = p->left;
   TNode *pR = p->right;
   int sumL = sumDel(pL);
   if(pL!=NULL)
	printf("pL not null");
   //loop
   int sumR = sumDel(pR);
   sum = p->key + sumL + sumR;
   free(p);
   if(p!=NULL){
    printf("p not null");
    p=NULL;
}
 }
 //post
 return sum;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    TNode * root = create_tree(size);

    int res = sumDel(root);

    return 0;
}
