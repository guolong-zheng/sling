struct node {
     int data;
     struct node* left;
     struct node* right;
}

/*
  Standard operations on binary trees
  collected from http://cslibrary.stanford.edu/110/BinaryTrees.html
 */


     
/* 
 Given a binary tree, return true if a node 
 with the target data is found in the tree. Recurs 
 down the tree, chooses the left or right 
 branch by comparing the target to each node. 
*/ 
static int lookup(struct node* node, int target) { 
  // 1. Base case == empty tree 
  // in that case, the target is not found so return false 
  if (node == NULL) { 
    return(false); 
  } 
  else { 
    // 2. see if found here 
    if (target == node->data) return(true); 
    else { 
      // 3. otherwise recur down the correct subtree 
      if (target < node->data) return(lookup(node->left, target)); 
      else return(lookup(node->right, target)); 
    } 
  } 
} 
 
/* 
 Helper function that allocates a new node 
 with the given data and NULL left and right 
 pointers. 
*/ 
struct node* NewNode(int data) { 
  struct node* node = new(struct node);    // "new" is like "malloc" 
  node->data = data; 
  node->left = NULL; 
  node->right = NULL;

  return(node); 
} 
 
/* 
 Give a binary search tree and a number, inserts a new node 
 with the given number in the correct place in the tree. 
 Returns the new root pointer which the caller should 
 then use (the standard trick to avoid using reference 
 parameters). 
*/ 
struct node* insert(struct node* node, int data) { 
  // 1. If the tree is empty, return a new, single node 
  if (node == NULL) { 
    return(newNode(data)); 
  } 
  else { 
    // 2. Otherwise, recur down the tree 
    if (data <= node->data) node->left = insert(node->left, data); 
    else node->right = insert(node->right, data);

    return(node); // return the (unchanged) node pointer 
  } 
} 
 



/* 
 Compute the number of nodes in a tree. 
*/ 
int size(struct node* node) { 
  if (node==NULL) { 
    return(0); 
  } else { 
    return(size(node->left) + 1 + size(node->right)); 
  } 
} 
 



/* 
 Compute the "maxDepth" of a tree -- the number of nodes along 
 the longest path from the root node down to the farthest leaf node. 
*/ 
int maxDepth(struct node* node) { 
  if (node==NULL) { 
    return(0); 
  } 
  else { 
    // compute the depth of each subtree 
    int lDepth = maxDepth(node->left); 
    int rDepth = maxDepth(node->right);
    // use the larger one 
    if (lDepth > rDepth) return(lDepth+1); 
    else return(rDepth+1); 
  } 
} 
 
/* 
 Given a non-empty binary search tree, 
 return the minimum data value found in that tree. 
 Note that the entire tree does not need to be searched. 
*/ 
int minValue(struct node* node) { 
  struct node* current = node;
  // loop down to find the leftmost leaf 
  while (current->left != NULL) { 
    current = current->left; 
  }

  return(current->data); 
} 
 

/* 
 Given a binary search tree, print out 
 its data elements in increasing 
 sorted order. 
*/ 
void printTree(struct node* node) { 
  if (node == NULL) return;
  printTree(node->left); 
  printf("%d ", node->data); 
  printTree(node->right); 
} 



/* 
 Given a binary tree, print its 
 nodes according to the "bottom-up" 
 postorder traversal. 
*/ 
void printPostorder(struct node* node) { 
  if (node == NULL) return;
  // first recur on both subtrees 
  printTree(node->left); 
  printTree(node->right);

  // then deal with the node 
  printf("%d ", node->data); 
} 



/* 
 Given a tree and a sum, return true if there is a path from the root 
 down to a leaf, such that adding up all the values along the path 
 equals the given sum.
 Strategy: subtract the node value from the sum when recurring down, 
 and check to see if the sum is 0 when you run out of tree. 
*/ 
int hasPathSum(struct node* node, int sum) { 
  // return true if we run out of tree and sum==0 
  if (node == NULL) { 
    return(sum == 0); 
  } 
  else { 
  // otherwise check both subtrees 
    int subSum = sum - node->data; 
    return(hasPathSum(node->left, subSum) || 
           hasPathSum(node->right, subSum)); 
  } 
} 
 


/* 
 Given a binary tree, print out all of its root-to-leaf 
 paths, one per line. Uses a recursive helper to do the work. 
*/ 
void printPaths(struct node* node) { 
  int path[1000];
  printPathsRecur(node, path, 0); 
}

/* 
 Recursive helper function -- given a node, and an array containing 
 the path from the root node up to but not including this node, 
 print out all the root-leaf paths. 
*/ 
void printPathsRecur(struct node* node, int path[], int pathLen) { 
  if (node==NULL) return;

  // append this node to the path array 
  path[pathLen] = node->data; 
  pathLen++;

  // it's a leaf, so print the path that led to here 
  if (node->left==NULL && node->right==NULL) { 
    printArray(path, pathLen); 
  } 
  else { 
  // otherwise try both subtrees 
    printPathsRecur(node->left, path, pathLen); 
    printPathsRecur(node->right, path, pathLen); 
  } 
}

// Utility that prints out an array on a line. 
void printArray(int ints[], int len) { 
  int i; 
  for (i=0; i<len; i++) { 
    printf("%d ", ints[i]); 
  } 
  printf("\n"); 
} 
 

/* 
 Change a tree so that the roles of the 
 left and right pointers are swapped at every node.
 So the tree... 
       4 
      / \ 
     2   5 
    / \ 
   1   3

 is changed to... 
       4 
      / \ 
     5   2 
        / \ 
       3   1 
*/ 
void mirror(struct node* node) { 
  if (node==NULL) { 
    return; 
  } 
  else { 
    struct node* temp;

    // do the subtrees 
    mirror(node->left); 
    mirror(node->right);

    // swap the pointers in this node 
    temp = node->left; 
    node->left = node->right; 
    node->right = temp; 
  } 
} 
 

/* 
 For each node in a binary search tree, 
 create a new duplicate node, and insert 
 the duplicate as the left child of the original node. 
 The resulting tree should still be a binary search tree.
 So the tree... 
    2 
   / \ 
  1   3

 Is changed to... 
       2 
      / \ 
     2   3 
    /   / 
   1   3 
  / 
 1

*/ 
void doubleTree(struct node* node) { 
  struct node* oldLeft;

  if (node==NULL) return;

  // do the subtrees 
  doubleTree(node->left); 
  doubleTree(node->right);

  // duplicate this node to its left 
  oldLeft = node->left; 
  node->left = newNode(node->data); 
  node->left->left = oldLeft; 
} 
 

/* 
 Given two trees, return true if they are 
 structurally identical. 
*/ 
int sameTree(struct node* a, struct node* b) { 
  // 1. both empty -> true 
  if (a==NULL && b==NULL) return(true);
  // 2. both non-empty -> compare them 
  else if (a!=NULL && b!=NULL) { 
    return( 
      a->data == b->data && 
      sameTree(a->left, b->left) && 
      sameTree(a->right, b->right) 
    ); 
  } 
  // 3. one empty, one not -> false 
  else return(false); 
} 
  
 


/* 
 For the key values 1...numKeys, how many structurally unique 
 binary search trees are possible that store those keys.
 Strategy: consider that each value could be the root. 
 Recursively find the size of the left and right subtrees. 
*/ 
int countTrees(int numKeys) {

  if (numKeys <=1) { 
    return(1); 
  } 
  else { 
    // there will be one value at the root, with whatever remains 
    // on the left and right each forming their own subtrees. 
    // Iterate through all the values that could be the root... 
    int sum = 0; 
    int left, right, root;

    for (root=1; root<=numKeys; root++) { 
      left = countTrees(root - 1); 
      right = countTrees(numKeys - root);

      // number of possible trees with this root == left*right 
      sum += left*right; 
    }

    return(sum); 
  } 
} 
  
 


/* 
 Returns true if a binary tree is a binary search tree. 
*/ 
int isBST(struct node* node) { 
  if (node==NULL) return(true);
  // false if the max of the left is > than us

  // (bug -- an earlier version had min/max backwards here) 
  if (node->left!=NULL && maxValue(node->left) > node->data) 
    return(false);

  // false if the min of the right is <= than us 
  if (node->right!=NULL && minValue(node->right) <= node->data) 
    return(false);

  // false if, recursively, the left or right is not a BST 
  if (!isBST(node->left) || !isBST(node->right)) 
    return(false);

  // passing all that, it's a BST 
  return(true); 
} 
  
 


/* 
 Returns true if the given tree is a binary search tree 
 (efficient version). 
*/ 
int isBST2(struct node* node) { 
  return(isBSTUtil(node, INT_MIN, INT_MAX)); 
}
/* 
 Returns true if the given tree is a BST and its 
 values are >= min and <= max. 
*/ 
int isBSTUtil(struct node* node, int min, int max) { 
  if (node==NULL) return(true);

  // false if this node violates the min/max constraint 
  if (node->data<min || node->data>max) return(false);

  // otherwise check the subtrees recursively, 
  // tightening the min or max constraint 
  return 
    isBSTUtil(node->left, min, node->data) && 
    isBSTUtil(node->right, node->data+1, max) 
  ); 
} 
 
