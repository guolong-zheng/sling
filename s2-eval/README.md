# S2 experiments

**Summary**: All results and run scripts to reproduce the **S2 experiment** are in the `s2_benchmarks` dir.  In particular, we used the [run-exp.sh](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/run-exp.sh) to generate our results.  It can be invoked as ```./run-exp.sh```.   

# Additional Details

## Tool 
The **binary s2** version used in evaluation:
```
HIP: A Verifier for Heap Manipulating Programs
Version 1.0
THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT ANY WARRANTIES.
IT IS FREE FOR NON-COMMERCIAL USE
Copyright @ PLS2 @ NUS
```
Its hash is: ```0d70a6584a7585ce277b4a76e35a244e590f149c```  

The tool is invoked using these flags:
- --tp z3:  uses the Z3 solver
- --lem-en-syn: enables the lemma synthesis
- --pred-en-seg: disable segmentation

# Steps used to get the results:
  (1) The benchmarks are taken from VCDryad benchmarks (http://madhu.cs.illinois.edu/vcdryad/examples/)
  
  (2) The benchmarks are in `s2_benchmarks/` and each method or loop in a program is annotated with
  ```
      /*@
        infer[@shape]
        requires true
        ensures true;
       */
  ```
  For example, the [glib_gslist/g_slist_concat.dryad.c](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_gslist/g_slist_concat.dryad.c) is annotated as:
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
  
  (3) The command to run the experiments is `./run.sh --flags /PATHTO/*.c`, where `flags` are those listed above. The generated results are in `s2_benchmarks/*/output` directory where `*` is the name of each benchmark category.
  
  `s2` successfully infers the following specification for the above example:
 ```
  HP_16(list1_1420,list2_1421) |#| emp&
  list2!=null ::= 
 emp&list2_1421!=null & list1_1420=null
 or emp&list2_1421=null
 or list1_1420::lseg<l_1413>&list2_1421!=null & list1_1420!=null & 
    list2_1421=DP_DP_DP_1405
 or emp&list1_1420!=null & list2_1421=null
 (4,5),
 GP_17(list1_1471,list2_1472,res_1473) ::= 
 emp&list2_1472=null & res_1473=list1_1471
 or list1_1471::lseg<last_1404>&res_1473=list1_1471 & list2_1472!=null
 or emp&list1_1471=null & res_1473=list2_1472 & list2_1472!=null
 (4,5)
 ```
 
  The full output is at [g_slist_concat.txt](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_gslist/output/g_slist_concat.txt).

  (4) We then analyze the inferred specifications (invariants) from these results. For examples, 

Some examples showing where we get expected specifications: [g_slist_concat.txt](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_gslist/output/g_slist_concat.txt); [g_slist_prepend.txt](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_gslist/output/g_slist_prepend.txt).

Some examples where the tool fails to run: [g_list_reverse.dryad.c](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_glist/output/g_list_reverse.txt) (output `Exception Not_found Occurred!`"); [g_slist_insert_at_pos.txt](https://github.com/guolong-zheng/s2-eval/blob/master/s2_benchmarks/glib_gslist/output/g_slist_insert_at_pos.txt)(output "Exception Failure("bind failure exception")").

### Online tools 

The directory `s2_web_result/` contains examples showing the online tools do not run properly.  We use the online tools:
- `s2`: http://loris-5.d2.comp.nus.edu.sg/s2/ and 
- `s2/beta`: http://loris-5.d2.comp.nus.edu.sg/s2/beta/. 


For example, when using the program `glist_last` on the `s2` website:
```
#include "stdhipmem.h"

/**
 * GList:
 * @data: holds the element's data, which can be a pointer to any kind
 *        of data, or any integer value using the <link
 *        linkend="glib-Type-Conversion-Macros">Type Conversion
 *        Macros</link>.
 * @next: contains the link to the next element in the list.
 * @prev: contains the link to the previous element in the list.
 *
 * The #GList struct is used for each element in a doubly-linked list.
 **/
struct GList {
  int key;
  struct GList* prev;
  struct GList* next;
};

/**
 * g_list_last:
 * @list: a #GList
 *
 * Gets the last element in a #GList.
 *
 * Returns: the last element in the #GList, 
 *     or %NULL if the #GList has no elements
 */
/*@
HeapPred H_last(GList a).
HeapPred G_last(GList a, GList b).
*/
struct GList*
g_list_last (struct GList* list)
{
  if (list != NULL) {
    while (list->next != NULL)
    /*@
      infer[H_last, G_last]
      requires H_last(list)
      ensures G_last(list, list');
    */
    {
      list = list->next;
    }
  }

  return list;
}
```

the `s2` tool fails to run
```
!!!Full processing file "../src/temp/glist-last.41832842.7783312.c" 
Parsing file "../src/temp/glist-last.41832842.7783312.c" by cil parser... 
GCC Preprocessing... 
gcc -C -E ../src/temp/glist-last.41832842.7783312.c -o ../src/temp/glist-last.41832842.7783312.c.prep 
../src/temp/glist-last.41832842.7783312.c:1:23: fatal error: stdhipmem.h: No such file or directory 
#include "stdhipmem.h" 
^ 
compilation terminated. 

ERROR: at _0:0_0:0 
Message: GCC Preprocessing failed! 
caught 

Exception occurred: Failure("GCC Preprocessing failed!") 
Error3(s) detected at main 
```

and the `s2/beta` also fails to run 
```
!!!Full processing file "../src/temp/isllhead.65370008.7991641.c" 
Parsing file "../src/temp/isllhead.65370008.7991641.c" by cil parser... 
GCC Preprocessing... 
gcc -C -E ../src/temp/isllhead.65370008.7991641.c -o ../src/temp/isllhead.65370008.7991641.c.prep 
../src/temp/isllhead.65370008.7991641.c:1:23: fatal error: stdhipmem.h: No such file or directory 
#include "stdhipmem.h" 
^ 
compilation terminated. 

ERROR: at _0:0_0:0 
Message: GCC Preprocessing failed! 
caught 

Exception occurred: Failure("GCC Preprocessing failed!") 
Error3(s) detected at main 
```

However, the **binary version** ran successfully
```
./s2 glist_last.c 

!!!Full processing file "glist_last.c"
Parsing file "glist_last.c" by cil parser...
GCC Preprocessing...
gcc -C -E glist_last.c -o glist_last.c.prep

!!! generate unknown predicate for Pre synthesis of g_list_last: :HP_16
!!! generate unknown predicate for Post synthesis of g_list_last: :GP_17
!!! processing primitives "["prelude.ss"]
Starting Omega.../usr/local/bin/oc

Checking procedure while_37_4$GList... 
...
Procedure while_37_4$GList SUCCESS.

*********************************************************
*******relational definition ********
*********************************************************
[ H_last(list_1238) ::= list_1238::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
HP_1224(next_37_1222)&list_1238!=null(4,5),
 G_last(list_1241,list_1242) ::= 
 list_1241::GList<key_37_1220,DP_DP_HP_1223,next_37_1222>&
 list_1242=list_1241 & next_37_1222=null
 or list_1241::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
    G_last(next_37_1222,list_1242)&next_37_1222!=null
 (4,5),
 HP_1224(list_1240) ::= 
 list_1240::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
 HP_1224(next_37_1222)
 or emp&list_1240=null
 (4,5)]
*************************************

!!! INFERRED SHAPE SPEC: EBase exists (Expl)[](Impl)[key_37_1220](ex)[]list::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
       next_37_1222::HP_1224{}<>&list!=null&{FLOW,(1,31)=__flow#E}[]
         EBase exists (Expl)[](Impl)[key_37_1220](ex)[]emp&MayLoop[]&
               {FLOW,(4,5)=__norm#E}[]
                 EAssume ref [list]
                   (exists list': list::G_last{}<list'>&
                   {FLOW,(4,5)=__norm#E})[]
                   
Checking procedure g_list_last$GList...
...
Procedure g_list_last$GList SUCCESS.

*********************************************************
*******relational definition ********
*********************************************************
[ HP_16(list_1315) ::= list_1315::HP_1224<>(4,5),
 GP_17(list_1316,res_1317) ::= 
 list_1316::G_last<list_1309>
 or emp&list_1316=null & res_1317=null
 (4,5),
 G_last(list_1241,list_1242) ::= 
 list_1241::GList<key_37_1220,DP_DP_HP_1223,next_37_1222>&
 list_1242=list_1241 & next_37_1222=null
 or list_1241::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
    G_last(next_37_1222,list_1242)&next_37_1222!=null
 (4,5),
 HP_1224(list_1240) ::= 
 list_1240::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
 HP_1224(next_37_1222)
 or emp&list_1240=null
 (4,5),
 H_last(list_1238) ::= list_1238::GList<key_37_1220,DP_DP_HP_1223,next_37_1222> * 
HP_1224(next_37_1222)&list_1238!=null(4,5)]
*************************************

!!! INFERRED SHAPE SPEC: EBase list::HP_1224{}<>&{FLOW,(4,5)=__norm#E}[]
         EBase emp&MayLoop[]&{FLOW,(4,5)=__norm#E}[]
                 EAssume 
                   list::GP_17{}<res>&{FLOW,(4,5)=__norm#E}[]
                   Stop Omega... 168 invocations 
1 false contexts at: ( (37,4) )

!!! log(small):(0.221306,560)
Total verification time: 0.191552 second(s)
	Time spent in main process: 0.133293 second(s)
	Time spent in child processes: 0.058259 second(s)
```

Furthermore, when replacing the annotation of the while loop in this program
```
/*@
HeapPred H_last(GList a).
HeapPred G_last(GList a, GList b).
*/
...
    /*@
      infer[H_last, G_last]
      requires H_last(list)
      ensures G_last(list, list');
    */
```
by the annotation used in `s2_benchmarks/` 
```
    /*@
      infer[@shape]
      requires true
      ensures true;
    */
  ```
  the **binary version** still ran successfully and returned the same output
  ```
  !!!Full processing file "glist_last_infer.c"
Parsing file "glist_last_infer.c" by cil parser...
GCC Preprocessing...
gcc -C -E glist_last_infer.c -o glist_last_infer.c.prep

!!! generate unknown predicate for Pre synthesis of g_list_last: :HP_16
!!! generate unknown predicate for Post synthesis of g_list_last: :GP_17
!!! processing primitives "["prelude.ss"]
Starting Omega.../usr/local/bin/oc

!!! generate unknown predicate for Pre synthesis of while_34_4$GList: :HP_1183
!!! generate unknown predicate for Post synthesis of while_34_4$GList: :GP_1185
Checking procedure while_34_4$GList... 
...
Procedure while_34_4$GList SUCCESS.

*********************************************************
*******relational definition ********
*********************************************************
[ HP_1183(list_1241) ::= list_1241::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
HP_1227(next_34_1225)&list_1241!=null(4,5),
 GP_1185(list_1244,list_1245) ::= 
 list_1244::GList<key_34_1223,DP_DP_HP_1226,next_34_1225>&
 list_1245=list_1244 & next_34_1225=null
 or list_1244::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
    GP_1185(next_34_1225,list_1245)&next_34_1225!=null
 (4,5),
 HP_1227(list_1243) ::= 
 list_1243::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
 HP_1227(next_34_1225)
 or emp&list_1243=null
 (4,5)]
*************************************

!!! INFERRED SHAPE SPEC: EBase exists (Expl)[](Impl)[key_34_1223](ex)[]list::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
       next_34_1225::HP_1227{}<>&list!=null&{FLOW,(1,31)=__flow#E}[]
         EBase exists (Expl)[](Impl)[key_34_1223](ex)[]emp&MayLoop[]&
               {FLOW,(4,5)=__norm#E}[]
                 EAssume ref [list]
                   (exists list': list::GP_1185{}<list'>&
                   {FLOW,(4,5)=__norm#E})[]
                   
Checking procedure g_list_last$GList... 
...
Procedure g_list_last$GList SUCCESS.

*********************************************************
*******relational definition ********
*********************************************************
[ HP_16(list_1318) ::= list_1318::HP_1227<>(4,5),
 GP_17(list_1319,res_1320) ::= 
 list_1319::GP_1185<list_1312>
 or emp&list_1319=null & res_1320=null
 (4,5),
 GP_1185(list_1244,list_1245) ::= 
 list_1244::GList<key_34_1223,DP_DP_HP_1226,next_34_1225>&
 list_1245=list_1244 & next_34_1225=null
 or list_1244::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
    GP_1185(next_34_1225,list_1245)&next_34_1225!=null
 (4,5),
 HP_1183(list_1241) ::= list_1241::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
HP_1227(next_34_1225)&list_1241!=null(4,5),
 HP_1227(list_1243) ::= 
 list_1243::GList<key_34_1223,DP_DP_HP_1226,next_34_1225> * 
 HP_1227(next_34_1225)
 or emp&list_1243=null
 (4,5)]
*************************************

!!! INFERRED SHAPE SPEC: EBase list::HP_1227{}<>&{FLOW,(4,5)=__norm#E}[]
         EBase emp&MayLoop[]&{FLOW,(4,5)=__norm#E}[]
                 EAssume 
                   list::GP_17{}<res>&{FLOW,(4,5)=__norm#E}[]
                   Stop Omega... 168 invocations 
1 false contexts at: ( (34,4) )

!!! log(small):(0.221813,560)
Total verification time: 0.197489 second(s)
	Time spent in main process: 0.13925 second(s)
	Time spent in child processes: 0.058239 second(s)
```
