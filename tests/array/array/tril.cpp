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

#include "nmtools/array/array/tril.hpp"
#include "nmtools/testing/data/array/tril.hpp"
#include "nmtools/testing/doctest.hpp"

#define TRIL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, tril, case_name); \
    using namespace args; \
    auto result = nmtools::array::tril(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("tril(case1a)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case1a, a );
    TRIL_SUBCASE( case1a, a_a );
    TRIL_SUBCASE( case1a, a_f );
    TRIL_SUBCASE( case1a, a_h );
    TRIL_SUBCASE( case1a, a_d );
}

TEST_CASE("tril(case1b)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case1b, a, k );
    TRIL_SUBCASE( case1b, a_a, k );
    TRIL_SUBCASE( case1b, a_f, k );
    TRIL_SUBCASE( case1b, a_h, k );
    TRIL_SUBCASE( case1b, a_d, k );
}

TEST_CASE("tril(case1c)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case1c, a, k );
    TRIL_SUBCASE( case1c, a_a, k );
    TRIL_SUBCASE( case1c, a_f, k );
    TRIL_SUBCASE( case1c, a_h, k );
    TRIL_SUBCASE( case1c, a_d, k );
}

TEST_CASE("tril(case2a)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case2a, a );
    TRIL_SUBCASE( case2a, a_a );
    TRIL_SUBCASE( case2a, a_f );
    TRIL_SUBCASE( case2a, a_h );
    TRIL_SUBCASE( case2a, a_d );
}

TEST_CASE("tril(case2b)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case2b, a, k );
    TRIL_SUBCASE( case2b, a_a, k );
    TRIL_SUBCASE( case2b, a_f, k );
    TRIL_SUBCASE( case2b, a_h, k );
    TRIL_SUBCASE( case2b, a_d, k );
}

TEST_CASE("tril(case2c)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case2c, a, k );
    TRIL_SUBCASE( case2c, a_a, k );
    TRIL_SUBCASE( case2c, a_f, k );
    TRIL_SUBCASE( case2c, a_h, k );
    TRIL_SUBCASE( case2c, a_d, k );
}

TEST_CASE("tril(case3a)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case3a, a );
    TRIL_SUBCASE( case3a, a_a );
    TRIL_SUBCASE( case3a, a_f );
    TRIL_SUBCASE( case3a, a_h );
    TRIL_SUBCASE( case3a, a_d );
}

TEST_CASE("tril(case3b)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case3b, a );
    TRIL_SUBCASE( case3b, a_a );
    TRIL_SUBCASE( case3b, a_f );
    TRIL_SUBCASE( case3b, a_h );
    TRIL_SUBCASE( case3b, a_d );
}

TEST_CASE("tril(case3c)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case3c, a, k );
    TRIL_SUBCASE( case3c, a_a, k );
    TRIL_SUBCASE( case3c, a_f, k );
    TRIL_SUBCASE( case3c, a_h, k );
    TRIL_SUBCASE( case3c, a_d, k );
}

TEST_CASE("tril(case3d)" * doctest::test_suite("array::tril"))
{
    TRIL_SUBCASE( case3d, a, k );
    TRIL_SUBCASE( case3d, a_a, k );
    TRIL_SUBCASE( case3d, a_f, k );
    TRIL_SUBCASE( case3d, a_h, k );
    TRIL_SUBCASE( case3d, a_d, k );
}