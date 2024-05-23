#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);

#include "nmtools/array/array/broadcast_arrays.hpp"
#include "nmtools/testing/data/constexpr/broadcast_arrays.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(constexpr_broadcast_arrays, case_name); \
    using namespace args; \
    constexpr auto results = nmtools::array::broadcast_arrays(__VA_ARGS__); \
    constexpr auto N = meta::len_v<decltype(nm::unwrap(results))>; \
    meta::template_for<N>([&](auto index){ \
        constexpr auto i = decltype(index)::value; \
        constexpr auto array       = nmtools::get<i>(nm::unwrap(results)); \
        constexpr auto expected    = nmtools::get<i>(expect::expected); \
        NMTOOLS_STATIC_ASSERT_EQUAL( nmtools::shape(array), expect::shape ); \
        NMTOOLS_STATIC_ASSERT_CLOSE( array, expected ); \
    }); \
}

TEST_CASE("broadcast_arrays(case1)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_ls_hb );

    // can't be constexpr because can't infer bounded size of data buffer
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_hs_hb );
    #endif

    // can't be constexpr because contains 1 in constant-shape (lhs)
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_ls_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_ls_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case2)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_ls_hb );
}

TEST_CASE("broadcast_arrays(case3)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_ls_hb );
}

TEST_CASE("broadcast_arrays(case4)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_ls_hb );
}

TEST_CASE("broadcast_arrays(case5)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_a, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_f, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_h, B_h, C_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_fb, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_ls_hb, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_ls_hb, C_ls_hb );
}

TEST_CASE("broadcast_arrays(case6)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_a, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_f, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_h, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_ls_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_hb, rhs );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_fb, rhs );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_hb, rhs );
}

TEST_CASE("broadcast_arrays(case7)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_hb );
}

TEST_CASE("broadcast_arrays(case8)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case8, lhs, rhs );
}

TEST_CASE("broadcast_arrays(case9)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_h, C_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case9, A, B_ls_hb, C_ls_hb );
}

TEST_CASE("broadcast_arrays(case10)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case10, A, B );
}

TEST_CASE("broadcast_arrays(case11)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_a, C_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_f, C_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_h, C_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_ls_hb );



    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_fs_hb );

    // NOTE: currently unsupported by index::broadcast_shape
    // mixed constant index vs runtime index when computing result
    #if 0
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_fb, C_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_cs_hb, C_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_fb, C_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case11, A, B_ls_hb, C_hs_hb );
    #endif
}

TEST_CASE("broadcast_arrays(case12)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_cs_hb, rhs_ls_hb );

    // rhs has max size info at compile time
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_hb, rhs_cs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_fs_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_hb, rhs_cs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case12, lhs_hs_hb, rhs_ls_hb );
}

TEST_CASE("broadcast_arrays(case13)" * doctest::test_suite("array::constexpr_broadcast_arrays"))
{
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_a, rhs_a );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_f, rhs_f );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_h, rhs_h );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_ls_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_cs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_cs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_ls_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_ls_hb );

    // lhs has max size info at compile time
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_fs_hb );
    
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_fs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_fs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_cs_hb, rhs_hs_hb );

    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_fb, rhs_hs_fb );
    CONSTEXPR_BROADCAST_ARRAYS_SUBCASE(case13, lhs_ls_hb, rhs_hs_hb );
}