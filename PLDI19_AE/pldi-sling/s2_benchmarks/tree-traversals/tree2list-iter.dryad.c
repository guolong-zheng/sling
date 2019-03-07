#include "stdhipmem.h"



Node * tree2list_iter(Node * t)
/*@
 infer[@shape]
 requires true
 ensures true;
 */
{

	if (t == NULL) {
		return NULL;
	} else {
		Node * l = NULL;

		Node * s = (Node *) malloc(sizeof(Node));
		
		s->tree = t;

		s->next = NULL;

		s->left = NULL;

		s->right = NULL;

		while(s != NULL)
        /*@
         infer[@shape]
         requires true
         ensures true;
         */
		{
			Node * tn = s->tree;
			Node * s1 = s->next;

			freeh(s);

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
      	ln->key = random();
      	ln->next = s;
      	ln->left  = NULL;
      	ln->right = NULL;
      	ln->tree  = NULL;

				l = ln;

				freeh(tn);

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

		return l;
	}
}

