#include "stdhipmem.h"



Node * g_slist_reverse(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node * prev = NULL;
	while(list != NULL) 
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{

		Node * next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}
	return prev;
}
