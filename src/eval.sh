dir=$1

for f in $dir/*.c;
    do
        echo "evaluating "$f 
	./run_c.sh 10 $dir/defn.sl $f | tail -1 >> newexp.csv;
        echo "finished "$f 
    done
