#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode{
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
} Node;

void insertTree(Node * root, int val);
Node * findTree(Node * root, int val);
Node * createNode(int val);

int main(){
  Node * root;
  root = createNode(5);
  insertTree(root,6);
  insertTree(root,3);
  insertTree(root,7);

  Node * x = root;
  Node * y = findTree(root,6);
 
  printf("%d %d\n", x->data, y->data);
  return 0;
}

Node * createNode(int val){
  Node * node = (Node *)malloc(sizeof(Node));
  node->data = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void insertTree(Node * root, int val){
  if(root == NULL){
    root = createNode(val);
    return;
  }else if( root->data == val )
    return;
  if(root->data > val){
    if(root->left == NULL){
      root->left = createNode(val);
    }
    else
      insertTree(root->left,val);
  }else{
      if(root->right == NULL)
      root->right = createNode(val);
    else
      insertTree(root->right,val);
  }
}

Node * findTree( Node *root,int target ){
  while(root != NULL){
    if(root->data == target){
      return root;
    }else{
      if(target < root->data)
	root = root->left;
      else
	root = root->right;
    }
  }
  return NULL;
}
