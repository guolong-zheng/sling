#include "header.h"
#include <stdio.h>
#include <stdlib.h>

SNnode * sll_append(SNnode * x1, SNnode * x2)
{
  //pre
  if (x1 == NULL) {
	  //post
    return x2;
  } else {
    SNnode * tmp = sll_append(x1->next, x2);
    x1->next = tmp;
  //post
    return x1;
  }
}

void test1(int size);
void test2(int size);
void test3(int size);
void test4(int size);

int main( int argc, char * argv[]){
    int size = 0;
    sscanf(argv[1], "%d", &size);

    test1(size);
    test2(size);
    test3(size);
    test4(size);

    return 0;
}

void test1(int szie){
    sll_append(NULL,NULL);
}

void test2(int size){
    SNnode * l1 = create_sll(size);
    sll_append(NULL, l1);
}

void test3(int size){
    SNnode * l1 = create_sll(size);
    sll_append(l1, NULL);
}

void test4(int size){
    SNnode * l1 = create_sll(size);
    SNnode * l2 = create_sll(size);
    sll_append(l1, l2);
}
