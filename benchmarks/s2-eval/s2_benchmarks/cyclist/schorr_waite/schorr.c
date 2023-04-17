#include "stdhipmem.h"

void schorr_waite(struct node* root)
/*
  infer[@shape]
  requires true
  ensures true;
*/
{
  //pre
  struct node* t = root;
  struct node* p = 0;
  while(p != 0 || (t != 0 && ! (t->m)))
  /*@
  infer[@shape]
  requires true
  ensures true;
*/
  {
    //loop
    if(t == 0 || t->m) {
      if(p->c) {
        struct node* q = t;
        t = p;
        p = p->r;
        t->r = q;
      } else {
        struct node* q = t;
        t = p->r;
        p->r = p->l;
        p->l = q;
        p->c = 1;
      }
    } else {
      struct node* q = p;
      p = t;
      t = t->l;
      p->l = q;
      p->m = 1;
      p->c = 0;
    }
  }
  //post
}

