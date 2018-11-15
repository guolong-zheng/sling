
#include <stdlib.h>

typedef
/*D_tag node */
struct node {
  int key;
  struct node * next;
} Node;

Node * g_slist_remove_link(Node * list, Node * link)
  /*D_requires (list^(x) & (((~ (link l= nil)) & lseg^(x, link)) * true)) */
  /*D_ensures ((list^(ret) & (~ (link l-in reachnodes^(ret)))) * ((link |-> loc next: z) & (z l= nil)))  */
;

Node * g_slist_delete_link(Node * list, Node * link_)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	list = g_slist_remove_link(list, link_);
	free(link_); 
	return list;
}

