#include "nmtools/array/swapaxes.hpp"
#include "nmtools/testing/data/index/swapaxes.hpp"
#include "nmtools/testing/doctest.hpp"

#define SWAPAXES_TO_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, swapaxes_to_transpose, case_name ); \
    using namespace args; \
    auto result = nmtools::index::swapaxes_to_transpose(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::result, __VA_ARGS__ ); \
}

TEST_CASE("swapaxes_to_transpose(case1)" * doctest::test_suite("index::swapaxes_to_transpose"))
{
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case1, src_dim, axis1, axis2 );
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case1, src_dim_ct, axis1_ct, axis2_ct );
}

TEST_CASE("swapaxes_to_transpose(case2)" * doctest::test_suite("index::swapaxes_to_transpose"))
{
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case2, src_dim, axis1, axis2 );
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case2, src_dim_ct, axis1_ct, axis2_ct );
}

TEST_CASE("swapaxes_to_transpose(case3)" * doctest::test_suite("index::swapaxes_to_transpose"))
{
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case3, src_dim, axis1, axis2 );
    SWAPAXES_TO_TRANSPOSE_SUBCASE( case3, src_dim_ct, axis1_ct, axis2_ct );
}