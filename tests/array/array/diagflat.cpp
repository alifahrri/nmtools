#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::array::kind::ndarray_ls_db);
#endif

#include "nmtools/array/array/diagflat.hpp"
#include "nmtools/testing/data/array/diagflat.hpp"
#include "nmtools/testing/doctest.hpp"

#define DIAGFLAT_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, diagflat, case_name ); \
    using namespace args; \
    auto result = nmtools::array::diagflat(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("diagflat(case1)" * doctest::test_suite("array::diagflat"))
{
    DIAGFLAT_SUBCASE( case1, v );
    DIAGFLAT_SUBCASE( case1, v_a );
    DIAGFLAT_SUBCASE( case1, v_f );
    DIAGFLAT_SUBCASE( case1, v_h );
    DIAGFLAT_SUBCASE( case1, v_d );
}

TEST_CASE("diagflat(case2)" * doctest::test_suite("array::diagflat"))
{
    DIAGFLAT_SUBCASE( case2, v, k );
    DIAGFLAT_SUBCASE( case2, v_a, k );
    DIAGFLAT_SUBCASE( case2, v_f, k );
    DIAGFLAT_SUBCASE( case2, v_h, k );
    DIAGFLAT_SUBCASE( case2, v_d, k );
}

TEST_CASE("diagflat(case3)" * doctest::test_suite("array::diagflat"))
{
    DIAGFLAT_SUBCASE( case3, v, k );
    DIAGFLAT_SUBCASE( case3, v_a, k );
    DIAGFLAT_SUBCASE( case3, v_f, k );
    DIAGFLAT_SUBCASE( case3, v_h, k );
    DIAGFLAT_SUBCASE( case3, v_d, k );
}