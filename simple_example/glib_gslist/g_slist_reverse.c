#include "g_slist.h"
#include <stdlib.h>

Node * g_slist_reverse(Node * list)
{
	//pre
	Node * prev = NULL;
	while(list != NULL)
	{
		//loop
		Node * next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}
	//post
	return prev;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    Node * res = g_slist_reverse(root);

    return 0;
}
