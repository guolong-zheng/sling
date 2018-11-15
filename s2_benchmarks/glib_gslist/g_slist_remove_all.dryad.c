
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_remove_all(Node * list, int data)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node *tmp, *prev = NULL;
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
			tmp = tmp_next;
		} else {
			prev = tmp;
			tmp = prev->next;
		}
	}
	return list;
}

