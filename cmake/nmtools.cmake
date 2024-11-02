function(apply_nmtools)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs COMPILE_OPTIONS)
    cmake_parse_arguments(apply_nmtools
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        "${ARGN}"
    )

    message(STATUS "apply nmtools ...")
    message(STATUS "    TARGET: ${apply_nmtools_TARGET}")
    message(STATUS "    COMPILE_OPTIONS: ${apply_nmtools_COMPILE_OPTIONS}")

    if(NMTOOLS_INCLUDE_DIR)
        message(STATUS "    NMTOOLS_INCLUDE_DIR: ${NMTOOLS_INCLUDE_DIR}")
    else()
        message(STATUS "trying to find nmtools")
        find_package(nmtools REQUIRED CONFIG)
        set(NMTOOLS_INCLUDE_DIR ${nmtools_INCLUDE_DIRS})
        message(STATUS "    NMTOOLS_INCLUDE_DIR: ${NMTOOLS_INCLUDE_DIR}")
    endif()

    target_compile_options(
        ${apply_nmtools_TARGET}
        PRIVATE
        -std=c++17
    )

    target_include_directories(
        ${apply_nmtools_TARGET}
        PRIVATE
        ${NMTOOLS_INCLUDE_DIR}
    )

    if(apply_nmtools_COMPILE_OPTIONS)
        target_compile_options(
            ${apply_nmtools_TARGET}
            PRIVATE
            ${apply_nmtools_COMPILE_OPTIONS}
        )
    endif()

endfunction()