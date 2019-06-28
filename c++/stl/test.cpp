#include<iostream>
#include "list_test.h"
#include<iterator>

using namespace std;

int main(){
  list <int> list1;
  for(int i = 0; i < 10; i++){
      list1.push_back(i);
  }

  return 0;
}
