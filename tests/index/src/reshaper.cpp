#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/data/index/reshaper.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nm::literals;

#define RESHAPER_INDICES_SUBCASE(case_name, expect_idx, dst_idx, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reshaper, case_name); \
    using namespace args; \
    auto r = nmtools::view::reshaper(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::has_value(r), true ); \
    auto result = nmtools::unwrap(r).indices(dst_idx); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::expect_idx, __VA_ARGS__, dst_idx ); \
}

TEST_CASE("reshaper::indices(case1)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case1, res00, idx00, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res01, idx01, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res10, idx10, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res11, idx11, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res20, idx20, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res21, idx21, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case1, res00, idx00, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res01, idx01, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res10, idx10, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res11, idx11, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res20, idx20, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res21, idx21, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case1, res00, idx00, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res01, idx01, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res10, idx10, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res11, idx11, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res20, idx20, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res21, idx21, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case1, res00, idx00, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res01, idx01, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res10, idx10, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res11, idx11, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res20, idx20, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case1, res21, idx21, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case1, res00, idx00_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case1, res01, idx01_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case1, res10, idx10_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case1, res11, idx11_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case1, res20, idx20_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case1, res21, idx21_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case2)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case2, res00, idx00, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res01, idx01, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res02, idx02, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res10, idx10, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res11, idx11, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res12, idx12, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case2, res00, idx00, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res01, idx01, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res02, idx02, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res10, idx10, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res11, idx11, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res12, idx12, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case2, res00, idx00, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res01, idx01, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res02, idx02, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res10, idx10, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res11, idx11, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res12, idx12, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case2, res00, idx00, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res01, idx01, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res02, idx02, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res10, idx10, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res11, idx11, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case2, res12, idx12, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case2, res00, idx00_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case2, res01, idx01_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case2, res02, idx02_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case2, res10, idx10_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case2, res11, idx11_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case2, res12, idx12_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case3)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case3, res00, idx00, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res01, idx01, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res05, idx05, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res10, idx10, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res15, idx15, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res35, idx35, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case3, res00, idx00, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res01, idx01, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res05, idx05, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res10, idx10, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res15, idx15, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res35, idx35, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case3, res00, idx00, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res01, idx01, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res05, idx05, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res10, idx10, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res15, idx15, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res35, idx35, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case3, res00, idx00, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res01, idx01, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res05, idx05, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res10, idx10, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res15, idx15, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case3, res35, idx35, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case3, res00, idx00_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case3, res01, idx01_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case3, res05, idx05_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case3, res10, idx10_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case3, res15, idx15_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case3, res35, idx35_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case4)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case4, res0, idx0, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res1, idx1, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res2, idx2, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res3, idx3, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res4, idx4, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res5, idx5, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case4, res0, idx0, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res1, idx1, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res2, idx2, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res3, idx3, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res4, idx4, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res5, idx5, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case4, res0, idx0, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res1, idx1, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res2, idx2, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res3, idx3, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res4, idx4, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res5, idx5, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case4, res0, idx0, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res1, idx1, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res2, idx2, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res3, idx3, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res4, idx4, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case4, res5, idx5, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case4, res0, idx0_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case4, res1, idx1_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case4, res2, idx2_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case4, res3, idx3_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case4, res4, idx4_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case4, res5, idx5_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case5)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case5, res00, idx00, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res01, idx01, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res03, idx03, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res10, idx10, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res20, idx20, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res23, idx23, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case5, res00, idx00, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res01, idx01, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res03, idx03, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res10, idx10, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res20, idx20, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res23, idx23, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case5, res00, idx00, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res01, idx01, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res03, idx03, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res10, idx10, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res20, idx20, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res23, idx23, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case5, res00, idx00, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res01, idx01, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res03, idx03, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res10, idx10, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res20, idx20, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case5, res23, idx23, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case5, res00, idx00_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case5, res01, idx01_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case5, res03, idx03_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case5, res10, idx10_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case5, res20, idx20_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case5, res23, idx23_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case6)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case6, res0, idx0, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res1, idx1, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res2, idx2, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res3, idx3, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res4, idx4, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res5, idx5, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case6, res0, idx0, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res1, idx1, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res2, idx2, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res3, idx3, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res4, idx4, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res5, idx5, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case6, res0, idx0, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res1, idx1, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res2, idx2, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res3, idx3, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res4, idx4, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res5, idx5, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case6, res0, idx0, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res1, idx1, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res2, idx2, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res3, idx3, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res4, idx4, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case6, res5, idx5, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case6, res0, idx0_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case6, res1, idx1_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case6, res2, idx2_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case6, res3, idx3_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case6, res4, idx4_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case6, res5, idx5_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case7)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case7, res000, idx000, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res001, idx001, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res012, idx012, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res100, idx100, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res110, idx110, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res112, idx112, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case7, res000, idx000, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res001, idx001, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res012, idx012, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res100, idx100, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res110, idx110, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res112, idx112, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case7, res000, idx000, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res001, idx001, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res012, idx012, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res100, idx100, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res110, idx110, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res112, idx112, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case7, res000, idx000, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res001, idx001, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res012, idx012, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res100, idx100, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res110, idx110, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case7, res112, idx112, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case7, res000, idx000_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case7, res001, idx001_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case7, res012, idx012_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case7, res100, idx100_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case7, res110, idx110_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case7, res112, idx112_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}

TEST_CASE("reshaper::indices(case8)" * doctest::test_suite("index::reshaper"))
{
    RESHAPER_INDICES_SUBCASE( case8, res00, idx00, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res03, idx03, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res05, idx05, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res10, idx10, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res13, idx13, src_shape, dst_shape, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res15, idx15, src_shape, dst_shape, src_size );

    RESHAPER_INDICES_SUBCASE( case8, res00, idx00, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res03, idx03, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res05, idx05, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res10, idx10, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res13, idx13, src_shape_a, dst_shape_a, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res15, idx15, src_shape_a, dst_shape_a, src_size );

    RESHAPER_INDICES_SUBCASE( case8, res00, idx00, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res03, idx03, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res05, idx05, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res10, idx10, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res13, idx13, src_shape_h, dst_shape_h, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res15, idx15, src_shape_h, dst_shape_h, src_size );

    RESHAPER_INDICES_SUBCASE( case8, res00, idx00, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res03, idx03, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res05, idx05, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res10, idx10, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res13, idx13, src_shape_v, dst_shape_v, src_size );
    RESHAPER_INDICES_SUBCASE( case8, res15, idx15, src_shape_v, dst_shape_v, src_size );

    RESHAPER_INDICES_SUBCASE( case8, res00, idx00_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case8, res03, idx03_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case8, res05, idx05_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case8, res10, idx10_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case8, res13, idx13_ct, src_shape_ct, dst_shape_ct, src_size_ct );
    RESHAPER_INDICES_SUBCASE( case8, res15, idx15_ct, src_shape_ct, dst_shape_ct, src_size_ct );
}
