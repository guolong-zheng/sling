data list_head{
    list_head next;
    list_head prev; };

pred dll(hd, p, tl, n) := hd=n & tl=p
         \/ (exists x. hd->list_head{x, p} * dll(x, hd, tl, n));
