#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode{
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
} Node;

void print_tree(Node * root);
void insertTree(Node * root, int val);
Node * findTree(Node * root, int val);
Node * createNode(int val);

int main(){
  Node * root;
  root = createNode(5);
  insertTree(root,6);
  insertTree(root,3);
  insertTree(root,7);

  //Node * x = root;
  Node * y = findTree(root,6);
 
  print_tree(root);  

  return 0;
}

void print_tree(Node * root){
  if(root != NULL)
     printf("%d\n", root->data);
  if(root->left != NULL){
     printf("%d left is:", root->data);
     print_tree(root->left);
  }else
     printf("%d left is null\n", root->data);
  if(root->right != NULL){
     printf("%d right is:", root->data);
     print_tree(root->right);
  }else
     printf("%d right is null\n", root->data);

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
