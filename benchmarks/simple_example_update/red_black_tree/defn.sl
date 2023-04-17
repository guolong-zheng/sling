data node {
  int key;
  int color;
  node left;
  node right; };

pred tree(x) := emp & x=nil
        \/ (exists k,c,l,r. x->node{k,c,l,r} * tree(l) * tree(r));
