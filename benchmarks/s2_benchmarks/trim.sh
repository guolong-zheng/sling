PATTERN=$1

for f in */; do
   if [ -d ${f} ]; then
     for fn in ${f}/*; do
       if [ -d ${fn} ]; then
         for fnn in ${fn}/*; do
           sed -i '/${PATTERN}/d' $fnn
         done 
       else
         sed -i '/${PATTERN}/d' $fn
       fi
     done
   fi
done
