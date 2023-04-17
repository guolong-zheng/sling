data b_node {
	b_node left;
	b_node right;
	int key;
};

pred bst(x, mi, mx) :=
     emp & x=nil & mi<=mx
  \/ (exists k. x->b_node{nil, nil, k} & mi=k & mx=k)
	\/ (exists l,r,k,mil,mxl,mir,mxr.
         x->b_node{l,r,k} * bst(l, mil, mxl) * bst(r, mir, mxr)
      	 & mxl <= k & k <= mir & mi = mil & mx = mxr);
