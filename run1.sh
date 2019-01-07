#/usr/bin/bash
i="1"
j="1"
while [ $i -le 100 ]
    do
    j="1"
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
