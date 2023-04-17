#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * g_slist_nth(Node * list, int n)
{
	//pre
	while(n > 0 && list != NULL)
	{
		//loop
		n--;
		list = list->next;
	}
	//post
	return list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
	int n = 0;
	if(size > 0)
		n = rand()%size;
    Node * res = g_slist_nth(root, n);
    return 0;
}
