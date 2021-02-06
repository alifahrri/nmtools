FROM alifahrri/nmtools-gcc-ubuntu:latest

WORKDIR /opt

RUN git clone https://github.com/emscripten-core/emsdk.git \
    && cd emsdk && ./emsdk install 2.0.13
