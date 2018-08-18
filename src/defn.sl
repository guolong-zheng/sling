data SlNode{
    int value;
    SlNode nextRef; };

pred sll(x) := emp & x=nil
    \/ (exists k, n. x->SlNode{k,n} * sll(n));

pred slseg(x,y) := emp & x=y
    \/ (exists u, v. x->SlNode{v, u} * slseg(u, y));
