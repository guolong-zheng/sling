SLING is a tool for dynamically inferring separation logic sepcifications. The input is traces so SLING can work with different programming languages. We have tested on C, C++, Java and Python. 

#Setup

The default setting of SLING works with C or C++. It uses LLDB to obtain traces and Python to infer seperation logic invariants based on the traces. SLING has been tested using the following setup:
  
  - Ubuntu 16.04
  - Python 2.7
  - LLDB 3.8

Follow the following steps to setup SLING:
  1. Install Python and LLDB: 'sudo apt install python python-pip lldb lldb-3.8-dev gcc'
  2. Install required Python libs: 'pip install lark-parser z3-solver'
  3. Link LLDB libs in case of version conflict:
     ```
     cd /usr/lib/llvm-3.8/lib/python2.7/site-packages/lldb/
     sudo ln -sf ../../../liblldb.so.1 _lldb.so
     sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.0.so.1
     sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.so.1
     export PYTHONPATH='/usr/lib/llvm-3.6/lib/python2.7/site-packages'
     ```
 
 
 
 
 #PLDI19 AE
 For information about artifect evaluation, 
