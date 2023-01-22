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

TEST_CASE("conv2d(case13)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case13, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case13, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case13, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case13, input_h, weight_h, None, stride, padding );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case13, input_d, weight_d, None, stride, padding );
    #endif // NMTOOLS_DISABLE_STL
    #endif
}

TEST_CASE("conv2d(case14)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case14, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case14, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case14, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case14, input_h, weight_h, None, stride, padding );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case14, input_d, weight_d, None, stride, padding );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case14, input_cs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_hs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ls_fb, weight_ls_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_hb, weight_ls_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_db, weight_ls_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_hs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ls_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_hs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ls_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ls_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_hs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ls_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ls_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_cs_fb, weight_ls_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_hb, weight_ls_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_cs_db, weight_ls_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_fs_fb, weight_ls_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_hb, weight_ls_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_fs_db, weight_ls_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_hs_fb, weight_ls_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_hb, weight_ls_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_hs_db, weight_ls_db, None, stride, padding );

    CONV2D_SUBCASE( case14, input_ds_fb, weight_ls_fb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_hb, weight_ls_hb, None, stride, padding );
    CONV2D_SUBCASE( case14, input_ds_db, weight_ls_db, None, stride, padding );
    #endif
}

TEST_CASE("conv2d(case15)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case15, input, weight, None, stride, padding );
    CONV2D_SUBCASE( case15, input_a, weight_a, None, stride, padding );
    CONV2D_SUBCASE( case15, input_f, weight_f, None, stride, padding );
    CONV2D_SUBCASE( case15, input_h, weight_h, None, stride, padding );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case15, input_d, weight_d, None, stride, padding );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case15, input_cs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_hs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_hs_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_cs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_cs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_cs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_hs_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_fs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_fs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_fs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_ds_fb, weight_hs_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_hb, weight_hs_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_ds_db, weight_hs_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_cs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_cs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_fs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_fs_db, weight_ds_db, None, stride, padding );

    CONV2D_SUBCASE( case15, input_hs_fb, weight_ds_fb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_hb, weight_ds_hb, None, stride, padding );
    CONV2D_SUBCASE( case15, input_hs_db, weight_ds_db, None, stride, padding );
    #endif
}

TEST_CASE("conv2d(case16)" * doctest::test_suite("array::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case16, input, weight, bias, stride, padding );
    CONV2D_SUBCASE( case16, input_a, weight_a, bias_a, stride, padding );
    CONV2D_SUBCASE( case16, input_f, weight_f, bias_f, stride, padding );
    CONV2D_SUBCASE( case16, input_h, weight_h, bias_h, stride, padding );
    #ifndef NMTOOLS_DISABLE_STL
    CONV2D_SUBCASE( case16, input_d, weight_d, bias_d, stride, padding );
    #endif // NMTOOLS_DISABLE_STL

    #else
    CONV2D_SUBCASE( case16, input_cs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_hs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ls_fb, weight_ls_fb, bias_ls_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_hb, weight_ls_hb, bias_ls_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_db, weight_ls_db, bias_ls_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_hs_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ls_fb, weight_cs_fb, bias_cs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_hb, weight_cs_hb, bias_cs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_db, weight_cs_db, bias_cs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_hs_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_fs_fb, bias_fs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_fs_hb, bias_fs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_fs_db, bias_fs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ls_fb, weight_hs_fb, bias_hs_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_hb, weight_hs_hb, bias_hs_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_db, weight_hs_db, bias_hs_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_hs_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ls_fb, weight_ds_fb, bias_ds_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_hb, weight_ds_hb, bias_ds_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ls_db, weight_ds_db, bias_ds_db, stride, padding );

    CONV2D_SUBCASE( case16, input_cs_fb, weight_ls_fb, bias_ls_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_hb, weight_ls_hb, bias_ls_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_cs_db, weight_ls_db, bias_ls_db, stride, padding );

    CONV2D_SUBCASE( case16, input_fs_fb, weight_ls_fb, bias_ls_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_hb, weight_ls_hb, bias_ls_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_fs_db, weight_ls_db, bias_ls_db, stride, padding );

    CONV2D_SUBCASE( case16, input_hs_fb, weight_ls_fb, bias_ls_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_hb, weight_ls_hb, bias_ls_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_hs_db, weight_ls_db, bias_ls_db, stride, padding );

    CONV2D_SUBCASE( case16, input_ds_fb, weight_ls_fb, bias_ls_fb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_hb, weight_ls_hb, bias_ls_hb, stride, padding );
    CONV2D_SUBCASE( case16, input_ds_db, weight_ls_db, bias_ls_db, stride, padding );
    #endif
}