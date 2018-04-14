data slave_item {
     slave_item next;
     slave_item prev; };

pred dll(hd, p, tl, n) := hd=n & tl=p
     \/ (exists x. hd->slave_item{x, p} * dll(x, hd, tl, n));
