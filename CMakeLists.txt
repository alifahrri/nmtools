cmake_minimum_required(VERSION 3.0.2)
project(nmtools)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(nmtools)

set(${PROJECT_NAME}_VERSION 0.1.0-alpha)
message(STATUS "nmtools v${${PROJECT_NAME}_VERSION}")

# Build
# =====

set(NMTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NMTOOLS_HEADERS
    ${NMTOOLS_INCLUDE_DIR}/nmtools/curvefit/sinusoid.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/curvefit/spline.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/differentiation/finite.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/fourier/series.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/fourier/transform.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/integration/trapezoidal.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/linalg/decomposition.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/linalg/elimination.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/linalg/matvec.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/ode/euler.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/runge_kutta.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/optimization/unconstrained.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/roots/bracketing.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/roots/open.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/taylor/taylor.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/utility/helper.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/curvefit.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/differentiation.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/fourier.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/integration.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/linalg.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/meta.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/ode.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/optimization.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/roots.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/taylor.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/traits.hpp
    ${NMTOOLS_INCLUDE_DIR}/nmtools/utility.hpp
)

add_library(nmtools INTERFACE)
target_include_directories(
    nmtools INTERFACE
    $<BUILD_INTERFACE:${NMTOOLS_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

option(BUILD_TESTS "build tests programs" ON)
option(BUILD_EXAMPLES "build example programs" OFF)
option(BUILD_BENCHMARKS "build benchmark programs" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif(BUILD_BENCHMARKS)

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS nmtools
    EXPORT ${PROJECT_NAME}-targets
)

export(
    EXPORT ${PROJECT_NAME}-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
)

install(
    DIRECTORY ${NMTOOLS_INCLUDE_DIR}/nmtools
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(NMTOOLS_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for nmtoolsConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${NMTOOLS_CMAKECONFIG_INSTALL_DIR}
)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${NMTOOLS_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${NMTOOLS_CMAKECONFIG_INSTALL_DIR})

configure_file(${PROJECT_NAME}.pc.in
               "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
                @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
