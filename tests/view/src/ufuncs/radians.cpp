#if 1
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db);
#endif

#include "nmtools/array/ufuncs/radians.hpp"
#include "nmtools/testing/data/array/radians.hpp"
#include "nmtools/testing/doctest.hpp"

#define RADIANS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, radians, case_name); \
    using namespace args; \
    auto result = nmtools::view::radians(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("radians(case1)" * doctest::test_suite("view::radians"))
{
    RADIANS_SUBCASE( case1,   a);
    RADIANS_SUBCASE( case1, a_a);
    RADIANS_SUBCASE( case1, a_f);
    RADIANS_SUBCASE( case1, a_d);
    RADIANS_SUBCASE( case1, a_h);

    RADIANS_SUBCASE( case1, a_cs_fb );
    RADIANS_SUBCASE( case1, a_cs_hb );
    RADIANS_SUBCASE( case1, a_cs_db );

    RADIANS_SUBCASE( case1, a_fs_fb );
    RADIANS_SUBCASE( case1, a_fs_hb );
    RADIANS_SUBCASE( case1, a_fs_db );

    RADIANS_SUBCASE( case1, a_hs_fb );
    RADIANS_SUBCASE( case1, a_hs_hb );
    RADIANS_SUBCASE( case1, a_hs_db );

    RADIANS_SUBCASE( case1, a_ds_fb );
    RADIANS_SUBCASE( case1, a_ds_hb );
    RADIANS_SUBCASE( case1, a_ds_db );
}

TEST_CASE("radians(case2)" * doctest::test_suite("view::radians"))
{
    RADIANS_SUBCASE( case2,   a);
    RADIANS_SUBCASE( case2, a_a);
    RADIANS_SUBCASE( case2, a_f);
    RADIANS_SUBCASE( case2, a_d);
    RADIANS_SUBCASE( case2, a_h);

    RADIANS_SUBCASE( case2, a_cs_fb );
    RADIANS_SUBCASE( case2, a_cs_hb );
    RADIANS_SUBCASE( case2, a_cs_db );

    RADIANS_SUBCASE( case2, a_fs_fb );
    RADIANS_SUBCASE( case2, a_fs_hb );
    RADIANS_SUBCASE( case2, a_fs_db );

    RADIANS_SUBCASE( case2, a_hs_fb );
    RADIANS_SUBCASE( case2, a_hs_hb );
    RADIANS_SUBCASE( case2, a_hs_db );

    RADIANS_SUBCASE( case2, a_ds_fb );
    RADIANS_SUBCASE( case2, a_ds_hb );
    RADIANS_SUBCASE( case2, a_ds_db );
}