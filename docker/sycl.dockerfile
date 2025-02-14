# ARG BASE=nvidia/cuda:11.8.0-devel-ubuntu22.04
ARG BASE=ubuntu:jammy
from ${BASE} as dev

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

# install powerlevel10k
RUN git clone https://github.com/romkatv/powerlevel10k.git ~/.oh-my-zsh/custom/themes/powerlevel10k

RUN cd $HOME && curl -fsSLO https://raw.githubusercontent.com/romkatv/dotfiles-public/master/.purepower

ADD .devcontainer/.zshrc $HOME

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

FROM dev as build

RUN bash scripts/install_doctest.sh

RUN apt install -y libclang-dev clang-tools libomp-dev llvm-dev lld libboost-dev libboost-fiber-dev libboost-context-dev

ARG opencl_backend=OFF
ENV OPENCL_BACKEND=${opencl_backend}

ARG cuda_backend=OFF
ENV CUDA_BACKEND=${cuda_backend}

ARG level_zero_backend=OFF
ENV LEVEL_ZERO_BACKEND=${level_zero_backend}

ARG toolchain=sycl-clang14-omp
ENV TOOLCHAIN=${toolchain}

# for llvm-spirv & pocl
ENV LLVM_VERSION="18"
ENV LLVM_SPV_VERSION="v18.1.8"
ENV POCL_VERSION="v6.0"
ENV ADAPTIVE_CPP_VERSION="v24.10.0"

# TODO: make the following installation conditional on selected backend
RUN bash scripts/install_llvm.sh
RUN bash scripts/install_llvm_spirv.sh
RUN bash scripts/install_pocl.sh

RUN bash scripts/install_opensycl.sh

FROM build as run

RUN mkdir -p build/${TOOLCHAIN} && cd build/${TOOLCHAIN} \
    && cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/${TOOLCHAIN}.cmake \
        -DNMTOOLS_BUILD_META_TESTS=OFF -DNMTOOLS_BUILD_UTL_TESTS=OFF -DNMTOOLS_TEST_ALL=OFF \
        -DNMTOOLS_BUILD_SYCL_TESTS=ON \
        ../.. \
    && make -j2 VERBOSE=1 numeric-tests-sycl-doctest

# got weird error on CI
# LLVM ERROR: Instruction Combining did not reach a fixpoint after 1 iterations
CMD ["sh", "-c", "/workspace/nmtools/build/${TOOLCHAIN}/tests/sycl/numeric-tests-sycl-doctest", "-tce=bilinear*"]

# device:
# [nmtools sycl] number of sycl devices: 2
# [nmtools sycl] platform #0:
# - name: OpenCL (platform 0)
# - vendor: The AdaptiveCpp project
# - version: AdaptiveCpp 24.10.0+git.7677cf6e.20241220.branch.HEAD
# - profile: FULL_PROFILE
# - extensions: 
# [nmtools sycl] platform #1:
# - name: OpenMP (platform 0)
# - vendor: The AdaptiveCpp project
# - version: AdaptiveCpp 24.10.0+git.7677cf6e.20241220.branch.HEAD
# - profile: FULL_PROFILE
# - extensions: 
# [nmtools sycl] default context using platform #0
# - name: cpu-znver3-AMD EPYC 7763 64-Core Processor
# - vendor: cpu-znver3-AMD EPYC 7763 64-Core Processor
# - driver_version: 6.0
# - profile: FULL_PROFILE
# - version: OpenCL OpenCL C 1.2 PoCL
# - opencl_c_version: 1.2 HIPSYCL
# - extensions: 
# - device_type: CPU
# - vendor_id: 65542
# - max_compute_units: 4