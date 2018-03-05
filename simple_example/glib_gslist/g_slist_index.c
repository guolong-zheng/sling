#include "g_slist.h"
#include <stdlib.h>

int g_slist_index(Node * list, int data)
{
	//pre
	int i;
	i = 0;
	while(list != NULL)
	{
		//loop
		if(list->key == data) {
			return i;
		}
		i ++;
		list = list->next;
	}
	//post
	return -1;
}

int main(int argc, char * argv[] ){
	int size;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    int res = g_slist_index(root, rand_num());

    return 0;
}
