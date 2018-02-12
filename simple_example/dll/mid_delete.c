#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    DLNode * node1 = node_create(1);
    DLNode * node2 = node_create(2);
    DLNode * node3 = node_create(3);

    dll_append(node1, node2);
    dll_append(node1, node3);

    dll_mid_delete(node2);
    return 0;
}
