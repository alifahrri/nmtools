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

set -e

## assuming this script is located in root/scripts & build directory in root/scripts
NMTOOLS_TESTBENCH_EPOCHS=3 NMTOOLS_TESTBENCH_WARMUP=1 $BUILD_DIR/tests/numeric-tests-doctest \
    && $BUILD_DIR/tests/numeric-tests-doctest-optional \
    && $BUILD_DIR/tests/numeric-tests-doctest-exception \
    && $BUILD_DIR/tests/numeric-tests-doctest-meta

gcovr -r $DIR/../include/ $BUILD_DIR --html-details=build/nmtools-coverage.html

cd $DIR/..
if [[ ! -z ${CODECOV_TOKEN} ]]; then
    bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
fi

cd $CWD