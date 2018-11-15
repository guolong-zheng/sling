
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_nth(Node * list, int n)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	while(n > 0 && list != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		n--;
		list = list->next; 
	}
	return list;
}

