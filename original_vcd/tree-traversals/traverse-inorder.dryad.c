// ---- Definitions for tree traversal examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag t_node */
struct t_node {
  struct t_node * left;
  struct t_node * right;
  int key;
} TNode;

/*D_defs 
define pred tree^(x):
  ( ((x l= nil) & emp)
  | ((x |-> loc left: lft; loc right: rgt; int key: ky) * (tree^(lft) * tree^(rgt)))  
  );

define pred intree^(x):
  ( ((x l= nil) & emp)
  | (((x |-> loc left: lft; loc right: rgt; int key: ky) * (intree^(lft) * intree^(rgt)))
    & ((((((order^(lft) + rsize^(lft)) + 1) i= ky) * true) | (lft l= nil))
    & (((order^(rgt) i= ((ky + lsize^(rgt)) + 1)) * true) | (rgt l= nil))))  
  );

define int-fun order^(x):
  ( case (x l= nil): 0;
    case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    ky;
    default: 0
  );

define int-fun size^(x):
  ( case (x l= nil): 0;
    case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    (1 + (size^(lft) + size^(rgt)));
    default: 0
  );

define int-fun lsize^(x):
  ( case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    size^(lft);
    default: 0
  );

define int-fun rsize^(x):
  ( case ((x |-> loc left: lft; loc right: rgt; int key: ky) * true): 
    size^(rgt);
    default: 0
  );
*/
// --------------------------------------------------

_(dryad)
int inorder(TNode * x, int n)
  /*D_requires tree^(x) */
  /*D_ensures (intree^(x) 
          & ((ret i= (n + old(size^(x)))) 
              & ((((order^(x) i= (n + lsize^(x))) 
                  & ((1 + (lsize^(x) + rsize^(x))) i= size^(x))) | (x l= nil)) 
                      & (size^(x) i= old(size^(x)))))) */
{
	if (x == NULL) {
		return n;
	} else {
		int n1 = inorder(x->left, n);
		x->key = n1;
		int n2 = n1 + 1;
		int n3 = inorder(x->right, n2);
		return n3;	
	}
}
