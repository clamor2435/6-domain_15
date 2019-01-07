#/usr/bin/bash

i="1"
while [ $i -le 100 ]
    do
    ./random_node 15 > $i.dat
    ./runDD 1 $i>run
    ampl run
    ./runLD 1 $i>run
    ampl run
    ./runSDS 1 $i>run
    ampl run
    i=`expr $i + 1`
    done
i="1"
while [ $i -le 100 ]
    do
    ./Intra_dat $i.dat DD$i.txt
    ./Intra_dat $i.dat LD$i.txt
    ./Intra_dat $i.dat SDS$i.txt
    i=`expr $i + 1`
    done
i="1"
j="1"
while [ $i -le 100 ]
    do
    j = "1"
    while [ $j -le 6 ]
    do
    ./intraDD 1 $i $j >run
    ampl run
    ./intraLD 1 $i $j >run
    ampl run
    ./intraSDS 1 $i $j >run
    ampl run
    j=`expr $j + 1`
    done
    i=`expr $i + 1`
    done
