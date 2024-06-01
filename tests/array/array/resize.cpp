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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::array::kind::ndarray_ls_db);
#endif

#include "nmtools/array/array/resize.hpp"
#include "nmtools/testing/data/array/resize.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;

#define RUN_resize_impl(...) \
nm::array::resize(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs resize fn to callable lambda
#define RUN_resize(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("resize-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_resize_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_resize(case_name, ...) \
RUN_resize_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RESIZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(resize, case_name); \
    using namespace args; \
    auto result = RUN_resize(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("resize(case1)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case1,   array, dst_shape );
    RESIZE_SUBCASE( case1, array_a, dst_shape_a );
    RESIZE_SUBCASE( case1, array_f, dst_shape_f );
    RESIZE_SUBCASE( case1, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    // TODO: fix utl::vector (double free or corruption)
    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_v );
    #endif

    #if !defined(NMTOOLS_DISABLE_STL)
    // TODO: fix utl::vector free(): invalid pointer
    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_v );
    #endif

    #if !defined(NMTOOLS_DISABLE_STL)
    // TODO: fix utl::vector segfault
    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_v );
    #endif

    #if !defined(NMTOOLS_DISABLE_STL)
    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_v );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_v );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_v );
    #endif

    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_h );

    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_h );

    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_h );

    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_h );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_h );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_h );

    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_f );

    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_f );

    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_f );

    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_f );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_f );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_f );

    RESIZE_SUBCASE( case1, array_cs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_cs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_cs_db, dst_shape_cl );

    RESIZE_SUBCASE( case1, array_fs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_fs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_fs_db, dst_shape_cl );

    RESIZE_SUBCASE( case1, array_hs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_hs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_hs_db, dst_shape_cl );

    RESIZE_SUBCASE( case1, array_ds_fb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_ds_hb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_ds_db, dst_shape_cl );

    RESIZE_SUBCASE( case1, array_ls_fb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_ls_hb, dst_shape_cl );
    RESIZE_SUBCASE( case1, array_ls_db, dst_shape_cl );
    #endif
}

TEST_CASE("resize(case2)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case2,   array, dst_shape );
    RESIZE_SUBCASE( case2, array_a, dst_shape_a );
    RESIZE_SUBCASE( case2, array_f, dst_shape_f );
    RESIZE_SUBCASE( case2, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_a );

    #if !defined(NMTOOLS_DISABLE_STL)
    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_v );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_v );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_v );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_v );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_v );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_v );
    #endif

    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_h );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_h );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_h );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_h );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_h );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_h );

    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_f );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_f );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_f );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_f );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_f );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_f );

    RESIZE_SUBCASE( case2, array_cs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_cs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_cs_db, dst_shape_cl );

    RESIZE_SUBCASE( case2, array_fs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_fs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_fs_db, dst_shape_cl );

    RESIZE_SUBCASE( case2, array_hs_fb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_hs_hb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_hs_db, dst_shape_cl );

    RESIZE_SUBCASE( case2, array_ds_fb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_ds_hb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_ds_db, dst_shape_cl );

    RESIZE_SUBCASE( case2, array_ls_fb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_ls_hb, dst_shape_cl );
    RESIZE_SUBCASE( case2, array_ls_db, dst_shape_cl );
    #endif
}

TEST_CASE("resize(case3)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case3,   array, dst_shape );
    RESIZE_SUBCASE( case3, array_a, dst_shape_a );
    RESIZE_SUBCASE( case3, array_f, dst_shape_f );
    RESIZE_SUBCASE( case3, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case3, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case3, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case3, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case3, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case3, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case3, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case3, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case3, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case3, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case3, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case3, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case3, array_ls_db, dst_shape_a );
    #endif
}

TEST_CASE("resize(case4)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case4,   array, dst_shape );
    RESIZE_SUBCASE( case4, array_a, dst_shape_a );
    RESIZE_SUBCASE( case4, array_f, dst_shape_f );
    RESIZE_SUBCASE( case4, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case4, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case4, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case4, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case4, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case4, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case4, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case4, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case4, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case4, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case4, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case4, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case4, array_ls_db, dst_shape_a );
    #endif
}

TEST_CASE("resize(case5)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case5,   array, dst_shape );
    RESIZE_SUBCASE( case5, array_a, dst_shape_a );
    RESIZE_SUBCASE( case5, array_f, dst_shape_f );
    RESIZE_SUBCASE( case5, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case5, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case5, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case5, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case5, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case5, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case5, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case5, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case5, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case5, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case5, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case5, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case5, array_ls_db, dst_shape_a );
    #endif
}

TEST_CASE("resize(case6)" * doctest::test_suite("array::resize"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESIZE_SUBCASE( case6,   array, dst_shape );
    RESIZE_SUBCASE( case6, array_a, dst_shape_a );
    RESIZE_SUBCASE( case6, array_f, dst_shape_f );
    RESIZE_SUBCASE( case6, array_h, dst_shape_h );
    #else
    RESIZE_SUBCASE( case6, array_cs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_cs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_cs_db, dst_shape_ct );

    RESIZE_SUBCASE( case6, array_fs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_fs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_fs_db, dst_shape_ct );

    RESIZE_SUBCASE( case6, array_hs_fb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_hs_hb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_hs_db, dst_shape_ct );

    RESIZE_SUBCASE( case6, array_ds_fb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_ds_hb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_ds_db, dst_shape_ct );

    RESIZE_SUBCASE( case6, array_ls_fb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_ls_hb, dst_shape_ct );
    RESIZE_SUBCASE( case6, array_ls_db, dst_shape_ct );

    RESIZE_SUBCASE( case6, array_cs_fb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_cs_hb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_cs_db, dst_shape_a );

    RESIZE_SUBCASE( case6, array_fs_fb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_fs_hb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_fs_db, dst_shape_a );

    RESIZE_SUBCASE( case6, array_hs_fb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_hs_hb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_hs_db, dst_shape_a );

    RESIZE_SUBCASE( case6, array_ds_fb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_ds_hb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_ds_db, dst_shape_a );

    RESIZE_SUBCASE( case6, array_ls_fb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_ls_hb, dst_shape_a );
    RESIZE_SUBCASE( case6, array_ls_db, dst_shape_a );
    #endif
}