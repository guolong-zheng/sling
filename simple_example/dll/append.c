#include "dll.h"
#include <stdio.h>

int main(){
    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    node1 = dll_append(node1, node2);
    node1 = dll_append(node1, node3);

    return 0;
}
