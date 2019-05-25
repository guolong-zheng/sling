1. The examples of using the website version are contained in ./web_s2_result/ 
   The website address are listed:
   
   http://loris-5.d2.comp.nus.edu.sg/s2/
   
   http://loris-5.d2.comp.nus.edu.sg/s2/beta/
   
2. The binary s2 version used in evaluation:
HIP: A Verifier for Heap Manipulating Programs
Version 1.0
THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT ANY WARRANTIES.
IT IS FREE FOR NON-COMMERCIAL USE
Copyright @ PLS2 @ NUS

3. Steps used to get the result:
  (1) The benchmarks are taken from VCDryad benchmarks(http://madhu.cs.illinois.edu/vcdryad/examples/)
  
  (2) The benchmarks are in s2_benchmarks/ and each benchmark are annotated with
      "/*@
        infer[@shape]
        requires true
        ensures true;
       */"
  
  (3) The command to run the experiments is "s2 *.c", and the generated results are in s2_benchmarks/*/output directory where * is the name of each category.

  (4) To check whether s2 successfully infer the correct invariants, we checked the output file of each program and see if it generates the same invariants as SLING does.

