package testsuites;

import java.util.Random;

public class Tree_Inorder {
    static TNode insert(TNode root, TNode node){
        Random rand = new Random();
        if(root == null)
            return node;

        if(rand.nextInt(10) >= 5){
            root.left = insert(root.left, node);
        }else{
            root.right = insert(root.right, node);
        }
        return root;
    }

    static TNode create_tree(int size){
        Random rand = new Random();
        TNode root = null;
        for(int i = 0; i < size; i++){
            TNode node = new TNode();
            node.left = null;
            node.right = null;
            node.key = rand.nextInt(20);
            root = insert(root, node);
        }
        return root;
    }
    
    static int inorder(TNode x, int n)
    {
        //pre
        if (x == null) {
            //post
            return n;
        } else {
            int n1 = inorder(x.left, n);
            x.key = n1;
            int n2 = n1 + 1;
            int n3 = inorder(x.right, n2);
            //post
            return n3;
        }
    }

    public static void main(String args[]){
        TNode root = create_tree(10);

        int res = inorder(root, 0);
        inorder(null, 0);
    }
}

class TNode{
    int key;
    TNode left;
    TNode right;
}
