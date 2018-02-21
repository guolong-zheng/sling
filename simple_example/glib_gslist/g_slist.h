#ifndef G_SLIST_H_
#define G_SLIST_H_

typedef struct node {
  int key;
  struct node * next;
} Node;

Node * create_list(int size);
Node * g_slist_last(Node * list);
Node * g_slist_remove_link(Node * list, Node * link);
Node * g_slist_prepend (Node * list, int data);
Node * g_slist_sort_merge(Node * l1, Node * l2);
Node * g_slist_append(Node * list, int data);

Node * create_list(int size){
    Node * root = NULL;
    Node * pos = root;
    for(int i = 0; i < size; i++){
        Node * new_node = (Node *)malloc(sizeof(Node));
        new_node->key = (int)rand();
        new_node->next = NULL;
        if(root == NULL){
            root = new_node;
            pos = root;
        }else{
            pos->next = new_node;
            pos = new_node;
        }
    }
    return root;
}

Node * g_slist_last(Node * list){
    if (list != NULL)
  {
    while(list->next != NULL)
    {
      list = list->next;
    }

  }
  return list;
}

Node * g_slist_remove_link(Node * list, Node * link){
    Node * tmp;
	Node * prev;
    int tp;
	prev = NULL;
	tmp = list;
	while(tmp != NULL)
	{
		if (tmp == link)
		{
			Node * tmp_next = tmp->next;
			if (prev != NULL) {
        tp = prev->key;
				prev->next = tmp_next;

			} else {
				list = tmp_next;
			}
			tmp->next = NULL;
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return list;
}

Node * g_slist_prepend (Node * list, int data)
{
  Node * new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;
  new_list->next = list;
  return new_list;
}

Node * g_slist_sort_merge(Node * l1, Node * l2)
{
	Node * list, * l, * y;
	list = (Node *) malloc(sizeof(Node));

    y = NULL;
	list->key = INT_MIN;
	list->next = y;
	l = list;
    Node * list_next =list->next;
	while(l1 != NULL && l2 != NULL)
	{
		if (l1->key <= l2->key)
		{
			l->next = l1;
			l1 = l1->next;
		} else {
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
    if (y == NULL) {
      y = l;
    }

		l->next = NULL;
	}
	if (l1 != NULL) {
		l->next = l1;
	} else {
		l->next = l2;
	}
	return list_next;
}

Node * g_slist_append(Node * list, int data)
{
  Node * new_list = (Node *) malloc(sizeof(Node));
  new_list->key = data;
  new_list->next = NULL;
  if (list != NULL) {
    Node * last = g_slist_last(list);
    last->next = new_list;
    return list;
  } else {
    return new_list;
  }
}

#endif
