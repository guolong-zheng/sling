#include "stdhipmem.h"


SNnode * find_last_sorted(SNnode * l)
{
  SNnode * curr = l;
	if (curr != NULL) {
	  while (curr->next != NULL)
		{ 
			curr = curr->next;
		}
	}
	return curr;
}

SNnode * concat_sorted(SNnode * l1, SNnode * l2)
{
	if (l2 != NULL) {
		if (l1 != NULL) {
			SNnode * last = find_last_sorted(l1);
			last->next = l2;
		} else {
			l1 = l2;
		}
	} 
	return l1;
}

SNnode * quick_sort(SNnode * l)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (l == NULL) {
		return l;
	} 

	SNnode * curr = l->next;

	int pivot = l->key;
	l->next = NULL;

	SNnode * lpt = NULL;
	SNnode * rpt = NULL;

	SNnode * tmp = curr;

	while(curr != NULL)
    /*@
     infer[@shape]
     requires true
     ensures true;
     */
	{
		tmp = curr->next;
		if (curr->key <= pivot) {
			curr->next = lpt;
			lpt = curr;
		} else {		
			curr->next = rpt;
			rpt = curr;
		}
		curr = tmp;
	}

	l->next = rpt;
	
	SNnode * t2 = quick_sort(l);

	if (lpt == NULL) {
		return t2;
	}
	SNnode * t1 = quick_sort(lpt);
	return concat_sorted(t1, t2);
}
