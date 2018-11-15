
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
   int key;
   struct node * next;
} SNnode;

SNnode * find_last_sorted(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
  SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
      /*@
       infer[@shape]
       requires true
       ensures true;
       */
		{ 
			curr = curr->next;
		}
	}
	return curr;
}
