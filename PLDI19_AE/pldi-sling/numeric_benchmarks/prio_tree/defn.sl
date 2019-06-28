data b_node {
	b_node left;
	b_node right;
	int key;
	int prio; };

pred treep(x, mi, mx, p) := emp & x=nil
        \/ (exists k. x->b_node{nil,nil,k,p} & mi=k & mx=k)
        \/ (exists l,r,k. x->b_node{l,r,k,p} * treep(l, mil, mxl, lp) * treep(r,mir,mxr,lr)
                & mxl<=k & k<=mir & mi = mil & mx=mxr & lp<p & lr<p );
