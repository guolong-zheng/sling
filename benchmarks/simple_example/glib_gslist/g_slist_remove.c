#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node * g_slist_remove (Node * list, int data)
{
	//pre
	Node *tmp;
    Node *prev = NULL;
	tmp = list;
    int tp;

	while(tmp != NULL)
	{
		//loop
		if (tmp->key == data)
		{
			Node * tmp_next = tmp->next;

			if (prev != NULL) {
        tp = prev->key;
				prev->next = tmp_next;
			} else {

				list = tmp_next;
			}
			free(tmp);
			break;
		}

		prev = tmp;
		tmp = prev->next;

	}
	//post
	return list;
}

int main(int argc, char * argv[]){
	int size = 0;
	sscanf(argv[1],"%d", &size);
    Node * root = create_list(size);
    Node * res = g_slist_remove(root, rand_num());

    return 0;
}
