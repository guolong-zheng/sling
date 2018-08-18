dir=$1

for f in $dir/*.c;
    do 
	./run.sh $f 5 $dir/defn.sl | tail -1 >> res.csv;
        echo $f 
    done
