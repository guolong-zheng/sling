data a_node {
	a_node left;
	a_node right;
	int key;
	int height; };

pred avl(x, h) := emp & x=nil & h=0
  \/ (exists l,r,k,hx,hl,hr. x->a_node{l, r, k, hx} * avl(l, hl) * avl(r, hr) & hl<=hr & hr<=hl+1 & h=hr+1)
  \/ (exists l,r,k,hx,hl,hr. x->a_node{l, r, k, hx} * avl(l, hl) * avl(r, hr) & hr<hl & hl<=hr+1 & h=hl+1);