#!/bin/bash

if ! g++ @opcjeCpp main_tester.cpp prev.cpp -o tested_code; then
    echo "Compilation error!"
    exit
fi

if ! g++ @opcjeCpp prev_brut.cpp -o brutal_code; then
    echo "Compilation error!"
    exit
fi
if ! g++ @opcjeCpp generator.cpp -o generator; then
    echo "Compilation error!"
    exit
fi






for((i=1; i > 0; i++))
do
        echo $i > ziarno
        ./generator < ziarno > input.in
        ./brutal_code < input.in > brut.out
        ./tested_code  < input.in > tested.out
        if diff  -c -b brut.out tested.out > /dev/null
        then
                echo -e "${COLOR_NC}$i          ${COLOR_GREEN}OK!${COLOR_NC}"
        else
                echo -e "${COLOR_NC}$i          ${COLOR_RED}NIEOK!${COLOR_NC}"
                diff  -b brut.out tested.out
#               echo -e "BRUT OUTPUT:"
#               cat brut.out;echo
#               echo -e "TESTED OUT:"
#               cat tested.out;echo
                echo -e "CONTINUE? [Y/n]"
                read ans
                if [[ $ans == "y" || $ans == "Y" ]]
                then
                echo -e "START IN:"
                for((j=10;j >= 0; j--))
                do
                        echo -e "${COLOR_YELLOW}$j${COLOR_NC}"
                        sleep .125
                done
                else
                        break
                fi
        fi
done


