package testsuites;

import java.util.Random;

public class Rbt_Insert {
    static RBNode rbt_insert_rec(RBNode x, int k)
    {
        //pre
        if (x == null) {
            RBNode nr = new RBNode();
            nr.key = k;
            nr.color = 1;
            nr.left = null;
            nr.right = null;
            //post
            return nr;
        } else if (k < x.key) {
            RBNode p = rbt_insert_rec(x.left, k);
            if (p!=null && p.color == 0) {
                x.left = p;
                //post
                return x;
            }
            else {
                RBNode xr = x.right;
                if (xr!=null && xr.color != 0) {
                    x.left = p;
                    p.color = 0;
                    xr.color = 0;
                    x.color = 1;
                    //post
                    return x;
                } else {
                    RBNode pl = p.left;
                    RBNode pr = p.right;
                    if (pr!=null && pr.color != 0) {
                        RBNode prl = pr.left;
                        RBNode prr = pr.right;
                        p.right = prl;
                        x.left = prr;
                        pr.left = p;
                        pr.right = x;
                        pr.color = 0;
                        x.color = 1;
                        //post
                        return pr;
                    } else if (pl!=null && pl.color != 0) {
                        p.right = x;
                        x.left = pr;
                        p.color = 0;
                        x.color = 1;
                        //post
                        return p;
                    } else {
                        x.left = p;
                        //post
                        return x;
                    }
                }
            }
        } else {
            RBNode p = rbt_insert_rec(x.right, k);
            if (p!=null && p.color == 0) {
                x.right = p;
                //post
                return x;
            }
            else {
                RBNode xl = x.left;
                if (xl!=null && xl.color != 0) {
                    x.right = p;
                    p.color = 0;
                    xl.color = 0;
                    x.color = 1;
                    //post
                    return x;
                } else {
                    RBNode pl = p.left;
                    RBNode pr = p.right;
                    if (pl!=null && pl.color != 0) {
                        RBNode pll = pl.left;
                        RBNode plr = pl.right;
                        p.left = plr;
                        x.right = pll;
                        pl.right = p;
                        pl.left = x;
                        pl.color = 0;
                        x.color = 1;
                        //post
                        return pl;
                    } else if (pr!=null && pr.color != 0) {
                        p.left = x;
                        x.right = pl;
                        p.color = 0;
                        x.color = 1;
                        //post
                        return p;
                    } else {
                        x.right = p;
                        //post
                        return x;
                    }
                }
            }
        }
    }

    public static void main(String args[]){
        Random rand = new Random();
        RBNode root = null;
        for(int i = 0; i < 10; i++)
            root = rbt_insert_rec(root, rand.nextInt(20));
    }
}

class RBNode{
    int key;
    int color;
    RBNode left;
    RBNode right;
}
