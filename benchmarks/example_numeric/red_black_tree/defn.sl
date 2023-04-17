data node {
  int key;
  int color;
  node left;
  node right; };

pred rbt(x, cl, bh) :=
     emp & x=nil & bh=1 & cl=0 
     \/ (exists k,l,r,bhl,bhr. x->node{k, 1, l, r} * rbt(l, 0, bhl) * rbt(r, 0, bhr) & cl=1 & bhl=bh & bhr=bh)
     \/ (exists k,l,r,bhl,bhr,cll,clr. x->node{k, 0, l, r} * rbt(l, cll, bhl) * rbt(r, clr, bhr) & cl=0 & bhl=bhr & bh=1+bhl);
