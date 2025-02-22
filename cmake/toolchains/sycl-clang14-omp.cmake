set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

SET (CMAKE_C_COMPILER_WORKS 1)

if (ACPP_CLANG_VERSION)
    message("Using clang version for acpp: '${ACPP_CLANG_VERSION}'")
else ()
    set(ACPP_CLANG_VERSION 18)
endif ()

if (ACPP_TARGETS)
    message("Using acpp-targets='${ACPP_TARGETS}'")
else ()
    set(ACPP_TARGETS "omp")
endif ()

add_compile_options(-W -Wall -Werror -Wextra -Wno-gnu-string-literal-operator-template -fopenmp
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
)
add_link_options(
    --acpp-targets="${ACPP_TARGETS}"
    --acpp-clang=/usr/bin/clang++-${ACPP_CLANG_VERSION}
)