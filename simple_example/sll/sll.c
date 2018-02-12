#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * node_create(int key)
{
    SNnode * node = (SNnode *)malloc(sizeof(SNnode));
    node->key = key;
    node->next = NULL;
    return node;
}

SNnode * create_sll(int size){
    SNnode * nodes[size];
    for(int i = 0; i < size; i++){
        nodes[i] = node_create((int)rand());
    }

    SNnode * root = NULL;
    for(int i = 0; i < size; i++){
        root = sll_append(root, nodes[i]);
    }

    return root;
}

SNnode * sll_append(SNnode * x1, SNnode * x2)
{
	if (x1 == NULL) {
		return x2;
	} else {
		SNnode * tmp = sll_append(x1->next, x2);
		x1->next = tmp;
		return x1;
	}
}

SNnode * sll_delete_all(SNnode * x, int k)
{
	if (x == NULL) {
		return x;
	} else if (x->key == k) {
		SNnode * tmp = sll_delete_all(x->next, k);
		free(x);
		return tmp;
	} else {
		SNnode * tmp = sll_delete_all(x->next, k);
		x->next = tmp;
		return x;
	}
}

SNnode * sll_insert_back(SNnode * x, int k)
{
	if (x == NULL) {
		SNnode * tail = (SNnode *) malloc(sizeof(SNnode));
		tail->key  = k;
		tail->next = NULL;
		return tail;
	} else {
		SNnode * tmp = sll_insert_back(x->next, k);
		x->next = tmp;
		return x;
	}
}

SNnode * sll_insert(SNnode * x, int k)
{
	if (x == NULL) {
		SNnode * leaf = (SNnode *) malloc(sizeof(SNnode));
		leaf->key = k;
		leaf->next = NULL;
		return leaf;

	} else if (k > x->key) {
		SNnode * tmp = sll_insert(x->next, k);
		x->next = tmp;
		return x;
	}	else {
		SNnode * new_root = (SNnode *) malloc(sizeof(SNnode));

		new_root->key = k;
		new_root->next = x;
		return new_root;
	}
}

SNnode * sll_copy(SNnode * x, int k)
{
	if (x == NULL) {
		return x;
	} else {
		SNnode * tmp = sll_copy(x->next, k);
		SNnode * new_node = (SNnode *) malloc(sizeof(SNnode));
        int tmp_key = x->key;
		new_node->key = tmp_key;
		new_node->next = tmp;
		return new_node;
	}
}

int sll_find(SNnode * x, int k)
{
	if (x == NULL) {
		return -1;
	} else if (k == x->key) {
		return 1;
	}	else {
    SNnode * x_next = x->next;
		int res = sll_find(x_next, k);
		return res;
	}
}

SNnode * sll_insert_front(SNnode * x, int k)
{
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
		return head;
}

SNnode * sll_reverse(SNnode * x)
{
	SNnode * y = NULL;

	while (x != NULL)
    {
		SNnode * tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
	return y;
}
