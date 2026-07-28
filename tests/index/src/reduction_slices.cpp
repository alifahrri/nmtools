#include "nmtools/index/reduce.hpp"
#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/data/index/reduction_slices.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

#define REDUCTION_SLICES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, reduction_slices, case_name); \
    using namespace args; \
    auto result = nmtools::index::reduction_slices(__VA_ARGS__); \
    NMTOOLS_ASSERT_APPLY_EQUAL( result, expect::result ); \
}

TEST_CASE("reduction_slices(case1)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case1, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case1, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case1, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case1, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case1, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case2)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case2, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case2, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case2, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case2, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case2, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case3)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case3, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case3, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case3, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case3, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case3, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case4)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case4, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case4, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case4, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case4, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case4, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case5)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case5, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case5, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case5, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case5, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case5, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case6)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case6, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case6, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case6, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case6, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case6, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case7)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case7, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case7, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case7, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case7, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case7, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case8)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case8, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case8, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case8, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case8, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case8, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case9)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case9, indices, shape, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case9, indices, shape_ct, axis, keepdims);
}

TEST_CASE("reduction_slices(case10)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case10, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case10, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case10, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case10, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case10, indices_ct, shape_ct, axis, keepdims);
}

TEST_CASE("reduction_slices(case11)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case11, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case11, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case11, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case11, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case11, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case12)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case12, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case12, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case12, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case12, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case12, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case13)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case13, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case13, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case13, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case13, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case13, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case14)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case14, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case14, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case14, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case14, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case14, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case15)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case15, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case15, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case15, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case15, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case15, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case16)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case16, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case16, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case16, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case16, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case16, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case17)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case17, indices, shape, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case17, indices, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case18)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case18, indices, shape, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case18, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case19)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case19, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case19, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case19, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case19, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case19, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case20)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case20, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case20, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case20, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case20, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case20, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case21)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case21, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case21, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case21, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case21, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case21, indices_ct, shape_ct, axis_ct, keepdims);
}

TEST_CASE("reduction_slices(case22)" * doctest::test_suite("index::reduction_slices"))
{
    REDUCTION_SLICES_SUBCASE(case22, indices, shape, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case22, indices_a, shape_a, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case22, indices_v, shape_v, axis, keepdims);
    REDUCTION_SLICES_SUBCASE(case22, indices_f, shape_f, axis, keepdims);

    REDUCTION_SLICES_SUBCASE(case22, indices_ct, shape_ct, axis_ct, keepdims);
}
