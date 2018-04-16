data node {
  int key;
  int color;
  node left;
  node right; };

pred tree(x) := emp & x=nil
        \/ (exists k,c,l,r. x->node{k,c,l,r} * tree(l) * tree(r));

pred tseg(x, y) := emp & x=y
        \/ (exists k,c,l,r. x->node{k,c,l,r} * tree(l) * tseg(r, y))
        \/ (exists k,c,l,r. x->node{k,c,l,r} * tseg(l, y) * tree(r));
