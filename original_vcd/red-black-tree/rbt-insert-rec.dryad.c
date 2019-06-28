// ---- Commmon definitions for rbt examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef 
/*D_tag node */
struct node {
  int key;
  int color;
  struct node * left;
  struct node * right;
} SNnode;

/*D_defs
 define pred rbp^(x):
 ( ((x l= nil) & emp) |
 (
 (
 (x |-> loc left: lft; loc right: rgt; int key: ky; int color: clr) *
 (
 (
 (rbp^(lft) & (keys^(lft) set-lt ky)) *
 (rbp^(rgt) & (ky lt-set keys^(rgt)))
 ) &
 (bh^(lft) i= bh^(rgt))
 )
 ) &
 ((clr i= 0) |
 ((black^(lft) * true) & (black^(rgt) * true))
 )
 )
 ) ;
 
 define pred black^(x):
 ( ((x l= nil) & emp) | ((x |-> int color: clr) & (clr i= 0)) ) ;
 
 define set-fun keys^(x):
 (case (x l= nil): emptyset;
 case ((x |-> loc left: lft; loc right: rgt; int key: ky; int color: clr) * true):
 ((singleton ky) union (keys^(lft) union keys^(rgt)));
 default: emptyset
 ) ;
 
 define int-fun bh^(x):
 (case (x l= nil): 1;
 case ((((x |-> loc left: lft; loc right: rgt; int key: ky; int color: clr) * true) &
 ((bh^(lft) < bh^(rgt)) * true)) & (clr i= 0)):
 (bh^(rgt) + 1);
 case ((((x |-> loc left: lft; loc right: rgt; int key: ky; int color: clr) * true) &
 ((bh^(lft) < bh^(rgt)) * true)) & (~ (clr i= 0))):
 bh^(rgt);
 case ((((x |-> loc left: lft; loc right: rgt; int key: ky; int color: clr) * true) &
 ((bh^(rgt) <= bh^(lft)) * true)) & (clr i= 0)):
 (bh^(lft) + 1);
 default: bh^(lft)
 ) ;
*/
// -----------------------------------------------

_(dryad)
SNnode * rbt_insert_rec(SNnode * x, int k)
/*D_requires (rbp^(x) & (~ (k i-in xks))) ; */
/*D_ensures (
 (
 rbp^(ret) &
 ((keys^(ret) s= (old(keys^(x)) union (singleton k))) & (bh^(ret) i= old(bh^(x))))
 ) &
 ( (ret |-> int color: 0) | ((ret |-> int color: 1) * (((black^(ret->left) * true) | (black^(ret->right) * true)) & ((~ old(black^(x))) | ((black^(ret->left) * true) & (black^(ret->right) * true))))) )
 ) */
{

	if (x == NULL) {
		SNnode * nr = (SNnode *) malloc(sizeof(SNnode));
		_(assume nr != NULL)
        
		nr->key = k;
        nr->color = 1;
		nr->left = NULL;
        nr->right = NULL;
        
        return nr;
	} else if (k < x->key) {
		SNnode * p = rbt_insert_rec(x->left, k);
        
		if (p->color == 0) {
            x->left = p;
            return x;
        }
        else {
            SNnode * xr = x->right;
            if (xr->color != 0) {
                x->left = p;
                p->color = 0;
                xr->color = 0;
                x->color = 1;
                return x;
            } else {
                SNnode * pl = p->left;
                SNnode * pr = p->right;
                if (pr->color != 0) {
                    SNnode * prl = pr->left;
                    SNnode * prr = pr->right;
                    p->right = prl;
                    x->left = prr;
                    pr->left = p;
                    pr->right = x;
                    pr->color = 0;
                    x->color = 1;
                    return pr;
                } else if (pl->color != 0) {
                    p->right = x;
                    x->left = pr;
                    p->color = 0;
                    x->color = 1;
                    return p;
                } else {
                    x->left = p;
                    return x;
                }
            }
        }
	} else {
        SNnode * p = rbt_insert_rec(x->right, k);
        
		if (p->color == 0) {
            x->right = p;
            return x;
        }
        else {
            SNnode * xl = x->left;
            if (xl->color != 0) {
                x->right = p;
                p->color = 0;
                xl->color = 0;
                x->color = 1;
                return x;
            } else {
                SNnode * pl = p->left;
                SNnode * pr = p->right;
                if (pl->color != 0) {
                    SNnode * pll = pl->left;
                    SNnode * plr = pl->right;
                    p->left = plr;
                    x->right = pll;
                    pl->right = p;
                    pl->left = x;
                    pl->color = 0;
                    x->color = 1;
                    return pl;
                } else if (pr->color != 0) {
                    p->left = x;
                    x->right = pl;
                    p->color = 0;
                    x->color = 1;
                    return p;
                } else {
                    x->right = p;
                    return x;
                }
            }
        }
	}
}
