#include "sort_list.h"

int main(){
    SNnode * root = create_list(5);
    SNnode * res = insertion_sort_copy(root);

    return 0;
}
