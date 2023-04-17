data node {
	node next;
	int value; };

data stack {
	node head; };

pred ls(x,y) := emp & x=y
     \/ (exists n, v. x->node{n, v} * ls(n,y));

pred sk(x) := (exists hd. x->stack{hd} * ls(hd, nil));
