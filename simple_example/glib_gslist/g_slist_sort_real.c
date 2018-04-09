#include "header.h"
#include <stdlib.h>
#include <stdio.h>
Node * g_slist_sort_merge(Node * l1, Node * l2);
Node * g_slist_sort_real(Node * list);

Node * g_slist_sort_real(Node * list)
{
	//pre
	Node * l1, * l2;

	if (list == NULL) {
		//post
		return list;
	}
	if (list->next == NULL) {
		//post
		return list;
	}
	l1 = list;
	l2 = list->next;

	Node * l2_next = l2->next;

	while(l2_next != NULL)
	{
		//loop
    	l2_next = l2_next->next;
    	l2 = l2_next;
		if(l2 == NULL) {
			break;
		}
		l1 = l1->next;
		l2_next = l2->next;
	}
  	if (l2 != NULL) {
    	l2 = l2_next;
  	}
  	l2 = l1->next;
  	l1->next = NULL;
  	if (l2 != NULL) {
    	Node * t1 = g_slist_sort_real(list);
	  	Node * t2 = g_slist_sort_real(l2);
		Node * ret = g_slist_sort_merge(t1, t2);
		//post
  		return ret;
  	} else {
    	Node * t1 = g_slist_sort_real(list);
		//post
    	return t1;
  	}
}

Node * g_slist_sort_merge(Node * l1, Node * l2)
{
	Node * list, * l, * y;
	list = (Node *) malloc(sizeof(Node));
    y = NULL;
	list->key = -MAX_RAND;
	list->next = y;
	l = list;
    Node * list_next =list->next;
	while(l1 != NULL && l2 != NULL)
	{
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
	return list_next;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * res = g_slist_sort_real(root);
    return 0;
}
