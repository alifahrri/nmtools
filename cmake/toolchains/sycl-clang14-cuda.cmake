set(CMAKE_C_COMPILER /usr/local/bin/syclcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/syclcc)

SET (CMAKE_C_COMPILER_WORKS 1)
add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    --acpp-targets="cuda:sm_60"
    --acpp-clang=/usr/bin/clang++-14
)
set(NMTOOLS_TEST_CUDA_PATH "/usr/local/cuda/" CACHE STRING "manually set cuda path")
link_directories("${NMTOOLS_TEST_CUDA_PATH}/lib64")
link_libraries(cudart_static dl rt pthread)