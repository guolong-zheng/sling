#ifndef SORT_LIST_H_
#define SORT_LIST_H_

typedef struct node {
   int key;
   struct node * next;
} SNnode;

SNnode * create_list(int size);
SNnode * concat_sorted(SNnode * l1, SNnode * l2);
SNnode * merge_sort_copy(SNnode * l1, SNnode * l2);
SNnode * sorted_delete_all(SNnode * x, int k);
SNnode * sorted_insert(SNnode *x, int k);
SNnode * find_last_sorted(SNnode * l);
SNnode * quick_sort(SNnode * l);
int sorted_find(SNnode * l, int k);
SNnode * sorted_insert_iter(SNnode * l, int k);
SNnode * insertion_sort_copy(SNnode * l);
SNnode * reverse_sorted(SNnode * l);

#endif
