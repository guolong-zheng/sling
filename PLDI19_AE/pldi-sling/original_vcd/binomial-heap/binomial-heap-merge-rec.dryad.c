// ---- Commmon definitions for binomial-heap examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  int order;
  struct node * children;
  struct node * sibling;
} SNnode;

/*D_defs
 define pred binomial-heap^(x):
 ( ((x l= nil) & emp) |
 (
 (x |-> loc children: chld; loc sibling: sbl; int key: ky; int order: odr) *
 ((
 (binomial-heap^(sbl) & ((orders^(sbl) set-lt odr) * true)) *
 ((binomial-heap^(chld) & (ky le-set keys^(chld))) &
 (((full-list^(chld) & ((length^(chld) + 1) i= odr)) & (orders^(chld) set-lt odr)) * true)
 )
 ) & (0 < odr))
 )
 ) ;
 
 define set-fun keys^(x):
 (case (x l= nil): emptyset;
 case ((x |-> loc children: chld2; loc sibling: sbl2; int key: ky2) * true):
 ((singleton ky2) union (keys^(chld2) union keys^(sbl2)));
 default: emptyset
 ) ;
 
 define set-fun orders^(x):
 (case (x l= nil): emptyset;
 case ((x |-> loc sibling: sbl3; int order: odr3) * true):
 ((singleton odr3) union orders^(sbl3));
 default: emptyset
 ) ;
 
 define pred full-list^(x):
 ( ((x l= nil) & emp) |
 (
 (x |-> loc sibling: sbl4; int order: odr4) *
 (
 full-list^(sbl4) & ((length^(sbl4) + 1) i= odr4)
 )
 )
 ) ;
 
 define int-fun length^(x):
 (case (x l= nil): 0;
 case ((x |-> loc sibling: sbl5) * true):
 (length^(sbl5) + 1);
 default: 0
 ) ;
*/
// ---------------------------------------------------------

_(dryad)
SNnode * binomial_heap_merge_rec(SNnode * x, SNnode * y)
/*D_requires ( (binomial-heap^(x) * binomial-heap^(y)) &
 (
 (((x l= nil) & (xord i= 0)) |
 ((((x |-> int order: xord) * (orders^(x->sibling) set-le xord)) & (orders^(x) s= (orders^(x->sibling) union (singleton xord)))) * (0 < xord))) &
 (((y l= nil) & (yord i= 0)) |
 ((((y |-> int order: yord) * (orders^(y->sibling) set-le yord)) & (orders^(y) s= (orders^(y->sibling) union (singleton yord)))) * (0 < yord)))
 ) ) */
/*D_ensures (
 (binomial-heap^(ret) & (keys^(ret) s= (old(keys^(x)) union old(keys^(y))))) &
 ((((xord i= 0) & (yord i= 0)) & ((ret l= nil) & emp)) |
 ( (((~ (xord i= 0)) | (~ (yord i= 0))) &
    (((xord i= yord) & (ret->order i= (xord + 1))) |
 ((((xord < yord) & (ret->order i= (yord + 1))) |
 ((xord < yord) & (ret->order i= yord))) |
 (((yord < xord) & (ret->order i= (xord + 1))) |
 ((yord < xord) & (ret->order i= xord)))))
 )
 &
 ((true * (orders^(ret->sibling) set-le ret->order)) & ((orders^(ret) s= (orders^(ret->sibling) union (singleton ret->order))) * true)) )
 )
 ) */
{
    
	if (x == NULL) {
        return y;
	}
    else if (y == NULL) {
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
            return x;
        } else {
            SNnode * ychld = y->children;
            x->sibling = ychld;
            y->children = x;
            y->sibling = z;
            y->order = ord2 + 1;
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
            return z;
        } else if (ord1 == zord && xk < zk) {
            SNnode * zsib = z->sibling;
            x->sibling = zsib;
            SNnode * xchld = x->children;
            z->sibling = xchld;
            x->children = z;
            x->order = ord1 + 1;
            return x;
        } else {
            x->sibling = z;
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
            return z;
        } else if (ord2 == zord && yk < zk) {
            SNnode * zsib = z->sibling;
            y->sibling = zsib;
            SNnode * ychld = y->children;
            z->sibling = ychld;
            y->children = z;
            y->order = ord2 + 1;
            return x;
        } else {
            y->sibling = z;
            return y;
        }
    }
}
