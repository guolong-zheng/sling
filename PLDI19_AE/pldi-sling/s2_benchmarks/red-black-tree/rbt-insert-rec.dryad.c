#include "stdhipmem.h"

SNnode * rbt_insert_rec(SNnode * x, int k)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{
    //pre
	if (x == NULL) {
		SNnode * nr = (SNnode *) malloc(sizeof(SNnode));
		nr->key = k;
        nr->color = 1;
		nr->left = NULL;
        nr->right = NULL;
        //post
        return nr;
	} else if (k < x->key) {
		SNnode * p = rbt_insert_rec(x->left, k);
		if (p!=NULL && p->color == 0) {
            x->left = p;
            //post
            return x;
        }
        else {
            SNnode * xr = x->right;
            if (xr!=NULL && xr->color != 0) {
                x->left = p;
                p->color = 0;
                xr->color = 0;
                x->color = 1;
                //post
                return x;
            } else {
                SNnode * pl = p->left;
                SNnode * pr = p->right;
                if (pr!=NULL && pr->color != 0) {
                    SNnode * prl = pr->left;
                    SNnode * prr = pr->right;
                    p->right = prl;
                    x->left = prr;
                    pr->left = p;
                    pr->right = x;
                    pr->color = 0;
                    x->color = 1;
                    //post
                    return pr;
                } else if (pl!=NULL && pl->color != 0) {
                    p->right = x;
                    x->left = pr;
                    p->color = 0;
                    x->color = 1;
                    //post
                    return p;
                } else {
                    x->left = p;
                    //post
                    return x;
                }
            }
        }
	} else {
        SNnode * p = rbt_insert_rec(x->right, k);
		if (p!=NULL && p->color == 0) {
            x->right = p;
            //post
            return x;
        }
        else {
            SNnode * xl = x->left;
            if (xl!=NULL && xl->color != 0) {
                x->right = p;
                p->color = 0;
                xl->color = 0;
                x->color = 1;
                //post
                return x;
            } else {
                SNnode * pl = p->left;
                SNnode * pr = p->right;
                if (pl!=NULL && pl->color != 0) {
                    SNnode * pll = pl->left;
                    SNnode * plr = pl->right;
                    p->left = plr;
                    x->right = pll;
                    pl->right = p;
                    pl->left = x;
                    pl->color = 0;
                    x->color = 1;
                    //post
                    return pl;
                } else if (pr!=NULL && pr->color != 0) {
                    p->left = x;
                    x->right = pl;
                    p->color = 0;
                    x->color = 1;
                    //post
                    return p;
                } else {
                    x->right = p;
                    //post
                    return x;
                }
            }
        }
	}
}
