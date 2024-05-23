// NOTE: to minimize memory footprint on ci
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

#include "nmtools/array/view/array_slice.hpp"
#include "nmtools/testing/data/array/array_slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

// TODO: properly deduce ndarray type
#define ARRAY_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, array_slice, case_name); \
    using namespace args; \
    auto view = nmtools::view::array_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(view), nm::shape(expect::result) ); \
    using ndarray_t = na::dynamic_ndarray<int>; \
    auto result = static_cast<ndarray_t>(view); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("array_slice(case1)" * doctest::test_suite("view::array_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ARRAY_SLICE_SUBCASE( case1, array, slice0, slice1 );
    ARRAY_SLICE_SUBCASE( case1, array_a, slice0_a, slice1_a );
    ARRAY_SLICE_SUBCASE( case1, array_f, slice0_f, slice1_f );
    ARRAY_SLICE_SUBCASE( case1, array_d, slice0_d, slice1_d );
    ARRAY_SLICE_SUBCASE( case1, array_h, slice0_h, slice1_h );

    #else
    ARRAY_SLICE_SUBCASE( case1, array_cs_fb, slice0_cs_fb, slice1_cs_fb );
    ARRAY_SLICE_SUBCASE( case1, array_cs_hb, slice0_cs_hb, slice1_cs_hb );
    ARRAY_SLICE_SUBCASE( case1, array_cs_db, slice0_cs_db, slice1_cs_db );

    ARRAY_SLICE_SUBCASE( case1, array_fs_fb, slice0_fs_fb, slice1_fs_fb );
    ARRAY_SLICE_SUBCASE( case1, array_fs_hb, slice0_fs_hb, slice1_fs_hb );
    ARRAY_SLICE_SUBCASE( case1, array_fs_db, slice0_fs_db, slice1_fs_db );

    ARRAY_SLICE_SUBCASE( case1, array_hs_fb, slice0_hs_fb, slice1_hs_fb );
    ARRAY_SLICE_SUBCASE( case1, array_hs_hb, slice0_hs_hb, slice1_hs_hb );
    ARRAY_SLICE_SUBCASE( case1, array_hs_db, slice0_hs_db, slice1_hs_db );

    ARRAY_SLICE_SUBCASE( case1, array_ds_fb, slice0_ds_fb, slice1_ds_fb );
    ARRAY_SLICE_SUBCASE( case1, array_ds_hb, slice0_ds_hb, slice1_ds_hb );
    ARRAY_SLICE_SUBCASE( case1, array_ds_db, slice0_ds_db, slice1_ds_db );
    #endif
}

TEST_CASE("array_slice(case2)" * doctest::test_suite("view::array_slice") * doctest::skip())
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ARRAY_SLICE_SUBCASE( case2, array, slice0, slice1 );
    ARRAY_SLICE_SUBCASE( case2, array_a, slice0_a, slice1_a );
    ARRAY_SLICE_SUBCASE( case2, array_f, slice0_f, slice1_f );
    ARRAY_SLICE_SUBCASE( case2, array_d, slice0_d, slice1_d );
    ARRAY_SLICE_SUBCASE( case2, array_h, slice0_h, slice1_h );

    #else
    // TODO: fix runtime error no-stl build
    #ifndef NMTOOLS_DISABLE_STL
    ARRAY_SLICE_SUBCASE( case2, array_cs_fb, slice0_cs_fb, slice1_cs_fb );
    ARRAY_SLICE_SUBCASE( case2, array_cs_hb, slice0_cs_hb, slice1_cs_hb );
    ARRAY_SLICE_SUBCASE( case2, array_cs_db, slice0_cs_db, slice1_cs_db );

    ARRAY_SLICE_SUBCASE( case2, array_fs_fb, slice0_fs_fb, slice1_fs_fb );
    ARRAY_SLICE_SUBCASE( case2, array_fs_hb, slice0_fs_hb, slice1_fs_hb );
    ARRAY_SLICE_SUBCASE( case2, array_fs_db, slice0_fs_db, slice1_fs_db );

    ARRAY_SLICE_SUBCASE( case2, array_hs_fb, slice0_hs_fb, slice1_hs_fb );
    ARRAY_SLICE_SUBCASE( case2, array_hs_hb, slice0_hs_hb, slice1_hs_hb );
    ARRAY_SLICE_SUBCASE( case2, array_hs_db, slice0_hs_db, slice1_hs_db );

    ARRAY_SLICE_SUBCASE( case2, array_ds_fb, slice0_ds_fb, slice1_ds_fb );
    ARRAY_SLICE_SUBCASE( case2, array_ds_hb, slice0_ds_hb, slice1_ds_hb );
    ARRAY_SLICE_SUBCASE( case2, array_ds_db, slice0_ds_db, slice1_ds_db );
    #endif // NMTOOLS_DISABLE_STL
    #endif
}

TEST_CASE("array_slice(case3)" * doctest::test_suite("view::array_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ARRAY_SLICE_SUBCASE( case3, array, slice0, slice1 );
    ARRAY_SLICE_SUBCASE( case3, array_a, slice0_a, slice1_a );
    ARRAY_SLICE_SUBCASE( case3, array_f, slice0_f, slice1_f );
    ARRAY_SLICE_SUBCASE( case3, array_d, slice0_d, slice1_d );
    ARRAY_SLICE_SUBCASE( case3, array_h, slice0_h, slice1_h );

    #else
    ARRAY_SLICE_SUBCASE( case3, array_cs_fb, slice0_cs_fb, slice1_cs_fb );
    ARRAY_SLICE_SUBCASE( case3, array_cs_hb, slice0_cs_hb, slice1_cs_hb );
    ARRAY_SLICE_SUBCASE( case3, array_cs_db, slice0_cs_db, slice1_cs_db );

    ARRAY_SLICE_SUBCASE( case3, array_fs_fb, slice0_fs_fb, slice1_fs_fb );
    ARRAY_SLICE_SUBCASE( case3, array_fs_hb, slice0_fs_hb, slice1_fs_hb );
    ARRAY_SLICE_SUBCASE( case3, array_fs_db, slice0_fs_db, slice1_fs_db );

    ARRAY_SLICE_SUBCASE( case3, array_hs_fb, slice0_hs_fb, slice1_hs_fb );
    ARRAY_SLICE_SUBCASE( case3, array_hs_hb, slice0_hs_hb, slice1_hs_hb );
    ARRAY_SLICE_SUBCASE( case3, array_hs_db, slice0_hs_db, slice1_hs_db );

    ARRAY_SLICE_SUBCASE( case3, array_ds_fb, slice0_ds_fb, slice1_ds_fb );
    ARRAY_SLICE_SUBCASE( case3, array_ds_hb, slice0_ds_hb, slice1_ds_hb );
    ARRAY_SLICE_SUBCASE( case3, array_ds_db, slice0_ds_db, slice1_ds_db );
    #endif
}

TEST_CASE("array_slice(case4)" * doctest::test_suite("view::array_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #ifndef NMTOOLS_DISABLE_STL
    ARRAY_SLICE_SUBCASE( case4, array, slice0, slice1 );
    ARRAY_SLICE_SUBCASE( case4, array_a, slice0_a, slice1_a );
    ARRAY_SLICE_SUBCASE( case4, array_f, slice0_f, slice1_f );
    ARRAY_SLICE_SUBCASE( case4, array_d, slice0_d, slice1_d );
    ARRAY_SLICE_SUBCASE( case4, array_h, slice0_h, slice1_h );
    #endif

    #else
    // TODO: fix utl no-stl runtime error
    #ifndef NMTOOLS_DISABLE_STL
    ARRAY_SLICE_SUBCASE( case4, array_cs_fb, slice0_cs_fb, slice1_cs_fb );
    ARRAY_SLICE_SUBCASE( case4, array_cs_hb, slice0_cs_hb, slice1_cs_hb );
    ARRAY_SLICE_SUBCASE( case4, array_cs_db, slice0_cs_db, slice1_cs_db );

    ARRAY_SLICE_SUBCASE( case4, array_fs_fb, slice0_fs_fb, slice1_fs_fb );
    ARRAY_SLICE_SUBCASE( case4, array_fs_hb, slice0_fs_hb, slice1_fs_hb );
    ARRAY_SLICE_SUBCASE( case4, array_fs_db, slice0_fs_db, slice1_fs_db );

    ARRAY_SLICE_SUBCASE( case4, array_hs_fb, slice0_hs_fb, slice1_hs_fb );
    ARRAY_SLICE_SUBCASE( case4, array_hs_hb, slice0_hs_hb, slice1_hs_hb );
    ARRAY_SLICE_SUBCASE( case4, array_hs_db, slice0_hs_db, slice1_hs_db );

    ARRAY_SLICE_SUBCASE( case4, array_ds_fb, slice0_ds_fb, slice1_ds_fb );
    ARRAY_SLICE_SUBCASE( case4, array_ds_hb, slice0_ds_hb, slice1_ds_hb );
    ARRAY_SLICE_SUBCASE( case4, array_ds_db, slice0_ds_db, slice1_ds_db );
    #endif // NMTOOLS_DISABLE_STL
    #endif
}

TEST_CASE("array_slice(case5)" * doctest::test_suite("view::array_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #ifndef NMTOOLS_DISABLE_STL
    ARRAY_SLICE_SUBCASE( case5, array, slice0, slice1 );
    ARRAY_SLICE_SUBCASE( case5, array_a, slice0_a, slice1_a );
    ARRAY_SLICE_SUBCASE( case5, array_f, slice0_f, slice1_f );
    ARRAY_SLICE_SUBCASE( case5, array_d, slice0_d, slice1_d );
    ARRAY_SLICE_SUBCASE( case5, array_h, slice0_h, slice1_h );
    #endif // NMTOOLS_DISABLE_STL

    #else
    #ifndef NMTOOLS_DISABLE_STL
    ARRAY_SLICE_SUBCASE( case5, array_cs_fb, slice0_cs_fb, slice1_cs_fb );
    ARRAY_SLICE_SUBCASE( case5, array_cs_hb, slice0_cs_hb, slice1_cs_hb );

    ARRAY_SLICE_SUBCASE( case5, array_fs_fb, slice0_fs_fb, slice1_fs_fb );
    ARRAY_SLICE_SUBCASE( case5, array_cs_db, slice0_cs_db, slice1_cs_db );
    ARRAY_SLICE_SUBCASE( case5, array_fs_hb, slice0_fs_hb, slice1_fs_hb );
    ARRAY_SLICE_SUBCASE( case5, array_fs_db, slice0_fs_db, slice1_fs_db );

    ARRAY_SLICE_SUBCASE( case5, array_hs_fb, slice0_hs_fb, slice1_hs_fb );
    ARRAY_SLICE_SUBCASE( case5, array_hs_hb, slice0_hs_hb, slice1_hs_hb );
    ARRAY_SLICE_SUBCASE( case5, array_hs_db, slice0_hs_db, slice1_hs_db );

    ARRAY_SLICE_SUBCASE( case5, array_ds_fb, slice0_ds_fb, slice1_ds_fb );
    ARRAY_SLICE_SUBCASE( case5, array_ds_hb, slice0_ds_hb, slice1_ds_hb );
    ARRAY_SLICE_SUBCASE( case5, array_ds_db, slice0_ds_db, slice1_ds_db );
    #endif // NMTOOLS_DISABLE_STL
    #endif
}

// NOTE: not supported yet, needs ndarray assignment
// TODO: fix view::array_slice for partial indexing/slicing
// TEST_CASE("array_slice(case6)" * doctest::test_suite("view::array_slice"))
// {
//     ARRAY_SLICE_SUBCASE( case6, array, slice0 );
//     ARRAY_SLICE_SUBCASE( case6, array_a, slice0_a );
//     ARRAY_SLICE_SUBCASE( case6, array_f, slice0_f );
//     ARRAY_SLICE_SUBCASE( case6, array_d, slice0_d );
//     ARRAY_SLICE_SUBCASE( case6, array_h, slice0_h );
// }

// TEST_CASE("array_slice(case7)" * doctest::test_suite("view::array_slice"))
// {
//     ARRAY_SLICE_SUBCASE( case7, array, slice0 );
//     ARRAY_SLICE_SUBCASE( case7, array_a, slice0_a );
//     ARRAY_SLICE_SUBCASE( case7, array_f, slice0_f );
//     ARRAY_SLICE_SUBCASE( case7, array_d, slice0_d );
//     ARRAY_SLICE_SUBCASE( case7, array_h, slice0_h );
// }