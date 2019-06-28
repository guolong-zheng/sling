echo 'program,loc,trace,inv,incomplete,time,single,pred,pure' >> result.csv

./eval.sh ../benchmarks/sll
echo '###' >> result.csv

./eval.sh ../benchmarks/sortlist
echo '###' >> result.csv

./eval.sh ../benchmarks/dll
echo '###' >> result.csv

./eval.sh ../benchmarks/circular_list
echo '###' >> result.csv

./eval.sh ../benchmarks/binary_search_tree
echo '###' >> result.csv

./eval.sh ../benchmarks/avl
echo '###' >> result.csv

./eval.sh ../benchmarks/prio_tree
echo '###' >> result.csv

./eval.sh ../benchmarks/red_black_tree
echo '###' >> result.csv

./eval.sh ../benchmarks/tree_traversals
echo '###' >> result.csv

./eval.sh ../benchmarks/tree_traversals/tree2list
echo '###' >> result.csv

#./eval.sh ../benchmarks/tree_traversals/tree2list_iter
#echo '###' >> result.csv

./eval.sh ../benchmarks/glib_glist
echo '###' >> result.csv

./eval.sh ../benchmarks/glib_gslist
echo '###' >> result.csv

./eval.sh ../benchmarks/openbsd_queue
echo '###' >> result.csv

./eval.sh ../benchmarks/memory_region
echo '###' >> result.csv

./eval.sh ../benchmarks/binomial_heap
echo '###' >> result.csv

./eval.sh ../benchmarks/sv-comp/dll_of_dll
echo '###' >> result.csv

./eval.sh ../benchmarks/sv-comp/rule_60_list
echo '###' >> result.csv

./eval.sh ../benchmarks/GRASShopper/sl
echo '###' >> result.csv

./eval.sh ../benchmarks/GRASShopper/rec
echo '###' >> result.csv

./eval.sh ../benchmarks/GRASShopper/dl
echo '###' >> result.csv

./eval.sh ../benchmarks/GRASShopper/sls
echo '###' >> result.csv

./eval.sh ../benchmarks/AFWP/dll
echo '###' >> result.csv

./eval.sh ../benchmarks/AFWP/sll
echo '###' >> result.csv

./eval.sh ../benchmarks/cyclist/aplas-stack
echo '###' >> result.csv

./eval.sh ../benchmarks/cyclist/composite4
echo '###' >> result.csv

./eval.sh ../benchmarks/cyclist/iter
echo '###' >> result.csv

./eval.sh ../benchmarks/cyclist/schorr_waite
echo '###' >> result.csv

python summary.py










