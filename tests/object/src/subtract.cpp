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

#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY) && defined(NMTOOLS_BUILD_CONSTEXPR_TESTS)
#define NMTOOLS_CONSTEXPR_CAST_ARRAYS_EXTRA(name) \
constexpr inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
constexpr inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
constexpr inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
constexpr inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
constexpr inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
constexpr inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
constexpr inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
constexpr inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);
#endif

#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/testing/data/array/subtract.hpp"
#include "nmtools/core/context/object.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_SUBTRACT_SUBCASE(case_name, lhs, rhs) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, subtract, case_name); \
    using namespace args; \
    auto object = nmtools::array(lhs); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object - rhs; \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define SUBTRACT_SUBCASE_NO_TRAIT(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_REDUCE_SUBTRACT_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_subtract, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.reduce_subtract(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define REDUCE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.reduce(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_ACCUMULATE_SUBTRACT_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_subtract, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.accumulate_subtract(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ACCUMULATE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.accumulate(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_OUTER_SUBTRACT_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_subtract, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.outer_subtract(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OUTER_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_subtract, case_name); \
    using namespace args; \
    auto result = nmtools::subtract.outer(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract(case1)" * doctest::test_suite("array::subtract"))
{
    SUBTRACT_SUBCASE( case1,   a,   b );
    SUBTRACT_SUBCASE( case1, a_a, b_a );
    SUBTRACT_SUBCASE( case1, a_f, b_f );
    SUBTRACT_SUBCASE( case1, a_d, b_d );
    SUBTRACT_SUBCASE( case1, a_h, b_h );

    OBJECT_SUBTRACT_SUBCASE( case1,   a,   b );
    OBJECT_SUBTRACT_SUBCASE( case1, a_a, b_a );
    OBJECT_SUBTRACT_SUBCASE( case1, a_f, b_f );
    OBJECT_SUBTRACT_SUBCASE( case1, a_d, b_d );
    OBJECT_SUBTRACT_SUBCASE( case1, a_h, b_h );

    SUBTRACT_SUBCASE( case1, a_cs_fb, b_cs_fb );
    SUBTRACT_SUBCASE( case1, a_cs_db, b_cs_db );

    SUBTRACT_SUBCASE( case1, a_fs_fb, b_fs_fb );
    SUBTRACT_SUBCASE( case1, a_fs_db, b_fs_db );

    SUBTRACT_SUBCASE( case1, a_hs_db, b_hs_db );
    SUBTRACT_SUBCASE( case1, a_ds_db, b_ds_db );

    SUBTRACT_SUBCASE( case1, a_ls_hb, b_ls_hb );
    SUBTRACT_SUBCASE( case1, a_ls_db, b_ls_db );

    OBJECT_SUBTRACT_SUBCASE( case1, a_cs_fb, b_cs_fb );
    OBJECT_SUBTRACT_SUBCASE( case1, a_cs_db, b_cs_db );

    OBJECT_SUBTRACT_SUBCASE( case1, a_fs_fb, b_fs_fb );
    OBJECT_SUBTRACT_SUBCASE( case1, a_fs_db, b_fs_db );

    OBJECT_SUBTRACT_SUBCASE( case1, a_hs_db, b_hs_db );
    OBJECT_SUBTRACT_SUBCASE( case1, a_ds_db, b_ds_db );

    OBJECT_SUBTRACT_SUBCASE( case1, a_ls_hb, b_ls_hb );
    OBJECT_SUBTRACT_SUBCASE( case1, a_ls_db, b_ls_db );
}

TEST_CASE("subtract(case2)" * doctest::test_suite("array::subtract"))
{
    SUBTRACT_SUBCASE( case2,   a, b );
    SUBTRACT_SUBCASE( case2, a_a, b );
    SUBTRACT_SUBCASE( case2, a_f, b );
    SUBTRACT_SUBCASE( case2, a_d, b );
    SUBTRACT_SUBCASE( case2, a_h, b );

    OBJECT_SUBTRACT_SUBCASE( case2,   a, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_a, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_f, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_d, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_h, b );

    SUBTRACT_SUBCASE( case2, a_cs_fb, b );
    SUBTRACT_SUBCASE( case2, a_fs_db, b );

    SUBTRACT_SUBCASE( case2, a_hs_db, b );
    SUBTRACT_SUBCASE( case2, a_ds_db, b );
    SUBTRACT_SUBCASE( case2, a_ls_db, b );

    OBJECT_SUBTRACT_SUBCASE( case2, a_cs_fb, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_fs_db, b );

    OBJECT_SUBTRACT_SUBCASE( case2, a_hs_db, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_ds_db, b );
    OBJECT_SUBTRACT_SUBCASE( case2, a_ls_db, b );
}

TEST_CASE("reduce_subtract(case1)" * doctest::test_suite("array::subtract.reduce"))
{
    REDUCE_SUBTRACT_SUBCASE( case1,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_h, axis );

    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1,   a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_d, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_h, axis );

    REDUCE_SUBTRACT_SUBCASE( case1, a_cs_fb, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_fs_db, axis );

    REDUCE_SUBTRACT_SUBCASE( case1, a_hs_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_ds_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_ls_db, axis );

    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_cs_fb, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_fs_db, axis );

    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_hs_db, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_ds_db, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case1, a_ls_db, axis );
}

TEST_CASE("reduce_subtract(case2)" * doctest::test_suite("array::subtract.reduce"))
{
    REDUCE_SUBTRACT_SUBCASE( case2,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_h, axis );

    OBJECT_REDUCE_SUBTRACT_SUBCASE( case2,   a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case2, a_a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case2, a_d, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case2, a_h, axis );

    REDUCE_SUBTRACT_SUBCASE( case2, a_cs_fb, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_fs_db, axis );

    REDUCE_SUBTRACT_SUBCASE( case2, a_hs_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_ds_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_ls_db, axis );
}

TEST_CASE("reduce_subtract(case3)" * doctest::test_suite("array::subtract.reduce"))
{
    REDUCE_SUBTRACT_SUBCASE( case3,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_h, axis );
    
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case3,   a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case3, a_a, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case3, a_d, axis );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case3, a_h, axis );

    REDUCE_SUBTRACT_SUBCASE( case3, a_cs_fb, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_fs_db, axis );

    REDUCE_SUBTRACT_SUBCASE( case3, a_hs_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_ds_db, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_ls_db, axis );
}

// TEST_CASE("reduce_subtract(case7)" * doctest::test_suite("array::subtract.reduce"))
// {
//     REDUCE_SUBTRACT_SUBCASE( case7,   a, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_a, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_d, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_h, axis, dtype );

//     OBJECT_REDUCE_SUBTRACT_SUBCASE( case7,   a, axis, dtype );
//     OBJECT_REDUCE_SUBTRACT_SUBCASE( case7, a_a, axis, dtype );
//     OBJECT_REDUCE_SUBTRACT_SUBCASE( case7, a_f, axis, dtype );
//     OBJECT_REDUCE_SUBTRACT_SUBCASE( case7, a_d, axis, dtype );
//     OBJECT_REDUCE_SUBTRACT_SUBCASE( case7, a_h, axis, dtype );

//     REDUCE_SUBTRACT_SUBCASE( case7, a_cs_fb, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_fs_db, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_hs_db, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_ds_db, axis, dtype );
//     REDUCE_SUBTRACT_SUBCASE( case7, a_ls_db, axis, dtype );
// }

TEST_CASE("reduce_subtract(case8)" * doctest::test_suite("array::subtract.reduce"))
{
    REDUCE_SUBTRACT_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_d, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_h, axis, dtype, initial );

    OBJECT_REDUCE_SUBTRACT_SUBCASE( case8,   a, axis, dtype, initial );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case8, a_a, axis, dtype, initial );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case8, a_f, axis, dtype, initial );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case8, a_d, axis, dtype, initial );
    OBJECT_REDUCE_SUBTRACT_SUBCASE( case8, a_h, axis, dtype, initial );

    REDUCE_SUBTRACT_SUBCASE( case8, a_cs_fb, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_fs_db, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_hs_db, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_ds_db, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case8, a_ls_db, axis, dtype, initial );
}

TEST_CASE("subtract.accumulate(case1)" * doctest::test_suite("array::subtract.accumulate"))
{
    ACCUMULATE_SUBTRACT_SUBCASE( case1,   a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_f, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_d, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_h, axis );

    OBJECT_ACCUMULATE_SUBTRACT_SUBCASE( case1,   a, axis );
    OBJECT_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_a, axis );
    OBJECT_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_f, axis );
    OBJECT_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_d, axis );
    OBJECT_ACCUMULATE_SUBTRACT_SUBCASE( case1, a_h, axis );

    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_cs_fb, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_fs_db, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_hs_db, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_ds_db, axis );
    ACCUMULATE_SUBTRACT_SUBCASE( case1, a_ls_db, axis );
}

TEST_CASE("subtract.outer(case1)" * doctest::test_suite("array::subtract.outer"))
{
    OUTER_SUBTRACT_SUBCASE( case1,   a,   b );
    OUTER_SUBTRACT_SUBCASE( case1, a_a, b_a );
    OUTER_SUBTRACT_SUBCASE( case1, a_f, b_f );
    OUTER_SUBTRACT_SUBCASE( case1, a_d, b_d );
    OUTER_SUBTRACT_SUBCASE( case1, a_h, b_h );

    OBJECT_OUTER_SUBTRACT_SUBCASE( case1,   a,   b );
    OBJECT_OUTER_SUBTRACT_SUBCASE( case1, a_a, b_a );
    OBJECT_OUTER_SUBTRACT_SUBCASE( case1, a_f, b_f );
    OBJECT_OUTER_SUBTRACT_SUBCASE( case1, a_d, b_d );
    OBJECT_OUTER_SUBTRACT_SUBCASE( case1, a_h, b_h );

    OUTER_SUBTRACT_SUBCASE( case1, a_cs_fb, b_cs_fb );
    OUTER_SUBTRACT_SUBCASE( case1, a_fs_db, b_fs_db );
    OUTER_SUBTRACT_SUBCASE( case1, a_hs_db, b_hs_db );
    OUTER_SUBTRACT_SUBCASE( case1, a_ds_db, b_ds_db );
    OUTER_SUBTRACT_SUBCASE( case1, a_ls_db, b_ls_db );
}