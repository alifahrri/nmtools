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

#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/sycl.hpp"
#include "nmtools/testing/data/array/multiply.hpp"

namespace nm = nmtools;
namespace na = nmtools;

#define OUTER_MULTIPLY(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, outer_multiply, case_name); \
    using namespace args; \
    auto result = na::outer_multiply(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::outer_multiply(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("outer_multiply(case1)" * doctest::test_suite("array::multiply.accumulate"))
{
    static_assert( nmtools::is_context_ptr_v<decltype(na::sycl::default_context())> );
    // can't transfer the following type to device (no .data())
    // OUTER_MULTIPLY( case1,   a,   b );
    // OUTER_MULTIPLY( case1, a_a, b_a );
    OUTER_MULTIPLY( case1, a_f, b_f );
    OUTER_MULTIPLY( case1, a_d, b_d );
    OUTER_MULTIPLY( case1, a_h, b_h );
}