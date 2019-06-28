package testsuites;

import java.util.Random;

public class Grass_Sl_Insert {
    static GSLNode create_list(int size){
        GSLNode root = null;
        GSLNode tl = root;
        for(int i = 0; i < size; i++){
            GSLNode new_node = new GSLNode();
            new_node.next = null;
            if(root == null){
                root = new_node;
                tl = root;
            }else{
                tl.next = new_node;
                tl = new_node;
            }
        }

        return root;
    }

    static GSLNode sl_insert(GSLNode lst, GSLNode elt)
    {
        Random rand = new Random();
        //pre
        if (lst == null) {
            //post
            return elt;
        } else {
            int nondet = rand.nextInt(10)%10 - 5;
            GSLNode curr = lst;
            while(nondet> 0 && curr.next != null)
            {
                //loop
                nondet = rand.nextInt(10)%10 - 5;
                curr = curr.next;
            }
            GSLNode curr_next = curr.next;
            elt.next = curr_next;
            curr.next = elt;
            //post
            return lst;
        }
    }

    public static void main(String args[]){
        GSLNode lst = create_list(10);
        GSLNode elt = new GSLNode();
        elt.next = null;
        GSLNode res = sl_insert(lst, elt);
        sl_insert(null, elt);
    }

}

class GSLNode{
    GSLNode next;
}
