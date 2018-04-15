data node{
    node next;
    int value; };

data l_list{
    node first;
    node last; };

data iter {
    node current;};


pred lseg(x, y) := emp & x=y
        \/ (exists n, v. x->node{n, v} * lseg(n,y));

pred llist(l) :=
        (exists fst, lst. l->l_list{fst,lst} * lseg(fst, lst));

pred lseg2(x, y, f) := emp & x=y
        \/ (exists n, v. x->node{n, v} * lseg2(n, y, f));

pred llist_with_node(l, n) :=
        (exists fst, lst. l->l_list{fst,lst} * lseg2(fst,n,l) * lseg(n,lst));

pred iterp(i, l) :=
        (exists n. i->iter{n} * llist_with_node(l, n));
