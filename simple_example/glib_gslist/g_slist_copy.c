#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_copy(Node * list)
{
	//pre
	Node * new_list = NULL;
	if (list != NULL) {
		Node * last = NULL;
		new_list = (Node *) malloc(sizeof(Node));
        int list_key = list->key;
		new_list->key = list_key;
		new_list->next = NULL;
		last = new_list;
		list = list->next;
		while(list != NULL)
		{
			//loop
			Node * tail = (Node *)malloc(sizeof(Node));
            int list_key = list->key;
 			tail->key = list_key;
			tail->next = NULL;
			last->next = tail;
			last = last->next;
			list = list->next;
		}
	}
	//post
	return new_list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * res = g_slist_copy(root);
    return 0;
}
