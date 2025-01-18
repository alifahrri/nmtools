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

#include "nmtools/array/take.hpp"
#include "nmtools/testing/data/array/take.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_take_impl(...) \
nm::view::take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs take fn to callable lambda
#define RUN_take(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("take-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_take_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_take(case_name, ...) \
RUN_take_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, take, case_name); \
    using namespace args; \
    auto result = RUN_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("case1" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case1,   array,   indices, axis );
    TAKE_SUBCASE( case1, array_a, indices_a, axis );
    TAKE_SUBCASE( case1, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case1, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case1, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case1, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case1, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case1, array_cs_db, indices, axis );

    TAKE_SUBCASE( case1, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case1, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case1, array_fs_db, indices, axis );

    TAKE_SUBCASE( case1, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case1, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case1, array_hs_db, indices, axis );

    TAKE_SUBCASE( case1, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case1, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case1, array_ds_db, indices, axis );

    TAKE_SUBCASE( case1, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case1, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case1, array_ls_db, indices, axis );

    TAKE_SUBCASE( case1, array_cs_fb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_cs_hb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_cs_db, indices_ct, axis );

    TAKE_SUBCASE( case1, array_fs_fb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_fs_hb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_fs_db, indices_ct, axis );

    TAKE_SUBCASE( case1, array_hs_fb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_hs_hb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_hs_db, indices_ct, axis );

    TAKE_SUBCASE( case1, array_ds_fb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_ds_hb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_ds_db, indices_ct, axis );

    TAKE_SUBCASE( case1, array_ls_fb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_ls_hb, indices_ct, axis );
    TAKE_SUBCASE( case1, array_ls_db, indices_ct, axis );

    TAKE_SUBCASE( case1, array_cs_fb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_cs_hb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_cs_db, indices_ct, axis_ct );

    TAKE_SUBCASE( case1, array_fs_fb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_fs_hb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_fs_db, indices_ct, axis_ct );

    TAKE_SUBCASE( case1, array_hs_fb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_hs_hb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_hs_db, indices_ct, axis_ct );

    TAKE_SUBCASE( case1, array_ds_fb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_ds_hb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_ds_db, indices_ct, axis_ct );

    TAKE_SUBCASE( case1, array_ls_fb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_ls_hb, indices_ct, axis_ct );
    TAKE_SUBCASE( case1, array_ls_db, indices_ct, axis_ct );

    TAKE_SUBCASE( case1, array_cs_fb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_cs_hb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_cs_db, indices_cl, axis );

    TAKE_SUBCASE( case1, array_fs_fb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_fs_hb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_fs_db, indices_cl, axis );

    TAKE_SUBCASE( case1, array_hs_fb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_hs_hb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_hs_db, indices_cl, axis );

    TAKE_SUBCASE( case1, array_ds_fb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_ds_hb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_ds_db, indices_cl, axis );

    TAKE_SUBCASE( case1, array_ls_fb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_ls_hb, indices_cl, axis );
    TAKE_SUBCASE( case1, array_ls_db, indices_cl, axis );

    TAKE_SUBCASE( case1, array_cs_fb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_cs_hb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_cs_db, indices_cl, axis_ct );

    TAKE_SUBCASE( case1, array_fs_fb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_fs_hb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_fs_db, indices_cl, axis_ct );

    TAKE_SUBCASE( case1, array_hs_fb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_hs_hb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_hs_db, indices_cl, axis_ct );

    TAKE_SUBCASE( case1, array_ds_fb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_ds_hb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_ds_db, indices_cl, axis_ct );

    TAKE_SUBCASE( case1, array_ls_fb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_ls_hb, indices_cl, axis_ct );
    TAKE_SUBCASE( case1, array_ls_db, indices_cl, axis_ct );
    #endif
}

TEST_CASE("case2" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case2,   array,   indices, axis );
    TAKE_SUBCASE( case2, array_a, indices_a, axis );
    TAKE_SUBCASE( case2, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case2, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case2, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case2, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case2, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case2, array_cs_db, indices, axis );

    TAKE_SUBCASE( case2, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case2, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case2, array_fs_db, indices, axis );

    TAKE_SUBCASE( case2, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case2, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case2, array_hs_db, indices, axis );

    TAKE_SUBCASE( case2, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case2, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case2, array_ds_db, indices, axis );

    TAKE_SUBCASE( case2, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case2, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case2, array_ls_db, indices, axis );
    #endif
}

TEST_CASE("case3" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case3,   array,   indices, axis );
    TAKE_SUBCASE( case3, array_a, indices_a, axis );
    TAKE_SUBCASE( case3, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case3, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case3, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case3, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case3, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case3, array_cs_db, indices, axis );

    TAKE_SUBCASE( case3, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case3, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case3, array_fs_db, indices, axis );

    TAKE_SUBCASE( case3, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case3, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case3, array_hs_db, indices, axis );

    TAKE_SUBCASE( case3, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case3, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case3, array_ds_db, indices, axis );

    TAKE_SUBCASE( case3, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case3, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case3, array_ls_db, indices, axis );
    #endif
}

TEST_CASE("case4" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case4,   array,   indices, axis );
    TAKE_SUBCASE( case4, array_a, indices_a, axis );
    TAKE_SUBCASE( case4, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case4, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case4, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case4, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case4, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case4, array_cs_db, indices, axis );

    TAKE_SUBCASE( case4, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case4, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case4, array_fs_db, indices, axis );

    TAKE_SUBCASE( case4, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case4, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case4, array_hs_db, indices, axis );

    TAKE_SUBCASE( case4, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case4, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case4, array_ds_db, indices, axis );

    TAKE_SUBCASE( case4, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case4, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case4, array_ls_db, indices, axis );
    #endif
}

TEST_CASE("case5" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case5,   array,   indices, axis );
    TAKE_SUBCASE( case5, array_a, indices_a, axis );
    TAKE_SUBCASE( case5, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case5, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case5, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case5, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case5, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case5, array_cs_db, indices, axis );

    TAKE_SUBCASE( case5, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case5, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case5, array_fs_db, indices, axis );

    TAKE_SUBCASE( case5, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case5, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case5, array_hs_db, indices, axis );

    TAKE_SUBCASE( case5, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case5, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case5, array_ds_db, indices, axis );

    TAKE_SUBCASE( case5, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case5, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case5, array_ls_db, indices, axis );
    #endif
}

TEST_CASE("case6" * doctest::test_suite("view::take"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TAKE_SUBCASE( case6,   array,   indices, axis );
    TAKE_SUBCASE( case6, array_a, indices_a, axis );
    TAKE_SUBCASE( case6, array_f, indices_f, axis );
    #ifndef NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case6, array_d, indices_d, axis );
    #endif // NMTOOLS_DISABLE_STL
    TAKE_SUBCASE( case6, array_h, indices_h, axis );

    #else
    TAKE_SUBCASE( case6, array_cs_fb, indices, axis );
    TAKE_SUBCASE( case6, array_cs_hb, indices, axis );
    TAKE_SUBCASE( case6, array_cs_db, indices, axis );

    TAKE_SUBCASE( case6, array_fs_fb, indices, axis );
    TAKE_SUBCASE( case6, array_fs_hb, indices, axis );
    TAKE_SUBCASE( case6, array_fs_db, indices, axis );

    TAKE_SUBCASE( case6, array_hs_fb, indices, axis );
    TAKE_SUBCASE( case6, array_hs_hb, indices, axis );
    TAKE_SUBCASE( case6, array_hs_db, indices, axis );

    TAKE_SUBCASE( case6, array_ds_fb, indices, axis );
    TAKE_SUBCASE( case6, array_ds_hb, indices, axis );
    TAKE_SUBCASE( case6, array_ds_db, indices, axis );

    TAKE_SUBCASE( case6, array_ls_fb, indices, axis );
    TAKE_SUBCASE( case6, array_ls_hb, indices, axis );
    TAKE_SUBCASE( case6, array_ls_db, indices, axis );
    #endif
}