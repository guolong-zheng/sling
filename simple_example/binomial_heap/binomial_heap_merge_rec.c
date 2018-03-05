#include <stdlib.h>

typedef struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

SNnode * binomial_heap_merge_rec(SNnode * x, SNnode * y)
{
    //pre
	if (x == NULL) {
        //post
        return y;
	}
    else if (y == NULL) {
        //post
        return x;
    }
    else if (x->order == y->order) {
        SNnode * xs = x->sibling;
        SNnode * ys = y->sibling;
        SNnode * z = binomial_heap_merge_rec(xs, ys);
        int ord1 = x->order;
        int ord2 = y->order;
        if (ord1 <= ord2) {
            SNnode * xchld = x->children;
            y->sibling = xchld;
            x->children = y;
            x->sibling = z;
            x->order = ord1 + 1;
            //post
            return x;
        } else {
            SNnode * ychld = y->children;
            x->sibling = ychld;
            y->children = x;
            y->sibling = z;
            y->order = ord2 + 1;
            //post
            return y;
        }
    }
    else if (y->order < x->order) {
        SNnode * xs = x->sibling;
        SNnode * z = binomial_heap_merge_rec(xs, y);
        int ord1 = x->order;
        int ord2 = y->order;
        int zord = z->order;
        int zk = z->key;
        int xk = x->key;

        if (ord1 == zord && zk <= xk) {
            SNnode * zchld = z->children;
            x->sibling = zchld;
            z->children = x;
            z->order = zord + 1;
            //post
            return z;
        } else if (ord1 == zord && xk < zk) {
            SNnode * zsib = z->sibling;
            x->sibling = zsib;
            SNnode * xchld = x->children;
            z->sibling = xchld;
            x->children = z;
            x->order = ord1 + 1;
            //post
            return x;
        } else {
            x->sibling = z;
            //post
            return x;
        }
    }
    else {
        SNnode * ys = y->sibling;
        SNnode * z = binomial_heap_merge_rec(ys, x);
        int ord1 = x->order;
        int ord2 = y->order;
        int zord = z->order;
        int zk = z->key;
        int yk = y->key;

        if (ord2 == zord && zk <= yk) {
            SNnode * zchld = z->children;
            y->sibling = zchld;
            z->children = y;
            z->order = zord + 1;
            //post
            return z;
        } else if (ord2 == zord && yk < zk) {
            SNnode * zsib = z->sibling;
            y->sibling = zsib;
            SNnode * ychld = y->children;
            z->sibling = ychld;
            y->children = z;
            y->order = ord2 + 1;
            //post
            return x;
        } else {
            y->sibling = z;
            //post
            return y;
        }
    }
}

int main(int argc, char * argv[]){
    int size;
    sccanf(argv[1],"%d",&size);
    int i = 0;
    SNnode * root = NULL;
    for(i = 0; i < size; i++){
        SNnode * x = (SNnode *)malloc(sizeof(SNnode));
        x->key = rand_num();
        x->order = 0;
        x->children = NULL;
        x->sibling = NULL;
        root = binomial_heap_merge_rec(root, x);
    }
}
