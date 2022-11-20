cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

add_library(nmtools-demo SHARED
            src/nmtools-demo.cpp)

target_include_directories(nmtools-demo PRIVATE
                           include)

target_compile_options(nmtools-demo PRIVATE -std=c++17)

target_link_libraries(nmtools-demo
                      android
                      log)
