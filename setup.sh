#!/bin/bash

set -e

# load settings and export variables
set -a          
source settings.env 
set +a

DIR_ROOT=$(pwd)

DEBUG=0

function clean_code {
    if [[ -d $DIR_BUILD ]]; then
	    rm -r $DIR_BUILD
    fi
}

function build_code {    
    if [[ ! -d $DIR_BUILD ]]; then
	    mkdir $DIR_BUILD
    fi
    if [[ $DEBUG == 1 ]]; then
	cmake -B $DIR_BUILD -DCOMPILE_DIP=OFF -DCOMPILE_PUQ_MAGNITUDE=value -DCMAKE_BUILD_TYPE=Debug
    else
	cmake -B $DIR_BUILD -DCOMPILE_DIP=OFF -DCOMPILE_PUQ_MAGNITUDE=value
    fi
    cd $DIR_BUILD
    make -j 1
    cd $DIR_ROOT
}

function install_code {
    cd $DIR_BUILD
    make install
    cd $DIR_ROOT
}

function test_code {
    if [[ $DEBUG == 1 ]]; then
	if [[ "${2}" == "" ]]; then
	    lldb ./$DIR_BUILD/gtest/$1/GTestModule-$1
	else
            lldb ./$DIR_BUILD/gtest/$1/GTestModule-$1 --gtest_filter="${2}"
	fi
    else
	if [[ "${2}" == "" ]]; then
	    ./$DIR_BUILD/gtest/$1/GTestModule-$1
	else
            ./$DIR_BUILD/gtest/$1/GTestModule-$1 --gtest_filter="${2}"
	fi
    fi
}

function run_code {
    ./$DIR_BUILD/$1
}

function compile_docs {
    doxygen
}

function grep_code {
    if [[ "${1}" != "" ]]; then
	    grep -Inr --color "${1}" ./src ./gtest ./exec
    fi
}

function show_help {
    echo "Open Scientific Numerical Tools (OpenSNT)"
    echo ""
    echo "Options:"
    echo " -c|--clean          clean the build directory"
    echo " -b|--build          build code"
    echo " -i|--install        install dip"
    echo " -r|--run <example>  run an example code"
    echo " -t|--test [<test>]  run all/specific tests"
    echo " -d|--docs           compile documentation"
    echo " -g|--grep <expr>    find expression in a code"
    echo " -h|--help           show this help"
    echo ""
    echo "Examples:"
    echo "./setup.sh -c -b               clean and build the code"
    echo "./setup.sh -t Output.Data      run 'Output.Data' test"
    echo "./setup.sh -g class            find 'class' in the code or test"
}

if [[ "${1}" == "" ]]; then
    show_help
fi
while [[ $# -gt 0 ]]; do
    case $1 in
	-c|--clean)
	    clean_code; shift;;
	-b|--build)
	    build_code; shift;;
	-i|--install)
	    install_code; shift;;
	-r|--run)
	    run_code $2; shift; shift;;
	-t|--test)
	    test_code $2 $3; shift; shift; shift;;
	-d|--docs)
	    compile_docs; shift;;
	-g|--grep)
	    grep_code $2; shift; shift;;
	-h|--help)
	    show_help; shift;;
	-*|--*)
	    show_help; exit 1;;
	*)
	    show_help; shift;;
    esac
done
