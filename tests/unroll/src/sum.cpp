#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_hb);

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

#include "nmtools/array/sum.hpp"
#include "nmtools/testing/data/array/add.hpp"
#include "nmtools/core/context/unroll.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
using namespace nmtools::literals;

#define UNROLL_SUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, reduce_add, case_name); \
    using namespace args; \
    auto result = nmtools::sum(__VA_ARGS__, nmtools::Unroll); \
    NMTOOLS_STATIC_CHECK_TRAIT( nmtools::meta::is_ndarray, decltype(result) ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sum(case1)" * doctest::test_suite("unroll_context::sum"))
{
    UNROLL_SUM_SUBCASE( case1, a, axis_ct );

    UNROLL_SUM_SUBCASE( case1, a_cs_fb, axis_ct );
    UNROLL_SUM_SUBCASE( case1, a_cs_hb, axis_ct );
    UNROLL_SUM_SUBCASE( case1, a_cs_db, axis_ct );
}

TEST_CASE("sum(case2)" * doctest::test_suite("unroll_context::sum"))
{
    UNROLL_SUM_SUBCASE( case2, a, axis_ct );

    UNROLL_SUM_SUBCASE( case2, a_cs_fb, axis_ct );
    UNROLL_SUM_SUBCASE( case2, a_cs_hb, axis_ct );
    UNROLL_SUM_SUBCASE( case2, a_cs_db, axis_ct );
}

TEST_CASE("sum(case3)" * doctest::test_suite("unroll_context::sum"))
{
    UNROLL_SUM_SUBCASE( case3, a, axis_ct );

    UNROLL_SUM_SUBCASE( case3, a_cs_fb, axis_ct );
    UNROLL_SUM_SUBCASE( case3, a_cs_hb, axis_ct );
    UNROLL_SUM_SUBCASE( case3, a_cs_db, axis_ct );
}
