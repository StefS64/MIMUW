#!/bin/bash
# autor: Grzegorz Krawczyk

check=false
while getopts v:* flag
do
    case "${flag}" in
        v) check=$OPTARG;;
    esac
done

g++ @opcjeCpp main.cpp prev.cpp -o wzor.e
if [ $? != 0 ]; then
	echo -ne "Kompilacja rozwiazania wzorcowego nie powiodla sie.\n"
    exit -1
fi
g++ @opcjeCpp main.cpp prevB.cpp -o brut.e
if [ $? != 0 ]; then
	echo -ne "Kompilacja rozwiazania brutalnego nie powiodla sie.\n"
    exit -1
fi
g++ -std=c++17 -static -Wall -pedantic -O3 -s -lm prevG.cpp -o gen.e
if [ $? != 0 ]; then
	echo -ne "Kompilacja generatorki testow nie powiodla sie.\n"
    exit -1
fi

if [ "$check" = true ]; then
    echo -ne "Testowanie przy uzyciu valgrinda.\n"
else
    echo -ne "Testowanie bez valgrinda.\n"
fi

for i in {00000..99999}
do
	echo $i > Z
	./gen.e < Z > wej.in

	./brut.e < wej.in > brut.out
	if [ "$check" = true ]; then
    	valgrind -q --exit-on-first-error=yes --error-exitcode=-3 --log-file=memcheck.log --tool=memcheck --leak-check=yes ./wzor.e < wej.in > wzor.out
		if [ $? != 0 ]; then
			echo -ne "$i NIEOK"
			break
		fi
    else
    	./wzor.e < wej.in > wzor.out
    fi

	./wzor.e < wej.in > wzor.out
	./brut.e < wej.in > brut.out
	if diff -b wzor.out brut.out > /dev/null
	then
		echo -ne "\r$i OK"
	else
		echo -ne "\r$i NIEOK"
		break
	fi
done
echo -ne "\n"
# chmod +x prev.sh