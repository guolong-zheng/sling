#include "sort_list.h"

int main(){
    SNnode * root = create_random(5);
    root = quick_sort(root);

    return 0;
}
