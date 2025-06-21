#include "nmtools/array/sum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define SUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    /* using test case from reduce_add since they're basically the same */ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto result = nmtools::view::sum(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sum(case1)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case1,   a, axis );
    SUM_SUBCASE( case1, a_a, axis );
    // TODO: drop support for nested vector
    // SUM_SUBCASE( case1, a_v, axis );
    SUM_SUBCASE( case1, a_f, axis );
    // not yet supported,
    // cant figure out apply_slice for dynamic dim array yet
    // SUM_SUBCASE( case1, a_d, axis );
    SUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("sum(case2)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case2,   a, axis );
    SUM_SUBCASE( case2, a_a, axis );
    // SUM_SUBCASE( case2, a_v, axis );
    SUM_SUBCASE( case2, a_f, axis );
    SUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("sum(case3)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case3,   a, axis );
    SUM_SUBCASE( case3, a_a, axis );
    // SUM_SUBCASE( case3, a_v, axis );
    SUM_SUBCASE( case3, a_f, axis );
    SUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("sum(case4)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case4,   a,   axis );
    SUM_SUBCASE( case4, a_a, axis_a );
    // SUM_SUBCASE( case4, a_v, axis_v );
    SUM_SUBCASE( case4, a_f, axis_f );
    SUM_SUBCASE( case4, a_h, axis_h );
}

TEST_CASE("sum(case5)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case5,   a,   axis );
    SUM_SUBCASE( case5, a_a, axis_a );
    // SUM_SUBCASE( case5, a_v, axis_v );
    SUM_SUBCASE( case5, a_f, axis_f );
    SUM_SUBCASE( case5, a_h, axis_h );
}

TEST_CASE("sum(case6)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case6,   a,   axis );
    SUM_SUBCASE( case6, a_a, axis_a );
    // SUM_SUBCASE( case6, a_v, axis_v );
    SUM_SUBCASE( case6, a_f, axis_f );
    SUM_SUBCASE( case6, a_h, axis_h );
}

TEST_CASE("sum(case7)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case7,   a, axis, dtype );
    SUM_SUBCASE( case7, a_a, axis, dtype );
    // SUM_SUBCASE( case7, a_v, axis, dtype );
    SUM_SUBCASE( case7, a_f, axis, dtype );
    SUM_SUBCASE( case7, a_h, axis, dtype );
}

TEST_CASE("sum(case8)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case8,   a, axis, dtype, initial );
    SUM_SUBCASE( case8, a_a, axis, dtype, initial );
    // SUM_SUBCASE( case8, a_v, axis, dtype, initial );
    SUM_SUBCASE( case8, a_f, axis, dtype, initial );
    SUM_SUBCASE( case8, a_h, axis, dtype, initial );
}

TEST_CASE("sum(case9)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case10)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case11)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case12)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case13)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case13,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case13, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case13, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case14)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case14,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_a, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case14, a_v, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_f, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case14, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case15)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case15,   a, axis );
    SUM_SUBCASE( case15, a_a, axis );
    // SUM_SUBCASE( case15, a_v, axis );
    SUM_SUBCASE( case15, a_f, axis );
    SUM_SUBCASE( case15, a_h, axis );
}

TEST_CASE("sum(case16)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case16,   a, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_a, axis, nmtools::None, initial );
    // SUM_SUBCASE( case16, a_v, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_f, axis, nmtools::None, initial );
    SUM_SUBCASE( case16, a_h, axis, nmtools::None, initial );
}

TEST_CASE("sum(case17)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case17,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_a, axis, nmtools::None, initial, keepdims );
    // SUM_SUBCASE( case17, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case17, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case18)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case18,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_a, axis, nmtools::None, initial, keepdims );
    // SUM_SUBCASE( case18, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case18, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case19)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case19,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_a, axis, nmtools::None, initial, keepdims );
    // SUM_SUBCASE( case19, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case19, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case20)" * doctest::test_suite("view::sum"))
{
    SUM_SUBCASE( case20,   a, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_a, axis, nmtools::None, initial, keepdims );
    // SUM_SUBCASE( case20, a_v, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_f, axis, nmtools::None, initial, keepdims );
    SUM_SUBCASE( case20, a_h, axis, nmtools::None, initial, keepdims );
}

TEST_CASE("sum(case25)" * doctest::test_suite("view::sum"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;

    SUBCASE("meta")
    {
        NMTOOLS_TESTING_USE_CASE( view, reduce_add, case25 );
        {
            auto result = nmtools::view::sum(a,axis,dtype,initial,keepdims);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
        {
            auto result = nmtools::view::sum(a_a,axis,dtype,initial,keepdims);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
        {
            auto result = nmtools::view::sum(a_f,axis,dtype,initial,keepdims);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
        // {
        //     auto result = nmtools::view::sum(a_d,axis,dtype,initial,keepdims);
        //     using result_t = decltype(result);
        //     NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        // }
        {
            auto result = nmtools::view::sum(a_h,axis,dtype,initial,keepdims);
            using result_t = decltype(result);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_num, result_t );
        }
    }

    SUM_SUBCASE( case25,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case25, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case25, a_f, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case25, a_d, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case25, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case26)" * doctest::test_suite("view::sum"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;

    SUM_SUBCASE( case26,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case26, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case26, a_f, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case26, a_d, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case26, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("sum(case27)" * doctest::test_suite("view::sum"))
{
    auto dtype   = nmtools::None;
    auto initial = nmtools::None;

    SUM_SUBCASE( case27,   a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case27, a_a, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case27, a_f, axis, dtype, initial, keepdims );
    // SUM_SUBCASE( case27, a_d, axis, dtype, initial, keepdims );
    SUM_SUBCASE( case27, a_h, axis, dtype, initial, keepdims );
}