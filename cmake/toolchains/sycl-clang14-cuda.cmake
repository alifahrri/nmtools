set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
if (ACPP_CLANG_VERSION)
    message("Using clang version for acpp: '${ACPP_CLANG_VERSION}'")
else ()
    set(ACPP_CLANG_VERSION 18)
endif ()
if (ACPP_TARGETS)
    message("Using acpp-targets='${ACPP_TARGETS}'")
else ()
    set(ACPP_TARGETS "cuda:sm_86")
endif ()
add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
)
add_link_options(
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
)
set(NMTOOLS_TEST_CUDA_PATH "/usr/local/cuda/" CACHE STRING "manually set cuda path")
link_directories("${NMTOOLS_TEST_CUDA_PATH}/lib64")
link_libraries(cudart_static dl rt pthread)