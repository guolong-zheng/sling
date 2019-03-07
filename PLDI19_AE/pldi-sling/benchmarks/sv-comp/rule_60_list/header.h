typedef struct list_head {
  struct list_head * next;
  struct list_head * prev;
} Node;

Node * create_list(int size);
