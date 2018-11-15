
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

unsigned int g_slist_length(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	unsigned int length;
	length = 0;
	while(list != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		length++; 
		list = list->next;
	}
	return length;
}

