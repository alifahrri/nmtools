#include "nmtools/array/view/convnd.hpp"
#include "nmtools/testing/data/index/convnd.hpp"
#include "nmtools/testing/doctest.hpp"

#define CONV_RESHAPE_INPUT(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,conv_reshape_input,case_name); \
    using namespace args; \
    auto result = nmtools::index::conv_reshape_input(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONV_RESHAPE_WEIGHT(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,conv_reshape_weight,case_name); \
    using namespace args; \
    auto result = nmtools::index::conv_reshape_weight(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONV_REDUCE_AXIS(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,conv_reduce_axis,case_name); \
    using namespace args; \
    auto result = nmtools::index::conv_sum_axes(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONV_RESHAPE_REDUCE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,conv_reshape_reduce,case_name); \
    using namespace args; \
    auto result = nmtools::index::conv_reshape_reduce(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define CONV_KERNEL_SIZE(case_name,...) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,conv_kernel_size,case_name); \
    using namespace args; \
    auto result = nmtools::index::conv_kernel_size(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("conv_reshape_input(case1)" * doctest::test_suite("index::conv_reshape_input"))
{
    CONV_RESHAPE_INPUT( case1, src_shape, groups, n_planes );
    CONV_RESHAPE_INPUT( case2, src_shape, groups, n_planes );
    CONV_RESHAPE_INPUT( case3, src_shape, groups, n_planes );
}

TEST_CASE("conv_reshape_weight(case1)" * doctest::test_suite("index::conv_reshape_weight"))
{
    CONV_RESHAPE_WEIGHT( case1, src_shape, groups, n_planes );
    CONV_RESHAPE_WEIGHT( case2, src_shape, groups, n_planes );
    CONV_RESHAPE_WEIGHT( case3, src_shape, groups, n_planes );
    CONV_RESHAPE_WEIGHT( case4, src_shape, groups, n_planes );
    CONV_RESHAPE_WEIGHT( case5, src_shape, groups, n_planes );
}

TEST_CASE("conv_reduce_axis(case1)" * doctest::test_suite("index::conv_reduce_axis"))
{
    CONV_REDUCE_AXIS( case1, n_planes );
}

TEST_CASE("conv_reduce_axis(case2)" * doctest::test_suite("index::conv_reduce_axis"))
{
    CONV_REDUCE_AXIS( case2, n_planes );
}

TEST_CASE("conv_reshape_reduce(case1)" * doctest::test_suite("index::conv_reshape_reduce"))
{
    CONV_RESHAPE_REDUCE( case1, src_shape, groups, n_planes );
    CONV_RESHAPE_REDUCE( case2, src_shape, groups, n_planes );
    CONV_RESHAPE_REDUCE( case3, src_shape, groups, n_planes );
    CONV_RESHAPE_REDUCE( case4, src_shape, groups, n_planes );
}

TEST_CASE("conv_kernel_size(case1)" * doctest::test_suite("index::conv_kernel_size"))
{
    CONV_KERNEL_SIZE( case1, weight_shape, n_planes );
    CONV_KERNEL_SIZE( case2, weight_shape, n_planes );
}