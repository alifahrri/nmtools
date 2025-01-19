cmake_minimum_required(VERSION 3.13)
project(numeric-tests-circle)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package(nmtools REQUIRED CONFIG)
    set(${NMTOOLS_INCLUDE_DIR} ${nmtools_INCLUDE_DIRS})
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
endif()

include(nmtools)

include(FetchContent)
FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        v0.7 #suggest using a tag so the library doesn't update whenever new commits are pushed to a branch
)
FetchContent_MakeAvailable(fetch_vk_bootstrap)

# optionally use boost (esp. for type_id)
find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

option(NMTOOLS_CIRCLE_TEST_ALL "test all circle modules" ON)
set(NMTOOLS_CIRCLE_TEST_SOURCES "")

set(NMTOOLS_CIRCLE_TEST_SOURCES
    array/activations/relu.cxx
)

add_executable(${PROJECT_NAME}-doctest tests.cpp ${NMTOOLS_CIRCLE_TEST_SOURCES})

set_source_files_properties(${NMTOOLS_CIRCLE_TEST_SOURCES} PROPERTIES COMPILE_FLAGS -shader)
set_source_files_properties(tests.cpp PROPERTIES COMPILE_FLAGS -shader)

set(NMTOOLS_TEST_CIRCLE_ARGS "" CACHE STRING "manually set extra circle args")

target_compile_options(${PROJECT_NAME}-doctest PRIVATE --std=c++17 ${NMTOOLS_TEST_CIRCLE_ARGS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME}-doctest PRIVATE -g)
    ## causes crash in circle
    # target_compile_definitions(${PROJECT_NAME}-doctest PRIVATE _GLIBCXX_DEBUG)
endif()
if (doctest_FOUND)
    target_link_libraries(${PROJECT_NAME}-doctest PRIVATE doctest::doctest)
endif ()
target_link_libraries(${PROJECT_NAME}-doctest
    glfw
    vulkan
    dl
    pthread
)
target_link_libraries(${PROJECT_NAME}-doctest vk-bootstrap::vk-bootstrap)