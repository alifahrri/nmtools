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

#include "nmtools/array/array/ufuncs/clip.hpp"
#include "nmtools/testing/data/array/clip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_clip_impl(...) \
nm::array::clip(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs clip fn to callable lambda
#define RUN_clip(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("clip-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_clip_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_clip(case_name, ...) \
RUN_clip_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, clip, case_name); \
    using namespace args; \
    auto result = RUN_clip(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("clip(case1)" * doctest::test_suite("array::clip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CLIP_SUBCASE( case1,   a,   amin,   amax);
    CLIP_SUBCASE( case1, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case1, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case1, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case1, a_h, amin_h, amax_h);

    #else
    CLIP_SUBCASE( case1, a_cs_fb, amin_cs_fb, amax_cs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_cs_hb, amax_cs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_cs_db, amax_cs_db);

    CLIP_SUBCASE( case1, a_fs_fb, amin_fs_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_fs_hb, amin_fs_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_fs_db, amin_fs_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_hs_fb, amin_hs_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_hs_hb, amin_hs_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_hs_db, amin_hs_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_ds_fb, amax_ds_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_ds_hb, amax_ds_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_ds_db, amax_ds_db);

    CLIP_SUBCASE( case1, a_ls_fb, amin_ls_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_ls_hb, amin_ls_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_ls_db, amin_ls_db, amax_ls_db);


    CLIP_SUBCASE( case1, a_cs_fb, amin_fs_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_fs_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_fs_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_fs_fb, amax_ds_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_fs_hb, amax_ds_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_fs_db, amax_ds_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_fs_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_fs_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_fs_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_hs_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_hs_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_hs_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_hs_fb, amax_ds_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_hs_hb, amax_ds_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_hs_db, amax_ds_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_hs_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_hs_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_hs_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ds_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ds_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ds_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ds_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ds_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ds_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ds_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ds_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ds_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ls_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ls_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ls_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ls_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ls_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ls_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_cs_fb, amin_ls_fb, amax_ds_fb);
    CLIP_SUBCASE( case1, a_cs_hb, amin_ls_hb, amax_ds_hb);
    CLIP_SUBCASE( case1, a_cs_db, amin_ls_db, amax_ds_db);


    CLIP_SUBCASE( case1, a_ds_fb, amin_fs_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_fs_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_fs_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_fs_fb, amax_cs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_fs_hb, amax_cs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_fs_db, amax_cs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_fs_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_fs_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_fs_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_hs_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_hs_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_hs_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_hs_fb, amax_cs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_hs_hb, amax_cs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_hs_db, amax_cs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_hs_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_hs_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_hs_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_cs_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_cs_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_cs_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_cs_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_cs_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_cs_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_cs_fb, amax_ls_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_cs_hb, amax_ls_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_cs_db, amax_ls_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_ls_fb, amax_fs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_ls_hb, amax_fs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_ls_db, amax_fs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_ls_fb, amax_hs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_ls_hb, amax_hs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_ls_db, amax_hs_db);

    CLIP_SUBCASE( case1, a_ds_fb, amin_ls_fb, amax_cs_fb);
    CLIP_SUBCASE( case1, a_ds_hb, amin_ls_hb, amax_cs_hb);
    CLIP_SUBCASE( case1, a_ds_db, amin_ls_db, amax_cs_db);
    #endif
}

TEST_CASE("clip(case2)" * doctest::test_suite("array::clip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CLIP_SUBCASE( case2,   a,   amin,   amax);
    CLIP_SUBCASE( case2, a_a, amin_a, amax_a);
    CLIP_SUBCASE( case2, a_f, amin_f, amax_f);
    CLIP_SUBCASE( case2, a_d, amin_d, amax_d);
    CLIP_SUBCASE( case2, a_h, amin_h, amax_h);

    #else
    CLIP_SUBCASE( case2, a_cs_fb, amin_cs_fb, amax_cs_fb);
    CLIP_SUBCASE( case2, a_cs_hb, amin_cs_hb, amax_cs_hb);
    CLIP_SUBCASE( case2, a_cs_db, amin_cs_db, amax_cs_db);

    CLIP_SUBCASE( case2, a_fs_fb, amin_fs_fb, amax_fs_fb);
    CLIP_SUBCASE( case2, a_fs_hb, amin_fs_hb, amax_fs_hb);
    CLIP_SUBCASE( case2, a_fs_db, amin_fs_db, amax_fs_db);

    CLIP_SUBCASE( case2, a_hs_fb, amin_hs_fb, amax_hs_fb);
    CLIP_SUBCASE( case2, a_hs_hb, amin_hs_hb, amax_hs_hb);
    CLIP_SUBCASE( case2, a_hs_db, amin_hs_db, amax_hs_db);

    CLIP_SUBCASE( case2, a_ds_fb, amin_ds_fb, amax_ds_fb);
    CLIP_SUBCASE( case2, a_ds_hb, amin_ds_hb, amax_ds_hb);
    CLIP_SUBCASE( case2, a_ds_db, amin_ds_db, amax_ds_db);

    CLIP_SUBCASE( case2, a_ls_fb, amin_ls_fb, amax_ls_fb);
    CLIP_SUBCASE( case2, a_ls_hb, amin_ls_hb, amax_ls_hb);
    CLIP_SUBCASE( case2, a_ls_db, amin_ls_db, amax_ls_db);
    #endif
}

TEST_CASE("clip(case3)" * doctest::test_suite("array::clip"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CLIP_SUBCASE( case3,   a,   amin, amax);
    CLIP_SUBCASE( case3, a_a, amin_a, amax);
    CLIP_SUBCASE( case3, a_f, amin_f, amax);
    CLIP_SUBCASE( case3, a_d, amin_d, amax);
    CLIP_SUBCASE( case3, a_h, amin_h, amax);

    #else
    CLIP_SUBCASE( case3, a_cs_fb, amin_cs_fb, amax);
    CLIP_SUBCASE( case3, a_cs_hb, amin_cs_hb, amax);
    CLIP_SUBCASE( case3, a_cs_db, amin_cs_db, amax);

    CLIP_SUBCASE( case3, a_fs_fb, amin_fs_fb, amax);
    CLIP_SUBCASE( case3, a_fs_hb, amin_fs_hb, amax);
    CLIP_SUBCASE( case3, a_fs_db, amin_fs_db, amax);

    CLIP_SUBCASE( case3, a_hs_fb, amin_hs_fb, amax);
    CLIP_SUBCASE( case3, a_hs_hb, amin_hs_hb, amax);
    CLIP_SUBCASE( case3, a_hs_db, amin_hs_db, amax);

    CLIP_SUBCASE( case3, a_ds_fb, amin_ds_fb, amax);
    CLIP_SUBCASE( case3, a_ds_hb, amin_ds_hb, amax);
    CLIP_SUBCASE( case3, a_ds_db, amin_ds_db, amax);

    CLIP_SUBCASE( case3, a_ls_fb, amin_ls_fb, amax);
    CLIP_SUBCASE( case3, a_ls_hb, amin_ls_hb, amax);
    CLIP_SUBCASE( case3, a_ls_db, amin_ls_db, amax);


    CLIP_SUBCASE( case3, a_cs_fb, amin_fs_fb, amax);
    CLIP_SUBCASE( case3, a_cs_hb, amin_fs_hb, amax);
    CLIP_SUBCASE( case3, a_cs_db, amin_fs_db, amax);

    CLIP_SUBCASE( case3, a_cs_fb, amin_hs_fb, amax);
    CLIP_SUBCASE( case3, a_cs_hb, amin_hs_hb, amax);
    CLIP_SUBCASE( case3, a_cs_db, amin_hs_db, amax);

    CLIP_SUBCASE( case3, a_cs_fb, amin_ds_fb, amax);
    CLIP_SUBCASE( case3, a_cs_hb, amin_ds_hb, amax);
    CLIP_SUBCASE( case3, a_cs_db, amin_ds_db, amax);

    CLIP_SUBCASE( case3, a_cs_fb, amin_ls_fb, amax);
    CLIP_SUBCASE( case3, a_cs_hb, amin_ls_hb, amax);
    CLIP_SUBCASE( case3, a_cs_db, amin_ls_db, amax);

    CLIP_SUBCASE( case3, a_fs_fb, amin_cs_fb, amax);
    CLIP_SUBCASE( case3, a_fs_hb, amin_cs_hb, amax);
    CLIP_SUBCASE( case3, a_fs_db, amin_cs_db, amax);

    CLIP_SUBCASE( case3, a_fs_fb, amin_hs_fb, amax);
    CLIP_SUBCASE( case3, a_fs_hb, amin_hs_hb, amax);
    CLIP_SUBCASE( case3, a_fs_db, amin_hs_db, amax);

    CLIP_SUBCASE( case3, a_fs_fb, amin_ds_fb, amax);
    CLIP_SUBCASE( case3, a_fs_hb, amin_ds_hb, amax);
    CLIP_SUBCASE( case3, a_fs_db, amin_ds_db, amax);

    CLIP_SUBCASE( case3, a_fs_fb, amin_ls_fb, amax);
    CLIP_SUBCASE( case3, a_fs_hb, amin_ls_hb, amax);
    CLIP_SUBCASE( case3, a_fs_db, amin_ls_db, amax);

    CLIP_SUBCASE( case3, a_hs_fb, amin_fs_fb, amax);
    CLIP_SUBCASE( case3, a_hs_hb, amin_fs_hb, amax);
    CLIP_SUBCASE( case3, a_hs_db, amin_fs_db, amax);

    CLIP_SUBCASE( case3, a_hs_fb, amin_cs_fb, amax);
    CLIP_SUBCASE( case3, a_hs_hb, amin_cs_hb, amax);
    CLIP_SUBCASE( case3, a_hs_db, amin_cs_db, amax);

    CLIP_SUBCASE( case3, a_hs_fb, amin_ds_fb, amax);
    CLIP_SUBCASE( case3, a_hs_hb, amin_ds_hb, amax);
    CLIP_SUBCASE( case3, a_hs_db, amin_ds_db, amax);

    CLIP_SUBCASE( case3, a_hs_fb, amin_ls_fb, amax);
    CLIP_SUBCASE( case3, a_hs_hb, amin_ls_hb, amax);
    CLIP_SUBCASE( case3, a_hs_db, amin_ls_db, amax);


    CLIP_SUBCASE( case3, a_ds_fb, amin_fs_fb, amax);
    CLIP_SUBCASE( case3, a_ds_hb, amin_fs_hb, amax);
    CLIP_SUBCASE( case3, a_ds_db, amin_fs_db, amax);

    CLIP_SUBCASE( case3, a_ds_fb, amin_hs_fb, amax);
    CLIP_SUBCASE( case3, a_ds_hb, amin_hs_hb, amax);
    CLIP_SUBCASE( case3, a_ds_db, amin_hs_db, amax);

    CLIP_SUBCASE( case3, a_ds_fb, amin_cs_fb, amax);
    CLIP_SUBCASE( case3, a_ds_hb, amin_cs_hb, amax);
    CLIP_SUBCASE( case3, a_ds_db, amin_cs_db, amax);

    CLIP_SUBCASE( case3, a_ds_fb, amin_ls_fb, amax);
    CLIP_SUBCASE( case3, a_ds_hb, amin_ls_hb, amax);
    CLIP_SUBCASE( case3, a_ds_db, amin_ls_db, amax);

    CLIP_SUBCASE( case3, a_ls_fb, amin_fs_fb, amax);
    CLIP_SUBCASE( case3, a_ls_hb, amin_fs_hb, amax);
    CLIP_SUBCASE( case3, a_ls_db, amin_fs_db, amax);

    CLIP_SUBCASE( case3, a_ls_fb, amin_hs_fb, amax);
    CLIP_SUBCASE( case3, a_ls_hb, amin_hs_hb, amax);
    CLIP_SUBCASE( case3, a_ls_db, amin_hs_db, amax);

    CLIP_SUBCASE( case3, a_ls_fb, amin_ds_fb, amax);
    CLIP_SUBCASE( case3, a_ls_hb, amin_ds_hb, amax);
    CLIP_SUBCASE( case3, a_ls_db, amin_ds_db, amax);

    CLIP_SUBCASE( case3, a_ls_fb, amin_cs_fb, amax);
    CLIP_SUBCASE( case3, a_ls_hb, amin_cs_hb, amax);
    CLIP_SUBCASE( case3, a_ls_db, amin_cs_db, amax);
    #endif
}