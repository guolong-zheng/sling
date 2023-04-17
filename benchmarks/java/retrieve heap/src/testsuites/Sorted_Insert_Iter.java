package testsuites;

import java.util.Random;

public class Sorted_Insert_Iter {

    static SortNode create_sorted_list(int min, int max, int size){
        Random rand = new Random();
        SortNode root = null;
        for(int i = 0; i < size; i++){
            root = sorted_insert_node(root, rand.nextInt(max - min) + min);
        }
        return root;
    }

    static SortNode create_list(int size){
        Random rand = new Random();
        SortNode root = null;
        for(int i = 0; i < size; i++){
            root = sorted_insert_node(root, rand.nextInt(20));
        }
        return root;
    }

    static SortNode sorted_insert_node(SortNode l, int k)
    {
        if (l == null) {
            SortNode tl = new SortNode();
            tl.key = k;
            tl.next = null;
            return tl;
        } else {
            if (k <= l.key) {
                SortNode hd = new SortNode();
                hd.key = k;
                hd.next = l;
                return hd;
            } else {
                SortNode prev = l;
                SortNode next = l.next;
                while(next != null && k > next.key)
                {
                    prev = next;
                    next = next.next;
                }
                SortNode curr = new SortNode();
                curr.key = k;
                curr.next = next;
                prev.next = curr;
                return l;
            }
        }
    }

    static SortNode create_random(int size){
        Random rand = new Random();
        SortNode root = null;
        SortNode tail = null;
        for(int i = 0; i < size; i++){
            SortNode tmp = new SortNode();
            tmp.next = null;
            tmp.key = rand.nextInt(20);
            if(root == null){
                root = tmp;
                tail = tmp;
            }else{
                tail.next = tmp;
                tail = tmp;
            }
        }
        return root;
    }

    static SortNode sorted_insert_iter(SortNode l, int k)
    {
        //pre
        SortNode ret;
        if (l == null) {
            SortNode tl = new SortNode();
            tl.key = k;
            tl.next = null;
            ret = tl;
            //return tl;
        } else {
            if (k <= l.key) {
                SortNode hd = new SortNode();
                hd.key = k;
                hd.next = l;
                ret = hd;
                //return hd;
            } else {
                SortNode prev = l;
                SortNode next = l.next;
                while(next != null && k > next.key)
                {
                    //loop
                    prev = next;
                    next = next.next;
                }
                SortNode curr = new SortNode();
                curr.key = k;
                curr.next = next;
                prev.next = curr;
                ret = l;
                //return l;
            }
        }
        //post
        return ret;
    }

    public static void main(String args[]){
        Random rand = new Random();
        SortNode root = create_sorted_list(0, 50, 10);

        SortNode res = sorted_insert_iter(root, rand.nextInt(20));
        sorted_insert_iter(root, 100);
        sorted_insert_iter(null, rand.nextInt(20));
    }
}

class SortNode{
    int key;
    SortNode next;
}
