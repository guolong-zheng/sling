
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sll_reverse(SNnode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	SNnode * y = NULL;

	while (x != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		SNnode * tmp = x->next;
		x->next = y;
		y = x;
		x = tmp;
	}
	return y;
}
