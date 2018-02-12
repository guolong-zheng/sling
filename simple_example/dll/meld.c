#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    DLNode * root1 = create_dll(5);
    DLNode * root2 = create_dll(5);

    dll_meld(root1, root2);

    return 0;
}
