FROM alifahrri/nmtools-gcc-ubuntu:latest

WORKDIR /opt

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd emsdk && ./emsdk install 2.0.13

## upgrade cmake, because of compile flag issues on default version (3.10)
RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz && \
    tar -zxvf cmake-3.18.4.tar.gz && cd cmake-3.18.4 && cmake -DCMAKE_USE_OPENSSL=OFF . && make -j4 && make install