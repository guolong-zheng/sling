data node {
  bool m;
  bool c;
  node l;
  node r; };

pred tree(t) := emp & t=nil
        \/ (exists m,c,l,r. t->node{m,c,l,r} * tree(l) * tree(r);
