package testsuites;

public class Grass_Sls_Pairwise {
    static GSLSNode create_list(int init, int size){
        GSLSNode root = null;
        GSLSNode tl = root;
        int i = 0;
        for(i = 0; i < size; i++){
            GSLSNode new_node = new GSLSNode();
            new_node.key = init + i;
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

    static GSLSNode sls_pairwise_sum(GSLSNode x, GSLSNode y)
    {
        //pre
        if (x == null || y == null) {
            //post
            return null;
        }
        GSLSNode curr_x = x;
        GSLSNode curr_y = y;
        GSLSNode z = new GSLSNode();
        GSLSNode last_z = z;
        int z_key = (curr_x.key + curr_y.key);
        z.key = z_key;
        z.next = null;
        while(curr_x.next != null && curr_y.next != null)
        {
            //loop
            GSLSNode tmp = last_z;
            curr_x = curr_x.next;
            curr_y = curr_y.next;
            last_z = new GSLSNode();

            last_z.next = null;
            z_key = (curr_x.key + curr_y.key);
            last_z.key = z_key;
            tmp.next = last_z;
        }
        //post
        return z;
    }
    
    public static void main(String args[]){
        GSLSNode x = create_list(1, 10);
        GSLSNode y = create_list(10, 10);
        GSLSNode res = sls_pairwise_sum(x,y);
        sls_pairwise_sum(null, null);
        sls_pairwise_sum(x, null);
        sls_pairwise_sum(null, x);
    }
}

class GSLSNode{
    int key;
    GSLSNode next;
}