FROM alifahrri/nmtools-gcc-ubuntu:latest

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