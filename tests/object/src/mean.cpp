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
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db);

#include "nmtools/array/mean.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/mean.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define MEAN_SUBCASE_NUM(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, mean, case_name); \
    using namespace args; \
    auto result = nmtools::mean(__VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_num, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define OBJECT_MEAN_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, mean, case_name); \
    using namespace args; \
    auto object = nmtools::array(a,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(object) ); \
    auto result = object.mean(__VA_ARGS__); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#define MEAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, mean, case_name); \
    using namespace args; \
    auto result = nmtools::mean(__VA_ARGS__,nmtools::Object); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_object_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

namespace meta = nm::meta;

TEST_CASE("mean(case1)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE_NUM(case1, a, axis);
    MEAN_SUBCASE_NUM(case1, a_a, axis);
    MEAN_SUBCASE_NUM(case1, a_f, axis);
    MEAN_SUBCASE_NUM(case1, a_h, axis);
    MEAN_SUBCASE_NUM(case1, a_d, axis);

    MEAN_SUBCASE_NUM(case1, a_cs_db, axis);
    MEAN_SUBCASE_NUM(case1, a_fs_db, axis);
    MEAN_SUBCASE_NUM(case1, a_hs_db, axis);
    MEAN_SUBCASE_NUM(case1, a_ds_db, axis);
}

TEST_CASE("mean(case2)" * doctest::test_suite("array::mean"))
{
    MEAN_SUBCASE(case2, a, axis);
    MEAN_SUBCASE(case2, a_a, axis);
    MEAN_SUBCASE(case2, a_f, axis);
    MEAN_SUBCASE(case2, a_h, axis);
    MEAN_SUBCASE(case2, a_d, axis);

    MEAN_SUBCASE(case2, a_cs_db, axis);
    MEAN_SUBCASE(case2, a_fs_db, axis);
    MEAN_SUBCASE(case2, a_hs_db, axis);
    MEAN_SUBCASE(case2, a_ds_db, axis);

    OBJECT_MEAN_SUBCASE(case2, a, axis);
    OBJECT_MEAN_SUBCASE(case2, a_a, axis);
    OBJECT_MEAN_SUBCASE(case2, a_f, axis);
    OBJECT_MEAN_SUBCASE(case2, a_h, axis);
    OBJECT_MEAN_SUBCASE(case2, a_d, axis);

    OBJECT_MEAN_SUBCASE(case2, a_cs_db, axis);
    OBJECT_MEAN_SUBCASE(case2, a_fs_db, axis);
    OBJECT_MEAN_SUBCASE(case2, a_hs_db, axis);
    OBJECT_MEAN_SUBCASE(case2, a_ds_db, axis);
}


TEST_CASE("mean(case6)" * doctest::test_suite("array::mean"))
{
    auto dtype = nm::None;
    MEAN_SUBCASE(case6, a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_a, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_f, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_h, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_d, axis, dtype, keepdims);

    MEAN_SUBCASE(case6, a_cs_db, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_fs_db, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_hs_db, axis, dtype, keepdims);
    MEAN_SUBCASE(case6, a_ds_db, axis, dtype, keepdims);

    OBJECT_MEAN_SUBCASE(case6, a, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_a, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_f, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_h, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_d, axis, dtype, keepdims);

    OBJECT_MEAN_SUBCASE(case6, a_cs_db, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_fs_db, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_hs_db, axis, dtype, keepdims);
    OBJECT_MEAN_SUBCASE(case6, a_ds_db, axis, dtype, keepdims);
}