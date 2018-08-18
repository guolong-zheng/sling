#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Node * g_slist_insert_before(Node * slist, Node * sibling, int data)
{
  //pre
  if (slist == NULL) {
    slist = (Node *) malloc (sizeof (Node));
    slist->key = data;

    slist->next = NULL;
    //post
    return slist;
  }

  Node * node = NULL;
  Node * last = NULL;
  node = slist;

  while(node != NULL && node != sibling)
  {
    //loop
    last = node;
    node = last->next;
  }

  if (last == NULL) {
    node = (Node *) malloc (sizeof(Node));
    node->key = data;
    node->next = slist;
    //post
    return node;
  } else {
    node = (Node *) malloc (sizeof(Node));
    Node * tmp_last = last->next;
    node->key = data;
    node->next = tmp_last;
    last->next = node;
    //post
    return slist;
  }
}

int main(int argc, char * argv[]){
    int size;
    sscanf(argv[1],"%d",&size);
    Node * root = create_list(size);
    Node * list = root->next;
    Node * rest = g_slist_insert_before(root, list, rand_num());
    g_slist_insert_before(NULL, list, rand_num());
    return 0;
}
