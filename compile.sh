#!/usr/bin/env bash

usage () {
    echo "The only arguments available are -c which cleans the build directory"
}

clean=0
while getopts "c" arg; do 
    case "${arg}" in 
        c)
            echo "Cleaning build directory"
            clean=1
            ;;
        *)
            usage
            ;;
    esac
done

DNDHOME=$HOME/dndcode

if [[ clean -eq 1 ]]; then
    rm -r $DNDHOME/build
else
    mkdir $DNDHOME/build
    g++ -std=c++11 -o $DNDHOME/build/dndhello -include \
        library/base/dice.h \
        library/base/dice.cc \
        main.cc \
        -l boost_program_options
fi

