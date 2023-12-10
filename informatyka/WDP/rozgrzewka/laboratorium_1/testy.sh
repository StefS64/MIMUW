#!/bin/bash
for((i = 0;i <= 15;i++))
do
        input="testy/dzielny$i.in"
        output="testy/dzielny$i.out"
        ./rozgrzewka.out < $input > rozgrzewka.output
        if  diff -w rozgrzewka.output $output > /dev/null
        then 
                echo "$i        OK!"
        else
                echo "$i NIEOK!"
        fi
done

