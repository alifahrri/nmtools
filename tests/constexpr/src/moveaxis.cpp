#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb);

#include "nmtools/array/moveaxis.hpp"
#include "nmtools/testing/data/constexpr/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define CONSTEXPR_MOVEAXIS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, constexpr_moveaxis, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::moveaxis(__VA_ARGS__); \
    NMTOOLS_STATIC_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("moveaxis(case1)" * doctest::test_suite("array::constexpr_moveaxis"))
{

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_a, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_f, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_h, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case1, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case2, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_h, source, destination );


    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case3, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case4)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case4, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case5)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case5, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case6)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case6, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case7)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case7, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case8, a_hs_hb, source_ct, destination_ct );
}

TEST_CASE("moveaxis(case9)" * doctest::test_suite("array::constexpr_moveaxis"))
{
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_a, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_f, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_h, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_fb, source, destination );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_hb, source, destination );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_cs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_fs_hb, source_ct, destination_ct );

    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_fb, source_ct, destination_ct );
    CONSTEXPR_MOVEAXIS_SUBCASE( case9, a_hs_hb, source_ct, destination_ct );
}