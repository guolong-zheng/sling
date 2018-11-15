
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

int g_slist_position(Node * list, Node * link)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	int i;

	i = 0;
	while(list != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		if (list == link) {
			return i;
		}
		i ++;
		list = list->next;
	}
	return -1;
}

