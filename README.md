# S2 experiments

All results and run scripts are in the `s2_benchmarks` dir.  

## Tool 
The binary s2 version used in evaluation:
```
HIP: A Verifier for Heap Manipulating Programs
Version 1.0
THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT ANY WARRANTIES.
IT IS FREE FOR NON-COMMERCIAL USE
Copyright @ PLS2 @ NUS
```
Its hash is: ```0d70a6584a7585ce277b4a76e35a244e590f149c```  


# Steps used to get the result:
  (1) The benchmarks are taken from VCDryad benchmarks(http://madhu.cs.illinois.edu/vcdryad/examples/)
  
  (2) The benchmarks are in `s2_benchmarks/` and each programs are annotated with
  ```
      "/*@
        infer[@shape]
        requires true
        ensures true;
       */"
  ```
  For example, the glib_glist/g_list_prepend.dryad.c is annotated as:
  ```
  #include "stdhipmem.h"
  DLNode * g_list_prepend(DLNode * list, int data, DLNode * p) 
  /*@
  infer[@shape]
  requires true
  ensures true;
  */
  {

    DLNode * ret = (DLNode *) malloc(sizeof(DLNode));
    ret->key = data;
    ret->next = list;
    ret->prev = p;
    if (list != NULL) {
      list->prev = ret;
    }
    if (p != NULL) {
      p->next = ret;
    }
    return ret;
  }
```
  
  (3) The command to run the experiments is `2 *.c` (no specicial flags, just run `s2` as is). The generated results are in `s2_benchmarks/*/output` directory where `*` is the name of each benchmark category.
  
  s2 successfully infers the specification for the above example and the output is:
```
!!!Full processing file "glib_glist//g_list_prepend.dryad.c"
Parsing file "glib_glist//g_list_prepend.dryad.c" by cil parser...
GCC Preprocessing...
gcc -C -E glib_glist//g_list_prepend.dryad.c -o glib_glist//g_list_prepend.dryad.c.prep

!!! generate unknown predicate for Pre synthesis of g_list_prepend: :HP_26
!!! generate unknown predicate for Post synthesis of g_list_prepend: :GP_27
!!! ss:EInfer @shape[HP_26,GP_27] EBase: [][](HRel HP_26(list,p))*(true)( FLOW __norm) {EAssume: 10,:(HRel GP_27(list,p,res))*(true)( FLOW __norm)}
!!! processing primitives "["prelude.ss"]
Starting z3... 
Starting Omega.../usr/local/bin/oc

Checking procedure g_list_prepend$node~int~node... 


******************************
   ******* SPECIFICATION1 ********
******************************
 infer[@shape HP_26,GP_27]requires HP_26(list,p)&
truerequires emp
 ensures GP_27(list,p,res)&true{,(4,5)=__norm#E};

*************************************
*******shape relational assumptions ********
*************************************
[ // BIND
(1;0)HP_26(list,p)&
list!=null --> list::node<key_17_1467,next_17_1468,prev_17_1469> * 
HP_1470(next_17_1468,p@NI) * HP_1471(prev_17_1469,p@NI) * HP_1472(p,list@NI)&
true,
 // BIND
(1;1;0)HP_1472(p',list@NI)&
p'!=null --> p'::node<key_20_1482,next_20_1483,prev_20_1484> * 
HP_1485(next_20_1483,list@NI) * HP_1486(prev_20_1484,list@NI)&
true,
 // BIND
(1;2;0)HP_26(list,p)&p!=null & 
list=null --> p::node<key_20_1487,next_20_1488,prev_20_1489> * 
HP_1490(next_20_1488) * HP_1491(prev_20_1489)&
true,
 // POST
(1;1;0)res::node<data',list,p> * HP_1470(next_17_1468,p@NI) * 
list::node<key_17_1467,next_17_1468,res> * HP_1486(prev_20_1484,list@NI) * 
p::node<key_20_1482,res,prev_20_1484>&true --> GP_27(list,p,res)&
true,
 // POST
(2;1;0)res::node<data',list,p> * HP_1470(next_17_1468,p@NI) * 
list::node<key_17_1467,next_17_1468,res>&p=null --> GP_27(list,p,res)&
true,
 // POST
(2;1;0)HP_1472(p',list'@NI)&p'=null --> emp&
true,
 // POST
(2;1;0)HP_1471(prev_17_1469,p'@NI)&p'=null --> emp&
true,
 // POST
(1;2;0)res::node<data',list,p> * HP_1491(prev_20_1489) * 
p::node<key_20_1487,res,prev_20_1489>&list=null --> GP_27(list,p,res)&
true,
 // POST
(2;2;0)HP_26(list,p) * res::node<data',list,p'>&list=null & p=null & 
p'=null & p'=list & p=list --> GP_27(list,p,res)&
true]

Procedure g_list_prepend$node~int~node SUCCESS.

*********************************************************
*******relational definition ********
*********************************************************
[ HP_26(list_1560,p_1561) ::= 
 list_1560::node<key_17_1467,DP_DP_HP_1470,prev_17_1469>&p_1561=null
 or list_1560::node<key_17_1467,DP_DP_HP_1470,prev_17_1469>&p_1561=null & 
    ((p_1561!=list_1560 | p_1561!=null))
 or p_1561::node<key_20_1487,DP_DP_HP_1490,DP_DP_HP_1491>&list_1560=null
 or p_1561::node<key_20_1487,DP_DP_HP_1490,DP_DP_HP_1491>&list_1560=null & 
    p_1561!=list_1560
 or emp&p_1561=null & list_1560=null
 (4,5),
 GP_27(list_1564,p_1565,res_1566) ::= 
 res_1566::node<data',list_1564,p_1565> * 
 list_1564::node<key_17_1467,DP_DP_HP_1470,res_1566>&p_1565=null
 or res_1566::node<data',list_1564,p_1565> * 
    p_1565::node<key_20_1482,res_1566,DP_DP_HP_1491>&list_1564=null
 or res_1566::node<data',list_1564,list_1564>&list_1564=null & p_1565=null
 or res_1566::node<data',list_1564,p_1565> * 
    list_1564::node<key_17_1467,DP_DP_HP_1470,res_1566> * 
    p_1565::node<key_20_1482,res_1566,DP_DP_HP_1486>
 (4,5)]
*************************************

!!! INFERRED SHAPE SPEC: EBase p::HP_26{}<list>&{FLOW,(4,5)=__norm#E}[]
         EBase emp&MayLoop[]&{FLOW,(4,5)=__norm#E}[]
                 EAssume 
                   (exists p: list::GP_27{}<p,res>&{FLOW,(4,5)=__norm#E})[]
                   Stop z3... 163 invocations Stop Omega... 60 invocations 
0 false contexts at: ()

!!! log(small):(0.083209,653)
Total verification time: 0.2 second(s)
	Time spent in main process: 0.128 second(s)
	Time spent in child processes: 0.072 second(s)
	Z3 Prover Time: 0.004 second(s)
```  

  (4) To check whether s2 successfully infer the correct invariants, we checked the output file of each program and see if it generates the same invariants as SLING does.

**TODO:  Give an example when it works, and it doesn't work.  Just copy and paste the results from the output dir here**


### Some examples showing the public online versions of S2 failed to work

The directory `/web_s2_result/` contains several examples causing problems to the online tools:  http://loris-5.d2.comp.nus.edu.sg/s2/ and http://loris-5.d2.comp.nus.edu.sg/s2/beta/.  
