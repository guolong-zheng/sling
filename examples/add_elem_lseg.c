pred lseg(x, y) == emp & x=y or (exists p: x->[n: p] * lseg(p, y))

void insert(List e, List h, List x) 
{
  { e->_ * lseg(h, x) }
  p = h;
  { e->_ * lseg(h, x) & p=h }
  q = null;
  { e->_ * lseg(h, x) & p=h & q=nil }
  
  while (p != x && p != null) 
  {
    { lseg(p, p') * lseg(p', x) & p'!=x & p'!=nil }
    q = p;
    { lseg(p, p') * p'->t * lseg(t, x) & p'!=x & p'!=nil & q'=p' }
    p = p->n; 
    { lseg(p, q') * q'->p' * lseg(p', x) }
  } 
  
  { e->_ * lseg(h, q') * q'->x & p'=x }
  q->n = e;
  { e->_ * lseg(h, q') * q'->e & p'=x }
  e->n = p; 
  { lseg(h, q') * q'->e * e->x }
} 