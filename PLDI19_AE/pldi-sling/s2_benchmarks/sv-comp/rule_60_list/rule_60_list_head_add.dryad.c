#include "stdhipmem.h"


void list_add(struct list_head * elem, struct list_head * head)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

    struct list_head * next = head->next;
    elem->next = NULL;
    elem->prev = NULL;
    elem->inserted = 1;
    head->next = elem;
    elem->prev = head;
    elem->next = next;
    next->prev = elem;
    return;
}
