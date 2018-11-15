
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_sort_merge(Node * l1, Node * l2)
  /*D_requires sorted-list^(l1) * sorted-list^(l2) */
  /*D_ensures (sorted-list^(ret) & (keys^(ret) s= (old(keys^(l1)) union old(keys^(l2))))) */
	;

Node * g_slist_sort_real(Node * list)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	Node * l1, * l2;

	if (list == NULL) {
		return list;
	}
	if (list->next == NULL) {
		return list;
	}
	l1 = list;
	l2 = list->next;
  
	Node * l2_next = l2->next;

	while(l2_next != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
    l2_next = l2_next->next;
    l2 = l2_next; 

		if(l2 == NULL) {
			break;
		}
		l1 = l1->next;

		l2_next = l2->next;
	}

  if (l2 != NULL) {
    l2 = l2_next;
  }

  l2 = l1->next;
  l1->next = NULL; 
  
  if (l2 != NULL) {
    Node * t1 = g_slist_sort_real(list);
	  Node * t2 = g_slist_sort_real(l2);
  	return g_slist_sort_merge(t1, t2);
  } else {
    Node * t1 = g_slist_sort_real(list);
    return t1;
  }
}
