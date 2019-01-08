#include<iostream>
class node{
    public:
    int data;
    node * next;

    node(int key){
       data = key;
       next = NULL;
    }
};


node* append(node* n1, node* n2){
    //pre
    if(n1 == NULL)
       //post
       return n2;
    else{
       node* tmp = append(n1->next, n2);
       n1->next = tmp;
       //post
       return n1;
    }
}

node* createsll(int size){
    int i = 0;
    node* root = NULL;
    for(i = 0; i < size; i++){
       root = append(root, new node(i));
    }

    return root;
}

int main(){
    node* root = createsll(5);
    return 0;
}
