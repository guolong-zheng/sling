
for f in */; do
   if [ -d ${f} ]; then
     for fn in ${f}/*; do
       if [ -d ${fn} ]; then
         for fnn in ${fn}/*.c; do
           sed -i '/^typedef/,/^\}/d' $fnn
         done 
       else
         if [ ${fn: -2} == ".c" ]; then
           sed -i '/^typedef/,/^\}/d' $fn
         fi
       fi
     done
   fi
done
