data b_node {
	b_node left;
	b_node right;
	int key; };

pred tree(x) := emp & x=nil
	\/ (exists l,r,k. x->b_node{l,r,k} * tree(l) * tree(r));

pred tseg(x, y) := emp & x=y
 	\/ (exists l,r,k. x->b_node{l,r,k} * tree(l) * tseg(r, y))
	\/ (exists l,r,k. x->b_node{l,r,k} * tseg(l, y) * tree(r));
