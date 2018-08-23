dir=$1

for f in $dir/*.c;
    do 
	./run.sh 10 $dir/defn.sl $f | tail -1 >> newexp.csv;
        echo $f 
    done
