data node {
	int key;
	node next; };

pred lseg(x, y) := emp & x=y
	\/ (exists k,n. x->node{k,n} * lseg(n,y));
