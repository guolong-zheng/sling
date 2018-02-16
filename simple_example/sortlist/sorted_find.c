#include "sort_list.h"

int main(){
    SNnode * root = create_list(5);
    int rest = sorted_find(root, (int)rand());

    return 0;
}
