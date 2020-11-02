FROM ubuntu:bionic

WORKDIR /opt/

## install sytem requirements
COPY requirements-apt.txt requirements.txt
RUN apt update && xargs apt install -y < requirements.txt

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