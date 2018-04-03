data node {
	int prio;
	int key;
	node left;
	node right; };

pred tree(x) := emp & x=nil
	\/ (exists p,k,l,r. x->node{p,k,l,r} * tree(l) * tree(r));
