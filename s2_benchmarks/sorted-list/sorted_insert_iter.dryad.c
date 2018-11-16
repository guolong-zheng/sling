#include "stdhipmem.h"



SNnode * sorted_insert_iter(SNnode * l, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
	if (l == NULL) {
		SNnode * tl = (SNnode *) malloc(sizeof(SNnode));
		
		tl->key = k;
		tl->next = NULL;
		return tl;
	} else {
		if (k <= l->key) {

			SNnode * hd = (SNnode *) malloc(sizeof(SNnode));
			

			hd->key = k;
			hd->next = l;

			return hd;
			
		} else {

			SNnode * prev = l;
			SNnode * next = l->next;

			while(next != NULL && k > next->key) 
            /*@
             infer[@shape]
             requires true
             ensures true;
             */
			{
				prev = next;
				next = next->next;
			}

			SNnode * curr = (SNnode *) malloc(sizeof(SNnode));

			curr->key = k;
			curr->next = next;
			
			prev->next = curr;
			return l;
		}
	}
}
