#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/data/index/pooling.hpp"
#include "nmtools/testing/doctest.hpp"

#define POOL_PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, pool_pad, case_name); \
    using namespace args; \
    auto result = nmtools::index::pool_pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::expected, __VA_ARGS__ ); \
}

#define POOL_PADDING_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, pool_padding, case_name); \
    using namespace args; \
    auto result = nmtools::index::pool_padding(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("pool_pad(case1)" * doctest::test_suite("index::pool_pad"))
{
    POOL_PAD_SUBCASE(case1, src_shape, kernel_size, stride );
    POOL_PAD_SUBCASE(case1, src_shape_a, kernel_size_a, stride_a );
    POOL_PAD_SUBCASE(case1, src_shape_v, kernel_size_v, stride_v );
    POOL_PAD_SUBCASE(case1, src_shape_f, kernel_size_f, stride_f );
    POOL_PAD_SUBCASE(case1, src_shape_h, kernel_size_h, stride_h );

    POOL_PAD_SUBCASE(case1, m_src_shape_a, kernel_size_a, stride_a );
}

TEST_CASE("pool_padding(case1)" * doctest::test_suite("index::pool_padding"))
{
    POOL_PADDING_SUBCASE(case1, src_shape, padding );
    POOL_PADDING_SUBCASE(case1, src_shape_a, padding_a );
    POOL_PADDING_SUBCASE(case1, src_shape_v, padding_v );
    POOL_PADDING_SUBCASE(case1, src_shape_f, padding_f );
    POOL_PADDING_SUBCASE(case1, src_shape_h, padding_h );
}

TEST_CASE("pool_padding(case2)" * doctest::test_suite("index::pool_padding"))
{
    POOL_PADDING_SUBCASE(case2, src_shape, padding );
    POOL_PADDING_SUBCASE(case2, src_shape_a, padding_a );
    POOL_PADDING_SUBCASE(case2, src_shape_v, padding_v );
    POOL_PADDING_SUBCASE(case2, src_shape_f, padding_f );
    POOL_PADDING_SUBCASE(case2, src_shape_h, padding_h );
}