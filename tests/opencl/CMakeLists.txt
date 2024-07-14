cmake_minimum_required(VERSION 3.10.2)
project(numeric-tests-opencl)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

# optionally use boost (esp. for type_id)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

option(NMTOOLS_OPENCL_TEST_ALL "test all opencl modules" OFF)
option(NMTOOLS_OPENCL_TEST_UFUNC "test opencl ufunc modules" OFF)
option(NMTOOLS_OPENCL_TEST_INDEX "test opencl index modules" OFF)

if (NMTOOLS_OPENCL_TEST_ALL)
    SET(NMTOOLS_OPENCL_TEST_UFUNC ON CACHE BOOL "test opencl ufunc modules" FORCE)
    SET(NMTOOLS_OPENCL_TEST_INDEX ON CACHE BOOL "test opencl index modules" FORCE)
endif (NMTOOLS_OPENCL_TEST_ALL)

set(NMTOOLS_OPENCL_TEST_SOURCES "")

set(OPENCL_KHR_EXTENSIONS
    -Dcl_khr_int64
    -Dcl_khr_fp64
    -Dcl_khr_byte_addressable_store
    -Dcl_khr_int64_extended_atomics
    -Dcl_khr_global_int32_base_atomics
    -Dcl_khr_global_int32_extended_atomics
    -Dcl_khr_local_int32_base_atomics
    -Dcl_khr_local_int32_extended_atomics
    -Dcl_khr_3d_image_writes
    -Dcl_khr_int64_base_atomics
)
set(LLVM_SPIRV_OPTIONS
    # -spirv-ocl-builtins-version=1.2
    -spirv-max-version=1.0
)

# somehow doesn't work on -O2, -O3, -O0 :(
set(CLANG_OPENCL_ARGS -emit-llvm -target spir64-unknown-unknown
    -Wall -Wextra -Wno-gnu-string-literal-operator-template
    -Xclang -finclude-default-header
    -Xclang -cl-std=CLC++ -O1
)
# TODO: check when __OPENCL_VERSION__ should be defined (host/kernel?)
set(NMTOOLS_OPENCL_MACROS
    -D__OPENCL_C_VERSION__=120
    -D__OPENCL_VERSION__=120
    -DNMTOOLS_OPENCL_BUILD_KERNELS
)

if (NMTOOLS_OPENCL_TEST_UFUNC)
    set(NMTOOLS_OPENCL_TEST_SOURCES ${NMTOOLS_OPENCL_TEST_SOURCES}
        kernels/relu.cpp
        kernels/relu6.cpp
        kernels/prelu.cpp
        kernels/celu.cpp
        kernels/elu.cpp
        kernels/hardshrink.cpp
        kernels/hardswish.cpp
        kernels/hardtanh.cpp
        kernels/leaky_relu.cpp
        kernels/log_sigmoid.cpp
        kernels/mish.cpp
        kernels/selu.cpp
        kernels/sigmoid.cpp
        kernels/silu.cpp
        kernels/softplus.cpp
        kernels/softshrink.cpp
        kernels/softsign.cpp
        kernels/tanhshrink.cpp
        kernels/arccos.cpp
        kernels/arccosh.cpp
        kernels/arcsin.cpp
        kernels/arcsinh.cpp
        kernels/arctan.cpp
        kernels/arctanh.cpp
        kernels/cbrt.cpp
        kernels/ceil.cpp
        kernels/cos.cpp
        kernels/cosh.cpp
        kernels/exp.cpp
        kernels/exp2.cpp
        kernels/expm1.cpp
        kernels/fabs.cpp
        kernels/floor.cpp
        kernels/invert.cpp
        kernels/isfinite.cpp
        kernels/isinf.cpp
        kernels/isnan.cpp
        kernels/log.cpp
        kernels/log1p.cpp
        kernels/log2.cpp
        kernels/log10.cpp
        kernels/negative.cpp
        kernels/positive.cpp
        kernels/reciprocal.cpp
        kernels/rint.cpp
        kernels/signbit.cpp
        kernels/sin.cpp
        kernels/sinh.cpp
        kernels/sqrt.cpp
        kernels/square.cpp
        kernels/tan.cpp
        kernels/tanh.cpp
        kernels/trunc.cpp

        ## binary ufuncs ##
        kernels/add.cpp
        kernels/multiply.cpp
        kernels/subtract.cpp
        kernels/divide.cpp

        ## indexing ##
        kernels/broadcast_to.cpp
        kernels/transpose.cpp
        kernels/repeat.cpp
        kernels/pad.cpp
        kernels/resize.cpp
        # TODO: fix kernel compilation error
        # kernels/pooling.cpp
        # kernels/flatten.cpp
        kernels/atleast_1d.cpp
        kernels/atleast_2d.cpp
        # kernels/reshape.cpp
        # kernels/squeeze.cpp
        kernels/expand_dims.cpp
        # kernels/flip.cpp
        kernels/tile.cpp
        kernels/where.cpp
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_custom_target( ${PROJECT_NAME}-build-kernels
                    ALL
                        ${CMAKE_CXX_COMPILER} --version
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i relu.spv > ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i relu6.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i prelu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i celu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i elu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i hardshrink.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i hardswish.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i hardtanh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i leaky_relu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i log_sigmoid.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i mish.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i selu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i sigmoid.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i silu.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i softplus.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i softshrink.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i softsign.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i tanhshrink.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arccos.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arccosh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arcsin.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arcsinh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arctan.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i arctanh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i cbrt.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i ceil.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i cos.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i cosh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i exp.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i exp2.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i expm1.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i fabs.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i floor.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i invert.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i isfinite.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i isinf.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i isnan.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i log.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i log1p.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i log2.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log10.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log10.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log10.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log10.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i log10.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i negative.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i positive.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i reciprocal.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i rint.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i signbit.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i sin.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i sinh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i sqrt.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i square.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i tan.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i tanh.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i trunc.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_add.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/add.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_add.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_add.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_add.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_broadcast_to.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/broadcast_to.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_broadcast_to.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_broadcast_to.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_broadcast_to.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_multiply.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/multiply.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_multiply.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_multiply.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_multiply.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_divide.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/divide.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_divide.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_divide.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_divide.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_subtract.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/subtract.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_subtract.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_subtract.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_subtract.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_transpose.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/transpose.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_transpose.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_transpose.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_transpose.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_repeat.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/repeat.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_repeat.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_repeat.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_repeat.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pad.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/pad.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pad.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pad.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_pad.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_resize.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/resize.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_resize.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_resize.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_resize.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        ## TODO: enable pooling
                        # &&
                        # ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        # -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pooling.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/pooling.cpp
                        # && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pooling.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pooling.bc
                        # && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_resize.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        ## TODO: enable flatten
                        # &&
                        # ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        # -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flatten.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/flatten.cpp
                        # && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flatten.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flatten.bc
                        # && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_flatten.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_1d.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/atleast_1d.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_1d.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_1d.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_atleast_1d.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_2d.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/atleast_2d.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_2d.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_2d.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_atleast_2d.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        ## TODO: enable reshape
                        # &&
                        # ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        # -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_reshape.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reshape.cpp
                        # && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_reshape.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_reshape.bc
                        # && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_reshape.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        ## TODO: enable squeeze
                        # &&
                        # ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        # -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_squeeze.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/squeeze.cpp
                        # && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_squeeze.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_squeeze.bc
                        # && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_squeeze.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_expand_dims.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expand_dims.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_expand_dims.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_expand_dims.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_expand_dims.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        # &&
                        # ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        # -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flip.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/flip.cpp
                        # && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flip.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flip.bc
                        # && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_flip.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_tile.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tile.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_tile.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_tile.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_tile.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                        &&
                        ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                        -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_where.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/kernels/where.cpp
                        && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_where.spv ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_where.bc
                        && cd ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ && xxd -i nm_cl_where.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                    BYPRODUCTS
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/relu6.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/prelu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/celu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/elu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardshrink.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardswish.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/hardtanh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/leaky_relu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log_sigmoid.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/mish.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/selu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sigmoid.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/silu.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softplus.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softshrink.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/softsign.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanhshrink.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccos.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arccosh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsin.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arcsinh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctan.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/arctanh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cbrt.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ceil.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cos.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cosh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/exp2.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/expm1.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/fabs.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/floor.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/invert.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isfinite.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isinf.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/isnan.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log2.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/log1p.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/negative.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/positive.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/reciprocal.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/rint.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/signbit.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sin.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sinh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/sqrt.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/square.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tan.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/tanh.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/trunc.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_add.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_add.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_broadcast_to.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_broadcast_to.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_multiply.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_multiply.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_subtract.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_subtract.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_divide.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_divide.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_transpose.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_transpose.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_repeat.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_repeat.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pad.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pad.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_resize.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_resize.spv
                        # TODO: enable pooling
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pooling.bc
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_pooling.spv
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flatten.bc
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flatten.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_1d.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_1d.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_2d.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_atleast_2d.spv
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_reshape.bc
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_reshape.spv
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_squeeze.bc
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_squeeze.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_expand_dims.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_expand_dims.spv
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flip.bc
                        # ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_flip.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_tile.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_tile.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_where.bc
                        ${CMAKE_CURRENT_SOURCE_DIR}/kernels/nm_cl_where.spv
                        ${CMAKE_CURRENT_SOURCE_DIR}/../../include/nmtools/array/eval/opencl/kernels_spv.hpp
                    )
        endif () # CMAKE_CXX_COMPILER_ID
endif (NMTOOLS_OPENCL_TEST_UFUNC)

if (NMTOOLS_OPENCL_TEST_INDEX)
    set(NMTOOLS_OPENCL_TEST_SOURCES ${NMTOOLS_OPENCL_TEST_SOURCES}
        index/broadcast_to.cpp
        index/logical_not.cpp
        index/nonzero.cpp
        index/broadcast_shape.cpp
        index/gather.cpp
        index/compute_strides.cpp
        index/compute_indices.cpp
        index/repeat.cpp
        index/transpose.cpp
        index/product.cpp
        index/resize.cpp
        index/pooling.cpp
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_custom_target( ${PROJECT_NAME}-build-index-tests
            ALL
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_to.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/broadcast_to.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_to.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_to.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_broadcast_to.spv > ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_logical_not.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/logical_not.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_logical_not.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_logical_not.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_logical_not.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_nonzero.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/nonzero.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_nonzero.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_nonzero.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_nonzero.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_shape.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/broadcast_shape.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_shape.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_shape.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_broadcast_shape.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_gather.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/gather.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_gather.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_gather.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_gather.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_strides.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/compute_strides.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_strides.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_strides.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_compute_strides.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_indices.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/compute_indices.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_indices.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_indices.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_compute_indices.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_offset.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/compute_offset.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_offset.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_compute_offset.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_compute_offset.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_repeat.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/repeat.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_repeat.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_repeat.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_repeat.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_transpose.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/transpose.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_transpose.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_transpose.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_transpose.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_product.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/product.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_product.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_product.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_product.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_resize.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/resize.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_resize.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_resize.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_resize.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
                &&
                ${CMAKE_CXX_COMPILER} ${NMTOOLS_OPENCL_MACROS} ${OPENCL_KHR_EXTENSIONS} -I${NMTOOLS_INCLUDE_DIR} ${CLANG_OPENCL_ARGS}
                -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_pooling.bc -x cl -c ${CMAKE_CURRENT_SOURCE_DIR}/index/pooling.cpp
                && llvm-spirv ${LLVM_SPIRV_OPTIONS} -o ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_pooling.spv ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_pooling.bc
                && cd ${CMAKE_CURRENT_SOURCE_DIR}/index/ && xxd -i nm_cl_test_pooling.spv >> ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
            BYPRODUCTS
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_to.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_to.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_logical_not.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_logical_not.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_nonzero.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_nonzero.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_shape.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_broadcast_shape.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_repeat.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_repeat.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_transpose.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_transpose.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_product.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_product.spv
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_pooling.bc
                ${CMAKE_CURRENT_SOURCE_DIR}/index/nm_cl_test_pooling.spv
        )
    endif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
endif (NMTOOLS_OPENCL_TEST_INDEX)
find_package(OpenCL REQUIRED)

add_executable(${PROJECT_NAME}-doctest tests.cpp
    ${NMTOOLS_OPENCL_TEST_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/kernels.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_dependencies(${PROJECT_NAME}-doctest ${PROJECT_NAME}-build-kernels)
    if (NMTOOLS_OPENCL_TEST_INDEX) 
    add_dependencies(${PROJECT_NAME}-doctest ${PROJECT_NAME}-build-index-tests)
    endif ()
endif ()
target_link_libraries(${PROJECT_NAME}-doctest PRIVATE OpenCL)

target_compile_features(${PROJECT_NAME}-doctest PRIVATE cxx_std_17)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE _GLIBCXX_DEBUG)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()

target_include_directories(
    ${PROJECT_NAME}-doctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (NMTOOLS_CODE_COVERAGE)
    target_link_libraries(${PROJECT_NAME}-doctest PUBLIC coverage_config)
endif (NMTOOLS_CODE_COVERAGE)