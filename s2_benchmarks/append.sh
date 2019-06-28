PATTERN=$1

for f in */; do
   if [ -d ${f} ]; then
     for fn in ${f}/*; do
       if [ -d ${fn} ]; then
         for fnn in ${fn}/*; do
           sed -i '1s;^;#include "stdhipmem.h"\n;' $fnn
         done 
       else
         sed -i '1s;^;#include "stdhipmem.h"\n;' $fn
       fi
     done
   fi
done
