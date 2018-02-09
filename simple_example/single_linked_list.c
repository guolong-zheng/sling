#include<stdio.h>
#include<stdlib.h>

typedef struct node {
  int key;
  struct node * next;
} SLnode;

SLnode * sll_append(SLnode * x1, SLnode * x2);
SLnode * node_create(int key);

SLnode * sll_append(SLnode * x1, SLnode * x2)
{
	if (x1 == NULL) {
		return x2;
	} else {
		SLnode * tmp = sll_append(x1->next, x2);
		x1->next = tmp;
		return x1;
	}
}

SLnode * node_create(int key)
{
    SLnode * node = (SLnode *)malloc(sizeof(SLnode));
    node->key = key;
    node->next = NULL;
    return node;
}

int main(){
    SLnode * node1 = node_create(1);
    SLnode * node2 = node_create(2);
    SLnode * node3 = node_create(3);

    SLnode * root = sll_append(node1, sll_append(node2, node3));

    return 0;
}
