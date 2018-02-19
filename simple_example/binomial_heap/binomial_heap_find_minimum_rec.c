#include <stdlib.h>

typedef struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

int binomial_heap_find__minimum_rec(SNnode * x)
{
    SNnode * xs = x->sibling;
    int xk = x->key;

	if (xs == NULL) {
		return xk;
	} else {
		int y = binomial_heap_find__minimum_rec(xs);
        if (xk <= y) return xk;
        else          return y;
	}
}

int main(){
    
}
