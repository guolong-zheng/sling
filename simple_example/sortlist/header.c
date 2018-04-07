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
		root = sorted_insert_node(root, range_num(min, max));
	}
	return root;
}

SNnode * create_list(int size){
	SNnode * root = NULL;
	for(int i = 0; i < size; i++){
		root = sorted_insert_node(root, rand_num());
	}
	return root;
}

SNnode * sorted_insert_node(SNnode * l, int k)
{
	if (l == NULL) {
		SNnode * tl = (SNnode *) malloc(sizeof(SNnode));
		tl->key = k;
		tl->next = NULL;
		return tl;
	} else {
		if (k <= l->key) {
			SNnode * hd = (SNnode *) malloc(sizeof(SNnode));
			hd->key = k;
			hd->next = l;
			return hd;
		} else {
			SNnode * prev = l;
			SNnode * next = l->next;
			while(next != NULL && k > next->key)
			{
				prev = next;
				next = next->next;
			}
			SNnode * curr = (SNnode *) malloc(sizeof(SNnode));
			curr->key = k;
			curr->next = next;
			prev->next = curr;
			return l;
		}
	}
}

SNnode * create_random(int size){
	SNnode * root = NULL;
	SNnode * tail = NULL;
	for(int i = 0; i < size; i++){
		SNnode * tmp = (SNnode *)malloc(sizeof(SNnode));
		tmp->next = NULL;
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
