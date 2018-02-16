#include "sort_list.h"

int main(){
    SNnode * root = create_list(5);
    SNnode * last_sorted = find_last_sorted(root);

    return 0;
}
