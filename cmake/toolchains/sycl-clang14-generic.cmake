set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    -fopenmp
    --acpp-targets="generic"
    # TODO: make clang version configurable?
    --acpp-clang=/usr/bin/clang++-18
)
add_link_options(
    --acpp-targets="generic"
    --acpp-clang=/usr/bin/clang++-18
    -fopenmp
)
# To avoid linking device code with assert
add_compile_definitions(NMTOOLS_NOASSERT NMTOOLS_DISABLE_STL)
link_libraries(rt pthread)