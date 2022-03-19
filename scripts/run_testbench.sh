#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -b|--build-dir)
    BUILD_DIR="$2"
    shift # past argument
    shift # past value
    ;;
    -o|--output-dir)
    OUTPUT_DIR="$2"
    shift # past argument
    shift # past value
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

if [ -z "$BUILD_DIR" -a "$BUILD_DIR" != " " ]; then
        BUILD_DIR="$DIR/../build/"
fi

if [ -z "$OUTPUT_DIR" -a "$OUTPUT_DIR" != " " ]; then
        OUTPUT_DIR="$BUILD_DIR"
fi

## MNIST testbench

export NMTOOLS_TESTBENCH_OUTPUT_ALL=1
export NMTOOLS_TESTBENCH_OUTPUT_DIR="${OUTPUT_DIR}"

export NMTOOLS_TESTBENCH_EPOCHS=100
export NMTOOLS_TESTBENCH_WARMUP=10
export NMTOOLS_TESTBENCH_QUIET=0
$BUILD_DIR/tests/testbench/numeric-tests-bench -q \
    -tc="matmul_add","softmax","pool2d_0","pool2d_1" \
    >&1 | tee $OUTPUT_DIR/testbench.md

## run (currently) slow ops:

export NMTOOLS_TESTBENCH_EPOCHS=15
export NMTOOLS_TESTBENCH_WARMUP=1
export NMTOOLS_TESTBENCH_QUIET=0
$BUILD_DIR/tests/testbench/numeric-tests-bench -q \
    -tce="matmul_add","softmax","pool2d_0","pool2d_1" \
    >&1 | tee -a $OUTPUT_DIR/testbench.md