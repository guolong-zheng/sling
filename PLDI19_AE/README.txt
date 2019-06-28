1. Set up
  (1) Install Docker. Please follow the instruction on https://docs.docker.com/install/ to install docker;
  (2) After docker is successfully installed, run 'docker build -t sling .' at directory paper494/sling/;
  (3) Run 'docker run --privileged -it sling', --privileged flag is needed due to the debugger needs full access;
  (4) To run SLING on single example, use the following command './run.sh 5 ../benchmarks/dll/defn.sl ../benchmarks/dll/concat.c' to run SLING on program 'dll/concat.c' with a size 5 input and the predicate defined in 'dll/defn.sl'. Then SLING infers pre and post conditions and other specified locations(if annotated in dll/concat.c) and outputs them in the terminal. The last line of the output is some statistics that used to generate Table 1 in the paper. For example, "../benchmarks/dll/concat,4,16,27,0,20.9,3,57,83" corresponds to the name of the program, # of specified locations, # of traces, # of invariants generated, whether all specified locations are covered, time, # of singleton pred, # of inductive pred and # of pure relations.
 

2. Evaluate
  (1) Run './run_exp.sh' to generate Table 1 in the paper. This runs SLING on the whole benchmark and it takes around 2 hours. Some numbers may be different from the ones presented in the paper, this is because the random input generation and is expected for dynamic analysis. The separated output for each program is stored in 'AEoutput' directory in each category and the csv file ‘result.csv’ is the raw statistics of the experiment, 'summary.csv' is the table 1 in the paper. 
      To run experiment for a specific category, for example, singly linked list, using './eval.sh ../benchmarks/sll'.

  (2) Table 2 in the paper compares SLING with S2. Because S2 is not publicly available, we couldn't put the binary file in our pack. But the result of running S2 on our benchmarks are in s2_benchmarks/ directory.
