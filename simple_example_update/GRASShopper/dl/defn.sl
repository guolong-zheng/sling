data node {
     node next;
     node prev; };

pred dll(hd, p, tl, n) := hd=n & tl=p
     \/ (exists x. hd->node{x, p} * dll(x, hd, tl, n));
