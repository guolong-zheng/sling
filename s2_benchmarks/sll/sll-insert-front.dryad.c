
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  struct node * next;
} SNnode;

SNnode * sll_insert_front(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
		SNnode * head = (SNnode *) malloc(sizeof(SNnode));
		head->key = k;
		head->next = x;
		return head;
}
