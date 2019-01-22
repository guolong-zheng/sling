data a_node {
	a_node left;
	a_node right;
	int key;
	int height; };

pred btree(x) := emp & x=nil
  \/ (exists l, r, k, h. x->a_node{l,r,k,h} * btree(l) * btree(r));

pred height(x, h) := emp & x=nil & h=0
  \/ (exists l,r,k,hx,hl,hr. x->a_node{l, r, k, hx} * height(l, hl) * height(r, hr) & hl<=hr & hr<=hl+1 & h=hr+1)
  \/ (exists l,r,k,hx,hl,hr. x->a_node{l, r, k, hx} * height(l, hl) * height(r, hr) & hr<hl & hl<=hr+1 & h=hl+1);

pred bst(x, mi, mx) := emp & x=nil
  \/ (exists k, h. x->a_node{nil, nil, k, h} & mi=k & mx=k)
  \/ (exists l,r,k, h. x->a_node{l,r,k, h} * bst(l, mil, mxl) * bst(r, mir, mxr)
      		& mxl <= k & k <= mir & mi = mil & mx = mxr);
