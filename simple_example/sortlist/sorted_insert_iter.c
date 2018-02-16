#include "sort_list.h"

int main(){
    SNnode * root = create_list(5);
    root = sorted_insert_iter(root, (int)rand());

    return 0;
}
