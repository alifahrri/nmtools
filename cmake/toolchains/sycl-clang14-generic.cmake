set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

if (ACPP_CLANG_VERSION)
    message("Using clang version for acpp: '${ACPP_CLANG_VERSION}'")
else ()
    set(ACPP_CLANG_VERSION 18)
endif ()

if (ACPP_TARGETS)
    message("Using acpp-targets='${ACPP_TARGETS}'")
else ()
    set(ACPP_TARGETS "generic")
endif ()

add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
    -Wno-unknown-cuda-version
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    -fopenmp
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
)
add_link_options(
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
    -fopenmp
)
# To avoid linking device code with assert
add_compile_definitions(NMTOOLS_NOASSERT NMTOOLS_DISABLE_STL)
link_libraries(rt pthread)