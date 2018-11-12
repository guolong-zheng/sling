# DynSL #

```shell
sudo apt install python-minimal lldb gcc python-pip lldb-3.8-dev 

pip install lark-parser networkx six z3-solver

cd /usr/lib/llvm-3.8/lib/python2.7/site-packages/lldb/
sudo ln -sf ../../../liblldb.so.1 _lldb.so
sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.0.so.1
sudo ln -sf ../../../libLLVM-3.6.0.so.1 libLLVM-3.6.so.1
export PYTHONPATH='/usr/lib/llvm-3.6/lib/python2.7/site-packages'
```
