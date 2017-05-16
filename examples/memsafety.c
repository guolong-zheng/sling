struct L2 {
    void        *proto;
    struct L2   *next;
};

# pred LL2(x) == emp & x=null or exists p, q. x->L2<p, q> * Proto(p) * LL2(q); 
# pred Proto(p) == emp or exists v. p->Void<v>;
# pred Proto_Set(s) == emp or exists p, ss. p->Proto(p) * Proto_Set(ss); 

static void l2_destroy(struct L2 *list)
  # requires LL2(list) & list != null
  # ensures emp;
{
    do
      # requires list->L2<p, q> * Proto(p) * LL2(q)
      # ensures LL2(q) & list'=q; // list' is the lastest value of the variable list
    {
        struct L2 *next = list->next;
        free(list->proto);
        free(list);
        list = next;
    }
    while (list);
}

static void l2_destroy_leak_1(struct L2 *list)
  # requires LL2(list) & list != null
  # ensures LL2(list);
{
    do
      # requires list->L2<p, q> * Proto(p) * LL2(q)
      # ensures list->L2<p, q> * LL2(q) & list'=q; // p becomes a dangling pointer after the current iteration
    {
        struct L2 *next = list->next;
        free(list->proto);
        list = next;
    }
    while (list);
}

static void l2_destroy_leak_2(struct L2 *list)
  # requires LL2(list) & list != null
  # ensures Proto_Set(s);
{
    // this is not enough to avoid leaking!
    # LL2(list) & list != null
    # exists p, q. list->L2<p, q> * Proto(p) * LL2(q)
    free(list->proto);
    # exists p, q. list->L2<p, q> * LL2(q)

    do
      # requires list->L2<p, q> * Proto(p) * LL2(q) * Proto_Set(s)
      # ensures LL2(q) * Proto_Set(s') & list'=q; // Proto_Set(s') contains the heap Proto(p) which is not freed
    {
        struct L2 *next = list->next;
        free(list);
        list = next;
    }
    while (list);
}
