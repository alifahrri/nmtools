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

#include "nmtools/array/view/conv.hpp"
#include "nmtools/testing/data/array/conv.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_conv2d_impl(...) \
nmtools::view::conv2d(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nmtools::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs conv2d fn to callable lambda
#define RUN_conv2d(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::conv2d-") + #case_name; \
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
    NMTOOLS_TESTING_USE_CASE(array, conv2d, case_name); \
    using namespace args; \
    auto result = RUN_conv2d(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

using nmtools::None;

TEST_CASE("conv2d(case5)" * doctest::test_suite("view::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case5, input, weight, None, stride );
    CONV2D_SUBCASE( case5, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case5, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case5, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case5, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case5, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case5, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case5, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

TEST_CASE("conv2d(case6)" * doctest::test_suite("view::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case6, input, weight, None, stride );
    CONV2D_SUBCASE( case6, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case6, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case6, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case6, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case6, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case6, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case6, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

TEST_CASE("conv2d(case7)" * doctest::test_suite("view::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case7, input, weight, None, stride );
    CONV2D_SUBCASE( case7, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case7, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case7, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case7, input_d, weight_d, None, stride_v );

    #else
    CONV2D_SUBCASE( case7, input_cs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_hs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ls_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_hs_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ls_fb, weight_cs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_hb, weight_cs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_db, weight_cs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_hs_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ls_fb, weight_fs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_hb, weight_fs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_db, weight_fs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ls_fb, weight_hs_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_hb, weight_hs_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_db, weight_hs_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_hs_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ls_fb, weight_ds_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_hb, weight_ds_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ls_db, weight_ds_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_cs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_cs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_fs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_fs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_hs_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_hs_db, weight_ls_db, None, stride_a );

    CONV2D_SUBCASE( case7, input_ds_fb, weight_ls_fb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_hb, weight_ls_hb, None, stride_a );
    CONV2D_SUBCASE( case7, input_ds_db, weight_ls_db, None, stride_a );
    #endif
}

TEST_CASE("conv2d(case8)" * doctest::test_suite("view::conv2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONV2D_SUBCASE( case8, input, weight, None, stride );
    CONV2D_SUBCASE( case8, input_a, weight_a, None, stride_a );
    CONV2D_SUBCASE( case8, input_f, weight_f, None, stride_f );
    CONV2D_SUBCASE( case8, input_h, weight_h, None, stride_h );
    CONV2D_SUBCASE( case8, input_d, weight_d, None, stride_v );
    #endif
}