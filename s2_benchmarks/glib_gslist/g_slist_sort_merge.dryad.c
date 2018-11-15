
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_sort_merge(Node * l1, Node * l2)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node * list, * l, * y;  
	list = (Node *) malloc(sizeof(Node));
	_(assume list != NULL)

  y = NULL;
	list->key = INT_MIN; 
	list->next = y; 
	l = list;
  Node * list_next =list->next;
	while(l1 != NULL && l2 != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		if (l1->key <= l2->key)
		{
			l->next = l1;
			l1 = l1->next;
		} else {
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
    if (y == NULL) {
      y = l;
    }

		l->next = NULL;
	}
	if (l1 != NULL) {
		l->next = l1;
	} else {
		l->next = l2;
	}
	return list_next;
}
