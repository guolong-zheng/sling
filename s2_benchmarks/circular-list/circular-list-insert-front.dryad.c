
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} CNode;

CNode * circular_list_insert_front(CNode * x)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	CNode * tmp = x->next;
	CNode * hd = (CNode *) malloc(sizeof(CNode)) ;
	_(assume hd != NULL)
	hd->next = tmp;
	x->next = hd; 
	return hd;
}
