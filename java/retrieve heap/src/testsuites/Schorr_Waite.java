package testsuites;

import java.util.Random;

public class Schorr_Waite {
    static void schorr_waite(node root)
    {
        //pre
        node t = root;
        node p = null;
        while(p != null || (t != null && ! (t.m)))
        {
            //loop
            if(t == null || t.m) {
                if(p.c) {
                    node q = t;
                    t = p;
                    p = p.r;
                    t.r = q;
                } else {
                    node q = t;
                    t = p.r;
                    p.r = p.l;
                    p.l = q;
                    p.c = true;
                }
            } else {
                node q = p;
                p = t;
                t = t.l;
                p.l = q;
                p.m = true;
                p.c = false;
            }
        }
        //post
    }

    static node makeNode()
    {
        //pre
        node n = new node();
        n.m = false;
        n.c = false;
        n.l = null;
        n. r = null;
        //post
        return n;
    }

    public static void main(String args[])
    {
        Random rand = new Random();
        int seed  = 10;
        int i = 1;
        node root = makeNode();
        while (i < 10) {
            node n = root;
            node p = null;
            int j = 0;
            while (n != null) {
                j = rand.nextInt(10) ;
                p = n;
                if (j>5) n = n.l;
                else n = n.r;
            }
            if (j>5) p.l = makeNode();
            else p.r = makeNode();
            i++;
        }
        schorr_waite(root);
        return;
    }

}

class node{
    boolean m;
    boolean c;
    node l;
    node r;
}