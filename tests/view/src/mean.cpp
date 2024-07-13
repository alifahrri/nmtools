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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/view/mean.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define MEAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, mean, case_name); \
    using namespace args; \
    auto result = nmtools::view::mean(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("mean(case1)" * doctest::test_suite("view::mean"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case1, a, axis);
    MEAN_SUBCASE(case1, a_a, axis);
    MEAN_SUBCASE(case1, a_f, axis);
    MEAN_SUBCASE(case1, a_h, axis);
    MEAN_SUBCASE(case1, a_d, axis);

    #else
    MEAN_SUBCASE(case1, a_cs_fb, axis);
    MEAN_SUBCASE(case1, a_cs_hb, axis);
    MEAN_SUBCASE(case1, a_cs_db, axis);

    MEAN_SUBCASE(case1, a_fs_fb, axis);
    MEAN_SUBCASE(case1, a_fs_hb, axis);
    MEAN_SUBCASE(case1, a_fs_db, axis);

    MEAN_SUBCASE(case1, a_hs_fb, axis);
    MEAN_SUBCASE(case1, a_hs_hb, axis);
    MEAN_SUBCASE(case1, a_hs_db, axis);

    MEAN_SUBCASE(case1, a_ds_fb, axis);
    MEAN_SUBCASE(case1, a_ds_hb, axis);
    MEAN_SUBCASE(case1, a_ds_db, axis);
    #endif
}

TEST_CASE("mean(case2)" * doctest::test_suite("view::mean"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case2, a, axis);
    MEAN_SUBCASE(case2, a_a, axis);
    MEAN_SUBCASE(case2, a_f, axis);
    MEAN_SUBCASE(case2, a_h, axis);
    MEAN_SUBCASE(case2, a_d, axis);

    #else
    MEAN_SUBCASE(case2, a_cs_fb, axis);
    MEAN_SUBCASE(case2, a_cs_hb, axis);
    MEAN_SUBCASE(case2, a_cs_db, axis);

    MEAN_SUBCASE(case2, a_fs_fb, axis);
    MEAN_SUBCASE(case2, a_fs_hb, axis);
    MEAN_SUBCASE(case2, a_fs_db, axis);

    MEAN_SUBCASE(case2, a_hs_fb, axis);
    MEAN_SUBCASE(case2, a_hs_hb, axis);
    MEAN_SUBCASE(case2, a_hs_db, axis);

    MEAN_SUBCASE(case2, a_ds_fb, axis);
    MEAN_SUBCASE(case2, a_ds_hb, axis);
    MEAN_SUBCASE(case2, a_ds_db, axis);
    #endif
}

TEST_CASE("mean(case3)" * doctest::test_suite("view::mean"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case3, a, axis);
    MEAN_SUBCASE(case3, a_a, axis);
    MEAN_SUBCASE(case3, a_f, axis);
    MEAN_SUBCASE(case3, a_h, axis);
    MEAN_SUBCASE(case3, a_d, axis);

    #else
    MEAN_SUBCASE(case3, a_cs_fb, axis);
    MEAN_SUBCASE(case3, a_cs_hb, axis);
    MEAN_SUBCASE(case3, a_cs_db, axis);

    MEAN_SUBCASE(case3, a_fs_fb, axis);
    MEAN_SUBCASE(case3, a_fs_hb, axis);
    MEAN_SUBCASE(case3, a_fs_db, axis);

    MEAN_SUBCASE(case3, a_hs_fb, axis);
    MEAN_SUBCASE(case3, a_hs_hb, axis);
    MEAN_SUBCASE(case3, a_hs_db, axis);

    MEAN_SUBCASE(case3, a_ds_fb, axis);
    MEAN_SUBCASE(case3, a_ds_hb, axis);
    MEAN_SUBCASE(case3, a_ds_db, axis);
    #endif
}

TEST_CASE("mean(case4)" * doctest::test_suite("view::mean"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case4, a, axis);
    MEAN_SUBCASE(case4, a_a, axis);
    MEAN_SUBCASE(case4, a_f, axis);
    MEAN_SUBCASE(case4, a_h, axis);
    MEAN_SUBCASE(case4, a_d, axis);

    #else
    MEAN_SUBCASE(case4, a_cs_fb, axis);
    MEAN_SUBCASE(case4, a_cs_hb, axis);
    MEAN_SUBCASE(case4, a_cs_db, axis);

    MEAN_SUBCASE(case4, a_fs_fb, axis);
    MEAN_SUBCASE(case4, a_fs_hb, axis);
    MEAN_SUBCASE(case4, a_fs_db, axis);

    MEAN_SUBCASE(case4, a_hs_fb, axis);
    MEAN_SUBCASE(case4, a_hs_hb, axis);
    MEAN_SUBCASE(case4, a_hs_db, axis);

    MEAN_SUBCASE(case4, a_ds_fb, axis);
    MEAN_SUBCASE(case4, a_ds_hb, axis);
    MEAN_SUBCASE(case4, a_ds_db, axis);
    #endif
}

TEST_CASE("mean(case5)" * doctest::test_suite("view::mean"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case5, a, axis);
    MEAN_SUBCASE(case5, a_a, axis);
    MEAN_SUBCASE(case5, a_f, axis);
    MEAN_SUBCASE(case5, a_h, axis);
    MEAN_SUBCASE(case5, a_d, axis);

    #else
    MEAN_SUBCASE(case5, a_cs_fb, axis);
    MEAN_SUBCASE(case5, a_cs_hb, axis);
    MEAN_SUBCASE(case5, a_cs_db, axis);

    MEAN_SUBCASE(case5, a_fs_fb, axis);
    MEAN_SUBCASE(case5, a_fs_hb, axis);
    MEAN_SUBCASE(case5, a_fs_db, axis);

    MEAN_SUBCASE(case5, a_hs_fb, axis);
    MEAN_SUBCASE(case5, a_hs_hb, axis);
    MEAN_SUBCASE(case5, a_hs_db, axis);

    MEAN_SUBCASE(case5, a_ds_fb, axis);
    MEAN_SUBCASE(case5, a_ds_hb, axis);
    MEAN_SUBCASE(case5, a_ds_db, axis);
    #endif
}

TEST_CASE("mean(case6)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case6, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case6, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case6, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case6, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case6, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case7)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case7, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case7, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case7, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case7, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case7, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_hs_db, axis, dtype, keepdims);

    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case7, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case7, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case8)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case8, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case8, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case8, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case8, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case8, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_hs_db, axis, dtype, keepdims);

    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case8, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case8, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case9)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case9, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case9, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case9, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case9, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case9, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case9, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case10)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case10, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case10, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case10, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case10, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case10, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case10, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case11)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case11, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case11, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case12)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case12, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case12, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case11, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case11, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case11, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case13)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case13, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case13, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case13, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case13, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case13, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case13, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case13, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case14)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case14, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case14, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case14, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case14, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case14, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case14, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case14, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case15)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case15, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case15, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case15, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case15, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case15, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case15, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case15, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case16)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case16, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case16, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case16, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case16, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case16, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case16, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case16, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case17)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case17, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case17, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case17, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case17, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case17, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case17, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case17, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case18)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case18, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case18, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case18, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case18, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case18, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case18, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case18, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case19)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case19, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case19, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case19, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case19, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case19, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case19, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case19, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case20)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case20, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case20, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case20, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case20, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case20, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case20, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case20, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case21)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case21, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case21, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case21, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case21, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case21, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case21, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case22)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case22, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case22, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case22, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case22, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case22, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case22, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case23)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case23, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case23, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case23)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case23, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_d, axis, dtype, keepdims);
    #else
    MEAN_SUBCASE(case23, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case23, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case23, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case24)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case24, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case24, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case24, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case24, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case24, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case24, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case25)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case25, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case25, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case25, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case25, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case25, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case25, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case26)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case26, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_d, axis, dtype, keepdims);

    #else
    MEAN_SUBCASE(case26, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case26, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case26, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_hs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case26, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case26, a_ds_db, axis, dtype, keepdims);
    #endif
}

TEST_CASE("mean(case27)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case27, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case27, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case27, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case27, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case27, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case27, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case27, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case28)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case28, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case28, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case28, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case28, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case28, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case28, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case28, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case30)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case30, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case30, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case30, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case30, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case30, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case30, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case30, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case31)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case31, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case31, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case31, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case31, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case31, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case31, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case31, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case32)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case32, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case32, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case32, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case32, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case32, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case32, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case32, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}

TEST_CASE("mean(case33)" * doctest::test_suite("view::mean"))
{
    auto dtype = nm::None;
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MEAN_SUBCASE(case33, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_h, axis, dtype, keepdims);
    // TODO: fix utl either
    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case33, a_d, axis, dtype, keepdims);
    #endif

    #else
    MEAN_SUBCASE(case33, a_cs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_cs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_cs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case33, a_fs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_fs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_fs_db, axis, dtype, keepdims);

    MEAN_SUBCASE(case33, a_hs_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_hs_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_hs_db, axis, dtype, keepdims);

    #ifndef NMTOOLS_DISABLE_STL
    MEAN_SUBCASE(case33, a_ds_fb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_ds_hb, axis, dtype, keepdims);
    MEAN_SUBCASE(case33, a_ds_db, axis, dtype, keepdims);
    #endif // NMTOOLS_DISABLE_STL

    #endif
}