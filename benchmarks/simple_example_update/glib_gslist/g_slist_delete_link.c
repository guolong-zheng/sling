#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node * g_slist_delete_link(Node * list, Node * link_);
Node * g_slist_remove_link(Node * list, Node * link);

Node * g_slist_delete_link(Node * list, Node * link_)
{
	//pre
	list = g_slist_remove_link(list, link_);
	free(link_);
	//post
	return list;
}

Node * g_slist_remove_link(Node * list, Node * link)
{
	Node * tmp;
	Node * prev;
    int tp;
	prev = NULL;
	tmp = list;
	while(tmp != NULL)
	{
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
	return list;
}


int main(int argc, char * argv[]){
	int size;
	sscanf(argv[1],"%d",&size);
    Node * list = create_list(size);
    Node * link_ = list->next->next->next;
    Node * res = g_slist_delete_link(list, link_);

    return 0;
}
