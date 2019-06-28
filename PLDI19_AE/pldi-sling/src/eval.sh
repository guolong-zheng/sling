dir=$1

echo ''
echo 'In directory '$dir

for f in $dir/*.c;
    do
      if [[ ${f} != *"header.c"* ]]; then
        echo 'start '$f
	    ./run.sh 10 $dir/defn.sl $f | tail -1 >> result.csv;
        echo 'finished '$f
        echo ''
      fi
    done


