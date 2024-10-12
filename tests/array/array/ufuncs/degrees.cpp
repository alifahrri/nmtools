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

#define NMTOOLS_TESTING_OUTPUT_PRECISION (1e-3)

#include "nmtools/array/array/ufuncs/degrees.hpp"
#include "nmtools/testing/data/array/degrees.hpp"
#include "nmtools/testing/doctest.hpp"

#define DEGREES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, degrees, case_name); \
    using namespace args; \
    auto result = nmtools::array::degrees(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("degrees(case1)" * doctest::test_suite("array::degrees"))
{
    DEGREES_SUBCASE( case1,   a);
    DEGREES_SUBCASE( case1, a_a);
    DEGREES_SUBCASE( case1, a_f);
    DEGREES_SUBCASE( case1, a_d);
    DEGREES_SUBCASE( case1, a_h);

    DEGREES_SUBCASE( case1, a_cs_fb );
    DEGREES_SUBCASE( case1, a_cs_hb );
    DEGREES_SUBCASE( case1, a_cs_db );

    DEGREES_SUBCASE( case1, a_fs_fb );
    DEGREES_SUBCASE( case1, a_fs_hb );
    DEGREES_SUBCASE( case1, a_fs_db );

    DEGREES_SUBCASE( case1, a_hs_fb );
    DEGREES_SUBCASE( case1, a_hs_hb );
    DEGREES_SUBCASE( case1, a_hs_db );

    DEGREES_SUBCASE( case1, a_ds_fb );
    DEGREES_SUBCASE( case1, a_ds_hb );
    DEGREES_SUBCASE( case1, a_ds_db );
}

TEST_CASE("degrees(case2)" * doctest::test_suite("array::degrees"))
{
    DEGREES_SUBCASE( case2,   a);
    DEGREES_SUBCASE( case2, a_a);
    DEGREES_SUBCASE( case2, a_f);
    DEGREES_SUBCASE( case2, a_d);
    DEGREES_SUBCASE( case2, a_h);

    DEGREES_SUBCASE( case2, a_cs_fb );
    DEGREES_SUBCASE( case2, a_cs_hb );
    DEGREES_SUBCASE( case2, a_cs_db );

    DEGREES_SUBCASE( case2, a_fs_fb );
    DEGREES_SUBCASE( case2, a_fs_hb );
    DEGREES_SUBCASE( case2, a_fs_db );

    DEGREES_SUBCASE( case2, a_hs_fb );
    DEGREES_SUBCASE( case2, a_hs_hb );
    DEGREES_SUBCASE( case2, a_hs_db );

    DEGREES_SUBCASE( case2, a_ds_fb );
    DEGREES_SUBCASE( case2, a_ds_hb );
    DEGREES_SUBCASE( case2, a_ds_db );
}