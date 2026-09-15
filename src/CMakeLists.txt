add_library(nmtoolsrt STATIC
    graph/ndarray.cpp
    graph/add.cpp
    graph/broadcast_to.cpp
    graph/multiply.cpp
    graph/subtract.cpp
    graph/divide.cpp

    cpu/cpu.cpp
    cpu/add.cpp
    cpu/multiply.cpp
    cpu/subtract.cpp
    cpu/divide.cpp
)

target_include_directories(nmtoolsrt PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(nmtoolsrt PUBLIC cxx_std_17)
