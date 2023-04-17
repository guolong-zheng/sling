#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int g_slist_nth_data(Node * list, int n)
{
	//pre
	int res;
	while(n > 0 && list != NULL)
	{
		//loop
		n--;
		list = list->next;
	}
	if (list != NULL) {
		res = list->key;
	} else {
		res = -1;
	}
	//post
	return res;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
	Node * p = root;
	while(p!=NULL){
		printf("%d\n", p->key);
		p = p->next;
	}
	int n  = 0;
	if(size > 0)
		n = rand()%size;
    int res = g_slist_nth_data(root, rand()%size);
    return 0;
}
