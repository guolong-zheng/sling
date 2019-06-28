package testsuites;

public class GSlist_Sort_Merge {
    static GSNode create_list(int size){
        GSNode root = null;
        GSNode pos = root;
        for(int i = 0; i < size; i++){
            GSNode new_node = new GSNode();
            new_node.key = i;
            new_node.next = null;
            if(root == null){
                root = new_node;
                pos = root;
            }else{
                pos.next = new_node;
                pos = new_node;
            }
        }
        return root;
    }

    static GSNode g_slist_sort_merge(GSNode l1, GSNode l2)
    {
        //pre
        GSNode list, l, y;
        list = new GSNode();
        y = null;
        list.key = -100;
        list.next = y;
        l = list;
        GSNode list_next =list.next;
        while(l1 != null && l2 != null)
        {
            //loop
            if (l1.key <= l2.key)
            {
                l.next = l1;
                l1 = l1.next;
            } else {
                l.next = l2;
                l2 = l2.next;
            }
            l = l.next;
            if (y == null) {
                y = l;
            }
            l.next = null;
        }
        if (l1 != null) {
            l.next = l1;
        } else {
            l.next = l2;
        }
        //post
        return list_next;
    }

    public static void main(String args[]){
        GSNode list1 = create_list(10);
        GSNode list2 = create_list(10);
        GSNode res = g_slist_sort_merge(list1, list2);
        g_slist_sort_merge(null, null);
        g_slist_sort_merge(create_list(10), null);
        g_slist_sort_merge(null, create_list(10));
    }
}

class GSNode{
    int key;
    GSNode next;
}