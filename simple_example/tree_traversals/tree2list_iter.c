#include <stdlib.h>

typedef struct node
{
  struct node * next;
  struct node * left;
  struct node * right;
  struct node * tree;
  int key;
} Node;

Node * tree2list_iter(Node * t)
{
    //pre
	if (t == NULL) {
        //post
		return NULL;
	} else {
		Node * l = NULL;
		Node * s = (Node *) malloc(sizeof(Node));
		s->tree = t;
		s->next = NULL;
		s->left = NULL;
		s->right = NULL;
		while(s != NULL)
		{
            //loop
			Node * tn = s->tree;
			Node * s1 = s->next;
			free(s);
			s = s1;
			if (tn->left != NULL) {
				Node * sn = (Node *) malloc(sizeof(Node));
	            sn->tree = tn;
      	        sn->next = s;
      	        sn->left = NULL;
      	        sn->right = NULL;
				s = sn;
			}
			if (tn->right == NULL) {
				Node * ln = (Node *) malloc(sizeof(Node));
      	        ln->key = k;
      	        ln->next = x;
      	        ln->left  = NULL;
      	        ln->right = NULL;
      	        ln->tree  = NULL;
				l = ln;
				free(tn);
			} else {
				Node * tn_right = tn->right;
				tn->left  = NULL;
				tn->right = NULL;
				Node * sn = (Node *) malloc(sizeof(Node));
      	        sn->tree = tn;
      	        sn->next = s;
      	        sn->left = NULL;
      	        sn->right = NULL;
				s = sn;
				sn = (Node *) malloc(sizeof(Node));
      	        sn->tree = tn;
      	        sn->next = s;
      	        sn->left = NULL;
      	        sn->right = NULL;
				s = sn;
			}
		}
        //post
		return l;
	}
}

Node * create_tree(int size){
    int i = 0;
    Node * root = NULL;
    for(i = 0; i < size; i++){
        Node * node = (Node *)malloc(sizeof(Node));
        node->left = NULL;
        node->right = NULL;
        node->next = NULL;
        node->tree = NULL;
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
    Node * tre = create_tree(size);
    Node * lst = NULL;
    lst = tree2list_iter(tre);
    return 0;
}
