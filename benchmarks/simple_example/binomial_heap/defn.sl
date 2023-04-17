data node {
  int key;
  int order;
  node children;
  node sibling; };

pred bh(x) := emp & x=nil
        \/(exists k,o,c,s. x->node{k,o,c,s} * bh(c) * bh(s));

pred bhseg(x,y) := emp & x=y
        \/(exists k,o,c,s. x->node{k,o,c,s} * bhseg(c,y) * bh(s))
        \/(exists k,o,c,s. x->node{k,o,c,s} * bh(c) * bhseg(s,y));
