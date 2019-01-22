#include<iostream>
#include <list>
#include<iterator>

using namespace std;
list<int> create();

int main(){
  create();
  return 0;
}

list<int> create(){
  //pre
  list<int> list1;
  for(int i = 0; i < 10; i++){
     list1.push_back(i);
  }
  
  list <int> :: iterator it;
  for(it = list1.begin(); it!=list1.end(); ++it)
       cout<< '\t' << &it;
  //post
  return list1;
}
