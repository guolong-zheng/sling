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

The output of glib_glist/g_list_reverse.dryad.c show that s2 fails to infer the correct invariants:
```

!!!Full processing file "glib_glist//g_list_reverse.dryad.c"
Parsing file "glib_glist//g_list_reverse.dryad.c" by cil parser...
GCC Preprocessing...
gcc -C -E glib_glist//g_list_reverse.dryad.c -o glib_glist//g_list_reverse.dryad.c.prep

!!! generate unknown predicate for Pre synthesis of g_list_reverse: :HP_26
!!! generate unknown predicate for Post synthesis of g_list_reverse: :GP_27
!!! ss:EInfer @shape[HP_26,GP_27] EBase: [][](HRel HP_26(list))*(true)( FLOW __norm) {EAssume: 11,:(HRel GP_27(list,res))*(true)( FLOW __norm)}
!!! processing primitives "["prelude.ss"]
Starting z3... 

!!! generate unknown predicate for Pre synthesis of while_14_2$node~node~node: :HP_1349
!!! generate unknown predicate for Post synthesis of while_14_2$node~node~node: :GP_1353Starting Omega.../usr/local/bin/oc

Checking procedure while_14_2$node~node~node... 


******************************
   ******* SPECIFICATION1 ********
******************************
 infer[@shape HP_1445,HP_1446,GP_1353]requires HP_1445(last_69,curr_68) * 
HP_1446(last_67)&
truerequires emp
 ensures GP_1353(last_69,last_69',last_67,last_67',curr_68,curr_68')&
true{,(4,5)=__norm#E};

*************************************
*******shape relational assumptions ********
*************************************
[ // BIND
(1;1;0)HP_1349(last_69,last_67,curr_68)&
curr_68!=null --> curr_68::node<key_22_1455,next_22_1456,prev_22_1457> * 
HP_1458(next_22_1456,last_69@NI,last_67@NI) * 
HP_1459(prev_22_1457,last_69@NI,last_67@NI) * 
HP_1460(last_69,last_67,curr_68@NI)&
true,
 // PRE_REC
(1;1;0)HP_1458(curr_68',last_69@NI,last_67@NI) * 
HP_1459(last_69',last_69@NI,last_67@NI) * 
curr_68::node<key_22_1455,last_69',curr_68'>&
true --> HP_1349(last_69',curr_68,curr_68')&
true,
 // POST
(1;1;0)HP_1460(last_69,last_67,curr_68@NI) * 
GP_1353(prev_22_1457,last_69',curr_68,last_67',next_24_1469,curr_68')&
curr_68!=null --> GP_1353(last_69,last_69',last_67,last_67',curr_68,curr_68')&
true,
 // POST
(2;1;0)HP_1349(last_69,last_67,curr_68)&curr_68=null & curr_68'=null & 
curr_68'=curr_68 & last_67'=last_67 & 
last_69'=last_69 --> GP_1353(last_69,last_69',last_67,last_67',curr_68,curr_68')&
true]

Procedure while_14_2$node~node~node SUCCESS.

Context of Verification Failure: 1 File "",Line:0,Col:0

Last Proving Location: 1 File "",Line:0,Col:0

ERROR: at glib_glist//g_list_reverse.dryad.c_14:2_26:3
Message: split_components: don't expect OR

 --error:  at:

*********************************************************
*******relational definition ********
*********************************************************
[]
*************************************

!!! INFERRED SHAPE SPEC: EInfer @shape[HP_1445,HP_1446,GP_1353]
   EBase HP_1445(last_69,curr_68) * HP_1446(last_67)&{FLOW,(4,5)=__norm#E}[]
           EBase emp&MayLoop[]&{FLOW,(4,5)=__norm#E}[]
                   EAssume ref [last_69;last_67;curr_68]
                     GP_1353(last_69,last_69',last_67,last_67',curr_68,curr_68')&
                     {FLOW,(4,5)=__norm#E}[]
                     
Checking procedure g_list_reverse$node... 


******************************
   ******* SPECIFICATION1 ********
******************************
 infer[@shape HP_26,GP_27]requires HP_26(list)&
truerequires emp
 ensures GP_27(list,res)&true{,(4,5)=__norm#E};

!!! WARNING logtime exception:0.
Procedure g_list_reverse$node FAIL.(2)

Exception Not_found Occurred!

Error(s) detected when checking procedure g_list_reverse$node
Stop z3... 77 invocations Stop Omega... 25 invocations 
1 false contexts at: ( (14,2) )

!!! log(small):(0.036483,308)
Total verification time: 0.144 second(s)
	Time spent in main process: 0.1 second(s)
	Time spent in child processes: 0.044 second(s)
	Z3 Prover Time: 0.004 second(s)
```

### Online tools 

The directory `/s2_web_result/` contains examples causing problems to the online tools `s2`: http://loris-5.d2.comp.nus.edu.sg/s2/ and `s2/beta` http://loris-5.d2.comp.nus.edu.sg/s2/beta/. For example, when using the program 
```
TODO: list some simple example here
```
the `s2` tools provides the output 
```
TODO: list the output here
```
and the `s2/beta` provides the output
```
TODO: list the output here
```.

However, the binary version was able to run the tool and produce the results
```
TODO
```


