ARG CUDA_BASE=nvidia/cuda:11.8.0-devel-ubuntu22.04
from ${CUDA_BASE} as dev

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia

run apt update && apt install -y \
    build-essential cmake clang \
    curl git-core gnupg locales \
    zsh wget fonts-powerline \
    && locale-gen en_US.UTF-8

ENV DEBIAN_FRONTEND=dialog

# generate locale for agnoster
RUN echo "en_US.UTF-8 UTF-8" > /etc/locale.gen && /usr/sbin/locale-gen

ENV TERM xterm

# Set the default shell to bash rather than sh
ENV SHELL /bin/zsh

 # run the installation script  
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true

RUN cd $HOME && curl -fsSLO https://raw.githubusercontent.com/romkatv/dotfiles-public/master/.purepower

ADD .devcontainer/.zshrc $HOME

from dev as build

WORKDIR /workspace/nmtools

COPY cmake cmake
COPY scripts scripts
COPY include include
COPY tests tests
COPY CMakeLists.txt CMakeLists.txt
COPY nmtools.pc.in nmtools.pc.in
COPY nmtoolsConfig.cmake.in nmtoolsConfig.cmake.in

## install doctest
COPY scripts/install_doctest.sh scripts/install_doctest.sh
RUN bash scripts/install_doctest.sh

RUN apt install -y libclang-dev clang-tools libomp-dev llvm-dev lld libboost-dev libboost-fiber-dev libboost-context-dev
RUN bash scripts/install_opensycl.sh

ARG toolchain=sycl-clang14-cuda
ENV TOOLCHAIN=${toolchain}

FROM build as run

RUN apt install -y build-essential

RUN mkdir -p build/${toolchain} && cd build/${toolchain} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${toolchain}.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF -DNMTOOLS_BUILD_UTL_TESTS=OFF -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_SYCL_TESTS=ON \
        ../.. \
    && make -j2 VERBOSE=1 numeric-tests-sycl-doctest

ENV toolchain=${toolchain}
CMD ["sh", "-c", "/workspace/nmtools/build/${toolchain}/tests/sycl/numeric-tests-sycl-doctest"]