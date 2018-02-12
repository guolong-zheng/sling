#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    DLNode * root = create_dll(5);
    root = dll_delete(root, (int)rand());
    return 0;
}
