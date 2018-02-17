#include "circular_list.h"

int main(){
    CNode * hd = create_list(5);
    CNode * res = circular_list_delete_front(hd);

    return 0;
}
