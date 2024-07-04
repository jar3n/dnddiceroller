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
DNDLIB=$DNDHOME/library

if [[ clean -eq 1 ]]; then
    rm -r $DNDHOME/build
else
    mkdir $DNDHOME/build
    protoc -I=$DNDHOME/library/serial/characterbook.proto --cpp_out=$DNDHOME/library/serial/
    g++ -std=c++11 -o $DNDHOME/build/dndhello -include \
    library/base/skill.h \
    library/base/skill.cc \
    library/base/dice.h \
    library/base/dice.cc \
    build/characterbook.pb.h \
    build/characterbook.pb.cc \
    main.cc -l boost_program_options
fi

