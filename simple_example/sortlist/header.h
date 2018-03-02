#ifndef SORT_LIST_H_
#define SORT_LIST_H_

#define MAX_RAND 2000

typedef struct node {
   int key;
   struct node * next;
} SNnode;

int rand_num();
int range_num(int min, int max);
SNnode * create_sorted_list(int min, int max, int size); //sorted list range min to max
SNnode * create_list(int size); //create sorted list within range -MAX_RAND to MAX_RAND
SNnode * create_random(int size); //not sorted list


#endif
