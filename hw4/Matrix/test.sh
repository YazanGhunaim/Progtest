#!/bin/bash
# Compares output of program with *_in.txt as input data with reference output *_out.txt
# Files must be in subdirectory "ENG"


TEST_DIR="ENG/"

for IN_FILE in ${TEST_DIR}*_in.txt
do
	REF_FILE=$(echo -n $IN_FILE | sed -e 's/_in\(.*\)$/_out\1/')

	./a.out < $IN_FILE > my_out.txt

	if ! diff $REF_FILE my_out.txt > temp.txt
	then
		printf "\e[0;31mFail: %s\e[0m\n" "$IN_FILE"
		cat temp.txt
		#echo "Input data:"
		#echo `cat "$IN_FILE"`
		#exit
	else
		printf "\e[0;32mOK:\e[0m %s\n" $IN_FILE
	fi
done

rm my_out.txt temp.txt
