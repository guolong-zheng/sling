#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int rand_num();
SNnode * rbt_delete_rec(SNnode * x, int k, int fixed);
int rbt_find_smallest(SNnode * x);
int rbt_delete_left_fixup(SNnode * x, SNnode * xl, SNnode * xr, int clr, int  fixed);
int rbt_delete_right_fixup(SNnode * x, SNnode * xl, SNnode * xr, int clr, int  fixed);
SNnode * rbt_insert_rec(SNnode * x, int k);

SNnode * rbt_delete_rec(SNnode * x, int k, int fixed)
{
    //pre
	if (x == NULL) {
        fixed = 1;
        //post
        return NULL;
	} else if (k == x->key) {
        SNnode * xl = x->left;
        SNnode * xr = x->right;
		if (xl == NULL && xr == NULL) {
            fixed = x->color;
            free(x);
            //post
            return NULL;
        } else if (xl == NULL){
            if (x->color != 0) {
                xr->color = 0;
                free(x);
                fixed = 1;
                //post
                return xr;
            } else {
                fixed = x->color;
                free(x);
                //post
                return xr;
            }
        } else if (xr == NULL) {
            if (x->color != 0) {
                xl->color = 0;
                free(x);
                fixed = 1;
                //post
                return xl;
            } else {
                fixed = x->color;
                free(x);
                //post
                return xl;
            }
        } else {
            int min = rbt_find_smallest(xr);
            x->key = min;
            SNnode * n = rbt_delete_rec(xr, min, fixed);
            x->right = n;
            if (fixed != 0)
                //post
                return x;
            else {
                SNnode * xl = x->left;
                SNnode * xr = x->right;
                int xc = x->color;
                SNnode * ret = rbt_delete_right_fixup(x, xl, xr, xc, fixed);
                //post
                return ret;
            }
        }
	} else if (k < x->key) {
        SNnode * newl = rbt_delete_rec(x->left, k);
		x->left = newl;
        if (fixed != 0)
            //post
            return x;
        else {
            SNnode * xl = x->left;
            SNnode * xr = x->right;
            int xc = x->color;
            SNnode * ret = rbt_delete_left_fixup(x, xl, xr, xc, fixed);
            //post
            return ret;
        }
	} else {
        SNnode * newr = rbt_delete_rec(x->right, k);
		x->right = newr;

        if (fixed != 0)
            //post
            return x;
        else {
            SNnode * xl = x->left;
            SNnode * xr = x->right;
            int xc = x->color;
            SNnode * ret = rbt_delete_right_fixup(x, xl, xr, xc, fixed);
            //post
            return ret;
        }
    }
}

int rbt_find_smallest(SNnode * x)
{
	if (x->left == NULL) {
        return x->key;
	} else {
		int ret = rbt_tree_find_smallest(x->left);
        return ret;
	}
}

SNnode * rbt_delete_left_fixup(SNnode * x, SNnode * xl, SNnode * xr, int clr, int  fixed)
{
	int xrcolor = xr->color;
	if (xrcolor != 0) {
        SNnode * xrl = xr->left;
        x->right = xrl;
        xr->left = x;
        x->color = 1;
        xr->color = 0;
        SNnode * p = rbt_delete_left_fixup(x, xl, xrl, 1, fixed);
        xr->left = p;
        return xr;
    } else {
        SNnode * xrl = xr->left;
        SNnode * xrr = xr->right;
        int xrlcolor = xrl->color;
        int xrrcolor = xrr->color;
        if (xrrcolor != 0) {
            fixed = 1;
            x->right = xrl;
            xr->left = x;
            xr->color = xcolor;
            x->color = 0;
            xrr->color = 0;
            return xr;
        }
        if (xrlcolor == 0) {
            fixed = xcolor;
            xr->color = 1;
            x->color = 0;
            return x;
        } else {
            fixed = 1;
            SNnode * xrll = xrl->left;
            SNnode * xrlr = xrl->right;
            xr->left = xrlr;
            xrl->right = xr;
            xrl->left = x;
            x->right = xrll;
            xrl->color = xcolor;
            x->color = 0;
            return xrl;
        }
    }
}

int rbt_delete_right_fixup(SNnode * x, SNnode * xl, SNnode * xr, int clr, int  fixed)
{
	int xlcolor = xl->color;
	if (xlcolor != 0) {
        SNnode * xlr = xl->right;
        x->left = xlr;
        xl->right = x;
        x->color = 1;
        xl->color = 0;
        SNnode * p = rbt_delete_right_fixup(x, xlr, xr, 1, fixed);
        xl->right = p;
        return xl;
    } else {
        SNnode * xlr = xl->right;
        SNnode * xll = xl->left;
        int xlrcolor = xlr->color;
        int xllcolor = xll->color;
        if (xllcolor != 0) {
            fixed = 1;
            x->left = xlr;
            xl->right = x;
            xl->color = xcolor;
            x->color = 0;
            xll->color = 0;
            return xl;
        }
        if (xlrcolor == 0) {
            fixed = xcolor;
            xl->color = 1;
            x->color = 0;
            return x;
        } else {
            fixed = 1;
            SNnode * xlrr = xlr->right;
            SNnode * xlrl = xlr->left;
            xl->right = xlrl;
            xlr->left = xl;
            xlr->right = x;
            x->left = xlrr;
            xlr->color = xcolor;
            x->color = 0;
            return xlr;
        }
    }
}

SNnode * rbt_insert_rec(SNnode * x, int k)
{
	if (x == NULL) {
		SNnode * nr = (SNnode *) malloc(sizeof(SNnode));
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

int rand_num(){
    return rand()%(2*MAX_RAND + 1) - MAX_RAND;
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    SNnode * root = NULL;
    for(int i = 0; i < size; i++)
        root = rbt_insert_rec(root, rand_num());

    SNnode * res = rbt_delete_rec(root, rand_num(),1);
    return 0;
}
