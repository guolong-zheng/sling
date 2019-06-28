data node {
    int key;
    node next;
    node prev; };

pred dll(hd, p, tl, n) := hd=n & tl=p
         \/ (exists d, x. hd->node{d, x, p} * dll(x, hd, tl, n));
