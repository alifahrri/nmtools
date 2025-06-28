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

#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;

#define BROADCAST_TO_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(broadcast_to, case_name); \
    using namespace args; \
    auto result = nmtools::broadcast_to(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), args::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case1, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case1, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case1, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case2, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case2, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case2, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case2, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case3, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case3, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case3, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case3, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case4, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case4, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case4, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case4, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case5, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case5, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case5, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case5, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case6, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case6, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case6, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case6, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case7, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case7, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case7, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case7, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case8)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case8, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case8, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case8, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case8, expected, x_h, shape );
}

TEST_CASE("broadcast_to(case9)" * doctest::test_suite("array::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case9, expected, x_a, shape );
    BROADCAST_TO_SUBCASE( case9, expected, x_f, shape );
    BROADCAST_TO_SUBCASE( case9, expected, x_d, shape );
    BROADCAST_TO_SUBCASE( case9, expected, x_h, shape );
}