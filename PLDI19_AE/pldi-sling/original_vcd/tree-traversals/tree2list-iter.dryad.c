// ---- Definitions for tree traversal examples  ----
#include <vcc.h>
#include <stdlib.h>

typedef
/*D_tag node */
struct node
{
  struct node * next;
  struct node * left;
  struct node * right;
  struct node * tree;
  int key;
} Node;

/*D_defs
define pred sorted-list^(x): 
  ( 
	((x l= nil) & emp) | 
          (((x |-> loc next: nxt; int value: ky; loc left: lft; loc right: rgt; loc tree: st) * 
			(sorted-list^(nxt) & (ky le-set keys-list^(nxt)))
		  )  & (((lft l= nil) & (rgt l= nil)) & (st l= nil)))
  ) ;
  
define set-fun keys-list^(x):
  (case (x l= nil): emptyset;
  case ((x |-> loc next: nxt; int value: ky; loc left: lft; loc right: rgt; loc tree: st) * true): 
   	((singleton ky) union keys-list^(nxt));
   default: emptyset
  ) ;


define pred sorted-stack^(x): 
  ( 
	((x l= nil) & emp) | 
          (((x |-> loc next: nxt; loc tree: st; loc left: lft; loc right: rgt) 
          * ((sorted-stack^(nxt) * (bst^(st) & (~ (st l= nil)))) 
          & (keys-stack^(nxt) le keys-bst^(st)))) & ((lft l= nil) & (rgt l= nil)))
  );

define set-fun keys-stack^(x):
  (case (x l= nil): emptyset;
  case ((x |-> loc next: nxt; loc tree: st; loc left: lft; loc right: rgt) * true): 
   	(keys-bst^(st) union keys-stack^(nxt));
   default: emptyset
  ) ;


define pred bst^(x): 
  ( ((x l= nil) & emp) |
	  (((x |-> loc left: lft; loc right: rgt; int key: ky; loc next: nxt; loc tree: st) 
    * ((bst^(lft) & (keys-bst^(lft) set-le ky)) 
    * (bst^(rgt) & (ky le-set keys-bst^(rgt))))) & ((nxt l= nil) & (st l= nil)))
  );

define set-fun keys-bst^(x):
  (case (x l= nil): emptyset;
  case ((x |-> loc left: lft; loc right: rgt; int key: ky; loc next: nxt; loc tree: st) * true): 
   	((singleton ky) union (keys-bst^(lft) union keys-bst^(rgt)));
   default: emptyset
  ) ;
*/
// --------------------------------------------------


_(dryad)
Node * tree2list_iter(Node * t)
	/*D_requires bst^(t) */
  /*D_ensures (sorted-list^(ret) & (keys-bst^(t) s= keys-list^(ret))) */
{

	if (t == NULL) {
		return NULL;
	} else {
		Node * l = NULL;

		Node * s = (Node *) malloc(sizeof(Node));
		_(assume s != NULL)
		
		s->tree = t;

		s->next = NULL;

		s->left = NULL;

		s->right = NULL;

		while(s != NULL)
      /*D_invariant (((sorted-stack^(s) * sorted-list^(l)) 
                     & (old(keys-bst^(t)) s= (keys-list^(l) union keys-stack^(s)))) 
                    & (keys-stack^(s) le keys-list^(l))) */
		{
			Node * tn = s->tree;
			Node * s1 = s->next;

			free(s);

			s = s1;
			
			if (tn->left != NULL) {

				Node * sn = (Node *) malloc(sizeof(Node));
      	_(assume sn != NULL)
	      sn->tree = tn;
      	sn->next = s;
      	sn->left = NULL;
      	sn->right = NULL;
				s = sn;
			}
			
			if (tn->right == NULL) {

				Node * ln = (Node *) malloc(sizeof(Node));
      	_(assume ln != NULL)
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
      	_(assume sn != NULL)
      	sn->tree = tn;
      	sn->next = s;
      	sn->left = NULL;
      	sn->right = NULL;
				
				s = sn;

				sn = (Node *) malloc(sizeof(Node));
      	_(assume sn != NULL)
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

