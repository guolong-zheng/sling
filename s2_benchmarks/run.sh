
FILE=$1

pushd $(dirname $FILE)
mkdir -p output
fname=${FILE%.dryad.c}
popd

echo $fname

timeout 30 ../s2 -tp z3 --lem-en-syn --pred-en-seg $FILE | tee $(dirname $FILE)/output/$(basename $fname).txt

