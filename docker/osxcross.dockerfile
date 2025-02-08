FROM ghcr.io/shepherdjerred/macos-cross-compiler:latest AS dev

RUN apt update \
    && apt install cmake -y