
/*
 * HIP/SLEEK standard library for C program
 * 
 * Created: Oct. 31, 2013.
 */
typedef
/*D_tag a_node */
struct a_node {
  struct a_node * left;
  struct a_node * right;
  int key;
  int height;
} AVLNode;

void* malloc(int size) __attribute__ ((noreturn))
/*@
  case {
    size <= 0 -> requires true ensures res = null;
    size >  0 -> requires true ensures res::memLoc<h,s> & (res != null) & h;
  }
*/;


void free(AVLNode * p) __attribute__ ((noreturn))
/*@
 requires p::memLoc<h,s> ensures p = null;
*/;


int avl_find_smallest_h(AVLNode * x)
/*@
 requires true
 ensures true;
 */
{
	if (x->left == NULL) {
		return x->key;
	} else {
		int r = avl_find_smallest_h(x->left);
		return r;
	}
}


int get_height(AVLNode * x)
/*@
  requires true
  ensures true;
*/
{
    if(x==NULL)
        return -1;
    else
        return x->height;
}

AVLNode * avl_balance(AVLNode * x)
/*@
  requires true
  ensures true;
*/
{

	int lht = get_height(x->left);
	int rht = get_height(x->right);
	AVLNode * right = x->right;
	AVLNode * left  = x->left;
	if (rht == lht + 2) {
		int rlht = get_height(right->left);
		int rrht = get_height(right->right);
		AVLNode * right_left = right->left;
		AVLNode * right_right = right->right;
		if (rlht <= rrht) {
            int inc_rlht = rlht + 1;
			x->height = inc_rlht;
			x->right = right_left;
            int inc_inc_rlht = rlht + 2;
			right->height = inc_inc_rlht;
			right->left = x;

			return right;
		} else {
			AVLNode * right_left_left = right_left->left;
			AVLNode * right_left_right = right_left->right;
            int inc_lht = lht + 1;
			x->height = inc_lht;
			x->right = right_left_left;
            int inc_rrht = rrht + 1;
			right->height = inc_rrht;
			right->left = right_left_right;
            int inc_inc_lht = lht + 2;
			right_left->height = inc_inc_lht;
			right_left->left = x;
			right_left->right = right;

			return right_left;
		}
	} else if (lht == rht + 2) {
		int llht = get_height(left->left);
		int lrht = get_height(left->right);
		AVLNode * left_left = left->left;
		AVLNode * left_right = left->right;
		if (lrht <= llht) {
            int inc_lrht = lrht + 1;
			x->height = inc_lrht;
			x->left = left_right;
            int inc_inc_lrht = lrht + 2;
			left->height = inc_inc_lrht;
			left->right = x;

			return left;
		} else {
			AVLNode * left_right_left = left_right->left;
			AVLNode * left_right_right = left_right->right;
            int inc_rht = rht + 1;
			x->height = inc_rht;
			x->left   = left_right_right;
            int inc_llht = llht + 1;
			left->height = inc_llht;
			left->right = left_right_left;
            int inc_inc_rht = rht + 2;
			left_right->height = inc_inc_rht;
			left_right->left = left;
			left_right->right = x;

			return left_right;
		}
	} else if (rht == lht + 1) {
        int inc_rht = rht + 1;
		x->height = inc_rht;

		return x;
	} else {
        int inc_lht = lht + 1;
		x->height = inc_lht;

		return x;
	}
}

int random()
/*@
  requires true
  ensures true;
*/;
