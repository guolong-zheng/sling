data node {
	int key;
	node next; };

pred sls(x,y,mi) :=
     emp & x=y
  \/ (exists v. x->node{v,y} & mi=v)
  \/ (exists u,v,miu. x->node{v, u} * ls(u, y, miu) & v<=miu);

pred sll(x,mi) :=
     emp & x=nil
  \/ (exists v. x->node{v, nil} & mi=v)
  \/ (exists v,y,miy. x->node{v, y} * sll(y,miy) & v<=miy);
