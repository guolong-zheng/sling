#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_sort_merge(Node * l1, Node * l2)
{
	//pre
	Node * list, * l, * y;
	list = (Node *) malloc(sizeof(Node));
    y = NULL;
	list->key = -MAX_RAND;
	list->next = y;
	l = list;
    Node * list_next =list->next;
	while(l1 != NULL && l2 != NULL)
	{
		//loop
		if (l1->key <= l2->key)
		{
			l->next = l1;
			l1 = l1->next;
		} else {
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
    	if (y == NULL) {
      		y = l;
    	}
		l->next = NULL;
	}
	if (l1 != NULL) {
		l->next = l1;
	} else {
		l->next = l2;
	}
	//post
	return list_next;
}

Node * create_sort(int size){
	Node * root = NULL;
	int i = 0;
	for(i = 0; i < size; i++){
		Node * n = (Node *)malloc(sizeof(Node));
		n->key = rand_num();
		n->next = NULL;
		if(root == NULL)
			root = n;
		else{
			Node * p = root;
			while(p->key < n->key && p != NULL)
				p = p->next;
			Node * q = root;
			while(q->next != p)
				q = q->next;
			q->next = n;
			n->next = p;
		}
	}
	return root;
}

int main(int argc, char * argv[]){
	int size;
	sscanf(argv[1],"%d",&size);
    Node * list1 = create_sort(size);
    Node * list2 = create_sort(size);
    Node * res = g_slist_sort_merge(list1, list2);

    return 0;
}
