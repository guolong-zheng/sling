data b_node {
	b_node left;
	b_node right;
	int key;
	int prio; };

pred tree(x) := emp & x=nil
	\/ (exists l,r,k,p. x->b_node{l,r,k,p} * tree(l) * tree(r));
