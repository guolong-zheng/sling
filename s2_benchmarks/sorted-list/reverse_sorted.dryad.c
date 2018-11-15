
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * reverse_sorted(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	SNnode * r = NULL;

	while(l != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		SNnode * t = l->next;
		
		l->next = r;
		r = l;
		l = t;
	}
	return r;
}

