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

#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/data/array/add.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define ACCUMULATE_ADD(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_add, case_name); \
    using namespace args; \
    auto result = na::add.accumulate(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::add.accumulate(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("accumulate_add(case1)" * doctest::test_suite("array::add.accumulate"))
{
    auto dtype = nm::none_t{};
    // ACCUMULATE_ADD( case1,   a, axis );
    // ACCUMULATE_ADD( case1, a_a, axis );
    // ACCUMULATE_ADD( case1, a_f, axis );
    // ACCUMULATE_ADD( case1, a_d, axis );
    // ACCUMULATE_ADD( case1, a_h, axis );

    // ACCUMULATE_ADD( case1, a_cs_fb, axis );
    // ACCUMULATE_ADD( case1, a_cs_hb, axis );
    // ACCUMULATE_ADD( case1, a_cs_db, axis );

    ACCUMULATE_ADD( case1, a_fs_fb, axis, dtype );
    ACCUMULATE_ADD( case1, a_fs_hb, axis, dtype );
    ACCUMULATE_ADD( case1, a_fs_db, axis, dtype );

    ACCUMULATE_ADD( case1, a_hs_fb, axis, dtype );
    ACCUMULATE_ADD( case1, a_hs_hb, axis, dtype );
    ACCUMULATE_ADD( case1, a_hs_db, axis, dtype );

    ACCUMULATE_ADD( case1, a_ds_fb, axis, dtype );
    ACCUMULATE_ADD( case1, a_ds_hb, axis, dtype );
    ACCUMULATE_ADD( case1, a_ds_db, axis, dtype );
}