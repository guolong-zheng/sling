#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int key;
  struct node * next;
  struct node * prev;
} DLNode;

DLNode * dll_append(DLNode * x1, DLNode * x2);

DLNode * node_create(int key);

DLNode * dll_append(DLNode * x1, DLNode * x2)
{
  if (x1 == NULL) {
    return x2;
  } else {
    DLNode * tmp = dll_append(x1->next, x2);
    x1->next = tmp;
    if (tmp) tmp->prev = x1;
    return x1;
  }
}

DLNode * node_create(int key){
    DLNode * node = (DLNode *)malloc(sizeof(DLNode));
    node->key = key;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

int main(){
    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    dll_append(node1, node2);
    dll_append(node1, node3);

    while(node1 != NULL)
    {
        printf("%d\n" , node1->key);
        node1 = node1->next;
    }
    return 0;
}
