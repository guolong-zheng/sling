package testsuites;

import java.util.Random;

public class Grass_Dl_Insert {
    static GNode create_list(int size){
        GNode root = null;
        GNode tl = root;
        for(int i = 0; i < size; i++){
            GNode new_node = new GNode();
            new_node.next = null;
            new_node.prev = null;

            if(root == null){
                root = new_node;
                tl = new_node;
            }else{
                tl.next = new_node;
                new_node.prev = tl;
                tl = new_node;
            }
        }

        return root;
    }

    static GNode dl_insert(GNode lst, GNode elt)
    {
        Random rand = new Random();
        //pre
        if (lst == null) {
            //post
            return elt;
        } else {
            int nondet = rand.nextInt(10) % 10 - 5;
            GNode curr = lst;
            while(nondet > 0 && curr.next != null)
            {
                //loop
                nondet = rand.nextInt(10) % 10 - 5;
                curr = curr.next;
            }
            GNode curr_next = curr.next;
            elt.next = curr_next;
            if (curr_next != null) {
                curr_next.prev = null;
            }
            curr.next = elt;
            elt.prev = curr;
            //post
            return lst;
        }
    }
    
    public static void main(String args[]){
        GNode lst = create_list(10);
        GNode elt = new GNode();
        elt.next = null;
        elt.prev = null;
        GNode res = dl_insert(lst, elt);
        dl_insert(null, elt);
    }
}

class GNode{
    GNode next;
    GNode prev;
}