
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

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
