SLING is a tool for dynamically inferring separation logic sepcifications. The input is traces so SLING can work with different programming languages. We have tested on C, C++, Java and Python. 

# Setup

The default setting of SLING works with C or C++. It uses LLDB to obtain traces and Python to infer seperation logic invariants based on the traces. SLING has been tested using the following setup:
  
  - Ubuntu 16.04
  - Python 2.7
  - LLDB 3.8

Follow the following steps to setup SLING:
  1. Install Python and LLDB: ```sudo apt install python python-pip lldb lldb-3.8-dev gcc```
  2. Install required Python libs: ```pip install lark-parser z3-solver```
  3. Link LLDB libs in case of version conflict:
     ```
     cd /usr/lib/llvm-3.8/lib/python2.7/site-packages/lldb/
     sudo ln -sf ../../../liblldb.so.1 _lldb.so
     sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.0.so.1
     sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.so.1
     export PYTHONPATH='/usr/lib/llvm-3.6/lib/python2.7/site-packages'
     ```
     
 # Usage
 
 Given a program ```PATH/TO/sling/simple_example/sll/append.c```:
 ```
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

 ```

 and a predicate defination(templates) ```PATH/TO/sling/simple_example/sll/defn.sl```, run the following command to call SLING to infer its invariants for a size 5 input:
  ```./run.sh 5 PATH/TO/sling/simple_example/sll/defn.sl PATH/TO/sling/simple_example/sll/append.c```
  
 SLING then outputs:
 ```
 dynsl.py:299 - Precondition at location 8:
 dynsl.py:307 - ll(x2) * ll(x1) 
 dynsl.py:309 - ==============================
 dynsl.py:312 - Postcondition at location 10:
 dynsl.py:320 - ll(x2)  & x2 = res
 dynsl.py:322 - ==============================
 dynsl.py:312 - Postcondition at location 15:
 dynsl.py:320 - ll(x2) * x1:node->node{fv0, tmp} 
 dynsl.py:322 - ==============================
 ```
 
 # PLDI19 AE
 
 For information and experiment about PLDI19 artifect evaluation, please refer to the [PLDI19_AE directory](PLDI19_AE/). 
