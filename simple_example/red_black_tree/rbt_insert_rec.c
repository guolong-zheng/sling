#include <stdlib.h>

typedef struct node {
  int key;
  int color;
  struct node * left;
  struct node * right;
} SNnode;

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

int main(){
    SNnode * root = NULL;
    for(int i = 0; i < 5; i++)
        root = rbt_insert_rec(root, (int)rand());

    return 0;
}
