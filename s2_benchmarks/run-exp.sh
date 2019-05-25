for f in */; do
   if [ -d ${f} ]; then
     for fn in ${f}/*; do
       if [ -d ${fn} ]; then
         for fnn in ${fn}/*.c; do
           ./run.sh $fnn
         done 
       else
         if [ ${fn: -2} == ".c" ]; then
           ./run.sh $fn
         fi
       fi
     done
   fi
done
