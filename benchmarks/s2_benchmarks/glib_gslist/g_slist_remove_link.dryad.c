#include "stdhipmem.h"



Node * g_slist_remove_link(Node * list, Node * link)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node * tmp;
	Node * prev;
  int tp;

	prev = NULL;
	tmp = list;

	while(tmp != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
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

