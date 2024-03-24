set(CMAKE_C_COMPILER /usr/local/bin/syclcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/syclcc)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    -fopenmp
    --acpp-targets="generic"
    --acpp-clang=/usr/bin/clang++-14
)
add_link_options(
    --acpp-targets="generic"
    --acpp-clang=/usr/bin/clang++-14
)
# To avoid linking device code with assert
add_compile_definitions(NMTOOLS_NOASSERT NMTOOLS_DISABLE_STL)
link_libraries(rt pthread)