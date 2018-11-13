data b_node {
    b_node left;
    b_node right;
    int key; };

data l_node {
    l_node next;
    int key; };

pred list(x) := emp & x=nil
        \/ (exists n,k. x->l_node{n, k} * list(n));

pred tree(x) := emp & x=nil
        \/ (exists l,r,k. x->b_node{l,r,k} * tree(l) * tree(r));
