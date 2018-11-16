#include "stdhipmem.h"



Node * g_slist_remove (Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node *tmp;
  Node *prev = NULL;
	tmp = list;
  int tp;

	while(tmp != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
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
	return list;
}

