for f in *.c; do
  sed -i -e 's/rec.h/header.h/g' $f
done
