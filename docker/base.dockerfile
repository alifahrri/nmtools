FROM ubuntu:focal AS nmtools-gcc-ubuntu

WORKDIR /opt/

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

## install sytem requirements
COPY requirements-apt.txt requirements.txt
RUN apt update && xargs apt install -y < requirements.txt
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 10000 && \
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 10000 && \
	update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-9 10000
RUN pip3 install -U gcovr

## install gtest
COPY scripts/install_gtest.sh install_gtest.sh
RUN bash install_gtest.sh

## install benchmark
COPY scripts/install_benchmark.sh install_benchmark.sh
RUN bash install_benchmark.sh

## install nanobench
COPY scripts/install_nanobench.sh install_nanobench.sh
RUN bash install_nanobench.sh

## install doctest
COPY scripts/install_doctest.sh install_doctest.sh
RUN bash install_doctest.sh

## install fmt
COPY scripts/install_fmt.sh install_fmt.sh
RUN bash install_fmt.sh

## install miniconda
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh && \
    bash Miniconda3-latest-Linux-x86_64.sh -b -p /opt/miniconda

## install armadillo
COPY scripts/install_armadillo.sh install_armadillo.sh
RUN bash install_armadillo.sh

## install eigen
RUN wget https://github.com/eigenteam/eigen-git-mirror/archive/3.3.7.tar.gz && \
	tar -zxvf 3.3.7.tar.gz && rm 3.3.7.tar.gz && \
	cd eigen-git-mirror-3.3.7 && mkdir build && cd build && cmake .. && make install

## install std::experimental::simd
COPY scripts/install_stdx_simd.sh install_stdx_simd.sh
RUN bash install_stdx_simd.sh

## install xsimd
COPY scripts/install_xsimd.sh install_xsimd.sh
RUN bash install_xsimd.sh

RUN rm -rf /opt/*

FROM alifahrri/nmtools-gcc-ubuntu:latest AS nmtools-clang-ubuntu

## install clang-11
RUN apt update && \
    apt install -y software-properties-common
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && ./llvm.sh 11
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-11 10000 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-11 10000

## upgrade cmake, because of compile flag issues on default version (3.10)
RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz && \
    tar -zxvf cmake-3.18.4.tar.gz && cd cmake-3.18.4 && cmake -DCMAKE_USE_OPENSSL=OFF . && make -j4 && make install

RUN rm -rf /opt/*

FROM alifahrri/nmtools-gcc-ubuntu:latest AS nmtools-emscripten-ubuntu

WORKDIR /opt

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd emsdk && ./emsdk install 2.0.13

## upgrade cmake, because of compile flag issues on default version (3.10)
RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz && \
    tar -zxvf cmake-3.18.4.tar.gz && cd cmake-3.18.4 && cmake -DCMAKE_USE_OPENSSL=OFF . && make -j4 && make install