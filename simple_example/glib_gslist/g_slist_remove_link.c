#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node * g_slist_remove_link(Node * list, Node * link)
{
	//pre
	Node * tmp;
	Node * prev;
    int tp;
	prev = NULL;
	tmp = list;
	while(tmp != NULL)
	{
		//loop
		if (tmp == link)
		{
			Node * tmp_next = tmp->next;
			if (prev != NULL) {
                tp = prev->key;
				prev->next = tmp_next;

			} else {
				list = tmp_next;
			}
			tmp->next = NULL;
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	//post
	return list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    Node * list = root->next;
    Node * res = g_slist_remove_link(root, list);

    return 0;
}
