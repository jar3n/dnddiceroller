#!/usr/bin/env bash
DNDHOME=$HOME/dndcode
DNDLIB=$DNDHOME/library
DNDBUILD=$DNDHOME/build

usage () {
    echo "We got a two arguments now, -b for building the code and -p for building the protocol buffers"
}

make_build_dir (){
    if [ ! -d $DNDBUILD ]; then 
        mkdir $DNDBUILD
    fi
} 

build_proto(){
    if [ -f $DNDBUILD/characterbook.pb.h ]; then
        rm $DNDBUILD/characterbook.pb.h
    fi
    if [ -f $DNDBUILD/characterbook.pb.cc ]; then
        rm $DNDBUILD/characterbook.pb.cc
    fi
    make_build_dir
    protoc --proto_path=$DNDLIB/serial/ --cpp_out=$DNDHOME/build characterbook.proto 
}

build_code(){
    if [ -f $DNDBUILD/dnddice ]; then
        rm $DNDBUILD/ddndice
    fi
    make_build_dir
    g++ -std=c++11 -o $DNDHOME/build/dnddice -include \
    library/base/dice.h \
    library/base/dice.cc \
    build/characterbook.pb.h \
    build/characterbook.pb.cc \
    library/serial/ledger.h \
    library/serial/ledger.cc \
    main.cc \
    -l boost_program_options \
    -l protoc \
    -l protobuf 
}

proto=0
build=0
while getopts "bp" arg; do 
    case "${arg}" in 
        p) 
            echo "Building Protocol Buffer"
            proto=1
            ;;
        b) 
            echo "Building code"
            build=1
            ;;
        *)
            usage
            ;;
    esac
done

if [[ proto -eq 1 ]]; then
    build_proto
fi 

if [[ build -eq 1 ]]; then
    build_code
fi

if [[ proto -eq 0 ]] && [[ build -eq 0 ]]; then
    echo "Must specify at at least one option othwise compile will not do anything."
fi

