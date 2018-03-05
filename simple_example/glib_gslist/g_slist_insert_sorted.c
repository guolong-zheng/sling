#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_insert_sorted(Node * list, int data)
{
	//pre
	Node * tmp_list = list;
	Node * prev_list = NULL;
	Node * new_list = NULL;

	if (list == NULL) {
		new_list = (Node *) malloc(sizeof(Node));
		new_list->key = data;
		new_list->next = NULL;
		//post
		return new_list;
	}

	while(tmp_list->next != NULL && tmp_list->key < data)
	{
		//loop
		prev_list = tmp_list;
		tmp_list = tmp_list->next;
	}

	new_list = (Node *) malloc(sizeof(Node));
	new_list->key = data;
	if (tmp_list->next == NULL && data >= tmp_list->key) {
		tmp_list->next = new_list;
		new_list->next = NULL;
		//post
		return list;
	}

	if (prev_list != NULL) {
		new_list->next = NULL;
		prev_list->next = new_list;
		new_list->next = tmp_list;
		//post
		return list;
	} else {
		new_list->next = list;
		//post
		return new_list;
	}
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[], "%d", &size);
    Node * root = create_list(size);
    Node * res = g_slist_insert_sorted(root, rand_num());

    return 0;
}
