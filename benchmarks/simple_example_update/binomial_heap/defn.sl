data node {
  int key;
  int order;
  node children;
  node sibling; };

pred bh(x) := emp & x=nil
        \/(exists k,o,c,s. x->node{k,o,c,s} * bh(c) * bh(s));
