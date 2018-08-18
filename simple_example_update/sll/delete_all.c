#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_delete_all(SNnode * x, int k)
{
    //pre
	if (x == NULL) {
        //post
		return x;
	} else if (x->key == k) {
		SNnode * tmp = sll_delete_all(x->next, k);
		free(x);
        //post
		return tmp;
	} else {
		SNnode * tmp = sll_delete_all(x->next, k);
		x->next = tmp;
        //post
		return x;
	}
}

void test1(int size);
void test2(int size);
void test3(int size);


int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    SNnode * root = create_sll(size);

    root = sll_delete_all(root, 2);

	test1(size);
	test2(size);
	test3(size);
    return 0;
}

void test1(int size){
	sll_delete_all(NULL, rand());
}

void test2(int size){
	SNnode * root = create_sll(size);
}

void test3(int size){
	SNnode * root = create_sll(size);
	sll_delete_all(root, rand());
}
