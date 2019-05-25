#include "stdhipmem.h"



Node * g_slist_insert_sorted(Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node * tmp_list = list;
	Node * prev_list = NULL;
	Node * new_list = NULL;

	if (list == NULL) {
		new_list = (Node *) malloc(sizeof(Node));

		new_list->key = data;
		new_list->next = NULL;
		return new_list;
	}

	while(tmp_list->next != NULL && tmp_list->key < data) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */

	{
		prev_list = tmp_list;
		tmp_list = tmp_list->next;
	}

	new_list = (Node *) malloc(sizeof(Node));

	new_list->key = data;
	if (tmp_list->next == NULL && data >= tmp_list->key) { 
		tmp_list->next = new_list;
		new_list->next = NULL;
		return list;
	}

	if (prev_list != NULL) {
		new_list->next = NULL;
		prev_list->next = new_list;
		new_list->next = tmp_list;
		return list;
	} else {
		new_list->next = list;
		return new_list;
	}
}	
