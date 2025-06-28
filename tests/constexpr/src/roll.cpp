#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);

#include "nmtools/array/roll.hpp"
#include "nmtools/testing/data/constexpr/roll.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#define CONSTEXPR_ROLL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(constexpr_roll, case_name) \
    using namespace args; \
    constexpr auto result = na::roll(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("roll(case1a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    // utl::maybe use placement-new which is non-constexpr
    #if 0
    CONSTEXPR_ROLL_SUBCASE( case1a, array, shift );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_a, shift );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_f, shift );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_h, shift );
    #endif

    CONSTEXPR_ROLL_SUBCASE( case1a, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_h, shift_ct );

    // utl::maybe use placement-new which is non-constexpr
    #if 0
    CONSTEXPR_ROLL_SUBCASE( case1a, array, shift_cl );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_a, shift_cl );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_f, shift_cl );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_h, shift_cl );
    #endif
    #else

    CONSTEXPR_ROLL_SUBCASE( case1a, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_cs_hb, shift_ct );

    // utl::maybe use placement-new which is non-constexpr
    #if 0
    CONSTEXPR_ROLL_SUBCASE( case1a, array_fs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_fs_hb, shift_ct );

    CONSTEXPR_ROLL_SUBCASE( case1a, array_hs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_hs_hb, shift_ct );

    CONSTEXPR_ROLL_SUBCASE( case1a, array_ls_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1a, array_ls_hb, shift_ct );
    #endif
    #endif
}


TEST_CASE("roll(case1b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case1b, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1b, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1b, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1b, array_h, shift_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case1b, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1b, array_cs_hb, shift_ct );

    #endif
}


TEST_CASE("roll(case1c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case1c, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1c, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1c, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1c, array_h, shift_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case1c, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case1c, array_cs_hb, shift_ct );

    #endif
}

TEST_CASE("roll(case2a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case2a, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2a, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2a, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2a, array_h, shift_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case2a, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2a, array_cs_hb, shift_ct );

    #endif
}

TEST_CASE("roll(case2b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case2b, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2b, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2b, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2b, array_h, shift_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case2b, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case2b, array_cs_hb, shift_ct );

    #endif
}

TEST_CASE("roll(case2c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case2c, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2c, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2c, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2c, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case2c, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2c, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case2d)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case2d, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2d, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2d, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2d, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case2d, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2d, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case2e)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case2e, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2e, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2e, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2e, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case2e, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case2e, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3a)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3a, array, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case3a, array_a, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case3a, array_f, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case3a, array_h, shift_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3a, array_cs_fb, shift_ct );
    CONSTEXPR_ROLL_SUBCASE( case3a, array_cs_hb, shift_ct );

    #endif
}

TEST_CASE("roll(case3b)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3b, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3b, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3b, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3b, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3b, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3b, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3c)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3c, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3c, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3c, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3c, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3c, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3c, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3d)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3d, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3d, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3d, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3d, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3d, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3d, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3e)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3e, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3e, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3e, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3e, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3e, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3e, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3f)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3f, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3f, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3f, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3f, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3f, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3f, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3g)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3g, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3g, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3g, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3g, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3g, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3g, array_cs_hb, shift_ct, axis_ct );

    #endif
}

TEST_CASE("roll(case3h)" * doctest::test_suite("array::roll"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)

    CONSTEXPR_ROLL_SUBCASE( case3h, array, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3h, array_a, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3h, array_f, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3h, array_h, shift_ct, axis_ct );

    #else

    CONSTEXPR_ROLL_SUBCASE( case3h, array_cs_fb, shift_ct, axis_ct );
    CONSTEXPR_ROLL_SUBCASE( case3h, array_cs_hb, shift_ct, axis_ct );

    #endif
}