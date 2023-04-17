package testsuites;

public class Dll_Concat {
    static DLNode  create_node(int i){
        DLNode  node = new DLNode();
        node.key = i;
        node.next = null;
        node.prev = null;

        return node;
    }

    static DLNode  create_dll(int size){
        DLNode  root = null;
        int i = 0;
        for(i = 0; i < size; i++){
            DLNode  node = create_node(i);
            if(root == null)
                root = node;
            else{
                root.prev = node;
                node.next = root;
                root = node;
            }
            //root = dll_append_node(root, node);
        }

        return root;
    }

    DLNode  dll_append_node(DLNode  x1, DLNode  x2)
    {
        if (x1 == null) {
            return x2;
        } else {
            DLNode  tmp = dll_append_node(x1.next, x2);
            x1.next = tmp;
            if (tmp != null) tmp.prev = x1;
            return x1;
        }
    }

    static DLNode dll_concat(DLNode x, DLNode y)
    {
        //pre
        if (x == null) {
            //post
            return y;
        } else {
            DLNode tmp = dll_concat(x.next, y);
            x.next = tmp;
            if (tmp!=null) tmp.prev = x;
            //post
            return x;
        }
    }
    
    public static void main(String args[]){
        DLNode  root = null;
        root = create_dll(10);

        DLNode  node = create_dll(10);
        DLNode  res = null;
        res = dll_concat(root, node);
        dll_concat(null, null);
        dll_concat(create_dll(10),null);
        dll_concat(null, create_dll(10));
    }
}

class DLNode{
    int key;
    DLNode next;
    DLNode prev;
}
