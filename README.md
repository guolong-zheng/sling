# S2 experiments

## Tool 
The binary s2 version used in evaluation:
```
HIP: A Verifier for Heap Manipulating Programs
Version 1.0
THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT ANY WARRANTIES.
IT IS FREE FOR NON-COMMERCIAL USE
Copyright @ PLS2 @ NUS
```
**TODO**: hash: # ?  


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
  **TODO**: give an example here
  
  (3) The command to run the experiments is `2 *.c` (no specicial flags, just run `s2` as is). The generated results are in `s2_benchmarks/*/output` directory where * is the name of each category.
  
  ** TODO:  Show the output of S2 on the above example**

  (4) To check whether s2 successfully infer the correct invariants, we checked the output file of each program and see if it generates the same invariants as SLING does.

**TODO:  Give an example when it works, and it doesn't work.  Just copy and paste the results from the output dir here**


## Some examples showing the public online versions of S2 failed to work

The directory `/web_s2_result/` contains several examples causing problems to the online tools:  http://loris-5.d2.comp.nus.edu.sg/s2/ and http://loris-5.d2.comp.nus.edu.sg/s2/beta/.  
