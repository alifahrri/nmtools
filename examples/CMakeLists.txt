add_executable(
    ${PROJECT_NAME}-spline
    src/spline.cpp
)

set_target_properties(
    ${PROJECT_NAME}-spline
    PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(
    ${PROJECT_NAME}-spline PRIVATE
    -g
)