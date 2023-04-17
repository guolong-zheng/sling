typedef struct slave_item {
  struct slave_item * next;
  struct slave_item * prev;
}Node;

struct slave_item * create_dll(int n);
