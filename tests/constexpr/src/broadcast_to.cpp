#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb);

#include "nmtools/array/array/broadcast_to.hpp"
#include "nmtools/testing/data/constexpr/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define CONSTEXPR_BROADCAST_TO_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_broadcast_to, case_name); \
    using namespace args; \
    constexpr auto result = nmtools::array::broadcast_to(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("constexpr_broadcast_to(case1)" * doctest::test_suite("array::broadcast_to"))
{
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_a, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_f, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_h, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_a, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_f, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_h, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_cs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_cs_hb, shape_ct );
    
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_fs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_fs_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_hs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_hs_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_ls_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_ls_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_cs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_cs_hb, shape_cl );
    
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_fs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_fs_hb, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_hs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_hs_hb, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_ls_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case1, expected, x_ls_hb, shape_cl );
}

TEST_CASE("constexpr_broadcast_to(case7)" * doctest::test_suite("array::broadcast_to"))
{
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_a, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_f, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_h, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_a, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_f, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_h, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_cs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_cs_hb, shape_ct );
    
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_fs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_fs_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_hs_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_hs_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_ls_fb, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_ls_hb, shape_ct );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_cs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_cs_hb, shape_cl );
    
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_fs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_fs_hb, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_hs_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_hs_hb, shape_cl );

    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_ls_fb, shape_cl );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case7, expected, x_ls_hb, shape_cl );
}

TEST_CASE("constexpr_broadcast_to(case10)" * doctest::test_suite("array::broadcast_to"))
{
    CONSTEXPR_BROADCAST_TO_SUBCASE( case10, expected, x, shape_ct );
    CONSTEXPR_BROADCAST_TO_SUBCASE( case10, expected, x, shape_cl );
}