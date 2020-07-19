#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

## assuming this script is located in root/scripts & build directory in root/scripts
cd $DIR/../build/
make numeric-tests-coverage

cd $DIR/..
if [[ ! -z ${CODECOV_TOKEN} ]]; then
    bash <(curl -s https://codecov.io/bash) -f build/numeric_coverage.info || echo "Codecov did not collect coverage reports"
fi

cd $CWD