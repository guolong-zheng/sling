#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    DLNode * root = dll_append(node1, node2);
    root = dll_append(root, node3);

    root = dll_mid_insert(node1, node2, 4);

    return 0;
}
