data node {
     int key;
     node next; };

pred slist(x, min) := emp & x=nil
     \/ (exists k. x->node{k, nil} & k = min)
     \/ (exists k, n, nmin. x->node{k, n} * slist(n,nmin) & k <= nmin);

pred ls(x, y) := emp & x=y
     \/ (exists k, n. x->node{k, n} * ls(n,y));
