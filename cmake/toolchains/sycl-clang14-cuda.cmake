set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    --acpp-targets="cuda:sm_86"
    --acpp-clang=/usr/bin/clang++
)
add_link_options(
    --acpp-targets="cuda:sm_86"
    --acpp-clang=/usr/bin/clang++
)
set(NMTOOLS_TEST_CUDA_PATH "/usr/local/cuda/" CACHE STRING "manually set cuda path")
link_directories("${NMTOOLS_TEST_CUDA_PATH}/lib64")
link_libraries(cudart_static dl rt pthread)