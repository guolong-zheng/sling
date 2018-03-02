#include "sort_list.h"

SNnode * sorted_insert_iter(SNnode * l, int k)
{
    //pre
	if (l == NULL) {
		SNnode * tl = (SNnode *) malloc(sizeof(SNnode));
		tl->key = k;
		tl->next = NULL;
        //post
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
			{
                //loop
				prev = next;
				next = next->next;
			}
			SNnode * curr = (SNnode *) malloc(sizeof(SNnode));
			curr->key = k;
			curr->next = next;
			prev->next = curr;
            //post
			return l;
		}
	}
}

int main( int argc, int argv[] ){
    int size;
    sscanf(argv[1], "%d", &size);
    SNnode * root = create_sorted_list(size);

    SNnode * res = sorted_insert_iter(root, rand_num());

    return 0;
}
