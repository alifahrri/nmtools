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

#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/testing/data/array/squeeze.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::view::squeeze(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs squeeze fn to callable lambda
#define RUN_squeeze(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("squeeze-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_squeeze(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SQUEEZE_SUBCASE(case_name, array) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(squeeze, case_name) \
    auto array_ref = RUN_squeeze(case_name, args::array); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("squeeze(case1)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case1, array );
    SQUEEZE_SUBCASE( case1, array_a );
    SQUEEZE_SUBCASE( case1, array_v );
    SQUEEZE_SUBCASE( case1, array_f );
    SQUEEZE_SUBCASE( case1, array_d );
    SQUEEZE_SUBCASE( case1, array_h );

    #else
    SQUEEZE_SUBCASE( case1, array_cs_fb );
    SQUEEZE_SUBCASE( case1, array_cs_hb );
    SQUEEZE_SUBCASE( case1, array_cs_db );

    SQUEEZE_SUBCASE( case1, array_fs_fb );
    SQUEEZE_SUBCASE( case1, array_fs_hb );
    SQUEEZE_SUBCASE( case1, array_fs_db );

    SQUEEZE_SUBCASE( case1, array_hs_fb );
    SQUEEZE_SUBCASE( case1, array_hs_hb );
    SQUEEZE_SUBCASE( case1, array_hs_db );

    SQUEEZE_SUBCASE( case1, array_ds_fb );
    SQUEEZE_SUBCASE( case1, array_ds_hb );
    SQUEEZE_SUBCASE( case1, array_ds_db );
    #endif
}

TEST_CASE("squeeze(case2)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case2, array );
    SQUEEZE_SUBCASE( case2, array_a );
    SQUEEZE_SUBCASE( case2, array_v );
    SQUEEZE_SUBCASE( case2, array_f );
    SQUEEZE_SUBCASE( case2, array_d );
    SQUEEZE_SUBCASE( case2, array_h );

    #else
    SQUEEZE_SUBCASE( case2, array_cs_fb );
    SQUEEZE_SUBCASE( case2, array_cs_hb );
    SQUEEZE_SUBCASE( case2, array_cs_db );

    SQUEEZE_SUBCASE( case2, array_fs_fb );
    SQUEEZE_SUBCASE( case2, array_fs_hb );
    SQUEEZE_SUBCASE( case2, array_fs_db );

    SQUEEZE_SUBCASE( case2, array_hs_fb );
    SQUEEZE_SUBCASE( case2, array_hs_hb );
    SQUEEZE_SUBCASE( case2, array_hs_db );

    SQUEEZE_SUBCASE( case2, array_ds_fb );
    SQUEEZE_SUBCASE( case2, array_ds_hb );
    SQUEEZE_SUBCASE( case2, array_ds_db );
    #endif
}

TEST_CASE("squeeze(case3)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case3, array );
    SQUEEZE_SUBCASE( case3, array_a );
    SQUEEZE_SUBCASE( case3, array_v );
    SQUEEZE_SUBCASE( case3, array_f );
    SQUEEZE_SUBCASE( case3, array_d );
    SQUEEZE_SUBCASE( case3, array_h );

    #else
    SQUEEZE_SUBCASE( case3, array_cs_fb );
    SQUEEZE_SUBCASE( case3, array_cs_hb );
    SQUEEZE_SUBCASE( case3, array_cs_db );

    SQUEEZE_SUBCASE( case3, array_fs_fb );
    SQUEEZE_SUBCASE( case3, array_fs_hb );
    SQUEEZE_SUBCASE( case3, array_fs_db );

    SQUEEZE_SUBCASE( case3, array_hs_fb );
    SQUEEZE_SUBCASE( case3, array_hs_hb );
    SQUEEZE_SUBCASE( case3, array_hs_db );

    SQUEEZE_SUBCASE( case3, array_ds_fb );
    SQUEEZE_SUBCASE( case3, array_ds_hb );
    SQUEEZE_SUBCASE( case3, array_ds_db );
    #endif
}

TEST_CASE("squeeze(case4)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case4, array );
    SQUEEZE_SUBCASE( case4, array_a );
    SQUEEZE_SUBCASE( case4, array_v );
    SQUEEZE_SUBCASE( case4, array_f );
    SQUEEZE_SUBCASE( case4, array_d );
    SQUEEZE_SUBCASE( case4, array_h );

    #else
    SQUEEZE_SUBCASE( case4, array_cs_fb );
    SQUEEZE_SUBCASE( case4, array_cs_hb );
    SQUEEZE_SUBCASE( case4, array_cs_db );

    SQUEEZE_SUBCASE( case4, array_fs_fb );
    SQUEEZE_SUBCASE( case4, array_fs_hb );
    SQUEEZE_SUBCASE( case4, array_fs_db );

    SQUEEZE_SUBCASE( case4, array_hs_fb );
    SQUEEZE_SUBCASE( case4, array_hs_hb );
    SQUEEZE_SUBCASE( case4, array_hs_db );

    SQUEEZE_SUBCASE( case4, array_ds_fb );
    SQUEEZE_SUBCASE( case4, array_ds_hb );
    SQUEEZE_SUBCASE( case4, array_ds_db );
    #endif
}

TEST_CASE("squeeze(case5)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case5, array );
    SQUEEZE_SUBCASE( case5, array_a );
    SQUEEZE_SUBCASE( case5, array_v );
    SQUEEZE_SUBCASE( case5, array_f );
    SQUEEZE_SUBCASE( case5, array_d );
    SQUEEZE_SUBCASE( case5, array_h );

    #else
    SQUEEZE_SUBCASE( case5, array_cs_fb );
    SQUEEZE_SUBCASE( case5, array_cs_hb );
    SQUEEZE_SUBCASE( case5, array_cs_db );

    SQUEEZE_SUBCASE( case5, array_fs_fb );
    SQUEEZE_SUBCASE( case5, array_fs_hb );
    SQUEEZE_SUBCASE( case5, array_fs_db );

    SQUEEZE_SUBCASE( case5, array_hs_fb );
    SQUEEZE_SUBCASE( case5, array_hs_hb );
    SQUEEZE_SUBCASE( case5, array_hs_db );

    SQUEEZE_SUBCASE( case5, array_ds_fb );
    SQUEEZE_SUBCASE( case5, array_ds_hb );
    SQUEEZE_SUBCASE( case5, array_ds_db );
    #endif
}

TEST_CASE("squeeze(case6)" * doctest::test_suite("view::squeeze"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SQUEEZE_SUBCASE( case6, array );
    SQUEEZE_SUBCASE( case6, array_a );
    SQUEEZE_SUBCASE( case6, array_v );
    SQUEEZE_SUBCASE( case6, array_f );
    SQUEEZE_SUBCASE( case6, array_d );
    SQUEEZE_SUBCASE( case6, array_h );

    #else
    SQUEEZE_SUBCASE( case6, array_cs_fb );
    SQUEEZE_SUBCASE( case6, array_cs_hb );
    SQUEEZE_SUBCASE( case6, array_cs_db );

    SQUEEZE_SUBCASE( case6, array_fs_fb );
    SQUEEZE_SUBCASE( case6, array_fs_hb );
    SQUEEZE_SUBCASE( case6, array_fs_db );

    SQUEEZE_SUBCASE( case6, array_hs_fb );
    SQUEEZE_SUBCASE( case6, array_hs_hb );
    SQUEEZE_SUBCASE( case6, array_hs_db );

    SQUEEZE_SUBCASE( case6, array_ds_fb );
    SQUEEZE_SUBCASE( case6, array_ds_hb );
    SQUEEZE_SUBCASE( case6, array_ds_db );
    #endif
}