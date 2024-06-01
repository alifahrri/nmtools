#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/testing/data/index/compute_indices.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define COMPUTE_INDICES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_indices, case_name); \
    using namespace args; \
    auto indices = nmtools::index::compute_indices(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( indices, expect::indices, __VA_ARGS__ ); \
}

TEST_CASE("compute_indices(case1)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case1_2d, offset, shape_ls_fb);

    COMPUTE_INDICES_SUBCASE(case1_2d, offset_ct, shape_ct);
}

TEST_CASE("compute_indices(case1)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case1_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case2)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case2_2d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case2)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case2_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case3)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case3_2d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case3)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case3_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case4)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case4_2d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case4)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case4_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case5)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case5_2d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case5)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case5_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case6)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case6_2d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case6)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case6_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case7)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case7_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case8)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case8_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case9)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case9_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case10)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case10_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case11)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case11_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case12)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case12_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case13)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case13_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case14)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case14_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case15)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case15_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case16)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case16_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case17)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case17_3d, offset, shape_ls_fb);
}

TEST_CASE("compute_indices(case18)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_a);
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_v);
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_f);
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_h);
    COMPUTE_INDICES_SUBCASE(case18_3d, offset, shape_ls_fb);
}