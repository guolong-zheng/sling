#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node * g_slist_find(Node * list, int data)
{
	//pre
	while(list != NULL)
	{
		//loop
		if (list->key == data) {
			break;
		}
		list = list->next;
	}
	//post
	return list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * res = g_slist_find(root, rand_num());

    return 0;
}
