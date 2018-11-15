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
  | ((x |-> loc left: lft; loc right: rgt; int key: ky) 
    * (tree^(lft) * tree^(rgt))));

define pred pretree^(x):
  ( ((x l= nil) & emp)
  | (((x |-> loc left: lft; loc right: rgt; int key: ky) 
        * (pretree^(lft) 
        *  pretree^(rgt)))
    & ((((order^(lft) i= (ky + 1)) * true) | (lft l= nil))
    & (((order^(rgt) i= ((ky + 1) + size^(lft))) * true) | (rgt l= nil))))  
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
*/
// --------------------------------------------------

_(dryad)
int preorder(TNode * x, int n)
	/*D_requires tree^(x) */
  /*D_ensurs (pretree^(x) 
             & ((ret i= (n + old(size^(x)))) 
               & (((order^(x) i= n) | (x l= nil)) & (size^(x) i= old(size^(x)))))) */
{

	if (x == NULL) {
		return n;
	} else {
		x->key = n;
		int n1 = n + 1;
		int n2 = preorder(x->left, n1);
		int n3 = preorder(x->right, n2);

		return n3;
	}
}

