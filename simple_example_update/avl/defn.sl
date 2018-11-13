data a_node {
	a_node left;
	a_node right;
	int key;
	int height; };

pred avl(x) := emp & x=nil
	\/ (exists l, r, k, h. x->a_node{l, r, k, h} * avl(l) * avl(r));
