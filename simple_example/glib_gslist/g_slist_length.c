#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int g_slist_length(Node * list)
{
	//pre
	int length;
	length = 0;
	while(list != NULL)
	{
		//loop
		length++;
		list = list->next;
	}
	//post
	return length;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    int res = g_slist_length(root);
    return 0;
}
