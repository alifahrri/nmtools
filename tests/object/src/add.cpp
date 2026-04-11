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

#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define OBJECT_ADD_SUBCASE(case_name, lhs, rhs) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, add, case_name); \
    using namespace args; \
    auto object = nmtools::array(lhs); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object + rhs; \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, add, case_name); \
    using namespace args; \
    auto result = nmtools::add(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ADD_SUBCASE_NO_TRAIT(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, add, case_name); \
    using namespace args; \
    auto result = nmtools::add(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_REDUCE_ADD_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.reduce_add(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define REDUCE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto result = nmtools::add.reduce(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_ACCUMULATE_ADD_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_add, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.accumulate_add(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define ACCUMULATE_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = nmtools::add.accumulate(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_OUTER_ADD_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_add, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.outer_add(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OUTER_ADD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_add, case_name); \
    using namespace args; \
    auto result = nmtools::add.outer(__VA_ARGS__, nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("add(case1)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE( case1,   a,   b );
    ADD_SUBCASE( case1, a_a, b_a );
    ADD_SUBCASE( case1, a_f, b_f );
    ADD_SUBCASE( case1, a_d, b_d );
    ADD_SUBCASE( case1, a_h, b_h );

    OBJECT_ADD_SUBCASE( case1,   a,   b );
    OBJECT_ADD_SUBCASE( case1, a_a, b_a );
    OBJECT_ADD_SUBCASE( case1, a_f, b_f );
    OBJECT_ADD_SUBCASE( case1, a_d, b_d );
    OBJECT_ADD_SUBCASE( case1, a_h, b_h );

    ADD_SUBCASE( case1, a_cs_fb, b_cs_fb );
    ADD_SUBCASE( case1, a_cs_db, b_cs_db );

    ADD_SUBCASE( case1, a_fs_fb, b_fs_fb );
    ADD_SUBCASE( case1, a_fs_db, b_fs_db );

    ADD_SUBCASE( case1, a_hs_db, b_hs_db );
    ADD_SUBCASE( case1, a_ds_db, b_ds_db );

    ADD_SUBCASE( case1, a_ls_hb, b_ls_hb );
    ADD_SUBCASE( case1, a_ls_db, b_ls_db );

    OBJECT_ADD_SUBCASE( case1, a_cs_fb, b_cs_fb );
    OBJECT_ADD_SUBCASE( case1, a_cs_db, b_cs_db );

    OBJECT_ADD_SUBCASE( case1, a_fs_fb, b_fs_fb );
    OBJECT_ADD_SUBCASE( case1, a_fs_db, b_fs_db );

    OBJECT_ADD_SUBCASE( case1, a_hs_db, b_hs_db );
    OBJECT_ADD_SUBCASE( case1, a_ds_db, b_ds_db );

    OBJECT_ADD_SUBCASE( case1, a_ls_hb, b_ls_hb );
    OBJECT_ADD_SUBCASE( case1, a_ls_db, b_ls_db );
}

TEST_CASE("add(case2)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE( case2,   a, b );
    ADD_SUBCASE( case2, a_a, b );
    ADD_SUBCASE( case2, a_f, b );
    ADD_SUBCASE( case2, a_d, b );
    ADD_SUBCASE( case2, a_h, b );

    OBJECT_ADD_SUBCASE( case2,   a, b );
    OBJECT_ADD_SUBCASE( case2, a_a, b );
    OBJECT_ADD_SUBCASE( case2, a_f, b );
    OBJECT_ADD_SUBCASE( case2, a_d, b );
    OBJECT_ADD_SUBCASE( case2, a_h, b );

    ADD_SUBCASE( case2, a_cs_fb, b );
    ADD_SUBCASE( case2, a_fs_db, b );

    ADD_SUBCASE( case2, a_hs_db, b );
    ADD_SUBCASE( case2, a_ds_db, b );
    ADD_SUBCASE( case2, a_ls_db, b );

    OBJECT_ADD_SUBCASE( case2, a_cs_fb, b );
    OBJECT_ADD_SUBCASE( case2, a_fs_db, b );

    OBJECT_ADD_SUBCASE( case2, a_hs_db, b );
    OBJECT_ADD_SUBCASE( case2, a_ds_db, b );
    OBJECT_ADD_SUBCASE( case2, a_ls_db, b );
}

TEST_CASE("add(case3)" * doctest::test_suite("array::add"))
{
   ADD_SUBCASE_NO_TRAIT(case3, a, b);
}

TEST_CASE("add(case4)" * doctest::test_suite("array::add"))
{
    ADD_SUBCASE(case4, a, b);
    ADD_SUBCASE(case4, a_a, b);
    ADD_SUBCASE(case4, a_f, b);
    ADD_SUBCASE(case4, a_d, b);
    ADD_SUBCASE(case4, a_h, b);
}

TEST_CASE("reduce_add(case1)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case1,   a, axis );
    REDUCE_ADD_SUBCASE( case1, a_a, axis );
    REDUCE_ADD_SUBCASE( case1, a_f, axis );
    REDUCE_ADD_SUBCASE( case1, a_d, axis );
    REDUCE_ADD_SUBCASE( case1, a_h, axis );

    OBJECT_REDUCE_ADD_SUBCASE( case1,   a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_f, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_d, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_h, axis );

    REDUCE_ADD_SUBCASE( case1, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case1, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case1, a_hs_db, axis );
    REDUCE_ADD_SUBCASE( case1, a_ds_db, axis );
    REDUCE_ADD_SUBCASE( case1, a_ls_db, axis );

    OBJECT_REDUCE_ADD_SUBCASE( case1, a_cs_fb, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_fs_db, axis );

    OBJECT_REDUCE_ADD_SUBCASE( case1, a_hs_db, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_ds_db, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case1, a_ls_db, axis );
}

TEST_CASE("reduce_add(case2)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case2,   a, axis );
    REDUCE_ADD_SUBCASE( case2, a_a, axis );
    REDUCE_ADD_SUBCASE( case2, a_f, axis );
    REDUCE_ADD_SUBCASE( case2, a_d, axis );
    REDUCE_ADD_SUBCASE( case2, a_h, axis );

    OBJECT_REDUCE_ADD_SUBCASE( case2,   a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case2, a_a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case2, a_f, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case2, a_d, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case2, a_h, axis );

    REDUCE_ADD_SUBCASE( case2, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case2, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case2, a_hs_db, axis );
    REDUCE_ADD_SUBCASE( case2, a_ds_db, axis );
    REDUCE_ADD_SUBCASE( case2, a_ls_db, axis );
}

TEST_CASE("reduce_add(case3)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case3,   a, axis );
    REDUCE_ADD_SUBCASE( case3, a_a, axis );
    REDUCE_ADD_SUBCASE( case3, a_f, axis );
    REDUCE_ADD_SUBCASE( case3, a_d, axis );
    REDUCE_ADD_SUBCASE( case3, a_h, axis );
    
    OBJECT_REDUCE_ADD_SUBCASE( case3,   a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case3, a_a, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case3, a_f, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case3, a_d, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case3, a_h, axis );

    REDUCE_ADD_SUBCASE( case3, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case3, a_fs_db, axis );

    REDUCE_ADD_SUBCASE( case3, a_hs_db, axis );
    REDUCE_ADD_SUBCASE( case3, a_ds_db, axis );
    REDUCE_ADD_SUBCASE( case3, a_ls_db, axis );
}

TEST_CASE("reduce_add(case4)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case4,   a,   axis );
    REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_d, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_h, axis_h );

    OBJECT_REDUCE_ADD_SUBCASE( case4,   a,   axis );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_a, axis_a );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_f, axis_f );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_d, axis_f );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_h, axis_h );

    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis );
    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_v );

    OBJECT_REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_f );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_h );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_cs_fb, axis_v );

    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_v );

    OBJECT_REDUCE_ADD_SUBCASE( case4, a_fs_db, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_f );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_h );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_fs_db, axis_v );

    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_f );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_h );
    REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_v );

    OBJECT_REDUCE_ADD_SUBCASE( case4, a_ds_db, axis );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_f );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_h );
    OBJECT_REDUCE_ADD_SUBCASE( case4, a_ds_db, axis_v );
}

TEST_CASE("reduce_add(case7)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_d, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );

    OBJECT_REDUCE_ADD_SUBCASE( case7,   a, axis, dtype );
    OBJECT_REDUCE_ADD_SUBCASE( case7, a_a, axis, dtype );
    OBJECT_REDUCE_ADD_SUBCASE( case7, a_f, axis, dtype );
    OBJECT_REDUCE_ADD_SUBCASE( case7, a_d, axis, dtype );
    OBJECT_REDUCE_ADD_SUBCASE( case7, a_h, axis, dtype );

    REDUCE_ADD_SUBCASE( case7, a_cs_fb, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_fs_db, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_hs_db, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_ds_db, axis, dtype );
    REDUCE_ADD_SUBCASE( case7, a_ls_db, axis, dtype );
}

TEST_CASE("reduce_add(case8)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_d, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );

    OBJECT_REDUCE_ADD_SUBCASE( case8,   a, axis, dtype, initial );
    OBJECT_REDUCE_ADD_SUBCASE( case8, a_a, axis, dtype, initial );
    OBJECT_REDUCE_ADD_SUBCASE( case8, a_f, axis, dtype, initial );
    OBJECT_REDUCE_ADD_SUBCASE( case8, a_d, axis, dtype, initial );
    OBJECT_REDUCE_ADD_SUBCASE( case8, a_h, axis, dtype, initial );

    REDUCE_ADD_SUBCASE( case8, a_cs_fb, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_fs_db, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_hs_db, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_ds_db, axis, dtype, initial );
    REDUCE_ADD_SUBCASE( case8, a_ls_db, axis, dtype, initial );
}

TEST_CASE("reduce_add(case9)" * doctest::test_suite("array::add.reduce"))
{
    REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    OBJECT_REDUCE_ADD_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_ADD_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_ADD_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_ADD_SUBCASE( case9, a_d, axis, dtype, initial, keepdims );
    OBJECT_REDUCE_ADD_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );

    REDUCE_ADD_SUBCASE( case9, a_cs_fb, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_fs_db, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_hs_db, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_ds_db, axis, dtype, initial, keepdims );
    REDUCE_ADD_SUBCASE( case9, a_ls_db, axis, dtype, initial, keepdims );
}

TEST_CASE("add.accumulate(case1)" * doctest::test_suite("array::add.accumulate"))
{
    ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );

    OBJECT_ACCUMULATE_ADD_SUBCASE( case1,   a, axis );
    OBJECT_ACCUMULATE_ADD_SUBCASE( case1, a_a, axis );
    OBJECT_ACCUMULATE_ADD_SUBCASE( case1, a_f, axis );
    OBJECT_ACCUMULATE_ADD_SUBCASE( case1, a_d, axis );
    OBJECT_ACCUMULATE_ADD_SUBCASE( case1, a_h, axis );

    ACCUMULATE_ADD_SUBCASE( case1, a_cs_fb, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_fs_db, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_hs_db, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_ds_db, axis );
    ACCUMULATE_ADD_SUBCASE( case1, a_ls_db, axis );
}

TEST_CASE("add.outer(case1)" * doctest::test_suite("array::add.outer"))
{
    OUTER_ADD_SUBCASE( case1,   a,   b );
    OUTER_ADD_SUBCASE( case1, a_a, b_a );
    OUTER_ADD_SUBCASE( case1, a_f, b_f );
    OUTER_ADD_SUBCASE( case1, a_d, b_d );
    OUTER_ADD_SUBCASE( case1, a_h, b_h );

    OBJECT_OUTER_ADD_SUBCASE( case1,   a,   b );
    OBJECT_OUTER_ADD_SUBCASE( case1, a_a, b_a );
    OBJECT_OUTER_ADD_SUBCASE( case1, a_f, b_f );
    OBJECT_OUTER_ADD_SUBCASE( case1, a_d, b_d );
    OBJECT_OUTER_ADD_SUBCASE( case1, a_h, b_h );

    OUTER_ADD_SUBCASE( case1, a_cs_fb, b_cs_fb );
    OUTER_ADD_SUBCASE( case1, a_fs_db, b_fs_db );
    OUTER_ADD_SUBCASE( case1, a_hs_db, b_hs_db );
    OUTER_ADD_SUBCASE( case1, a_ds_db, b_ds_db );
    OUTER_ADD_SUBCASE( case1, a_ls_db, b_ls_db );
}