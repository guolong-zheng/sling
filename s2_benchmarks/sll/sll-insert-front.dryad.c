#include "stdhipmem.h"



SNnode * sll_insert_front(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
		return head;
}
