#!/bin/bash

if [[ ! -d ~/miniconda3/bin/activate ]]; then
    mkdir -p ~/miniconda3
    wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
    bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
    rm ~/miniconda3/miniconda.sh

    source ~/miniconda3/bin/activate

    conda init --all

    conda create -n cling -c conda-forge cmake xeus-zmq cling=1.0 nlohmann_json=3.11.2 cppzmq xtl pugixml doctest cpp-argparse jupyterlab -y
    source activate cling
    # conda install xeus-cling jupyter -c conda-forge -y

    cd /opt/
    git clone https://github.com/jupyter-xeus/xeus-cling.git
    echo "CONDA_PREFIX: ${CONDA_PREFIX}"
    cd xeus-cling
    mkdir -p build && cd build
    cmake -D CMAKE_INSTALL_PREFIX=${CONDA_PREFIX} -D CMAKE_C_COMPILER=$CC -D CMAKE_CXX_COMPILER=$CXX -D CMAKE_INSTALL_LIBDIR=${CONDA_PREFIX}/lib ..
    make -j `nproc` all && make install

    # conda install jupyterlab -c conda-forge -y
    jupyter kernelspec install /root/miniconda3/envs/cling/share/jupyter/kernels/xcpp17 --user
    apt install graphviz
fi

cd /workspace/
ls
jupyter-lab --allow-root