#include "sort_list.h"

int main(){
    SNnode * l1 = create_list(5);
    SNnode * l2 = create_list(5);
    SNnode * l = concat_sorted(l1, l2);

    return 0;
}
