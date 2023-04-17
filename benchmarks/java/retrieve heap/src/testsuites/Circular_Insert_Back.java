package testsuites;
import java.util.Random;

public class Circular_Insert_Back {
    static CNode  create_list(int size){
        Random rand = new Random();
        CNode  hd = null;
        for(int i = 0; i < size; i++){
            CNode  newnode = new CNode();
            newnode.key = rand.nextInt(20);
            if(hd == null){
                hd = newnode;
                hd.next = hd;
            }else{
                newnode.next = hd.next;
                hd.next = newnode;
            }
        }
        return hd;
    }

    static CNode  lseg_insert_back(CNode  hd, CNode  tl)
    {
        CNode  new_node = new CNode();
        new_node.next = hd;
        tl.next = new_node;
        return new_node;
    }

    static CNode  circular_list_insert_back(CNode  x)
    {
        //pre
        CNode  next = x.next;
        if (next == x) {
            CNode  tl = new CNode();
            tl.next = x;
            x.next = tl;
            //post
            return tl;
        } else {
            CNode  tl = lseg_insert_back(next, x);
            x.next = tl;
            //post
            return tl;
        }
    }

    public static void main(String args[]){
        CNode  root = create_list(10);
        CNode  res = circular_list_insert_back(root);
        circular_list_insert_back(create_list(1));
    }
}

class CNode{
    int key;
    CNode next;
}
