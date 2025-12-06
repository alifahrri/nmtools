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
    -c|--coverage-dir)
    COVERAGE_DIR="$2"
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

if [ -z "$COVERAGE_DIR" -a "$COVERAGE_DIR" != " " ]; then
        COVERAGE_DIR="$BUILD_DIR/coverage/"
fi

set -e

ulimit -s unlimited

## assuming this script is located in root/scripts & build directory in root/scripts
NMTOOLS_TESTBENCH_EPOCHS=3 NMTOOLS_TESTBENCH_WARMUP=1 NMTOOLS_TESTBENCH_QUIET=1 \
       $BUILD_DIR/tests/array/numeric-tests-doctest \
    && $BUILD_DIR/tests/meta/numeric-tests-doctest-meta \
    && $BUILD_DIR/tests/utl/meta/numeric-tests-utl-meta \
    && $BUILD_DIR/tests/utl/array/numeric-tests-utl-array \
    && $BUILD_DIR/tests/utility/numeric-tests-utility-doctest \
    && $BUILD_DIR/tests/utl/utl/numeric-tests-utl

mkdir -p ${COVERAGE_DIR}
gcovr -r $DIR/../include/nmtools $BUILD_DIR --html-details=${COVERAGE_DIR}/nmtools-coverage.html

cd $DIR/..
if [[ ! -z ${CODECOV_TOKEN} ]]; then
    bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
fi

cd $CWD