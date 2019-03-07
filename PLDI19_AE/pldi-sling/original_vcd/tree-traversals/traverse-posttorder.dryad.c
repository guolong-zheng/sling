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

define pred posttree^(x):
  ( ((x l= nil) & emp)
  | (((x |-> loc left: lft; loc right: rgt; int key: ky) 
    * (posttree^(lft) 
    * posttree^(rgt)))
    & ((((((order^(lft) + 1) + size^(rgt)) i= ky) * true) | (lft l= nil))
    & ((((order^(rgt) + 1) i= ky) * true) | (rgt l= nil))))  
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
int postorder(TNode * x, int n)
	/*D_requires tree^(x) */
  /*D_ensures (posttree^(x) 
          & ((ret i= (n + old(size^(x)))) 
            & (((order^(x) i= ((n + old(size^(x))) - 1)) | (x l= nil)) & (size^(x) i= old(size^(x)))))) */
{

	if (x == NULL) {
		return n;
	} else {
		int n1 = postorder(x->left, n);
		int n2 = postorder(x->right, n1);
		x->key = n2;
		int n3 = n2 + 1;
		return n3;
	}
}
