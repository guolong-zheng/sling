#include "g_slist.h"
#include <stdlib.h>

int g_slist_position(Node * list, Node * link)
{
	//pre
	int i;
	i = 0;
	while(list != NULL)
	{
		//loop
		if (list == link) {
			//post
			return i;
		}
		i ++;
		list = list->next;
	}
	//post
	return -1;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    Node * list = root->next;
    int res = g_slist_position(root, list);

    return 0;
}
