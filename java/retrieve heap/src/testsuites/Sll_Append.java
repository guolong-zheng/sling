package testsuites;

public class Sll_Append {
    static SLnode create_node(int i)
    {
        SLnode node = new SLnode();
        node.key = i;
        node.next = null;
        return node;
    }

    static SLnode create_sll(int size){
        int i;
        SLnode root = null;
        for(i = 0; i < size; i++){
            root = sll_append_node(root, create_node(i));
        }

        return root;
    }

    static SLnode sll_append_node(SLnode x1, SLnode x2)
    {
        if (x1 == null) {
            return x2;
        } else {
            SLnode tmp = sll_append_node(x1.next, x2);
            x1.next = tmp;
            return x1;
        }
    }

    static SLnode sll_append(SLnode x1, SLnode x2)
    {
        //pre
        if (x1 == null) {
            //post
            return x2;
        } else {
            SLnode tmp = sll_append(x1.next, x2);
            x1.next = tmp;
            //post
            return x1;
        }
    }

    public static void main(String args[]){
        sll_append(null,null);
        SLnode l1 = create_sll(10);
        sll_append(null, l1);
        sll_append(l1, null);
        SLnode l2 = create_sll(10);
        sll_append(l1, l2);
    }
}

class SLnode{
    int key;
    SLnode next;
}
