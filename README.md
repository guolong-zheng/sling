# Sling #

SLING is a tool for dynamically inferring separation logic sepcifications. The input is traces so SLING can work with different programming languages. We have tested on C, C++, Java and Python. 

# Setup

The default setting of SLING works with C or C++. It uses LLDB to obtain traces and Python to infer seperation logic invariants based on the traces. SLING has been tested using the following setup:
  
  - Ubuntu 16.04
  - Python 2.7
  - LLDB 3.8

Follow the following steps to setup SLING:
  1. Install Python and LLDB: ```sudo apt install python python-pip lldb lldb-3.8-dev gcc```
  2. Install required Python libs: ```pip install lark-parser z3-solver```
  3. Link LLDB libs in case of version conflict(when SLING couldn't obtain any traces):
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

 The predicate defination(templates) ```PATH/TO/sling/simple_example/sll/defn.sl```:
 ```
 pred ll(x) := emp & x=nil
            \/ (exists v, y. x->node{v, y} * ll(y));
 ```
 
 Run the following command under `PATH/TO/sling/src` directory to call SLING to infer its invariants for a size 5 input:
 
 ```./run.sh 5 PATH/TO/sling/simple_example/sll/defn.sl PATH/TO/sling/simple_example/sll/append.c```
  
 SLING then outputs the inferred precondition and postcondition for `append.c`:
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
 The dll concat motivating example in the paper is in the `PAHT/TO/sling/simple_example/dll/concat.c`:
 ```
 DLNode* dll_concat(DLNode* a, DLNode* b)
 {
   //pre
   if (a == NULL) {
     //post
     return b;
   } else {
     DLNode* tmp = dll_concat(a->next, b);
     a->next = tmp;
     if (tmp) tmp->prev = a;
     //post
     return a;
   }
 }
 ```
 With the following predicate defination `PATH/TO/sling/simple_example/dll/defn.sl`:
 
 ```
 pred dll(hd, p, tl, n) := hd=n & tl=p
                        \/ (exists d, x. hd->node{d, x, p} * dll(x, hd, tl, n));
 ```
 Run the following command in `PATH/TO/sling/src` directory:
 
 ```./run.sh 5 PATH/TO/sling/simple_example/dll/defn.sl PATH/TO/sling/simple_example/dll/concat.c```
 
 SLING infers the following results:
 ```
dynsl.py:299 - Precondition at location 7:
dynsl.py:307 -  dll(b, nil, fv2, nil) * dll(a, fv1, fv0, nil) 
dynsl.py:307 -  dll(b, nil, fv2, nil) * dll(a, nil, fv1, fv0) 
dynsl.py:307 -  dll(b, nil, fv0, nil) * dll(a, nil, nil, a) 
dynsl.py:309 - ==============================
dynsl.py:312 - Postcondition at location 9:
dynsl.py:320 -  dll(b, nil, fv0, nil)  & a = nil & b = res
dynsl.py:322 - ==============================
dynsl.py:312 - Postcondition at location 15:
dynsl.py:320 -  dll(a, fv2, a, tmp) * dll(b, fv1, tmp, fv0) * dll(tmp, b, b, tmp)  & a = res
dynsl.py:320 -  dll(a, fv4, a, tmp) * dll(b, fv3, tmp, fv2) * dll(tmp, fv1, fv0, b)  & a = res
dynsl.py:320 -  dll(a, fv3, a, tmp) * dll(b, tmp, fv2, fv1) * dll(tmp, a, fv0, b)  & a = res
dynsl.py:320 -  dll(a, fv2, a, tmp) * dll(b, fv1, fv0, nil) * dll(tmp, b, b, tmp)  & a = res
dynsl.py:320 -  dll(a, fv4, a, tmp) * dll(b, fv3, fv2, nil) * dll(tmp, fv1, fv0, b)  & a = res
dynsl.py:320 -  dll(a, nil, fv3, fv2) * dll(b, fv1, tmp, fv0) * dll(tmp, b, b, tmp)  & a = res
dynsl.py:320 -  dll(a, nil, fv5, fv4) * dll(b, fv3, tmp, fv2) * dll(tmp, fv1, fv0, b)  & a = res
dynsl.py:320 -  dll(a, nil, fv4, fv3) * dll(b, tmp, fv2, fv1) * dll(tmp, a, fv0, b)  & a = res
dynsl.py:320 -  dll(a, nil, fv3, fv2) * dll(b, fv1, fv0, nil) * dll(tmp, b, b, tmp)  & a = res
dynsl.py:320 -  dll(a, nil, fv5, fv4) * dll(b, fv3, fv2, nil) * dll(tmp, fv1, fv0, b)  & a = res
 ```
 
 For information and experiment about PLDI19 artifect evaluation, please refer to the [PLDI19_AE directory](PLDI19_AE/).
