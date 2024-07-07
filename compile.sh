#!/usr/bin/env bash
DNDHOME=$HOME/dndcode
DNDLIB=$DNDHOME/library
DNDBUILD=$DNDHOME/build
DNDPROTOBUILD=$DNDLIB/serial/build

usage () {
    echo "We got a two arguments now, -b for building the code and -p for building the protocol buffers"
}

make_build_dir (){
    if [ ! -d $DNDBUILD ]; then 
        mkdir $DNDBUILD
    fi
} 

make_proto_build_dir (){
    if [ ! -d $DNDPROTOBUILD ]; then 
        mkdir $DNDPROTOBUILD
    fi
} 

build_proto(){
    if [ -f $DNDPROTOBUILD/characterbook.pb.h ]; then
        rm $DNDPROTOBUILD/characterbook.pb.h
    fi
    if [ -f $DNDPROTOBUILD/characterbook.pb.cc ]; then
        rm $DNDPROTOBUILD/characterbook.pb.cc
    fi
    make_proto_build_dir
    protoc --proto_path=$DNDLIB/serial/ --cpp_out=$DNDPROTOBUILD characterbook.proto 
}

build_code(){
    if [ -f $DNDBUILD/dnddice ]; then
        rm $DNDBUILD/ddndice
    fi
    make_build_dir
    g++ -std=c++11 -o $DNDHOME/build/dnddice -include \
    library/base/dice.h \
    library/base/dice.cc \
    library/serial/build/characterbook.pb.h \
    library/serial/build/characterbook.pb.cc \
    library/serial/ledger.h \
    library/serial/ledger.cc \
    main.cc \
    -l boost_program_options \
    -l protoc \
    -l protobuf 
}

clean_code() {
    if [ -d $DNDBUILD ]; then
        rm -r $DNDBUILD
    fi
}

proto=0
build=0
clean=0
while getopts "bpc" arg; do 
    case "${arg}" in 
        p) 
            proto=1
            ;;
        b)  
            build=1
            ;;
        c)
            clean=1
            ;;
        *)
            usage
            ;;
    esac
done

if [[ proto -eq 1 ]]; then
    echo "Building Protocol Buffer"
    build_proto
    exit
fi 

if [[ build -eq 1 ]]; then
    if [[ clean -eq 0 ]]; then
        echo "Building code"
        build_code
    else
        echo "cleaning and building is pointless pick one."
        exit
    fi
fi

if [[ clean -eq 1 ]]; then
    if [[ build -eq 0 ]]; then
        echo "Cleaning build directory"
        clean_code
    else 
        echo "cleaning and building is pointless pick one."
        exit
    fi
fi

if [[ proto -eq 0 ]] && [[ build -eq 0 ]] && [[ clean -eq 0 ]]; then
    echo "Must specify at at least one option othwise compile will not do anything."
    exit
fi

