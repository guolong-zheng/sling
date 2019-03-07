data node{
    node left;
    node right;
    node parent;
    int count; };

pred root(x) := emp & x=nil
        \/ (exists l, r, c. x->node{l,r,nil,c} * tree(l) * tree(r));

pred tree(x) := emp & x=nil
        \/ (exists l, r, p, c. x->node{l, r, p, c} * tree(l) * tree(r));

pred tseg(x, y) := emp & x=y
        \/ (exists l, r, p, c. x->node{l,r,p,c} * tseg(l, y) * tree(r))
        \/ (exists l, r, p, c. x->node{l,r,p,c} * tree(l) * tseg(r, y));
