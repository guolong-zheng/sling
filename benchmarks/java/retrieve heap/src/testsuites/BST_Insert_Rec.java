package testsuites;
import java.util.Random;

public class BST_Insert_Rec {
    static BNode  bst_insert_rec(BNode  x, int k)
    {
        //pre
        if (x == null) {
            BNode  leaf = new BNode();
            leaf.key   = k;
            leaf.left  = null;
            leaf.right = null;
            //post
            return leaf;
        } else if (k < x.key) {
            BNode  l = x.left;
            BNode  r = x.right;
            BNode  tmp = bst_insert_rec(l, k);
            x.left = tmp;
            //post
            return x;
        } else {
            BNode  l = x.left;
            BNode  r = x.right;
            BNode  tmp = bst_insert_rec(r, k);
            x.right = tmp;
            //post
            return x;
        }
    }

    static BNode  create_tree(int size)
    {
        BNode  root = null;
        int key;
        Random rand = new Random();
        for(int i = 0; i < size; i++){
            key = rand.nextInt(20);
            root = bst_insert_node(root, key);
        }
        return root;
    }

    static BNode  bst_insert_node(BNode  x, int k)
    {
        //pre
        if (x == null) {
            BNode  leaf = new BNode();
            leaf.key   = k;
            leaf.left  = null;
            leaf.right = null;
            //post
            return leaf;
        } else if (k < x.key) {
            BNode  l = x.left;
            BNode  r = x.right;
            BNode  tmp = bst_insert_node(l, k);
            x.left = tmp;
            //post
            return x;
        } else {
            BNode  l = x.left;
            BNode  r = x.right;
            BNode  tmp = bst_insert_node(r, k);
            x.right = tmp;
            //post
            return x;
        }
    }

    public static void main(String args[]){
        BNode root = create_tree(10);
        bst_insert_rec(root, 5);
        bst_insert_rec(null, 10);
        bst_insert_rec(root, -100);
        bst_insert_rec(root, 100);
    }
}

class BNode{
    BNode left;
    BNode right;
    int key;
}
