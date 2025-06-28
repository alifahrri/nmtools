#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_db);
#endif

#include "nmtools/array/triu.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/data/array/triu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#define TRIU_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, triu, case_name); \
    using namespace args; \
    auto view = nmtools::view::triu(__VA_ARGS__); \
    auto ctx = na::sycl::default_context(); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("triu(case1a)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case1a, a );
    // TRIU_SUBCASE( case1a, a_a );
    TRIU_SUBCASE( case1a, a_f );
    TRIU_SUBCASE( case1a, a_h );
    TRIU_SUBCASE( case1a, a_d );
}

TEST_CASE("triu(case1b)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case1b, a, k );
    // TRIU_SUBCASE( case1b, a_a, k );
    TRIU_SUBCASE( case1b, a_f, k );
    TRIU_SUBCASE( case1b, a_h, k );
    TRIU_SUBCASE( case1b, a_d, k );
}

TEST_CASE("triu(case1c)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case1c, a, k );
    // TRIU_SUBCASE( case1c, a_a, k );
    TRIU_SUBCASE( case1c, a_f, k );
    TRIU_SUBCASE( case1c, a_h, k );
    TRIU_SUBCASE( case1c, a_d, k );
}

TEST_CASE("triu(case2a)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case2a, a );
    // TRIU_SUBCASE( case2a, a_a );
    TRIU_SUBCASE( case2a, a_f );
    TRIU_SUBCASE( case2a, a_h );
    TRIU_SUBCASE( case2a, a_d );
}

TEST_CASE("triu(case2b)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case2b, a, k );
    // TRIU_SUBCASE( case2b, a_a, k );
    TRIU_SUBCASE( case2b, a_f, k );
    TRIU_SUBCASE( case2b, a_h, k );
    TRIU_SUBCASE( case2b, a_d, k );
}

TEST_CASE("triu(case2c)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case2c, a, k );
    // TRIU_SUBCASE( case2c, a_a, k );
    TRIU_SUBCASE( case2c, a_f, k );
    TRIU_SUBCASE( case2c, a_h, k );
    TRIU_SUBCASE( case2c, a_d, k );
}


TEST_CASE("triu(case3a)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case3a, a );
    // TRIU_SUBCASE( case3a, a_a );
    TRIU_SUBCASE( case3a, a_f );
    TRIU_SUBCASE( case3a, a_h );
    TRIU_SUBCASE( case3a, a_d );
}

TEST_CASE("triu(case3b)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case3b, a );
    // TRIU_SUBCASE( case3b, a_a );
    TRIU_SUBCASE( case3b, a_f );
    TRIU_SUBCASE( case3b, a_h );
    TRIU_SUBCASE( case3b, a_d );
}

TEST_CASE("triu(case3c)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case3c, a, k );
    // TRIU_SUBCASE( case3c, a_a, k );
    TRIU_SUBCASE( case3c, a_f, k );
    TRIU_SUBCASE( case3c, a_h, k );
    TRIU_SUBCASE( case3c, a_d, k );
}

TEST_CASE("triu(case3d)" * doctest::test_suite("array::triu"))
{
    // TRIU_SUBCASE( case3d, a, k );
    // TRIU_SUBCASE( case3d, a_a, k );
    TRIU_SUBCASE( case3d, a_f, k );
    TRIU_SUBCASE( case3d, a_h, k );
    TRIU_SUBCASE( case3d, a_d, k );
}