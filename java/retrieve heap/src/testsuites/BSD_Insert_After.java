package testsuites;

public class BSD_Insert_After {

    static Node create_queue(int size){
        Node hd = new Node();
        hd.next = null;
        hd.last = hd;

        for(int i = 0; i < size; i++){
            Node new_node = new Node();
            new_node.next = null;
            Node  lst = hd.last;
            lst.next = new_node;
            hd.last = new_node;
        }
        return hd;
    }

    static Node simpleq_insert_after(Node  head, Node listelm)
    {
        //pre
        Node  elm = new Node();
        Node  lenn = listelm.next;
        elm.next = lenn;
        if (lenn == null) {
            head.last = elm;
        }
        listelm.next = elm;
        //post
        return head;
    }

    public static void main(String args[]){
        Node hd = create_queue(10);
        Node elm = hd.next;
        simpleq_insert_after(hd, elm);
    }
}

class Node{
    Node next;
    Node last;
}
