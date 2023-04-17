#include "header.h"
#include <stdlib.h>
#include <stdio.h>

SNnode * sorted_insert_iter(SNnode * l, int k)
{
    //pre
	SNnode * ret;
	if (l == NULL) {
		SNnode * tl = (SNnode *) malloc(sizeof(SNnode));
		tl->key = k;
		tl->next = NULL;
        ret = tl;
		//return tl;
	} else {
		if (k <= l->key) {
			SNnode * hd = (SNnode *) malloc(sizeof(SNnode));
			hd->key = k;
			hd->next = l;
			ret = hd;
			//return hd;
		} else {
			SNnode * prev = l;
			SNnode * next = l->next;
			while(next != NULL && k > next->key)
			{
                //loop
				prev = next;
				next = next->next;
			}
			SNnode * curr = (SNnode *) malloc(sizeof(SNnode));
			curr->key = k;
			curr->next = next;
			prev->next = curr;
            ret = l;
			//return l;
		}
	}
	//post
	return ret;
}

int main( int argc, char * argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sorted_list(0, 50, size);

    SNnode * res = sorted_insert_iter(root, rand_num());
	sorted_insert_iter(root, 100);
	sorted_insert_iter(NULL, rand_num());
    return 0;
}
