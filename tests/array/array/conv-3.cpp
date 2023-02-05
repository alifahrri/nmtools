#define NMTOOLS_CAST_ARRAYS_NESTED_VEC(...)

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

#include "nmtools/array/array/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_conv2d_impl(...) \
nmtools::array::conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs conv2d fn to callable lambda
#define RUN_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::conv2d-") + #case_name; \
    auto name  = nmtools::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_conv2d_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_conv2d(case_name, ...) \
RUN_conv2d_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CONV2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, conv2d, case_name); \
    using namespace args; \
    auto result = RUN_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

#ifndef NMTOOLS_TESTING_CONSTEXPR

TEST_CASE("conv2d(case9)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case9, input, weight, None, stride );
    CONV2D_SUBCASE( case9, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case9, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case9, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case9, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case9, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case9, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case9, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

TEST_CASE("conv2d(case10)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case10, input, weight, None, stride );
    CONV2D_SUBCASE( case10, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case10, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case10, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case10, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case10, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case10, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case10, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

TEST_CASE("conv2d(case11)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case11, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case11, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case11, input_h, weight_h, None, stride_h, padding_h );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case11, input_d, weight_d, None, stride_v, padding_v );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case11, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ls_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ls_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ls_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ls_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ls_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ls_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_cs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_cs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_fs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_fs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_hs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_hs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case11, input_ds_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case11, input_ds_db, weight_ls_db, None, stride_a, padding_a );
    #endif
}

TEST_CASE("conv2d(case12)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case12, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case12, input_a, weight_a, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_f, weight_f, None, stride_f, padding_f );
    CONV2D_SUBCASE( case12, input_h, weight_h, None, stride_h, padding_h );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case12, input_d, weight_d, None, stride_v, padding_v );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case12, input_cs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_hs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ls_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_hs_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ls_fb, weight_cs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_cs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_cs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_hs_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ls_fb, weight_fs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_fs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_fs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ls_fb, weight_hs_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_hs_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_hs_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_hs_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ls_fb, weight_ds_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_hb, weight_ds_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ls_db, weight_ds_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_cs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_cs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_fs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_fs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_hs_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_hs_db, weight_ls_db, None, stride_a, padding_a );

    CONV2D_SUBCASE( case12, input_ds_fb, weight_ls_fb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_hb, weight_ls_hb, None, stride_a, padding_a );
    CONV2D_SUBCASE( case12, input_ds_db, weight_ls_db, None, stride_a, padding_a );
    #endif
}

#else // NMTOOLS_TESTING_CONSTEXPR

#endif