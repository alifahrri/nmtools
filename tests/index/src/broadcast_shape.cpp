#include "nmtools/index/broadcast_shape.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/index/broadcast_shape.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;

#define BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(broadcast_shape, case_name); \
    using namespace args; \
    const auto result = nmtools::index::broadcast_shape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

#define CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(broadcast_shape, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::index::broadcast_shape(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("broadcast_shape(case1)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a, b);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_sv);

    BROADCAST_SHAPE_SUBCASE(case1, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case1)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case1, a, b);
}

TEST_CASE("broadcast_shape(case2)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_sv);

    BROADCAST_SHAPE_SUBCASE(case2, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case2)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case2, a, b);
}

TEST_CASE("broadcast_shape(case3)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_sv);

    BROADCAST_SHAPE_SUBCASE(case3, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case3)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case3, a, b);
}

TEST_CASE("broadcast_shape(case4)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_sv);

    BROADCAST_SHAPE_SUBCASE(case4, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case4)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case4, a, b);
}

TEST_CASE("broadcast_shape(case5)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_sv);

    BROADCAST_SHAPE_SUBCASE(case5, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case5)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case5, a, b);
}

TEST_CASE("broadcast_shape(case6)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_sv);

    // results in error type (as it should be)
    // TODO: provide isequal for error type (?)
    // BROADCAST_SHAPE_SUBCASE(case6, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case6)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case6, a, b);
}

TEST_CASE("broadcast_shape(case7)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_sv);

    // results in error type (as it should be)
    // TODO: provide isequal for error type (?)
    // BROADCAST_SHAPE_SUBCASE(case7, a_ct, b_ct);
}

TEST_CASE("constexpr_broadcast_shape(case7)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case7, a, b);
}

TEST_CASE("broadcast_shape(case8)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_ct, b_ct, c_ct);
}

TEST_CASE("constexpr_broadcast_shape(case8)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case8, a, b, c);
}

TEST_CASE("broadcast_shape(case9)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);

    //
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);

    // results in error type (as it should be)
    // TODO: provide isequal for error type (?)
    // BROADCAST_SHAPE_SUBCASE(case9, a_ct, b_ct, c_ct);
}

TEST_CASE("constexpr_broadcast_shape(case9)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case9, a, b, c);
}

TEST_CASE("broadcast_shape(case10)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);

    //
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_ct, b_ct, c_ct, d_ct);
}

TEST_CASE("constexpr_broadcast_shape(case10)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case10, a, b, c, d);
}

TEST_CASE("broadcast_shape(case11)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);

    //
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_ct, b_ct, c_ct, d_ct, e_ct, f_ct, g_ct);
}

TEST_CASE("constexpr_broadcast_shape(case11)" * doctest::test_suite("index::broadcast_shape"))
{
    CONSTEXPR_BROADCAST_SHAPE_SUBCASE(case11, a, b, c, d, e, f, g);
}