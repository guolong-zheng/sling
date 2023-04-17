package testsuites;

import java.util.Random;

public class Glist_Prepend {
    static DLnode create_list(int size){
        DLnode hd = null;
        DLnode tl = hd;
        for(int i = 0; i < size; i++){
            DLnode new_node = new DLnode();
            new_node.key = i;
            new_node.next = null;
            new_node.prev = null;
            if(hd == null){
                hd = new_node;
                tl = hd;
            }else{
                new_node.prev = tl;
                //new_node.next = hd;
                //hd.prev = new_node;
                tl.next = new_node;
                tl = new_node;
            }
        }

        return hd;
    }

    static DLnode g_list_prepend(DLnode list, int data, DLnode p)
    {
        //pre
        DLnode ret = new DLnode();
        ret.key = data;
        ret.next = list;
        ret.prev = p;
        if (list != null) {
            list.prev = ret;
        }
        if (p != null) {
            p.next = ret;
        }
        //post
        return ret;
    }
    
    public static void main(String args[]){
        Random rand = new Random();
        DLnode hd = create_list(10);
        DLnode p = hd.prev;
        DLnode res = g_list_prepend(hd, rand.nextInt(20), p);
        p = hd.next.next;
        g_list_prepend(hd, rand.nextInt(20), p);
        g_list_prepend(null, rand.nextInt(20), p);
    }
}

class DLnode{
    int key;
    DLnode next;
    DLnode prev;
}
