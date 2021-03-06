data t_node {
	t_node left;
	t_node right;
	int key; };

pred tree(x) := emp & x=nil
	\/ (exists l,r,k. x->t_node{l,r,k} * tree(l) * tree(r));

pred tseg(x, y) := emp & x=y
 	\/ (exists l,r,k. x->t_node{l,r,k} * tree(l) * tseg(r, y))
	\/ (exists l,r,k. x->t_node{l,r,k} * tseg(l, y) * tree(r));
