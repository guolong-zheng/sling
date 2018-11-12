data node {
  int key;
  int color;
  node left;
  node right; };

pred rb(x, cl, bh) :=
     emp & x=nil & bh=1 & cl=0 
     \/ (exists k,l,r,bhl,bhr. x->node{k, 1, l, r} * rb(l, 0, bhl) * rb(r, 0, bhr) & cl=1 & bhl=bh & bhr=bh)
     \/ (exists k,l,r,bhl,bhr,cll,clr. x->node{k, 0, l, r} * rb(l, cll, bhl) * rb(r, clr, bhr) & cl=0 & bhl=bhr & bh=1+bhl);
