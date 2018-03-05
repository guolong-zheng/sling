#include <stdlib.h>

typedef struct b_node {
  struct b_node * left;
  struct b_node * right;
  int key;
} BNode;

typedef struct l_node {
  struct l_node * next;
  int key;
} LNode;

LNode * tree2list_rec(BNode * t, LNode * l)
{
    //pre
	if (t == NULL) {
        //post
		return l;
	} else {
		LNode * lnode = (LNode *) malloc(sizeof(LNode));
		int tkey = t->key;
		lnode->key = tkey;
		lnode->next = NULL;
        BNode * tright = t->right;
		BNode * tleft = t->left;
		LNode * tmp_list1 = tree2list_rec(tright, l);
		lnode->next = tmp_list1;
		free(t);
		LNode * tmp_list2 = tree2list_rec(tleft, lnode);
        //post
		return tmp_list2;
	}
}

BNode * create_tree(int size){
    int i = 0;
    BNode * root = NULL;
    for(i = 0; i < size; i++){
        BNode * node = (BNode *)malloc(sizeof(BNode));
        node->left = NULL;
        node->right = NULL;
        node->key = rand();
        if(root === NULL){
            root = node;
        }else{
            BNode * p = root;
            while(p != NULL){
                if(p->key > node->key){
                    if(p->left == NULL){
                        p->left = node;
                        break;
                    }else
                        p = p->left;
                }
                else{
                    if(p->right == NULL){
                        p->right = node;
                        break;
                    } else
                        p = p->right;
                }
            }
        }
    }
}

int main(int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1],"%d", &size);
    BNode * tre = create_tree(root);
    LNode * lst = NULL;
    lst = tree2list_rec(tre,lst);
    return 0;
}
