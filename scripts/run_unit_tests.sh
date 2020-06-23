#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )" 

## assuming this script is located in root/scripts & build directory in root/scripts
cd $DIR/../build/
make numeric_coverage
cd $CWD