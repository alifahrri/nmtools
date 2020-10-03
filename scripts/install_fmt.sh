
#!/bin/bash

CWD=$pwd
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
fmt_url="https://github.com/fmtlib/fmt/archive/7.0.3.tar.gz"
fmt_file="7.0.3.tar.gz"
fmt_dir="fmt-7.0.3"

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -d|--dest)
    DEST="$2"
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

if [ -z "$DEST" -a "$DEST" != " " ]; then
    DEST="$HOME/tmp/"
fi

mkdir -p $DEST
wget -O $DEST/$fmt_file $fmt_url

cd $DEST
tar -zxvf $fmt_file

cd $fmt_dir
mkdir -p build && cd build && cmake -D CMAKE_INSTALL_PREFIX=/usr/local/ .. && make install

cd $CWD