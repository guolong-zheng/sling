#include "sort_list.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * create_list(int size){
	SNnode * root = NULL;
	for(int i = 0; i < size; i++){
		root = sorted_insert(root, (int)rand());
	}

	return root;
}

SNnode * create_random(int size){
	SNnode * root = NULL;
	SNnode * tail = root;
	for(int i = 0; i < size; i++){
		SNnode * tmp = (SNnode *)malloc(sizeof(SNnode));
		tmp->key = (int)rand();
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

SNnode * concat_sorted(SNnode * l1, SNnode * l2)
{
	if (l2 != NULL) {
		if (l1 != NULL) {
			SNnode * last = find_last_sorted(l1);
			last->next = l2;
		} else {
			l1 = l2;
		}
	}
	return l1;
}

SNnode * merge_sort_copy(SNnode * l1, SNnode * l2)
{
	if (l1 == NULL) {
		return l2;
	} else if (l2 == NULL) {
		return l1;
	} else {
		if (l1->key <= l2->key) {
			SNnode * tl = merge_sort_copy(l1->next, l2);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
            int l1_key = l1->key;
			nl->key  = l1_key;
			nl->next = tl;
			return nl;
		} else {
			SNnode * tl = merge_sort_copy(l1, l2->next);
			SNnode * nl = (SNnode *) malloc(sizeof(SNnode));
            int l2_key = l2->key;
			nl->key = l2_key;
			nl->next = tl;
			return nl;
		}
	}
}

SNnode * sorted_delete_all(SNnode * x, int k)
{
	if (x == NULL) {
		return x;
	} else if (x->key == k) {
		SNnode * tmp = sorted_delete_all(x->next, k);
		free(x);
		return tmp;
	} else {
		SNnode * tmp = sorted_delete_all(x->next, k);
		x->next = tmp;
		return x;
	}
}

SNnode * sorted_insert(SNnode *x, int k)
{

	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key = k;
		tail->next = NULL;
		return tail;
	}
	else if (k > x->key) {
		SNnode * tmp = sorted_insert(x->next, k);
		x->next = tmp;
		return x;
	}
	else {
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
		return head;
	}
}

SNnode * find_last_sorted(SNnode * l)
{
    SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{
			curr = curr->next;
		}
	}
	return curr;
}

SNnode * quick_sort(SNnode * l)
{

	if (l == NULL) {
		return l;
	}

	SNnode * curr = l->next;

	int pivot = l->key;
	l->next = NULL;

	SNnode * lpt = NULL;
	SNnode * rpt = NULL;

	SNnode * tmp = curr;

	while(curr != NULL)
	{
		tmp = curr->next;
		if (curr->key <= pivot) {
			curr->next = lpt;
			lpt = curr;
		} else {
			curr->next = rpt;
			rpt = curr;
		}
		curr = tmp;
	}

	l->next = rpt;

	SNnode * t2 = quick_sort(l);

	if (lpt == NULL) {
		return t2;
	}
	SNnode * t1 = quick_sort(lpt);
	return concat_sorted(t1, t2);
}

int sorted_find(SNnode * l, int k)
{
	if (l == NULL) {
		return -1;
	} else if (l->key == k) {
		return 1;
	} else {
		int res = sorted_find(l->next, k);
		return res;
	}
}

SNnode * sorted_insert_iter(SNnode * l, int k)
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

SNnode * insertion_sort_copy(SNnode * l)
{
	if (l == NULL) {
		return l;
	} else {
		SNnode * tl = insertion_sort_copy(l->next);

		SNnode * nl = sorted_insert(tl, l->key);
		return nl;
	}
}

SNnode * reverse_sorted(SNnode * l)
{
	SNnode * r = NULL;
	while(l != NULL)
	{
		SNnode * t = l->next;
		l->next = r;
		r = l;
		l = t;
	}
	return r;
}
