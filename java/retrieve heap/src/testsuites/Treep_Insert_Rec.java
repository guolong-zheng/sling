package testsuites;

import java.util.Random;

public class Treep_Insert_Rec {
    static PNode create_tree(int size){
        Random rand = new Random();
        PNode root = null;
        for(int i = 0; i < size - 3; i++){
            root = treap_insert_node(root, i, rand.nextInt(20));
        }
        root = treap_insert_node(root, -5, rand.nextInt(20));
        root = treap_insert_node(root, -2, rand.nextInt(20));
        root = treap_insert_node(root, -4, rand.nextInt(20));
        return root;
    }

    static PNode treap_insert_node(PNode x, int k, int p)
    {
        if (x == null) {
            PNode leaf = new PNode();
            leaf.key = k;
            leaf.prio = p;
            leaf.left = null;
            leaf.right = null;
            return leaf;
        } else {
            if (k < x.key) {
                PNode xr = x.right;
                PNode xl = x.left;
                PNode tmp = treap_insert_node(xl, k, p);
                if (tmp.prio <= x.prio) {
                    x.left = tmp;
                    return x;
                } else {
                    PNode lr = tmp.right;
                    x.left = lr;
                    tmp.right = x;
                    return tmp;
                }
            } else {
                PNode xr = x.right;
                PNode xl = x.left;
                PNode tmp = treap_insert_node(xr, k, p);
                if (tmp.prio <= x.prio) {
                    x.right = tmp;
                    return x;
                } else {
                    PNode rl = tmp.left;
                    x.right = rl;
                    tmp.left = x;
                    return tmp;
                }
            }
        }
    }

    static PNode treap_insert_rec(PNode x, int k, int p)
    {
        //pre
        if (x == null) {
            PNode leaf = new PNode();
            leaf.key = k;
            leaf.prio = p;
            leaf.left = null;
            leaf.right = null;
            //post
            return leaf;
        } else {
            if (k < x.key) {
                PNode xr = x.right;
                PNode xl = x.left;
                PNode tmp = treap_insert_rec(xl, k, p);
                if (tmp.prio <= x.prio) {
                    x.left = tmp;
                    //post
                    return x;
                } else {
                    PNode lr = tmp.right;
                    x.left = lr;
                    tmp.right = x;
                    //post
                    return tmp;
                }
            } else {
                PNode xr = x.right;
                PNode xl = x.left;
                PNode tmp = treap_insert_rec(xr, k, p);
                if (tmp.prio <= x.prio) {
                    x.right = tmp;
                    //post
                    return x;
                } else {
                    PNode rl = tmp.left;
                    x.right = rl;
                    tmp.left = x;
                    //post
                    return tmp;
                }
            }
        }
    }

    public static void main(String args[]){
        Random rand = new Random();
        PNode root = create_tree(10);
        PNode res = treap_insert_rec(root, rand.nextInt(20),rand.nextInt(10));
        treap_insert_rec(root, -100,rand.nextInt(10));
        treap_insert_rec(root, 100,rand.nextInt(20));
    }
}

class PNode{
    int key;
    int prio;
    PNode left;
    PNode right;
}