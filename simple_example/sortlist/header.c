#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int rand_num(){
	return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

int range_num(int min, int max){
	return min + rand()%(max - min + 1);
}

SNnode * create_sorted_list(int min, int max, int size){
	SNnode * root = NULL;
	for(int i = 0; i < size; i++){
		root = sorted_insert(root, range_num(min, max));
	}
	return root;
}

SNnode * create_list(int size){
	SNnode * root = NULL;
	for(int i = 0; i < size; i++){
		root = sorted_insert(root, rand_num());
	}
	return root;
}

SNnode * create_random(int size){
	SNnode * root = NULL;
	SNnode * tail = root;
	for(int i = 0; i < size; i++){
		SNnode * tmp = (SNnode *)malloc(sizeof(SNnode));
		tmp->key = rand_num();
		if(root == NULL){
			root = tmp;
			tail = tmp;
		}else{
			tail->next = tmp;
			tail = tmp;
		}
	}
	return root;
}
